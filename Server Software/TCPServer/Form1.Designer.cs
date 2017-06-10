namespace waterQualityServer
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea3 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend3 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea4 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend4 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series4 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea5 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend5 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series5 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.eventLog1 = new System.Diagnostics.EventLog();
            this.dataBox = new System.Windows.Forms.TextBox();
            this.startServerButton = new System.Windows.Forms.Button();
            this.portBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.addressBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.saveButton = new System.Windows.Forms.Button();
            this.setNameBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.renameButton = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.setIPBox = new System.Windows.Forms.TextBox();
            this.setIPButton = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.setPortBox = new System.Windows.Forms.TextBox();
            this.setPortButton = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.setMobileBox = new System.Windows.Forms.TextBox();
            this.setMobileButton = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.apnBox = new System.Windows.Forms.TextBox();
            this.setAPNButton = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.intervalBox = new System.Windows.Forms.TextBox();
            this.setIntervalBox = new System.Windows.Forms.Button();
            this.chartTab = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.chart2 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.chart3 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.chart4 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.tabPage5 = new System.Windows.Forms.TabPage();
            this.chart5 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label9 = new System.Windows.Forms.Label();
            this.boardSelectBox = new System.Windows.Forms.ComboBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.runningLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.eventLog1)).BeginInit();
            this.chartTab.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart2)).BeginInit();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart3)).BeginInit();
            this.tabPage4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart4)).BeginInit();
            this.tabPage5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart5)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // eventLog1
            // 
            this.eventLog1.SynchronizingObject = this;
            // 
            // dataBox
            // 
            this.dataBox.Location = new System.Drawing.Point(7, 208);
            this.dataBox.Multiline = true;
            this.dataBox.Name = "dataBox";
            this.dataBox.ReadOnly = true;
            this.dataBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.dataBox.Size = new System.Drawing.Size(777, 195);
            this.dataBox.TabIndex = 2;
            this.dataBox.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            // 
            // startServerButton
            // 
            this.startServerButton.Location = new System.Drawing.Point(706, 9);
            this.startServerButton.Name = "startServerButton";
            this.startServerButton.Size = new System.Drawing.Size(91, 23);
            this.startServerButton.TabIndex = 3;
            this.startServerButton.Text = "Start Server";
            this.startServerButton.UseVisualStyleBackColor = true;
            this.startServerButton.Click += new System.EventHandler(this.startServerButton_Click);
            // 
            // portBox
            // 
            this.portBox.Location = new System.Drawing.Point(474, 9);
            this.portBox.MaxLength = 5;
            this.portBox.Name = "portBox";
            this.portBox.Size = new System.Drawing.Size(100, 20);
            this.portBox.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(439, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Port:";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // addressBox
            // 
            this.addressBox.Location = new System.Drawing.Point(276, 9);
            this.addressBox.Name = "addressBox";
            this.addressBox.ReadOnly = true;
            this.addressBox.Size = new System.Drawing.Size(157, 20);
            this.addressBox.TabIndex = 6;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(212, 12);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(61, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "IP Address:";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // saveButton
            // 
            this.saveButton.Location = new System.Drawing.Point(23, 8);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(75, 23);
            this.saveButton.TabIndex = 9;
            this.saveButton.Text = "Save Data";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.saveButton_Click);
            // 
            // setNameBox
            // 
            this.setNameBox.Location = new System.Drawing.Point(17, 44);
            this.setNameBox.Name = "setNameBox";
            this.setNameBox.Size = new System.Drawing.Size(100, 20);
            this.setNameBox.TabIndex = 10;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(17, 25);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(69, 13);
            this.label3.TabIndex = 11;
            this.label3.Text = "Name Board:";
            // 
            // renameButton
            // 
            this.renameButton.Location = new System.Drawing.Point(17, 69);
            this.renameButton.Name = "renameButton";
            this.renameButton.Size = new System.Drawing.Size(75, 23);
            this.renameButton.TabIndex = 12;
            this.renameButton.Text = "Rename";
            this.renameButton.UseVisualStyleBackColor = true;
            this.renameButton.Click += new System.EventHandler(this.renameButton_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(144, 24);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(73, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "Set Target IP:";
            // 
            // setIPBox
            // 
            this.setIPBox.Location = new System.Drawing.Point(147, 43);
            this.setIPBox.Name = "setIPBox";
            this.setIPBox.Size = new System.Drawing.Size(117, 20);
            this.setIPBox.TabIndex = 14;
            // 
            // setIPButton
            // 
            this.setIPButton.Location = new System.Drawing.Point(147, 70);
            this.setIPButton.Name = "setIPButton";
            this.setIPButton.Size = new System.Drawing.Size(75, 23);
            this.setIPButton.TabIndex = 15;
            this.setIPButton.Text = "Set IP Address";
            this.setIPButton.UseVisualStyleBackColor = true;
            this.setIPButton.Click += new System.EventHandler(this.setIPButton_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(290, 24);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(82, 13);
            this.label5.TabIndex = 16;
            this.label5.Text = "Set Target Port:";
            // 
            // setPortBox
            // 
            this.setPortBox.Location = new System.Drawing.Point(293, 43);
            this.setPortBox.Name = "setPortBox";
            this.setPortBox.Size = new System.Drawing.Size(100, 20);
            this.setPortBox.TabIndex = 17;
            // 
            // setPortButton
            // 
            this.setPortButton.Location = new System.Drawing.Point(293, 70);
            this.setPortButton.Name = "setPortButton";
            this.setPortButton.Size = new System.Drawing.Size(75, 23);
            this.setPortButton.TabIndex = 18;
            this.setPortButton.Text = "Set Port";
            this.setPortButton.UseVisualStyleBackColor = true;
            this.setPortButton.Click += new System.EventHandler(this.setPortButton_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(411, 24);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(100, 13);
            this.label6.TabIndex = 19;
            this.label6.Text = "Set Mobile Number:";
            // 
            // setMobileBox
            // 
            this.setMobileBox.Location = new System.Drawing.Point(414, 43);
            this.setMobileBox.Name = "setMobileBox";
            this.setMobileBox.Size = new System.Drawing.Size(100, 20);
            this.setMobileBox.TabIndex = 20;
            // 
            // setMobileButton
            // 
            this.setMobileButton.Location = new System.Drawing.Point(414, 69);
            this.setMobileButton.Name = "setMobileButton";
            this.setMobileButton.Size = new System.Drawing.Size(80, 23);
            this.setMobileButton.TabIndex = 21;
            this.setMobileButton.Text = "Set Mobile";
            this.setMobileButton.UseVisualStyleBackColor = true;
            this.setMobileButton.Click += new System.EventHandler(this.setMobileButton_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(528, 24);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(51, 13);
            this.label7.TabIndex = 22;
            this.label7.Text = "Set APN:";
            // 
            // apnBox
            // 
            this.apnBox.Location = new System.Drawing.Point(531, 43);
            this.apnBox.Name = "apnBox";
            this.apnBox.Size = new System.Drawing.Size(100, 20);
            this.apnBox.TabIndex = 23;
            // 
            // setAPNButton
            // 
            this.setAPNButton.Location = new System.Drawing.Point(531, 71);
            this.setAPNButton.Name = "setAPNButton";
            this.setAPNButton.Size = new System.Drawing.Size(75, 23);
            this.setAPNButton.TabIndex = 24;
            this.setAPNButton.Text = "Set APN";
            this.setAPNButton.UseVisualStyleBackColor = true;
            this.setAPNButton.Click += new System.EventHandler(this.setAPNButton_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(648, 24);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(64, 13);
            this.label8.TabIndex = 25;
            this.label8.Text = "Set Interval:";
            // 
            // intervalBox
            // 
            this.intervalBox.Location = new System.Drawing.Point(651, 43);
            this.intervalBox.Name = "intervalBox";
            this.intervalBox.Size = new System.Drawing.Size(100, 20);
            this.intervalBox.TabIndex = 26;
            // 
            // setIntervalBox
            // 
            this.setIntervalBox.Location = new System.Drawing.Point(651, 70);
            this.setIntervalBox.Name = "setIntervalBox";
            this.setIntervalBox.Size = new System.Drawing.Size(75, 23);
            this.setIntervalBox.TabIndex = 27;
            this.setIntervalBox.Text = "Set Interval";
            this.setIntervalBox.UseVisualStyleBackColor = true;
            this.setIntervalBox.Click += new System.EventHandler(this.setIntervalBox_Click);
            // 
            // chartTab
            // 
            this.chartTab.Controls.Add(this.tabPage1);
            this.chartTab.Controls.Add(this.tabPage2);
            this.chartTab.Controls.Add(this.tabPage3);
            this.chartTab.Controls.Add(this.tabPage4);
            this.chartTab.Controls.Add(this.tabPage5);
            this.chartTab.Location = new System.Drawing.Point(7, 19);
            this.chartTab.Name = "chartTab";
            this.chartTab.SelectedIndex = 0;
            this.chartTab.Size = new System.Drawing.Size(781, 187);
            this.chartTab.TabIndex = 29;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.chart1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(773, 161);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Temperature";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // chart1
            // 
            chartArea1.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea1);
            legend1.Alignment = System.Drawing.StringAlignment.Center;
            legend1.Docking = System.Windows.Forms.DataVisualization.Charting.Docking.Bottom;
            legend1.Name = "Legend1";
            this.chart1.Legends.Add(legend1);
            this.chart1.Location = new System.Drawing.Point(0, 0);
            this.chart1.Name = "chart1";
            series1.BorderWidth = 2;
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series1.Legend = "Legend1";
            series1.Name = "Temperature";
            series1.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Time;
            this.chart1.Series.Add(series1);
            this.chart1.Size = new System.Drawing.Size(773, 161);
            this.chart1.TabIndex = 0;
            this.chart1.Text = "tempChart";
            this.chart1.Click += new System.EventHandler(this.chart1_Click_1);
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.chart2);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(773, 161);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Conductivity";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // chart2
            // 
            chartArea2.Name = "ChartArea1";
            this.chart2.ChartAreas.Add(chartArea2);
            legend2.Alignment = System.Drawing.StringAlignment.Center;
            legend2.Docking = System.Windows.Forms.DataVisualization.Charting.Docking.Bottom;
            legend2.Name = "Legend1";
            this.chart2.Legends.Add(legend2);
            this.chart2.Location = new System.Drawing.Point(0, 0);
            this.chart2.Name = "chart2";
            series2.BorderWidth = 2;
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series2.Color = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            series2.Legend = "Legend1";
            series2.Name = "Conductivity";
            series2.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Time;
            this.chart2.Series.Add(series2);
            this.chart2.Size = new System.Drawing.Size(777, 165);
            this.chart2.TabIndex = 0;
            this.chart2.Text = "conductivityChart";
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.chart3);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(773, 161);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "pH";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // chart3
            // 
            chartArea3.Name = "ChartArea1";
            this.chart3.ChartAreas.Add(chartArea3);
            legend3.Alignment = System.Drawing.StringAlignment.Center;
            legend3.Docking = System.Windows.Forms.DataVisualization.Charting.Docking.Bottom;
            legend3.Name = "Legend1";
            this.chart3.Legends.Add(legend3);
            this.chart3.Location = new System.Drawing.Point(0, 0);
            this.chart3.Name = "chart3";
            series3.BorderWidth = 2;
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series3.Color = System.Drawing.Color.OrangeRed;
            series3.Legend = "Legend1";
            series3.Name = "pH";
            series3.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Time;
            this.chart3.Series.Add(series3);
            this.chart3.Size = new System.Drawing.Size(777, 161);
            this.chart3.TabIndex = 0;
            this.chart3.Text = "chart3";
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.chart4);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(773, 161);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "Depth";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // chart4
            // 
            chartArea4.Name = "ChartArea1";
            this.chart4.ChartAreas.Add(chartArea4);
            legend4.Alignment = System.Drawing.StringAlignment.Center;
            legend4.Docking = System.Windows.Forms.DataVisualization.Charting.Docking.Bottom;
            legend4.Name = "Legend1";
            this.chart4.Legends.Add(legend4);
            this.chart4.Location = new System.Drawing.Point(0, 0);
            this.chart4.Name = "chart4";
            series4.BorderWidth = 2;
            series4.ChartArea = "ChartArea1";
            series4.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series4.Color = System.Drawing.Color.DarkCyan;
            series4.Legend = "Legend1";
            series4.Name = "Depth";
            series4.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Time;
            this.chart4.Series.Add(series4);
            this.chart4.Size = new System.Drawing.Size(777, 161);
            this.chart4.TabIndex = 0;
            this.chart4.Text = "chart4";
            // 
            // tabPage5
            // 
            this.tabPage5.Controls.Add(this.chart5);
            this.tabPage5.Location = new System.Drawing.Point(4, 22);
            this.tabPage5.Name = "tabPage5";
            this.tabPage5.Size = new System.Drawing.Size(773, 161);
            this.tabPage5.TabIndex = 4;
            this.tabPage5.Text = "Battery";
            this.tabPage5.UseVisualStyleBackColor = true;
            // 
            // chart5
            // 
            chartArea5.Name = "ChartArea1";
            this.chart5.ChartAreas.Add(chartArea5);
            legend5.Alignment = System.Drawing.StringAlignment.Center;
            legend5.Docking = System.Windows.Forms.DataVisualization.Charting.Docking.Bottom;
            legend5.Name = "Legend1";
            this.chart5.Legends.Add(legend5);
            this.chart5.Location = new System.Drawing.Point(0, 0);
            this.chart5.Name = "chart5";
            series5.BorderWidth = 2;
            series5.ChartArea = "ChartArea1";
            series5.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.StepLine;
            series5.Color = System.Drawing.Color.Gold;
            series5.Legend = "Legend1";
            series5.Name = "Battery";
            series5.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Time;
            this.chart5.Series.Add(series5);
            this.chart5.Size = new System.Drawing.Size(777, 161);
            this.chart5.TabIndex = 0;
            this.chart5.Text = "chart5";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.boardSelectBox);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.setNameBox);
            this.groupBox1.Controls.Add(this.setIntervalBox);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.intervalBox);
            this.groupBox1.Controls.Add(this.renameButton);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.setAPNButton);
            this.groupBox1.Controls.Add(this.setIPBox);
            this.groupBox1.Controls.Add(this.apnBox);
            this.groupBox1.Controls.Add(this.setIPButton);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.setMobileButton);
            this.groupBox1.Controls.Add(this.setPortBox);
            this.groupBox1.Controls.Add(this.setMobileBox);
            this.groupBox1.Controls.Add(this.setPortButton);
            this.groupBox1.Location = new System.Drawing.Point(9, 38);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(798, 134);
            this.groupBox1.TabIndex = 30;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Program Board";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(70, 102);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(71, 13);
            this.label9.TabIndex = 29;
            this.label9.Text = "Select Board:";
            this.label9.Click += new System.EventHandler(this.label9_Click);
            // 
            // boardSelectBox
            // 
            this.boardSelectBox.FormattingEnabled = true;
            this.boardSelectBox.Location = new System.Drawing.Point(147, 99);
            this.boardSelectBox.Name = "boardSelectBox";
            this.boardSelectBox.Size = new System.Drawing.Size(192, 21);
            this.boardSelectBox.TabIndex = 28;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.chartTab);
            this.groupBox2.Controls.Add(this.dataBox);
            this.groupBox2.Location = new System.Drawing.Point(9, 178);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(798, 409);
            this.groupBox2.TabIndex = 31;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Received Data";
            // 
            // runningLabel
            // 
            this.runningLabel.AutoSize = true;
            this.runningLabel.Location = new System.Drawing.Point(589, 12);
            this.runningLabel.Name = "runningLabel";
            this.runningLabel.Size = new System.Drawing.Size(83, 13);
            this.runningLabel.TabIndex = 32;
            this.runningLabel.Text = "Status: Stopped";
            this.runningLabel.Click += new System.EventHandler(this.runningLabel_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(817, 599);
            this.Controls.Add(this.runningLabel);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.addressBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.portBox);
            this.Controls.Add(this.startServerButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "Water Quality Sensor Server";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.eventLog1)).EndInit();
            this.chartTab.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            this.tabPage2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chart2)).EndInit();
            this.tabPage3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chart3)).EndInit();
            this.tabPage4.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chart4)).EndInit();
            this.tabPage5.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chart5)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Diagnostics.EventLog eventLog1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox portBox;
        private System.Windows.Forms.Button startServerButton;
        private System.Windows.Forms.TextBox dataBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox addressBox;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button setIPButton;
        private System.Windows.Forms.TextBox setIPBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button renameButton;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox setNameBox;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button setIntervalBox;
        private System.Windows.Forms.TextBox intervalBox;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button setAPNButton;
        private System.Windows.Forms.TextBox apnBox;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button setMobileButton;
        private System.Windows.Forms.TextBox setMobileBox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button setPortButton;
        private System.Windows.Forms.TextBox setPortBox;
        private System.Windows.Forms.TabControl chartTab;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.TabPage tabPage5;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart3;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart4;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart5;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.ComboBox boardSelectBox;
        private System.Windows.Forms.Label runningLabel;
    }
}

