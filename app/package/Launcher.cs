using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;

class Launcher {
    static void Main() {
        string targetExe = "sameboy.exe";
        string targetRom = Config.AppName + ".gb";
        
        // ■ 設定：フォルダ扱いする接頭辞
        string shaderPrefix = "Shaders."; 

        // 一時フォルダ作成
        string tempPath = Path.Combine(Path.GetTempPath(), Config.AppName + "_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(tempPath);

        try {
            Assembly assembly = Assembly.GetExecutingAssembly();
            
            foreach (string resourceName in assembly.GetManifestResourceNames()) {
                string fileName = resourceName;
                string outputDir = tempPath;

                // シェーダーフォルダの処理
                if (resourceName.StartsWith(shaderPrefix)) {
                    fileName = resourceName.Substring(shaderPrefix.Length);
                    outputDir = Path.Combine(tempPath, "Shaders");
                    if (!Directory.Exists(outputDir)) {
                        Directory.CreateDirectory(outputDir);
                    }
                }

                // ファイル書き出し
                using (Stream stream = assembly.GetManifestResourceStream(resourceName)) {
                    if (stream == null) continue;
                    string destPath = Path.Combine(outputDir, fileName);
                    using (FileStream fileStream = new FileStream(destPath, FileMode.Create)) {
                        stream.CopyTo(fileStream);
                    }
                }
            }

            // 起動設定
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = Path.Combine(tempPath, targetExe);
            // ROMファイル名にスペースが含まれても大丈夫なように引用符で囲む
            startInfo.Arguments = "\"" + targetRom + "\" " + Config.SameboyArg;
            startInfo.WorkingDirectory = tempPath;
            startInfo.UseShellExecute = false;
            startInfo.CreateNoWindow = true;

            using (Process proc = Process.Start(startInfo)) {
                proc.WaitForExit();
            }

        } catch (Exception e) {
            // エラー時もアプリ名を表示
            System.Windows.Forms.MessageBox.Show("Error (" + Config.AppName + "):\n" + e.Message);
        } finally {
            try {
                if (Directory.Exists(tempPath)) Directory.Delete(tempPath, true);
            } catch { }
        }
    }
}