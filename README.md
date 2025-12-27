# GB1

## 動作環境

- Windows
- Mac

## 外部ツールやライブラリ

| 名称&リンク                                         | 概要                                 | OS      | バージョン |
| --------------------------------------------------- | ------------------------------------ | ------- | ---------- |
| [GBDK-2020](https://github.com/gbdk-2020/gbdk-2020) | GB 開発キット                        | Win,Mac | 4.4.0      |
| [SameBoy](https://github.com/LIJI32/SameBoy)        | 開発および製品同梱用 GB エミュレータ | Win,Mac | 1.0.2      |
| [BGB](https://bgb.bircd.org/)                       | 開発用 GB エミュレータ               | Win     | 1.6.6      |

# スタートアップ(Mac)

1. make を利用可能にします
   - ターミナルを開き make --version と入力します
     - GNU Make ~ と表示されたら OK です
     - Command Line Tools for Xcode のインストールが案内されたらそれに従ってください
2. clean_build_run.command を実行できるようにする
   - ターミナルで[]内を適切に書き換えて以下のコマンドを実行してください
   ```
   chmod -x [gb1をインストールしたディレクトリパス]/app/clean_build_run.command
   ```
