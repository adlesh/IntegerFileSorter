#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

enum Exceptions {no_exc = 0, inv_arg_exc, out_of_range_exc};

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

vector<int> tokenize_line(string curr_line)
{
	size_t pos = 0;
	string token;
	vector<int> values_from_line;
	string delimiter = " ";
	try 
	{
		int value = -1;
		while ((pos = curr_line.find(delimiter)) != string::npos)
		{
		    token = curr_line.substr(0, pos);
		    //cout << token << ", ";
		    curr_line.erase(0, pos + delimiter.length());
		    
		    value = stoi(token);
		    
		    if (value != -1)
		    {
		    	values_from_line.push_back(value);
		    	value = -1;
		    }
		}
		
		value = stoi(curr_line);
		if (value != -1)
			values_from_line.push_back(value);
		
	}
	// handle an invalid argument error
	catch (const invalid_argument& ia)
	{
		cout << "Invalid Argument, " << ia.what() << ", was entered.\n";
	}
	// handle integer range error
	catch (const out_of_range& oor)
	{
		cout << "Input, "<< oor.what()<<", was outside of integer value range.\n";
	}
	
	return values_from_line;
	/*
	*/
}

vector<int> sort_line(vector<int> values_from_line)
{
	stable_sort(values_from_line.begin(), values_from_line.end());
	/*for (vector<int>::iterator it = values_from_line.begin(); it != values_from_line.end(); ++it)
	{
		cout << " " << *it;
	}
	cout << endl;*/
	
	return values_from_line;
}

vector<vector<int>> read_file()
{
	cout << in_file_name << " was opened successfully.\n";
    string curr_line;    
    vector<vector<int>> lines_from_file;
    try
    {
	    while (getline(my_infile, curr_line))
	    {
	    	//cout << curr_line << endl;
	    	vector<int> parsed_ints_from_line = tokenize_line(curr_line);
	    	parsed_ints_from_line = sort_line(parsed_ints_from_line);
	    	lines_from_file.push_back (parsed_ints_from_line);
	    }
    
    }
    catch (ios_base::failure fail)
    {
    	cout << "Unable to get line " << fail.what() << endl;
    }
    
    return lines_from_file;
}

int write_file(vector<vector<int>> parsed_lines)
{
	for (vector<vector<int>>::iterator main_it = parsed_lines.begin();
	     main_it != parsed_lines.end();
	     ++main_it)
	{
		vector<int> line = *main_it;
		stringstream line_string;
		for (vector<int>::iterator line_it = line.begin();
		     line_it != line.end();
		     ++line_it)
		{
		    (line_it < line.end()-1) ?
		        line_string << *line_it << " " : line_string << *line_it;
		}
		//cout << line_string.str() << endl;
		(main_it < parsed_lines.end()-1) ?
	        my_outfile << line_string.str() << endl : my_outfile << line_string.str();
	}
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
	  	  bool file_read_success = false;
		  
		  // if it was created/opened correctly,
		  if (my_infile.is_open())
		  {
		  	file_read_success = true;
		  	vector<vector<int>> parsed_lines = read_file();
		  	if (parsed_lines.size() > 0)
		  	{
		  		// create the stream for writing to the new file
		  		my_outfile.open(out_file_name.str(), ios::out);
		  		if (my_outfile.is_open())
		  		{
			  		write_file(parsed_lines);
		  		}
		  		else cout << "Unable to open file " << out_file_name.str() << endl;
		  	}
		    my_infile.close();
		  }
		  else cout << "Unable to open file " << in_file_name << endl;
	  
  }
  return 0;
}
