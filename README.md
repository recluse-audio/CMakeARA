## CMakeARA 

This project is the simplest way I could think of to display the contents of an ARA document.  The goal would be to draw a timeline of all the active ARA instances.  Audio transformations will be minimal, just enough to demonstrate save/restore, undo/redo, and the function of the AudioModification object.

After cloning don't forget the classic `git submodule update --init --recursive` to get the juce and ARA SDK submodules.


After adding a new file you should run regenSource.py to update the SourceFiles.cmake which is important to the CmakeLists.txt

Then you can run `scripts/rebuild_all.sh` to build the vst3 / au / test objects

You need to be online for the cmakelists to work currently (to grab catch2)   -- Sorry!


Do what you want with this and leverage ARA for all the good things in the world.