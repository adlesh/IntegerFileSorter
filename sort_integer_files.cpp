#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <chrono>

//typedef std::chrono::high_resolution_clock Clock;

enum Exceptions {no_exc = 0, inv_arg_exc, out_of_range_exc};

const int numerical_arg_start_ndx = 2;

using namespace std;

string file_name = "file0";
string file_amend = "-sorted";
string file_format = ".txt";

string in_file_name = "";

ifstream my_infile;
ofstream my_outfile;

int parse_command_arguments(int argc, char* argv[])
{
	// if there were additional commands entered
	if (argc > 1)
	{
		// set the base file name
		file_name = argv[1];		
	}
	
	// create the input file name by concatenating file_name and file_format
	in_file_name = file_name + file_format;
	
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
	
	return values_from_line;
}

vector<vector<int>> read_file()
{
    string curr_line;    
    vector<vector<int>> lines_from_file;
    try
    {
	    while (getline(my_infile, curr_line))
	    {
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
		
		(main_it < parsed_lines.end()-1) ?
	        my_outfile << line_string.str() << endl : my_outfile << line_string.str();
	}
}

vector<chrono::high_resolution_clock::time_point> execute(int argc, char* argv[])
{
  vector<chrono::high_resolution_clock::time_point> io_clocks;
  
  int args_parsed = parse_command_arguments(argc, argv);
  if (args_parsed == no_exc)
  {
	  // create the file's name
	  stringstream out_file_name;
	  out_file_name << file_name << file_amend << file_format;
	  
	  io_clocks.push_back(chrono::high_resolution_clock::now());
  	  my_infile.open(in_file_name, ios::in);
	  bool file_read_success = false;
  
	  // if it was created/opened correctly,
	  if (my_infile.is_open())
	  {
	  	file_read_success = true;
	  	
	  	vector<vector<int>> parsed_lines = read_file();
	  	my_infile.close();
	  	io_clocks.push_back(chrono::high_resolution_clock::now());
	  	
	  	if (parsed_lines.size() > 0)
	  	{
	  		io_clocks.push_back(chrono::high_resolution_clock::now());
	  		// create the stream for writing to the new file
	  		my_outfile.open(out_file_name.str(), ios::out);
	  		if (my_outfile.is_open())
	  		{
	  			
		  		write_file(parsed_lines);
		  		my_outfile.close();
		  		io_clocks.push_back(chrono::high_resolution_clock::now());
	  		}
	  		else cout << "Unable to open file " << out_file_name.str() << endl;
	  	}
	    
	  }
	  else cout << "Unable to open file " << in_file_name << endl;
  }
  
  return io_clocks;
}
int main (int argc, char* argv[]) 
{
  chrono::high_resolution_clock::time_point start_clock, end_clock;
  
  start_clock = chrono::high_resolution_clock::now();
  
  vector<chrono::high_resolution_clock::time_point> io_clocks = execute(argc, argv);
  
  end_clock = chrono::high_resolution_clock::now();
  
  double diff_input_clocks = chrono::duration_cast<chrono::nanoseconds>(io_clocks[1] - io_clocks[0]).count();
  double diff_output_clocks = chrono::duration_cast<chrono::nanoseconds>(io_clocks[3] - io_clocks[2]).count();
  
  double clock_diff = chrono::duration_cast<chrono::nanoseconds>(end_clock - start_clock).count();
  
  double io_time = (diff_input_clocks + diff_output_clocks);
  
  ofstream times_log("times.log", ios::app);
  
  if (times_log.is_open())
  {
      times_log << in_file_name << endl;
      times_log << "CPU Time: " << clock_diff << " ns"<< endl;
	  times_log << "IO Time:   " << endl << 
	          "   Total:  " << io_time << " ns" << endl <<
	          "   Input:  " << diff_input_clocks << " ns" << endl <<
	          "   Output: " << diff_output_clocks<< " ns" << endl;
  }
  return 0; 
}
