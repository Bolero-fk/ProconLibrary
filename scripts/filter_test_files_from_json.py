import json
import sys
import os

def update_previous_json(json_path, include_files_list):
    with open(json_path, 'r') as file:
        previous_data = json.load(file)

    updated_files = {k: v for k, v in previous_data['files'].items() if k not in include_files_list}

    previous_data['files'] = updated_files

    print(json.dumps(previous_data, indent=2))

def main():
    if len(sys.argv) != 3:
        print("Usage: python script.py <previous_json_path> <include_files_list>")
        sys.exit(1)

    json_path = sys.argv[1]
    include_files_list = sys.argv[2].split()
    update_previous_json(json_path, include_files_list)

if __name__ == "__main__":
    main()
