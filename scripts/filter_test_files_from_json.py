import json
import sys

def update_previous_json(json_path, include_files_list):
    # previous.jsonを読み込む
    with open(json_path, 'r') as file:
        previous_data = json.load(file)

    # INCLUDE_FILES_LISTに含まれるファイルを除外
    updated_files = {k: v for k, v in previous_data['files'].items() if k not in include_files_list}

    # 更新したデータを保存
    previous_data['files'] = updated_files
    with open(json_path, 'w') as file:
        json.dump(previous_data, file, indent=2)

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
