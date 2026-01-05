using System;
using System.Runtime.InteropServices;

[StructLayout(LayoutKind.Sequential)]
public struct PathInfo
{
    public ulong size;
    public ulong blocks;
    public IntPtr nlink;
    public long creation;
    public long modified;
    public FileType file_type;
}

[StructLayout(LayoutKind.Sequential)]
public struct FSTree
{
    public IntPtr path;
    public PathInfo info;
    public IntPtr children; // FSTree**
    public ulong children_count;
}

public enum FileType
{
    Directory,
    File,
    Symlink,
    CharDevice,
    BlockDevice,
    NamedPipe,
    Socket,
    Unknown
}

public class IDeviceAFC
{

    void ReadTree(IntPtr treePtr)
    {
        var tree = Marshal.PtrToStructure<FSTree>(treePtr);
        string path = Marshal.PtrToStringAnsi(tree.path);

        if (tree.children != IntPtr.Zero)
        {
            for (int i = 0; i < (int)tree.children_count; i++)
            {
                IntPtr childPtr = Marshal.ReadIntPtr(tree.children, (int)(i * IntPtr.Size));
                ReadTree(childPtr);
            }
        }
    }
}