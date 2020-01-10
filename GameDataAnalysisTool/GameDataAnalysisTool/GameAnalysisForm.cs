using System;
using System.Data;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace GameDataAnalysisTool
{
    public partial class GameAnalysisForm : Form
    {
        public GameAnalysisForm()
        {
            InitializeComponent();
        }


        // Open a dialogue file menu for the user to choose a database. Once selected, it is loaded into the controls
        private void OpenDatabase_Click(object sender, EventArgs e)
        {
            using (var selectFileDialog = openFileDialog)
            {
                if (selectFileDialog.ShowDialog() == DialogResult.OK)
                {
                    string fileName = selectFileDialog.FileName;
                    System.IO.FileInfo fInfo = new System.IO.FileInfo(selectFileDialog.FileName);

                    string path = fInfo.FullName;
                    databaseLabel.Text = "Database: " + fInfo.Name;
                    DatabaseReader.connectionString = "Data Source =" + path;

                    DataTable dataTable = DatabaseReader.GetAllTableData("player_stats");

                    if(dataTable != null)
                    {
                        SetDataViewTable(dataTable);
                        SetBarGraph(dataTable);
                    }
                }
            }
        }

        // Sets the database table shown in the DataGridView to dataTable
        private void SetDataViewTable(DataTable dataTable)
        {

            dataTable = DatabaseReader.GetAllTableData("player_stats");
            databaseTableView.DataSource = dataTable;
            totalSessionsLabel.Text = "Number of play sessions: " + dataTable.Rows.Count.ToString();
        }

        // Sets the bar chart to show the data in the datatable.
        // The xAxis is the column names, the yAxis is the average of all the values in each column
        private void SetBarGraph(DataTable dataTable)
        {
            dataBarChart.Series[0].LegendText = "Player Action Stats";
            dataBarChart.Series[0].ChartType = SeriesChartType.Column;
            //dataBarChart.Series[0].IsValueShownAsLabel = true;

            foreach (DataColumn col in dataTable.Columns)
            {
                string colName = col.ColumnName;
                
                // Get the average using sum and count for the column
                var sum = Convert.ToSingle(dataTable.Compute("SUM([" + colName + "])", ""));
                var count = Convert.ToSingle(dataTable.Compute("COUNT(["+ colName + "])", ""));
                var avg = sum / count;


                // If no data is in the table
                if (count <= 0)
                {
                    totalSessionsLabel.Text = "Total play sessions: 0";
                    break;
                }

                // This column won't be in the bar chart
                if(colName.Equals("num_respawn"))
                {
                    numRespawnLabel.Text = "Average umber of times the player was tranquilized and respawned: " + avg;
                    continue;
                }

                // This column won't be in the bar chart
                if (colName.Equals("game_session_id"))
                {
                    totalSessionsLabel.Text = "Total play sessions: " + count;
                    continue;
                }

                dataBarChart.Series[0].Points.AddXY(colName, avg);
            }
        }
    }
}
