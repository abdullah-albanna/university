using RustyOptions;
using System.Runtime.InteropServices;
using ReaLTaiizor.Controls;
using System.Diagnostics;
using System.DirectoryServices;
using System.Collections;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using Krypton.Toolkit;

namespace Simple_OpeniTools
{

    public partial class MainForm : Form
    {

        private readonly DeviceState _deviceState = new DeviceState();
        private IDeviceProvider? _deviceProvider = null;
        private IDeviceFFI.ProgressCallback? _progressCb;
        private readonly System.Windows.Forms.Timer _eventTimer = new();

        [DllImport("kernel32.dll")]
        static extern bool AllocConsole();

        public MainForm()
        {
            AllocConsole();
            InitializeComponent();

            var icons = new ImageList();
            icons.Images.Add("folder", Image.FromFile(@"C:\Users\abdullah\Pictures\closed_folder.png"));
            icons.Images.Add("folder_open", Image.FromFile(@"C:\Users\abdullah\Pictures\opened_folder.png"));
            icons.Images.Add("file", Image.FromFile(@"C:\Users\abdullah\Pictures\file.png"));


            var root = new CrownTreeNode("/");
            root.Nodes.Add(new CrownTreeNode("Loading..."));

            root.NodeExpanded += (object? sender, EventArgs e) =>
            {
                TreeViewBeforeExpand(root);
            };

            FileExplorerTree.Nodes.Add(root);

            _deviceState.onInfoChanged += (Dictionary<string, string> info) =>
            {
                InfoPanel.Controls.Clear();

                foreach (var kv in info)
                {
                    var key = kv.Key;
                    var value = kv.Value;

                    var label = new Label
                    {
                        Text = $"{key}: {value}",
                        AutoSize = true,
                        ForeColor = Color.White,
                        Font = new Font("Segoe UI", 14, FontStyle.Regular),
                        Margin = new Padding(0, 0, 0, 14)
                    };
                    var separator = new ReaLTaiizor.Controls.Separator();

                    InfoPanel.Controls.Add(label);
                    InfoPanel.Controls.Add(separator);

                }

            };
            IDeviceFFI.start_device_watcher();

            _eventTimer.Interval = 1000;
            _eventTimer.Tick += (_, __) =>
            {
                if (IDeviceFFI.poll_event(out int ev))
                {
                    this.OnDeviceEventChange((EventKind)ev);
                }
            };
            _eventTimer.Start();

        }

        public IDeviceProvider? TryGetProvider()
        {
            var provider = IDeviceProvider.create();

            if (provider.IsOk(out var value))
            {
                return provider.Unwrap();
            }
            else
            {
                string errorMsg = provider.UnwrapErr();

                var result = MessageBox.Show(errorMsg, "error getting the provider", MessageBoxButtons.RetryCancel, MessageBoxIcon.Error);

                if (result == DialogResult.Retry)
                {
                    return this.TryGetProvider();
                }
            }

            return null;

        }


        public void OnDeviceEventChange(EventKind e)
        {
            if (this.IsDisposed)
                return;

            if (this.InvokeRequired)
            {
                this.BeginInvoke(new Action(() =>
                {
                    this.HandleDeviceEvent(e);
                }));
            }
            else
            {
                this.HandleDeviceEvent(e);
            }
        }


