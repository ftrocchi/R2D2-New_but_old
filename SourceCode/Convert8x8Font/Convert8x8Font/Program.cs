using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Convert8x8Font
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] lines = File.ReadAllLines(@"C:\Users\Frank\Desktop\Sinclair_S.txt");
            List<string> outputLines = new List<string>();

            foreach (string line in lines)
            {

                List<string> rows = new List<string>();

                for (int i = 0; i < 8; i++)
                    rows.Add(Convert.ToString(Convert.ToInt32(line.Substring(i * 2, 2), 16), 2).PadLeft(8, '0'));

                // convert here
                List<string> final = new List<string>();
                for (int col = 0; col < 8; col++)
                {
                    string temp = "B";
                    for (int row = 7; row >=0; row--)
                    {
                        temp += rows[row].Substring(col, 1);
                    }
                    final.Add(temp);
                }

                // build the output line here
                StringBuilder outputline = new StringBuilder();
                outputline.Append("case '");
                outputline.Append(line.Substring(line.Length - 1));
                outputline.Append("' :");

                foreach (string fin in final)
                {
                    outputline.Append(" FeedGridLeft(");
                    outputline.Append(fin);
                    outputline.Append(");");
                }
                outputline.Append(" break;");

                outputLines.Add(outputline.ToString());
            }

            // save it
            File.WriteAllLines(@"C:\Users\Frank\Desktop\8x8.txt", outputLines);

            Console.WriteLine("ALL DONE");
            Console.ReadLine();
        }
    }
}
