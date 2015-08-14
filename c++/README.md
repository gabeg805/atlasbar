===========
What is it?
===========

Atlas is a status bar for your linux system that displays items such as:
    
    - Workspace
    - Date and time
    - Brightness level
    - Volume level
    - Wifi strength
    - Battery level
    - and more!

Using the API, users can easily create, add, and modify new or existing status
bar applications. Atlas was primarily built as an improvement to the DWM window
manager, which did not allow for graphical status bar items. Consequently, Atlas
accepts graphical status bar applications.

=============
Documentation
=============

The documentation for each program can be found in the header of each respective
file.

============
Installation
============

$ make
$ ./atlas

========
Contacts
========

If you have any problems, feel free to email me at 'gabeg@bu.edu'.

==================
Potential Problems
==================

- Occasionally, DWM resets and all windows move to the first workspace.

=====
To-Do
=====

- Sometimes the volume icon mistakes a mocp pid, fix this
- Check which is faster, socket or semaphore (or alternative IPC)
- Remove file opening and printing to stuff.txt
