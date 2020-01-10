namespace GameDataAnalysisTool
{
    partial class GameAnalysisForm
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
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Title title1 = new System.Windows.Forms.DataVisualization.Charting.Title();
            this.databaseTableView = new System.Windows.Forms.DataGridView();
            this.dataBarChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.openDatabase = new System.Windows.Forms.Button();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.databaseLabel = new System.Windows.Forms.Label();
            this.totalSessionsLabel = new System.Windows.Forms.Label();
            this.numRespawnLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.databaseTableView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataBarChart)).BeginInit();
            this.SuspendLayout();
            // 
            // databaseTableView
            // 
            this.databaseTableView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.databaseTableView.Location = new System.Drawing.Point(102, 1019);
            this.databaseTableView.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.databaseTableView.Name = "databaseTableView";
            this.databaseTableView.ReadOnly = true;
            this.databaseTableView.RowHeadersWidth = 82;
            this.databaseTableView.Size = new System.Drawing.Size(1696, 498);
            this.databaseTableView.TabIndex = 0;
            // 
            // dataBarChart
            // 
            chartArea1.Name = "ChartArea1";
            this.dataBarChart.ChartAreas.Add(chartArea1);
            this.dataBarChart.Location = new System.Drawing.Point(102, 177);
            this.dataBarChart.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.dataBarChart.Name = "dataBarChart";
            series1.ChartArea = "ChartArea1";
            series1.Name = "Series1";
            this.dataBarChart.Series.Add(series1);
            this.dataBarChart.Size = new System.Drawing.Size(1696, 754);
            this.dataBarChart.TabIndex = 1;
            this.dataBarChart.Text = "chart1";
            title1.Name = "Title1";
            title1.Text = "Average Frequency Of Player Actions For All Game Sessions";
            this.dataBarChart.Titles.Add(title1);
            // 
            // openDatabase
            // 
            this.openDatabase.Location = new System.Drawing.Point(102, 38);
            this.openDatabase.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.openDatabase.Name = "openDatabase";
            this.openDatabase.Size = new System.Drawing.Size(268, 42);
            this.openDatabase.TabIndex = 2;
            this.openDatabase.Text = "Open Database";
            this.openDatabase.UseVisualStyleBackColor = true;
            this.openDatabase.Click += new System.EventHandler(this.OpenDatabase_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "openFileDialog1";
            this.openFileDialog.Filter = "Database Files (*.db) | *.db";
            // 
            // databaseLabel
            // 
            this.databaseLabel.AutoSize = true;
            this.databaseLabel.Location = new System.Drawing.Point(422, 48);
            this.databaseLabel.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.databaseLabel.Name = "databaseLabel";
            this.databaseLabel.Size = new System.Drawing.Size(116, 25);
            this.databaseLabel.TabIndex = 4;
            this.databaseLabel.Text = "Database: ";
            // 
            // totalSessionsLabel
            // 
            this.totalSessionsLabel.AutoSize = true;
            this.totalSessionsLabel.Location = new System.Drawing.Point(96, 119);
            this.totalSessionsLabel.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.totalSessionsLabel.Name = "totalSessionsLabel";
            this.totalSessionsLabel.Size = new System.Drawing.Size(0, 25);
            this.totalSessionsLabel.TabIndex = 5;
            // 
            // numRespawnLabel
            // 
            this.numRespawnLabel.AutoSize = true;
            this.numRespawnLabel.Location = new System.Drawing.Point(96, 962);
            this.numRespawnLabel.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.numRespawnLabel.Name = "numRespawnLabel";
            this.numRespawnLabel.Size = new System.Drawing.Size(0, 25);
            this.numRespawnLabel.TabIndex = 6;
            this.numRespawnLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // GameAnalysisForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1904, 1594);
            this.Controls.Add(this.numRespawnLabel);
            this.Controls.Add(this.totalSessionsLabel);
            this.Controls.Add(this.databaseLabel);
            this.Controls.Add(this.openDatabase);
            this.Controls.Add(this.dataBarChart);
            this.Controls.Add(this.databaseTableView);
            this.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.Name = "GameAnalysisForm";
            this.Text = "Text Based Game Analysis";
            ((System.ComponentModel.ISupportInitialize)(this.databaseTableView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataBarChart)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView databaseTableView;
        private System.Windows.Forms.DataVisualization.Charting.Chart dataBarChart;
        private System.Windows.Forms.Button openDatabase;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.Label databaseLabel;
        private System.Windows.Forms.Label totalSessionsLabel;
        private System.Windows.Forms.Label numRespawnLabel;
    }
}

