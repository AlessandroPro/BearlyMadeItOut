using System;
using System.Data;
using System.Data.SQLite;
using System.Windows.Forms;

namespace GameDataAnalysisTool
{
    // A class with functions for querying the TextBasedGameAnalytics database table
    class DatabaseReader
    {
        // Default location
        public static string connectionString = "Data Source=.\\TextBasedGameAnalytics.db";

        // Returns all data from the specified table
        public static DataTable GetAllTableData(string tableName)
        {
            DataTable table = new DataTable();

            try
            {
                using (SQLiteConnection connection = new SQLiteConnection(connectionString))
                {
                    connection.Open();
                    string command = "SELECT * from " + tableName;
                    SQLiteDataAdapter adapter = new SQLiteDataAdapter(command, connection);
                    adapter.Fill(table);
                    connection.Close();
                }
            }
            catch (SQLiteException ex)
            {
                Console.WriteLine(ex.Message);
                MessageBox.Show(ex.ToString(), "Database Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return null;
            }
            return table;
        }
    }
}
