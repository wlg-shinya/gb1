using System;
using System.Diagnostics;
using System.IO;

class Launcher {
    static void Main() {
        // 起動したいファイル名（同じフォルダにあること）
        string emulator = "sameboy.exe";
        string rom = "gb1.gb";
        
        // 起動コマンドの引数（ROMファイルパスなど）
        // SameBoyがフルスクリーン起動をサポートしているなら --fullscreen などをつけてもOK
        string arguments = rom; 

        // 実行ファイルが存在するかチェック
        if (!File.Exists(emulator)) {
            // エラー表示（Windows標準機能を利用）
            System.Windows.Forms.MessageBox.Show(
                emulator + " が見つかりません。", 
                "Error", 
                System.Windows.Forms.MessageBoxButtons.OK, 
                System.Windows.Forms.MessageBoxIcon.Error
            );
            return;
        }

        // プロセス起動設定
        ProcessStartInfo startInfo = new ProcessStartInfo();
        startInfo.FileName = emulator;
        startInfo.Arguments = arguments;
        startInfo.UseShellExecute = false; // 独自ウィンドウを出さない
        startInfo.CreateNoWindow = true;   // コンソール画面を出さない（重要）

        try {
            Process.Start(startInfo);
        } catch (Exception e) {
            System.Windows.Forms.MessageBox.Show("起動に失敗しました:\n" + e.Message);
        }
    }
}