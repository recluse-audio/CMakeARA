import os
import sys
import subprocess


#########################
## Create file in Source directory
#########################
def create_file_with_name(filename):
    # Create the file path using the current working directory
    file_path = os.path.join(os.getcwd(), filename)
    
    # Create any missing directories in the path
    directory, _ = os.path.split(file_path)
    if not os.path.exists(directory):
        os.makedirs(directory)

    # Create the new file
    open(file_path, 'a').close()

if __name__ == '__main__':
    # Get the file name from the command line arguments
    if len(sys.argv) < 2:
        print('Usage: python addFile.py <filename>')
        sys.exit(1)
    filename = sys.argv[1]

    # Create the new file
    create_file_with_name(filename)



# Call another Python script as a new process
subprocess.run(['python', 'regenSource.py', 'arg1', 'arg2'])


subprocess.run(['./genXcode.sh', 'arg1', 'arg2'])