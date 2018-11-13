# I/O Performance: File sort

This project is implemented to fulfill my SW Eng course's Individual Project.
The goal of the project is to map and model the effects on the CPU and I/O perfo
rmance of a program under various situations. The system provides two C++ progra
ms: one to create the input files and the other that will be modelled. The input
files contain a variable number of lines, variable number of integer values per
line, and modifiable min/max integer values to be pseudo-randomly generated. Th-
ese files will be read by the other and each line sorted; using stable-sort. Th-
ese lines are then written into a new file with -sorted appended to the original
file's name.

## Building system:
> Included with the system is a Makefile
 - make: compiles create_new_files.cpp and sort_integer_files.cpp to create
         executables for user to use: create_files and sort_file
         
 - make run: compiles aforementioned .cpp files into executables and runs 
             them using the default command-line arguments.
             
 - make clean: clears the working directory of generated files
     
###### ** This README expects that you are in the directory where files will be stored **
## Creating new input files:
> Input files can be created by calling the create_files executable generated
> using the Makefile with/without command line arguments.
 
### Usage: 
  **./create_files** file_name nbr_files nbr_lines nbr_values min_value max_value
 
 Command-Line Arguments, if present, are **position locked** and all arguments prior
 to any desired to be omitted __*must*__ be stated:
 1. file_name - desired base name for any files created 
                  [may be omitted without affecting position-lock system]
                  {default='file'}
 2. nbr_files - desired number of files to be created
                  {default=3}
 3. nbr_lines - desired number of lines for the initial file created
                  [each consecutive file receives an monotonically increasing 
                   multiple of the initial argument
                   i.e: 
                        the second file will have 2*nbr_lines created
                        third file will have 3*nbr_lines created]
                  {default=100}
 4. nbr_values - desired number of values per line for the initial file created
                  [each consecutive file receives an monotonically increasing 
                   multiple of the initial argument
                   i.e: 
                        the second file will have 2*nbr_values per line created
                        third file will have 3*nbr_values per line created]
                  {default=100}
 5. min_value - desired minimum integer value to be generated
                  {default=1}
 6. max_value - desired maximum integer value to be generated
                  {default=100}



## Sorting Files:
### Usage:
  **./sort_file** file_name
  
 Command-Line Arguments, if present, are **position locked** and all arguments prior
 to any desired to be omitted __*must*__ be stated:
 1. file_name - desired base name for any files created 
                  [may be omitted without affecting position-lock system]
                  {default='file0'}
