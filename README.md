# Open Linux Course
**What is in the repository?**
- **lecture**  Handbook - Lecture materials are designed in Markdown format with pictures. Also, some files for practical work are saved there.
- **lms-export-course** - file archives for export course to LMS. At the moment there is a file for exporting to Canvas.
- **presentation** catalog - presentation files for lectures in pdf and pptx format
- **task-checker** - source code for utilities for checking practical tasks. Written in C language.
- **virtual-machine-ssh** directory is the files needed to create the virtual machine, which are needed for the ssh related job. The virtual machine is built using a Vagrant file.
- **webuihelper** directory is the source code for a helper web application written in Python using the Django framework.

**What is the course program?**

1. Introduction. Comparison of Windows and Linux Basic introductory concepts: OS, OS kernel, license, distribution. Task: installing Ubuntu on a virtual machine
2. Linux distributions Description of popular distributions and their differences
3. Command shell Introduction to the use of the terminal, basic commands for working with files, searching, archiving. Working with history. The concept of internal and external commands. Task: a test and a zero task aimed at getting acquainted with task_checker
4. Working with files in Linux. Part 1. File extraction, special paths and standard directories. Detailed study of commands for working with files. Task: a task from task_checker - creating a hierarchy of directories and files
5. Working with files in Linux. Part 2 Link extraction, file editing in Vim and Nano, commands for searching text files, access rights. Task: two tasks - "Archiving, text filtering and regular expressions" and "Access rights and links"
6. Process Understanding of the process, process tree, procfs, commands for working with processes, priorities of processes. Task: a task for processes tied to the launches of the sleep program 
7. Advanced features of pipelines, return code, combining commands, redirecting input and output streams, commands often used in pipelines, substitutions, operators, functions. Tasks: 4 tasks for writing bash scripts - output of computer information, calculating the sum of arithmetic progression, node search, using positional parameters
8. Administration The concept of a user and its properties, package management, system services, using SSH and creating tunnels. Task: installing packages, connecting via ssh, copying and reading files from a remote host, running scripts on a remote host, creating SSH tunnels
