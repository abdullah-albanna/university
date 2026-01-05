using System.Runtime.InteropServices;
using System.Text.Json;

[StructLayout(LayoutKind.Sequential)]
public struct RustResult
{
    public IntPtr ok;
    public IntPtr err;
}


public enum EventKind { Connected = 0, Disconnected = 1 }

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void EventCallback(EventKind ev);

public static class IDeviceFFI
{

    [DllImport("idevice_lib.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern RustResult get_provider();

    [DllImport("idevice_lib.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void free_provider(IntPtr provider);

    [DllImport("idevice_lib.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void free_c_string(IntPtr s);

    [DllImport("idevice_lib.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void start_device_watcher();

    [DllImport("idevice_lib.dll", CallingConvention = CallingConvention.Cdecl)]
    [return: MarshalAs(UnmanagedType.I1)]
    public static extern bool poll_event(out int ev);

    [DllImport("idevice_lib.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern RustResult get_battery_info(IntPtr provider);

    [DllImport("idevice_lib.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern RustResult get_storage_info(IntPtr provider);

    [DllImport("idevice_lib.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern RustResult get_hardware_info(IntPtr provider);

    [DllImport("idevice_lib.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern RustResult get_os_info(IntPtr provider);


    [DllImport("idevice_lib.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr list_path_ffi(IntPtr path, IntPtr provider);

    [DllImport("idevice_lib.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void free_fstree(IntPtr tree);


    [DllImport("idevice_lib.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern RustResult get_device_info(IntPtr provider);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void ProgressCallback(byte progress);

    [DllImport("idevice_lib.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void download_a_file(
        IntPtr path,
        IntPtr dest,
        IntPtr provider,
        ProgressCallback callback
    );

    public static Dictionary<string, string> JsonStringToDict(string json)
    {
        return JsonSerializer.Deserialize<Dictionary<string, string>>(json);

    }

    public static string ReadAndFreeString(IntPtr ptr)
    {
        if (ptr == IntPtr.Zero)
            return null;

        var s = Marshal.PtrToStringAnsi(ptr);
        free_c_string(ptr);
        return s!;
    }
}
