import os

def generate_source_files_list(root_folder, output_file):
    source_files_list = []
    for folder, subfolders, files in os.walk(root_folder):
        for filename in files:
            if filename.endswith('.cpp') or filename.endswith('.h'):
                source_files_list.append(os.path.join(folder, filename))
    source_files_list.sort()
    output = 'set(SourceFiles\n    {}\n)'.format('\n    '.join(source_files_list))
    with open(output_file, 'w') as f:
        f.write(output)

root_folder = 'Source'
output_file = 'cmake/SourceFiles.cmake'
generate_source_files_list(root_folder, output_file)
