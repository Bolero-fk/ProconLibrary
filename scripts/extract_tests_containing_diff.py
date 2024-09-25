import os
import subprocess
import re
import sys
import networkx as nx

def find_all_cpp_hpp_files(root_dir, exclude_dirs):
    """Find all .cpp and .hpp files in the root directory recursively."""
    if exclude_dirs is None:
        exclude_dirs = []

    cpp_hpp_files = []
    for root, _, files in os.walk(root_dir):
        if any(exclude_dir in root for exclude_dir in exclude_dirs):
            continue

        for file in files:
            if not file.endswith('.cpp') and not file.endswith('.hpp'):
                continue

            full_path = os.path.join(root, file)
            relative_path = os.path.relpath(full_path, root_dir)
            cpp_hpp_files.append(relative_path)

    return cpp_hpp_files

def build_dependency_graph(files):
    """Build a directed graph based on #include dependencies."""
    include_pattern = re.compile(r'#\s*include\s*"(.+?\.hpp)"')
    graph = nx.DiGraph()

    # Add nodes and edges to the graph
    for file in files:
        graph.add_node(file)  # Each file is a node
        if not file.endswith('.cpp') and not file.endswith('.hpp'):
            continue
        with open(file, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
            includes = include_pattern.findall(content)
            for included_file in includes:
                if os.path.exists(included_file):
                    graph.add_edge(included_file, file)  # Create an edge from included_file to file

    return graph

def get_diff_files(commit_sha):
    """Get list of files with differences from a specified commit."""
    result = subprocess.run(['git', 'diff', '--name-only', commit_sha], capture_output=True, text=True)
    diff_files = result.stdout.splitlines()
    return [file for file in diff_files if file.endswith('.cpp') or file.endswith('.hpp')]

def extract_test_files_from_graph(graph, diff_files):
    """Extract all files that are affected by the diff_files using the dependency graph."""
    affected_files = set()

    for diff_file in diff_files:
        if not diff_file in graph:
            continue
        # Get all nodes that have a path from the changed file
        descendants = nx.descendants(graph, diff_file)
        affected_files.update(descendants)
        affected_files.add(diff_file)  # Include the diff_file itself

    # Return only the test files (.cpp files)
    return [file for file in affected_files if file.endswith('.cpp')]

def main():
    if len(sys.argv) != 2:
        print("Usage: python extract_changed_tests.py <COMMIT_SHA>")
        sys.exit(1)
    commit_sha = sys.argv[1]

    root_dir = "."  # Root directory to start searching for files

    exclude_dirs = ["ac-library", ".verify-helper"]

    # Step 1: Find all .cpp and .hpp files
    cpp_hpp_files = find_all_cpp_hpp_files(root_dir, exclude_dirs)

    # Step 2: Build the dependency graph
    dependency_graph = build_dependency_graph(cpp_hpp_files)

    # Step 3: Get diff files from the given commit
    diff_files = get_diff_files(commit_sha)

    # Step 4: Extract test files that need to be tested
    test_files = extract_test_files_from_graph(dependency_graph, diff_files)

    # Output the results
    print(' '.join(test_files))

if __name__ == "__main__":
    main()