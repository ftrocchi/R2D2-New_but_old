using System;
using System.Collections.Generic;
using System.IO;

namespace I2C_Sync
{
    class Program
    {
        const string sourcePath = @"C:\Users\Frank\Documents\Arduino";
        const string destinationPath = @"C:\Users\Frank\Documents\GitHub\R2D2";

        static void Main()
        {
            if (AreFilesTheSame())
            {
                Console.WriteLine("Copying...");
                CopyFilesToGitHub();
            }
            else
            {
                Console.WriteLine("Files are not the same!!!");
                Console.WriteLine("Files are not the same!!!");
                Console.WriteLine("Files are not the same!!!");
            }

            Console.WriteLine("ALL DONE!");
            Console.ReadLine();
        }

        private static bool AreFilesTheSame()
        {
            List<string> checkSums = new List<string>();

            string[] files = Directory.GetFiles(sourcePath, "I2C_Common.h", SearchOption.AllDirectories);

            foreach (string file in files)
                checkSums.Add(GetFileChecksum(file));

            var matchingChecksum = checkSums[0];

            foreach (var checkSum in checkSums)
                if (checkSum != matchingChecksum)
                    return false;

            return true;
        }

        private static string GetFileChecksum(string file)
        {
            Console.WriteLine("Checking file: " + file);
            using (System.Security.Cryptography.MD5 md5 = System.Security.Cryptography.MD5.Create())
                return BitConverter.ToString(md5.ComputeHash(File.ReadAllBytes(file))).Replace("-", string.Empty);
        }

        private static void CopyFilesToGitHub()
        {

            foreach (var dirPath in Directory.GetDirectories(sourcePath, "*", SearchOption.AllDirectories))
            {
                var finalPath = dirPath.Replace(sourcePath, destinationPath);

                if (!Directory.Exists(finalPath))
                    Directory.CreateDirectory(finalPath);
            }

            foreach (var newPath in Directory.GetFiles(sourcePath, "*", SearchOption.AllDirectories))
                File.Copy(newPath, newPath.Replace(sourcePath, destinationPath), true);
        }
    }
}
