# Lecterm
### A terminal document editor inspired by Evernote
---------------------------------------

This is a TUI application designed to edit and organize text files. In many ways, it's an awful reimagining of a terminal file manager, and a piss-poor excuse for a local-machine-bound Evernote rip off. But that's entirely the point. It's a program designed by me, for my own use in writing, and to sharpen my skills in programming.

The interface layout is primarily inspired by the layout of Evernote, with two columns/panes/windows dedicated to Notebooks and their Notes, and a third larger window where the currently selected note is displayed. The program will interpret the internal directories and files of a filesystem as Notebooks and Notes, respectively. Simply supply a root directory in the configuration file, and it will allow the user the traverse the tree of deeper directories and files.

---------------------------------------

## Compilation and Execution

To run Lecterm, you can run `make` to compile and execute the binary with `./lecterm`, or just use `make run`.

__This program is a work in progress, and is not meant for serious use. You have been warned.__
