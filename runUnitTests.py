#!/usr/bin/python3

import argparse
import os
import subprocess
import sys

def main():
    parser = argparse.ArgumentParser(description='Build project and run unit tests.')
    parser.add_argument('-w', '--wibu', action='store_true', help='Enable WIBU.')
    parser.add_argument('--skip-export', action='store_true', help='Skip the Create build directory and Build with cmake steps.')
    args = parser.parse_args()

    # Set WIBU variable
    WIBU = int(args.wibu)
    
    if sys.platform == "linux":
        build_dir = "build"
    else:
        build_dir = "build-tests"

    # CMake configuration
    if not args.skip_export: # check if already exported
        script_dir = os.path.dirname(os.path.realpath(__file__))
        config_script = os.path.join(script_dir, "runCMakeConfiguration.py")
        if subprocess.run(["python3", config_script, "--build_dir", build_dir]).returncode != 0:
            print("Error running CMake configuration")
            sys.exit(1)
        
    os.chdir(build_dir)
        
    # Build tests
    if subprocess.run(['cmake', '--build', '.', '--target', 'Tests']).returncode != 0:
        print('build failed')
        sys.exit(1)

    # Run tests
    if subprocess.run(['ctest', '--verbose']).returncode != 0:
        print('tests failed')
        sys.exit(1)

    # Return to top level directory
    os.chdir('..')

if __name__ == '__main__':
    main()

