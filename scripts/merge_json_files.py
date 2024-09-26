import json
import sys

def merge_json_files(json_files):
    merged_data = {
        "files": {}
    }

    for json_file in json_files:
        with open(json_file, 'r') as f:
            data = json.load(f)

        # Merge files
        for file_key, file_value in data.get("files", {}).items():
            merged_data["files"][file_key] = file_value

    return merged_data

def main():
    if len(sys.argv) < 2:
        print("Usage: python merge_json.py <json_file1> <json_file2> ...")
        sys.exit(1)

    json_files = sys.argv[1:]

    merged_data = merge_json_files(json_files)

    # Print the merged result as JSON
    print(json.dumps(merged_data, indent=2))

if __name__ == "__main__":
    main()
