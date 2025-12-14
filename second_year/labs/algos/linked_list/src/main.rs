use std::fmt::{Debug, Display};

use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
enum Major {
    Cyber,
    IT,
}

impl Display for Major {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{self:?}")
    }
}

#[derive(Serialize, Deserialize, Debug, Clone)]
struct Student {
    id: u32,

    name: String,
    major: Major,
}

impl Display for Student {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "(ID: {}, Name: {}, Major: {})",
            self.id, self.name, self.major
        )
    }
}

impl Student {
    pub fn new(id: u32, name: String, major: Major) -> Self {
        Self { id, name, major }
    }
}

#[derive(Debug)]
struct Node<T: Display> {
    data: T,
    next: *mut Node<T>,
}

impl<T: Display> Display for Node<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        if self.next.is_null() {
            write!(f, "{} -| ", self.data)
        } else {
            write!(f, "{} -> ", self.data)
        }
    }
}

impl<T: Display> Node<T> {
    pub fn new(data: T) -> Self {
        Self {
            data,
            next: std::ptr::null_mut(),
        }
    }
}

struct LinkedList<T: Display> {
    head: *mut Node<T>,
    tail: *mut Node<T>,
}

impl<T: Display> LinkedList<T> {
    pub fn new() -> Self {
        Self {
            head: std::ptr::null_mut(),
            tail: std::ptr::null_mut(),
        }
    }

    pub fn append(&mut self, data: T) {
        let new_node = Box::into_raw(Box::new(Node::new(data)));

        if self.head.is_null() {
            self.head = new_node;
            self.tail = new_node;
        } else {
            unsafe {
                (*self.tail).next = new_node;
            }
            self.tail = new_node;
        }
    }

    pub fn prepend(&mut self, data: T) {
        let new_node = Box::into_raw(Box::new(Node::new(data)));

        unsafe {
            (*new_node).next = self.head;
        }
        self.head = new_node;

        if !self.tail.is_null() {
            self.tail = new_node;
        }
    }

    pub fn insert_at(&mut self, idx: usize, data: T) {
        if idx == 0 {
            self.prepend(data);
            return;
        }

        let new_node = Box::into_raw(Box::new(Node::new(data)));

        let mut current = self.head;

        for _ in 0..(idx - 1) {
            if current.is_null() {
                panic!("idx is out of bound");
            }
            unsafe {
                current = (*current).next;
            }
        }

        unsafe {
            (*new_node).next = (*current).next;
            (*current).next = new_node;
        }
    }
}

impl<T: Clone + Display + Serialize + for<'a> Deserialize<'a>> LinkedList<T> {
    fn to_vec(&self) -> Vec<T> {
        let mut out = Vec::new();
        let mut current = self.head;

        unsafe {
            while !current.is_null() {
                out.push((*current).data.clone());
                current = (*current).next;
            }
        }

        out
    }

    fn from_vec(vec: Vec<T>) -> Self {
        let mut list = LinkedList::new();

        for item in vec {
            list.append(item);
        }

        list
    }

    pub fn to_file(&self, file_name: &str) {
        let file = std::fs::File::options()
            .create(true)
            .truncate(true)
            .write(true)
            .open(file_name)
            .unwrap();

        serde_json::to_writer_pretty(file, &self.to_vec());
    }

    pub fn from_file(file_name: &str) -> Self {
        let file_data = std::fs::read(file_name).unwrap();

        let data: Vec<T> = serde_json::from_slice(&file_data).unwrap();

        LinkedList::from_vec(data)
    }
}

impl<T: Display> Display for LinkedList<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let mut current = self.head;

        while !current.is_null() {
            unsafe {
                let node = &*current;
                write!(f, "{node}")?;
                current = (*current).next
            }
        }

        Ok(())
    }
}

impl<T: Display> Drop for LinkedList<T> {
    fn drop(&mut self) {
        let mut current = self.head;

        while !current.is_null() {
            unsafe {
                let next = (*current).next;
                drop(Box::from_raw(current));
                current = next;
            }
        }
    }
}

fn main() {
    let mut linked_list = LinkedList::new();

    linked_list.append(Student::new(2, "Qasm".to_string(), Major::IT));
    linked_list.append(Student::new(3, "Mohmmed".to_string(), Major::Cyber));
    linked_list.prepend(Student::new(1, "Abdullah".to_string(), Major::Cyber));
    linked_list.insert_at(2, Student::new(4, "Mohmmed".to_string(), Major::Cyber));

    linked_list.to_file("students.json");

    println!("{linked_list}");

    let linked_list_from_file = LinkedList::<Student>::from_file("students.json");

    println!("from file: {linked_list_from_file}");
}
