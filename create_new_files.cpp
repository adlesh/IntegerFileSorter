/*
 *  Program that creates files containing lines of randomly generated integers
 *  Argument Order is strict and follows: ./prog_name BASE_FILE_NAME NBR_FILES NBR_LINES NBR_VALUES MIN_VALUE MAX_VALUE
 *   Latter arguments may be excluded from invocation, however, the program does
 *   NOT attempt to reorder them if missing...i.e.
 *     ./prog file 5 6 7 creates 5 files named 'file#.txt' 6 lines/file 7 values/line with default MIN_VALUE and MAX_VALUE
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdexcept>

using namespace std;

// different, default attributes of the file to be created
// will be extended to take command-line arguments
int min_line_value = 100;
int max_line_value = 1000;
int nbr_values_per_line = 10;
int nbr_lines_per_file = 100; 
int nbr_files_to_create = 3;

string file_name = "file";

enum Exceptions {no_exc = 0, inv_arg_exc, out_of_range_exc};

const int numerical_arg_start_ndx = 2;

int parse_command_arguments(int argc, char* argv[])
{
	int ret_val = no_exc;
	// if there were additional commands entered
	if (argc > 0)
	{
		int diff = -1;
		// try to parse each command into an integer
		for (int arg_ndx = 1; arg_ndx < argc; ++arg_ndx)
		{
			
			// default error value for parsed argv[arg_ndx], arg
			int arg = -1;
			// attempt to parse the current argument
			try 
			{
				arg = stoi(argv[arg_ndx]);
				if (diff == -1)
					diff = numerical_arg_start_ndx - arg_ndx;
			}
			// handle an non-integer argument
			catch (const invalid_argument& ia)
			{
				if (arg_ndx > 0)
				{
					int was_arg = false;
					// check if it's actually an argument
					switch (arg_ndx)
					{
						case char_arg_start_ndx:
							file_name = argv[arg_ndx];
							was_arg = true;
							break;
					}
					if (!was_arg)
						cout << arg_ndx << " Invalid Argument, " << ia.what() << ", was entered.\n";
					ret_val = (was_arg) ? no_exc : inv_arg_exc;
				}
			}
			// handle integer range error
			catch (const out_of_range& oor)
			{
				cout << "Input, "<< oor.what()<<", was outside of integer value range.\n";
				return out_of_range_exc;
			}
			// if parsing was successful
			if (arg != -1)
			{
				//handle the parsed argument
				switch (arg_ndx+diff)
				{
					case numerical_arg_start_ndx:
						nbr_files_to_create = arg;
						break;
					case numerical_arg_start_ndx+1:
						nbr_lines_per_file = arg;
						break;
					case numerical_arg_start_ndx+2:
						nbr_values_per_line = arg;
						break;
					case numerical_arg_start_ndx+3:
						min_line_value = arg;
						break;
					case numerical_arg_start_ndx+4:
						max_line_value = arg;
						break;
				}
			}
		}
	}
	
	return ret_val;
}

int main (int argc, char* argv[]) {  
  int args_parsed = parse_command_arguments(argc, argv);
  if (args_parsed == no_exc)
  {
	  // seed the random number generator with a call to current epoch time
	  srand((unsigned) time(NULL));
	  
	  // repeat the generator for the desired number of files
	  for (int file_no = 0; file_no < nbr_files_to_create; ++file_no)
	  {
	  	  // create the file's name
	  	  stringstream filename;
	  	  filename << file_name << file_no << ".txt";
	  	  
	  	  int multiplier = file_no+1;
	  	  // create the stream for writing to the new file
		  ofstream myfile (filename.str());
		  
		  // if it was created/opened correctly,
		  if (myfile.is_open())
		  {
		  	
		    // generate the desired number of lines 
		    int curr_nbr_lines = 0;
		    
		    while (curr_nbr_lines < multiplier * nbr_lines_per_file)
		    {
		        // generate nbr_values_per_line random numbers
			    int curr_nbr_values = 0;
			    while (curr_nbr_values < multiplier * nbr_values_per_line)
			    {
			    	int value = (rand()%(max_line_value-min_line_value))+min_line_value;
			    	(curr_nbr_values < multiplier * nbr_values_per_line - 1) ?
			    	    myfile << value << " " : myfile << value;
			    	++curr_nbr_values;
			    }
			    (curr_nbr_lines != multiplier * nbr_lines_per_file-1) ?
			        myfile << endl : myfile << "";
			    ++curr_nbr_lines;
			   
		    }
		    myfile.close();
		  }
		  else cout << "Unable to open file";
	  }
  }
  return 0;
}
