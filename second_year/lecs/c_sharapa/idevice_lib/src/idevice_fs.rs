use std::{ffi::CString, path::Path, ptr};

use idevice::{
    IdeviceService,
    afc::{AfcClient, FileInfo},
    provider::UsbmuxdProvider,
};

use std::os::raw::c_char;

#[repr(C)]
pub struct FSTreeFFI {
    pub path: *mut c_char,
    pub info: PathInfoFFI,
    pub children: *mut *mut FSTreeFFI,
    pub children_count: usize,
}

#[repr(C)]
pub struct PathInfoFFI {
    pub size: usize,
    pub blocks: usize,
    pub nlink: *mut c_char,
    pub creation: i64,
    pub modified: i64,
    pub file_type: FileTypeFFI,
}

#[repr(C)]
pub enum FileTypeFFI {
    Directory = 0,
    File,
    Symlink,
    CharDevice,
    BlockDevice,
    NamedPipe,
    Socket,
    Unknown,
}

pub fn convert_to_ffi(tree: FSTree) -> *mut FSTreeFFI {
    let path = CString::new(tree.path).unwrap();
    let nlink = CString::new(tree.info.nlink).unwrap();

    // allocate children
    let mut children_ptrs: Vec<*mut FSTreeFFI> = Vec::new();
    for child in tree.children {
        children_ptrs.push(convert_to_ffi(child));
    }
    let children_ptrs_len = children_ptrs.len();

    let children_ptr = if children_ptrs.is_empty() {
        ptr::null_mut()
    } else {
        let boxed = children_ptrs.into_boxed_slice();
        Box::into_raw(boxed) as *mut *mut FSTreeFFI
    };

    let node = FSTreeFFI {
        path: path.into_raw(),
        info: PathInfoFFI {
            size: tree.info.size,
            blocks: tree.info.blocks,
            nlink: nlink.into_raw(),
            creation: tree.info.creation.timestamp(),
            modified: tree.info.modified.timestamp(),
            file_type: match tree.info.file_type {
                FileType::Directory => FileTypeFFI::Directory,
                FileType::File => FileTypeFFI::File,
                FileType::Symlink => FileTypeFFI::Symlink,
                FileType::CharDevice => FileTypeFFI::CharDevice,
                FileType::BlockDevice => FileTypeFFI::BlockDevice,
                FileType::NamedPipe => FileTypeFFI::NamedPipe,
                FileType::Socket => FileTypeFFI::Socket,
                FileType::Unknown => FileTypeFFI::Unknown,
            },
        },
        children: children_ptr,
        children_count: if children_ptr.is_null() {
            0
        } else {
            children_ptrs_len
        },
    };

    Box::into_raw(Box::new(node))
}

#[derive(Debug, Default, Clone)]
pub struct FSTree {
    pub path: String,
    pub info: PathInfo,
    pub children: Vec<FSTree>,
}

impl FSTree {
    pub fn new(path: &str) -> Self {
        Self {
            path: path.into(),
            ..Default::default()
        }
    }

    pub fn add_child(&mut self, child: FSTree) {
        self.children.push(child);
    }
}

impl From<FileInfo> for PathInfo {
    fn from(value: FileInfo) -> Self {
        Self {
            size: value.size,
            blocks: value.blocks,
            nlink: value.st_nlink,
            creation: value.creation,
            modified: value.modified,
            file_type: FileType::from(value.st_ifmt),
        }
    }
}

#[derive(Debug, Default, Clone)]
pub struct PathInfo {
    pub size: usize,
    pub blocks: usize,
    pub nlink: String,
    pub creation: chrono::NaiveDateTime,
    pub modified: chrono::NaiveDateTime,
    pub file_type: FileType,
}

impl PathInfo {
    pub fn is_dir(&self) -> bool {
        matches!(self.file_type, FileType::Directory)
    }

    pub fn is_file(&self) -> bool {
        matches!(self.file_type, FileType::File)
    }
}

#[derive(Debug, Default, Clone)]
pub enum FileType {
    Directory,
    File,
    Symlink,

    CharDevice,
    BlockDevice,
    NamedPipe,
    Socket,

    #[default]
    Unknown,
}

impl From<String> for FileType {
    fn from(value: String) -> Self {
        match value.as_str() {
            "S_IFDIR" => Self::Directory,
            "S_IFREG" => Self::File,
            "S_IFLNK" => Self::Symlink,

            "S_IFCHR" => Self::CharDevice,
            "S_IFBLK" => Self::BlockDevice,
            "S_IFIFO" => Self::NamedPipe,
            "S_IFSOCK" => Self::Socket,

            _ => Self::Unknown,
        }
    }
}

impl std::fmt::Display for FileType {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::File => write!(f, "file"),
            Self::Directory => write!(f, "directory"),
            Self::Symlink => write!(f, "symlink"),

            Self::CharDevice => write!(f, "character device"),
            Self::BlockDevice => write!(f, "block device"),
            Self::NamedPipe => write!(f, "named pipe(fifo)"),
            Self::Socket => write!(f, "socket"),
            Self::Unknown => write!(f, "unknown"),
        }
    }
}

pub async fn list_path(path: String, provider: &UsbmuxdProvider) -> FSTree {
    let mut afc = AfcClient::connect(provider).await.unwrap();

    let afc_path_info: PathInfo = afc.get_file_info(&path).await.unwrap().into();

    let mut node = FSTree::new(&path);
    let is_dir = afc_path_info.is_dir();
    node.info = afc_path_info;

    if is_dir {
        let path_dirs = afc
            .list_dir(&path)
            .await
            .unwrap()
            .into_iter()
            .filter(|s| s.as_str() != "." && s.as_str() != "..")
            .collect::<Vec<_>>();

        for dir in path_dirs {
            let inner_node_info = afc.get_file_info(&format!("{path}/{dir}")).await.unwrap();

            let mut inner_node = FSTree::new(&dir);
            inner_node.info = inner_node_info.into();

            node.add_child(inner_node);
        }
    }

    node
}
