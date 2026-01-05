using Krypton.Toolkit;

namespace Simple_OpeniTools
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            MainNavbar = new ReaLTaiizor.Controls.ForeverTabPage();
            deviceinfoPage = new TabPage();
            InfoPanel = new FlowLayoutPanel();
            deviceFileExplrerPage = new TabPage();
            ToolsGroupBox = new ReaLTaiizor.Controls.CrownGroupBox();
            progressbar = new ReaLTaiizor.Controls.CircleProgressBar();
            DownloadButton = new ReaLTaiizor.Controls.CrownButton();
            FileExplorerTree = new ReaLTaiizor.Controls.CrownTreeView();
            MainNavbar.SuspendLayout();
            deviceinfoPage.SuspendLayout();
            deviceFileExplrerPage.SuspendLayout();
            ToolsGroupBox.SuspendLayout();
            SuspendLayout();
            // 
            // MainNavbar
            // 
            resources.ApplyResources(MainNavbar, "MainNavbar");
            MainNavbar.ActiveColor = Color.FromArgb(35, 168, 109);
            MainNavbar.ActiveFontColor = Color.White;
            MainNavbar.BaseColor = Color.FromArgb(45, 47, 49);
            MainNavbar.BGColor = Color.FromArgb(60, 70, 73);
            MainNavbar.Controls.Add(deviceinfoPage);
            MainNavbar.Controls.Add(deviceFileExplrerPage);
            MainNavbar.DeactiveFontColor = Color.White;
            MainNavbar.Multiline = true;
            MainNavbar.Name = "MainNavbar";
            MainNavbar.SelectedIndex = 0;
            MainNavbar.SizeMode = TabSizeMode.Fixed;
            // 
            // deviceinfoPage
            // 
            resources.ApplyResources(deviceinfoPage, "deviceinfoPage");
            deviceinfoPage.BackColor = Color.FromArgb(60, 70, 73);
            deviceinfoPage.Controls.Add(InfoPanel);
            deviceinfoPage.Name = "deviceinfoPage";
            // 
            // InfoPanel
            // 
            resources.ApplyResources(InfoPanel, "InfoPanel");
            InfoPanel.Name = "InfoPanel";
            // 
            // deviceFileExplrerPage
            // 
            resources.ApplyResources(deviceFileExplrerPage, "deviceFileExplrerPage");
            deviceFileExplrerPage.BackColor = Color.FromArgb(60, 70, 73);
            deviceFileExplrerPage.Controls.Add(ToolsGroupBox);
            deviceFileExplrerPage.Controls.Add(FileExplorerTree);
            deviceFileExplrerPage.Name = "deviceFileExplrerPage";
            // 
            // ToolsGroupBox
            // 
            resources.ApplyResources(ToolsGroupBox, "ToolsGroupBox");
            ToolsGroupBox.BorderColor = Color.FromArgb(51, 51, 51);
            ToolsGroupBox.Controls.Add(progressbar);
            ToolsGroupBox.Controls.Add(DownloadButton);
            ToolsGroupBox.Name = "ToolsGroupBox";
            ToolsGroupBox.TabStop = false;
            // 
            // progressbar
            // 
            resources.ApplyResources(progressbar, "progressbar");
            progressbar.BackColor = Color.FromArgb(60, 70, 73);
            progressbar.Maximum = 100L;
            progressbar.Name = "progressbar";
            progressbar.PercentColor = Color.White;
            progressbar.ProgressColor1 = Color.FromArgb(92, 92, 92);
            progressbar.ProgressColor2 = Color.FromArgb(92, 92, 92);
            progressbar.ProgressShape = ReaLTaiizor.Controls.CircleProgressBar._ProgressShape.Round;
            progressbar.Value = 0L;
            // 
            // DownloadButton
            // 
            resources.ApplyResources(DownloadButton, "DownloadButton");
            DownloadButton.Name = "DownloadButton";
            DownloadButton.Click += DownloadButton_Click;
            // 
            // FileExplorerTree
            // 
            resources.ApplyResources(FileExplorerTree, "FileExplorerTree");
            FileExplorerTree.MaxDragChange = 20;
            FileExplorerTree.Name = "FileExplorerTree";
            FileExplorerTree.ShowIcons = true;
            FileExplorerTree.SelectedNodesChanged += FileExplorerTree_SelectedNodesChanged;
            FileExplorerTree.AfterNodeExpand += FileExplorerTree_AfterNodeExpand;
            FileExplorerTree.DoubleClick += FileExplorerTree_DoubleClick;
            // 
            // MainForm
            // 
            resources.ApplyResources(this, "$this");
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = SystemColors.Desktop;
            Controls.Add(MainNavbar);
            Name = "MainForm";
            Load += Form1_Load;
            MainNavbar.ResumeLayout(false);
            deviceinfoPage.ResumeLayout(false);
            deviceFileExplrerPage.ResumeLayout(false);
            ToolsGroupBox.ResumeLayout(false);
            ResumeLayout(false);
        }

        #endregion

        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private ReaLTaiizor.Controls.ForeverTabPage MainNavbar;
        private TabPage deviceinfoPage;
        private TabPage deviceFileExplrerPage;
        private ReaLTaiizor.Controls.ForeverTabPage foreverTabPage1;
        private TabPage tabPage2;
        private TabPage tabPage1;
        private FlowLayoutPanel InfoPanel;
        private ReaLTaiizor.Controls.CrownTreeView FileExplorerTree;
        private ReaLTaiizor.Controls.CrownGroupBox ToolsGroupBox;
        private ReaLTaiizor.Controls.CrownButton DownloadButton;
        private ReaLTaiizor.Controls.CircleProgressBar progressbar;
    }
}