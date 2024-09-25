import json
import sys

def merge_json_files(json_files):
    merged_data = {
        "total_seconds": 0,
        "files": {}
    }

    for json_file in json_files:
        with open(json_file, 'r') as f:
            data = json.load(f)

        # Accumulate total_seconds
        merged_data["total_seconds"] += data.get("total_seconds", 0)

        # Merge files
        for file_key, file_value in data.get("files", {}).items():
            if file_key not in merged_data["files"]:
                merged_data["files"][file_key] = {
                    "verifications": file_value.get("verifications", []),
                    "newest": True
                }
            else:
                # Merge verifications (overwrite duplicates with later ones)
                existing_verifications = merged_data["files"][file_key]["verifications"]
                existing_verifications.extend(file_value.get("verifications", []))
                merged_data["files"][file_key]["verifications"] = existing_verifications
                merged_data["files"][file_key]["newest"] = True

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
