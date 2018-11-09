// writing on a text file
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main () {
  int num_files_to_create = 1;
  int min_line_value = 100;
  int max_line_value = 1000;
  int nbr_values_per_line = 10;
  int nbr_lines_per_file = 100;
  
  srand((unsigned) time(NULL));
  for (int file_no = 0; file_no < num_files_to_create; ++file_no)
  {
	  ofstream myfile ("example.txt");
	  if (myfile.is_open())
	  {
	    int curr_nbr_lines = 0;
	    while (curr_nbr_lines < nbr_lines_per_file)
	    {
		    int curr_nbr_values = 0;
		    while (curr_nbr_values < nbr_values_per_line)
		    {
		    	int value = (rand()%(max_line_value-min_line_value))+min_line_value;
		    	(curr_nbr_values < nbr_values_per_line - 1) ? myfile << value << " " : myfile << value;
		    	++curr_nbr_values;
		    }
		    myfile << "\n";
		    ++curr_nbr_lines;
	    }
	    myfile.close();
	  }
	  else cout << "Unable to open file";
  }
  return 0;
}
