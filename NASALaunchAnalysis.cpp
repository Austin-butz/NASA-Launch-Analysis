#include "TimeCode.h"
#include <iostream>
#include <fstream> //used to read data file
#include <cstring> //used to operate with strings
#include <vector>
using namespace std;

int main()
{
  vector <TimeCode> acc;
  int counter; //counts lines with colons for use in average equation
  ifstream myfile;
  string line;
  myfile.open("Space_Corrected.csv");
  if (myfile.is_open())
    {
      getline(myfile, line); //used to ignore first line
      while (getline(myfile, line))
	{
	  if (line.find(':') < 50) //lines without colons return a very large number
	    {
	      string temp;
	      string temp2;
	      size_t num = line.find(':');
	      const char* hrs = &(line[num-2]);
	      int hr; hr = atoi(hrs);
	      const char* mins = &(line[num+1]);
	      int min; min = atoi(mins);
	      TimeCode time = TimeCode(hr, min, 0);
	      acc.push_back(time);
	      counter += 1;
	    }
	}
      myfile.close();
    }
  TimeCode output = 0;
  for (unsigned int i = 0; i < acc.size(); i++) output = output + acc[i];
  output = output / counter; 
  cout << "Number of Launches With Times: " << counter << endl << "Average: " << output.ToString() << endl;
  return 0;
}
