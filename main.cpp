/******************************************************************************
Kenneth Ly
KLL200003
*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

//Calculates the area based off a 3d array of coordinates representing a polygon  and returns it as a double
double
getArea (double arr[][16][2], int driver)
{
  //calculates the sum of the first 2 points
  double sum =
    (arr[driver][1][0] + arr[driver][0][0]) * (arr[driver][1][1] -
					       arr[driver][0][1]);
  int i = 1;
  
  //calcualtes a summation of the points until all points of the polygon has been added
  while ((arr[driver][i][0] != arr[driver][0][0])
	 || (arr[driver][i][1] != arr[driver][0][1]))
    {
      sum +=
	(arr[driver][i + 1][0] + arr[driver][i][0]) * (arr[driver][i + 1][1] -
						       arr[driver][i][1]);
      i++;
    }
    
  //returns the absolute value of half of the summation calculated above which is the area of the shape
  return .5 * abs (sum);

}

/*Takes a string of coordinates from ReadFile and chops them point by point to store into the 3d array 
*/
void
GetCoords (double pointArray[][16][2], string coords, int index)
{
  double x;
  double y;
  istringstream iss (coords);
  string point;
  int c = 0;
  int comma;
  
  //seperates a points x and y value based on the position of the comma in order to store the values in the 3d array 
  while (iss >> point)
    {
      comma = static_cast < int >(point.find (','));
      x = stod (point.substr (0, comma + 1));
      y = stod (point.substr (comma + 1, point.length () - comma + 2));
      pointArray[index][c][0] = x;
      pointArray[index][c][1] = y;
      c++;
    }
}

/*reads a given file and put all of the names and points into arrays  
*/
void
ReadFile (ifstream & input, double pointArray[][16][2], string names[])
{
  string line;
  string coords;
  int i = 0;
  
  while (getline (input, line))
    {
        if (line.empty())
            continue;
        //gets the substring of the name corresponding to the polygon and stores it in the names array
      names[i] = line.substr (0, line.find (" ") + 1);
      
      //takes the coordinates of the corresponding polygon and stores them as a string to send to GetCoords
      coords =
	line.substr (line.find (" ") + 1,
		     line.length () + line.find (" ") + 2);
      GetCoords (pointArray, coords, i);
      i++;
    }

}

int
main ()
{
  string name;
  double pointArray[20][16][2];
  string stringArray[20];
  double area;

//prompts user to enter a file to open and opens an output file for the calculated data
  cout << "Enter file name: " << endl;
  cin >> name;
  ifstream input (name);
  ofstream output;
  output.open ("areas.txt");

//checks if the input file is valid and is open then extracts its data into the arrays declared above 
  if (input.is_open ())
    {
      ReadFile (input, pointArray, stringArray);

//writes the area calculated from the input files onto an output file and prints them in the console 
      for (int i = 0; i < 20; i++)
	{
	  if (stringArray[i].empty ())
	    break;
	  area = getArea (pointArray, i);
	  output << stringArray[i] << " " << setprecision (2) << fixed << area
	    << endl;
	  cout << stringArray[i] << " " << setprecision (2) << fixed << area
	    << endl;
	}
	
	// closes the files 
      input.close ();
      output.close ();
    }
  return 0;
}