        public void HandleDeviceEvent(EventKind e)
        {
            if (e == EventKind.Connected)
            {
                var provider = this.TryGetProvider();

                if (provider == null)
                {
                    MessageBox.Show("Failed to get the provider", "getting the provider", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                this._deviceProvider = provider;

                this.FillDeviceInfo();

            }
            else
            {
                this._deviceProvider?.Dispose();
                this._deviceProvider = null;
            }

        }

        public void FillDeviceInfo()
        {
            if (this._deviceProvider == null)
            {
                return;
            }

            var device_info_result = IDeviceFFI.get_device_info(this._deviceProvider.Provider);

            if (Utils.IsNull(device_info_result.ok))
            {
                string errorMsg = IDeviceFFI.ReadAndFreeString(device_info_result.err);
                MessageBox.Show($"Failed to get the battery info: {errorMsg}", "get battery info", MessageBoxButtons.OK, MessageBoxIcon.Error); ;
                return;
            }

            string device_info_string = IDeviceFFI.ReadAndFreeString(device_info_result.ok);
            var device_info_dict = IDeviceFFI.JsonStringToDict(device_info_string);

            _deviceState.info = device_info_dict;
        }



        private void TreeViewBeforeExpand(CrownTreeNode node)
        {
            Console.WriteLine($"called {node.Text}");

            if (node.Nodes.Count == 1 && node.Nodes[0].Text == "Loading...")
            {
                node.Nodes.Clear();

                string path = node.FullPath.Replace("\\", "/");
                Console.WriteLine($"Full path: {path}");
                if (string.IsNullOrEmpty(path))
                    return;

                try
                {
                    IntPtr pathPtr = Marshal.StringToHGlobalAnsi(path);
                    IntPtr fstreePtr = IDeviceFFI.list_path_ffi(pathPtr, _deviceProvider.Provider);
                    Marshal.FreeHGlobal(pathPtr);

                    if (fstreePtr == IntPtr.Zero)
                        return;

                    FSTree rootStruct = Marshal.PtrToStructure<FSTree>(fstreePtr);

                    if (rootStruct.children != IntPtr.Zero && rootStruct.children_count > 0)
                    {
                        for (int i = 0; i < (int)rootStruct.children_count; i++)
                        {
                            IntPtr childPtr = Marshal.ReadIntPtr(rootStruct.children, i * IntPtr.Size);
                            FSTree childStruct = Marshal.PtrToStructure<FSTree>(childPtr);

                            string childPath = Marshal.PtrToStringAnsi(childStruct.path);
                            bool isDirectory = childStruct.info.file_type == FileType.Directory;

                            var childNode = new CrownTreeNode(childPath);
                            childNode.NodeExpanded += (object? sender, EventArgs e) => { TreeViewBeforeExpand(childNode); };

                            if (isDirectory)
                                childNode.Nodes.Add(new CrownTreeNode("Loading..."));

                            node.Nodes.Add(childNode);
                            node.Expanded = true;
                        }
                    }

                    IDeviceFFI.free_fstree(fstreePtr);
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Failed to list AFC path: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }


        private void Form1_Load(object sender, EventArgs e)
        {

        }



        private void FileExplorerTree_AfterNodeExpand(object sender, EventArgs e)
        {
        }

        private void FileExplorerTree_DoubleClick(object sender, EventArgs e)
        {

        }

        private void FileExplorerTree_SelectedNodesChanged(object sender, EventArgs e)
        {

        }

        private void DownloadButton_Click(object sender, EventArgs e)
        {

            var to_be_copied = FileExplorerTree.SelectedNodes[0].FullPath.Replace("\\", "/");
            var to_be_copied_ptr = Marshal.StringToHGlobalAnsi(to_be_copied);
            var dialog = new SaveFileDialog
            {
                Title = "Save downloaded file",
                FileName = "file.bin",
                Filter = "All files (*.*)|*.*"
            };

            if (!dialog.ShowDialog().Equals(DialogResult.OK))
                return;

            _progressCb = OnProgress;

            GC.KeepAlive(_progressCb);

            var dialog_filename_ptr = Marshal.StringToHGlobalAnsi(dialog.FileName);

            Console.WriteLine(to_be_copied);
            Console.WriteLine(dialog.FileName);
            progressbar.Visible = true;

            Task.Run(() =>
            {

                IDeviceFFI.download_a_file(
                   to_be_copied_ptr,
                   dialog_filename_ptr,
                   _deviceProvider.Provider,
                   _progressCb
               );
            });
        }

        private void OnProgress(byte percentage)
        {
            Console.WriteLine($"Progress: {percentage}");
            progressbar.Value = percentage;

            if (progressbar.Value == 100)
            {
                progressbar.Value = 0;

                progressbar.Visible = false;
            }
        }
    }

}