// writing on a text file
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdexcept>

using namespace std;

// different attributes of the file to be created
// will be extended to take command-line arguments
int min_line_value = 100;
int max_line_value = 1000;
int nbr_values_per_line = 10;
int nbr_lines_per_file = 100; 
int nbr_files_to_create = 3;

enum Exceptions {inv_arg_exc = 1, out_of_range_exc};

int parseCommandArguments(int argc, char* argv[])
{
	if (argc > 1)
	{
		for (int arg_ndx = 1; arg_ndx < argc; ++arg_ndx)
		{
			int arg = -1;
			try 
			{
				arg = stoi(argv[arg_ndx]);
			}
			catch (const invalid_argument& ia)
			{
				cout << "Invalid Argument, " << ia.what() << ", was entered.\n";
				return inv_arg_exc;
			}
			catch (const out_of_range& oor)
			{
				cout << "Input, "<< oor.what()<<", was outside of integer value range.\n";
				return out_of_range_exc;
			}
			
			if (arg != -1)
			{
				switch (arg_ndx)
				{
					case 1:
						nbr_files_to_create = arg;
						break;
					case 2:
						nbr_lines_per_file = arg;
						break;
					case 3:
						nbr_values_per_line = arg;
						break;
					case 4:
						min_line_value = arg;
						break;
					case 5:
						max_line_value = arg;
						break;
				}
			}
			
		}
	}
	
	return 0;
}

int main (int argc, char* argv[]) {  
  int args_parsed = parse_command_arguments(argc, argv);
  if (args_parsed == 0)
  {
	  // seed the random number generator with a call to current epoch time
	  srand((unsigned) time(NULL));
	  
	  // repeat the generator for the desired number of files
	  for (int file_no = 0; file_no < nbr_files_to_create; ++file_no)
	  {
	  	  // create the file's name
	  	  stringstream filename;
	  	  filename << "example" << file_no << ".txt";
	  	  
	  	  // create the stream for writing to the new file
		  ofstream myfile (filename.str());
		  
		  // if it was created/opened correctly,
		  if (myfile.is_open())
		  {
		    // generate the desired number of lines 
		    int curr_nbr_lines = 0;
		    while (curr_nbr_lines < nbr_lines_per_file)
		    {
		        // generate nbr_values_per_line random numbers
			    int curr_nbr_values = 0;
			    while (curr_nbr_values < nbr_values_per_line)
			    {
			    	int value = (rand()%(max_line_value-min_line_value))+min_line_value;
			    	(curr_nbr_values < nbr_values_per_line - 1) ? myfile << value << " " : myfile << value;
			    	++curr_nbr_values;
			    }
			    (curr_nbr_lines != nbr_lines_per_file-1) ? myfile << "\n" : myfile << "";
			    ++curr_nbr_lines;
		    }
		    myfile.close();
		  }
		  else cout << "Unable to open file";
	  }
  }
  return 0;
}
