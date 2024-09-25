import json
import sys
import os

def update_previous_json(json_path, include_files_list):
    # ファイルの存在とサイズを確認
    if not os.path.exists(json_path):
        print(f"Error: JSON file {json_path} does not exist.")
        sys.exit(1)

    if os.path.getsize(json_path) == 0:
        print(f"Error: JSON file {json_path} is empty.")
        sys.exit(1)

    # previous.jsonを読み込む
    with open(json_path, 'r') as file:
        try:
            previous_data = json.load(file)
        except json.JSONDecodeError as e:
            print(f"Error decoding JSON: {e}")
            sys.exit(1)

    # previous.jsonを読み込む
    with open(json_path, 'r') as file:
        previous_data = json.load(file)

    # INCLUDE_FILES_LISTに含まれるファイルを除外
    updated_files = {k: v for k, v in previous_data['files'].items() if k not in include_files_list}

    # 更新したデータを保存
    previous_data['files'] = updated_files

    # 結果の確認
    print(json.dumps(previous_data, indent=2))

def main():
    if len(sys.argv) != 3:
        print("Usage: python script.py <previous_json_path> <include_files_list>")
        sys.exit(1)

    json_path = sys.argv[1]
    include_files_list = sys.argv[2].split()  # 空白区切りの文字列をリストに変換
    update_previous_json(json_path, include_files_list)

if __name__ == "__main__":
    main()
