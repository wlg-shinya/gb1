#!/bin/bash
cd "$(dirname "$0")"

make clean && make

echo "------------------------------"
echo "処理が完了しました。何かキーを押すと終了します。"
read -n 1
