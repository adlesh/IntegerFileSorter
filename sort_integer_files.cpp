#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdexcept>

enum Exceptions {no_exc = 0, inv_arg_exc, out_of_range_exc, };

int numerical_arg_start_ndx = 2;

using namespace std;

string file_name = "file0";
string file_amend = "-sorted";
string file_format = ".txt";

string in_file_name = "";

ifstream my_infile;
ofstream my_outfile;

/*
int handle_integer_arguments(int argc, char* argv[])
{
	// try to parse each command into an integer
	for (int arg_ndx = numerical_arg_start_ndx; arg_ndx < argc; ++arg_ndx)
	{
		// default error value for parsed argv[arg_ndx], arg
		int arg = -1;
		// attempt to parse the current argument
		try 
		{
			arg = stoi(argv[arg_ndx]);
		}
		// handle an invalid argument error
		catch (const invalid_argument& ia)
		{
			cout << "Invalid Argument, " << ia.what() << ", was entered.\n";
			return inv_arg_exc;
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
			// handle the parsed argument
			switch (arg_ndx)
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
}*/

int parse_command_arguments(int argc, char* argv[])
{
	// if there were additional commands entered
	if (argc > 1)
	{
		// set the base file name
		file_name = argv[1];
		// create the input file name by concatenating file_name and file_format
		in_file_name = file_name + file_format;
	}
	
	return no_exc;
}

int read_file()
{
	cout << in_file_name << " was opened successfully.\n";
    string curr_line;
    
    while (getline(my_infile, curr_line))
    {
    	cout << curr_line << "\n";
    }
    my_infile.close();
}

int main (int argc, char* argv[]) 
{  
  int args_parsed = parse_command_arguments(argc, argv);
  if (args_parsed == no_exc)
  {
          // create the file's name
	  	  stringstream out_file_name;
	  	  out_file_name << file_name << file_amend << file_format;
  	  	  my_infile.open(in_file_name, ios::in);
	  	  
	  	  
	  	  // create the stream for writing to the new file
		  //my_outfile.open(out_file_name.str(), ios::out);
		  
		  // if it was created/opened correctly,
		  if (my_infile.is_open())
		  {
		    
		  }
		  else cout << "Unable to open file";
	  cout << "File name: " << in_file_name << "\n";
	  cout << "Out File Name: " << out_file_name.str() << "\n";
	  
  }
  return 0;
}
