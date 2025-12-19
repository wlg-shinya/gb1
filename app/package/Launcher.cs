using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;

class Launcher {
    static void Main() {
        // ■ 設定：起動するファイル名
        string targetExe = "sameboy.exe";
        string targetRom = "gb1.gb";
        
        // ■ 設定：フォルダ扱いする接頭辞
        string shaderPrefix = "Shaders."; 

        // 一時フォルダ作成
        string tempPath = Path.Combine(Path.GetTempPath(), "gb1_" + Guid.NewGuid().ToString("N"));
        Directory.CreateDirectory(tempPath);

        try {
            Assembly assembly = Assembly.GetExecutingAssembly();
            
            // ★重要：埋め込まれている全リソースをループで処理
            foreach (string resourceName in assembly.GetManifestResourceNames()) {
                string fileName = resourceName;
                string outputDir = tempPath;

                // "Shaders." で始まるリソースなら、Shadersフォルダの中に配置する
                if (resourceName.StartsWith(shaderPrefix)) {
                    // "Shaders.Nearest.fsh" -> "Nearest.fsh"
                    fileName = resourceName.Substring(shaderPrefix.Length);
                    outputDir = Path.Combine(tempPath, "Shaders");
                    // フォルダがなければ作る
                    if (!Directory.Exists(outputDir)) {
                        Directory.CreateDirectory(outputDir);
                    }
                }

                // ファイル書き出し
                using (Stream stream = assembly.GetManifestResourceStream(resourceName)) {
                    if (stream == null) continue; // 読み込めないものはスキップ
                    string destPath = Path.Combine(outputDir, fileName);
                    using (FileStream fileStream = new FileStream(destPath, FileMode.Create)) {
                        stream.CopyTo(fileStream);
                    }
                }
            }

            // 起動設定
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = Path.Combine(tempPath, targetExe);
            startInfo.Arguments = "\"" + targetRom + "\" --fullscreen";
            startInfo.WorkingDirectory = tempPath;
            startInfo.UseShellExecute = false;
            startInfo.CreateNoWindow = true;

            using (Process proc = Process.Start(startInfo)) {
                proc.WaitForExit();
            }

        } catch (Exception e) {
            System.Windows.Forms.MessageBox.Show("Error:\n" + e.Message);
        } finally {
            // お掃除
            try {
                if (Directory.Exists(tempPath)) Directory.Delete(tempPath, true);
            } catch { }
        }
    }
}