/******************************************************************************
Kenneth Ly
*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "Driver.h"
#include "Node.h"
#include "LinkedList.h"

using namespace std;
bool Driver::sort = true;

//Calculates the area based off a 3d array of coordinates representing a polygon  and returns it as a double
double
getArea (double*** arr, int driver)
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

  return .5 * fabs (sum);
}

//Takes a string of coordinates from ReadFile and chops them point by point to store into the 3d array 
bool
GetCoords (double*** pointArray, string coords, int index)
{
    try{
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
        return true;
    }
    
    catch(exception e)
    {
        return false;
    }
}

//checks to make sure the name consists of valid characters
bool checkName (string& name)
{
    for (char const &c : name) 
    {
        if (!(isdigit(c) || isalpha(c) || c == '-' || c == '\'' )) 
            return false;
    }
    return true;
    
}

//checks to make sure the coordinates a valid 
bool checkCoords (string coords)
{
    istringstream iss (coords);
    string firstPoint;
    string lastPoint;
    iss >> firstPoint;
    while(iss >> lastPoint)
    {
    }
    if(firstPoint != lastPoint)
        return false;


        //return false;
    return true;
}

//reads a given file and put all of the names and points into arrays  

void
readDriverFile (ifstream & input, double*** pointArray, string names[])
{
  string line;
  string coords;
  string name;
  int i = 0;
  while (getline (input, line))
    {
        if (line.empty())
            continue;
        //gets the substring of the name corresponding to the polygon and stores it in the names array
        istringstream iss (line);
        iss >> name;
        while(name.find(",") == string::npos)
        {
            names[i] += name + " ";
            iss >> name;
        }
        names[i] = names[i].substr(0,names[i].length() - 1);
      //takes the coordinates of the corresponding polygon and stores them as a string to send to GetCoords
      //stores the driver as "Invalid" if the name or coordinates arent valid 
      if(!checkName(names[i]))
        names[i] = "Invalid";
        else
        {
            coords = line.substr (names[i].length() + 1,
     		    line.length () + names[i].length() + 2);
     		if(!checkCoords(coords))
     	        names[i] = "Invalid";;
            if(!GetCoords (pointArray, coords, i))
                names[i] = "Invalid"; 
        }

  
        i++; 
    }

}

//intializes the 3D array based on how many drivers and points there are in the file
double*** initializeArray(ifstream & input, int& dCount) 
{
  int pCount = 0;
  int maxPoints = 0;
  string line;
  string point;

//finds the max amount of coordinates a driver has within the file
  while (getline (input, line))
    {
        if (line.empty())
            continue;
        istringstream iss(line);
        while(iss >> point)
            pCount ++;
        dCount++;
        pCount--;
        if(pCount > maxPoints)
            maxPoints = pCount;
        pCount = 0;
    }

    double*** pointArray = new double**[dCount];
 
 //intializes a 3D array based off the amount of drivers and the max possible coordinates 
    for (int i = 0; i < dCount; i++)
    {
        pointArray[i] = new double*[maxPoints];
        for (int j = 0; j < maxPoints; j++) {
            pointArray[i][j] = new double[2];
        }
    } 
    return pointArray; 
}

//checks a string to see if it could be converted to a number
bool isNumber(const string& s)
{
    for (char const &c : s) 
    {
        if (!isdigit(c) && c!= '.') 
            return false;
    }
    return true;
}

//reads the command file 
void readCommandsFile(istream& input, LinkedList<Driver> list)
{
  string line;
  string command;

  
  while (getline (input, line))
    {
          istringstream iss (line);
          iss >> command;
          //performs the sort command on the list
          if(command == "sort")
          {
              iss >> command;
              //sorts by area
              if(command == "area")
              {
                  Driver::sort = false;
                  list.sort();
              }
              //sorts by driver
              else if(command == "driver")
              {
                  Driver::sort = true;
                  list.sort();
              }
              else
                  return;
              
              iss >> command;
              //displays sorted list in ascending order
              if(command == "asc")
              {
                cout << setprecision (2) << fixed << list<< endl;  
              }
              //displayss sorted list in dscending order
              else if(command == "dsc")
              {
                Node<Driver>* temp = list.getTail();
                while(temp != nullptr)
                {
                    cout << setprecision (2) << fixed << temp->getData() << endl;
                    temp = temp->getPrev();
                }
                cout << endl;
              }
              else
              return;
          }
          //searches the list for the given number
          else if (isNumber(command))
          {
            list.search(stod(command));
          }
          //searches the list for the given name
          else
          {
            list.search(line);  
          }
    }
}

//Removes any invalid drivers from the list
void removeInvalid(LinkedList<Driver>& list)
{
    Node<Driver>* index = list.getHead();
    Driver invalid("Invalid", -1);
    while(index != nullptr)
    {
         Node<Driver>* temp = index; 
         if(temp->getData() == invalid)
            list.Remove(*temp);
    
        index = index->getNext();
    }
}

int
main ()
{
  string driverFile;
  string commandsFile;
  double area;
  int dCount = 0;
  LinkedList<Driver> driverList;

  Driver::sort = false;
//prompts user to enter a file to open and opens an output file for the calculated data
  cout << "Enter Driver file name: " << endl;
  cin >> driverFile; 
  //driverFile = "pilot_routes1.txt";
  cout << "Enter Commands file name: " << endl;
  cin >> commandsFile;
  //commandsFile = "sample_commands.txt";
  ifstream driverInput (driverFile);
  ifstream commandsInput (commandsFile);

//checks if the input file is valid and is open then extracts its data into the arrays declared above 
  if (driverInput.is_open ())
    {
      double*** pointArray = initializeArray(driverInput, dCount);
      string* stringArray = new string[dCount];
      driverInput.close ();
      ifstream driverInput (driverFile);
      readDriverFile (driverInput, pointArray, stringArray);


//writes the area calculated from the input files onto an output file and prints them in the console 
      Driver* d;
	  Node<Driver>* n;
      
      for (int i = 0; i < dCount; i++)
	    {
    	  if (stringArray[i].empty ())
    	    continue;
    	  if(stringArray[i] == "Invalid")
    	    area = -1;
    	  else
    	    area = getArea (pointArray, i);
    	  d = new Driver(stringArray[i], area);
    	  n = new Node<Driver>(*d);
     	  driverList.insert(n);
	    }
	  removeInvalid(driverList);
	  cout << endl << setprecision (2) << fixed << driverList<< endl; 
	// closes the files 
      driverInput.close ();
    }
    
  if (commandsInput.is_open ())
    {   
        readCommandsFile(commandsInput, driverList); 
        commandsInput.close(); 
    }
  return 0;
}
