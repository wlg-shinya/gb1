using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;

class Launcher {
    static void Main() {
        string targetExe = "sameboy.exe";
        string targetRom = Config.AppName + ".gb";

        // 一時フォルダ作成
        string tempPath = Path.Combine(Path.GetTempPath(), Config.AppName + "_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(tempPath);

        try {
            // 埋め込みリソースをディレクトリかファイルかを判断して展開
            Assembly assembly = Assembly.GetExecutingAssembly();
            foreach (string resourceName in assembly.GetManifestResourceNames()) {
                string relativePath = resourceName.Replace("__", Path.DirectorySeparatorChar.ToString());
                string destPath = Path.Combine(tempPath, relativePath);
                string dirName = Path.GetDirectoryName(destPath);
                if (!string.IsNullOrEmpty(dirName) && !Directory.Exists(dirName)) {
                    Directory.CreateDirectory(dirName);
                }
                using (Stream stream = assembly.GetManifestResourceStream(resourceName)) {
                    if (stream == null) continue;
                    using (FileStream fileStream = new FileStream(destPath, FileMode.Create)) {
                        stream.CopyTo(fileStream);
                    }
                }
            }

            // 起動
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = Path.Combine(tempPath, targetExe);
            startInfo.Arguments = "\"" + targetRom + "\" " + Config.SameboyArg;
            startInfo.WorkingDirectory = tempPath;
            startInfo.UseShellExecute = false;
            startInfo.CreateNoWindow = true;
            using (Process proc = Process.Start(startInfo)) {
                proc.WaitForExit();
            }

        } catch (Exception e) {
            System.Windows.Forms.MessageBox.Show("Error (" + Config.AppName + "):\n" + e.Message);
        } finally {
            try {
                if (Directory.Exists(tempPath)) Directory.Delete(tempPath, true);
            } catch { }
        }
    }
}