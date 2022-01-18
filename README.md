# Polygon-Area-Calculator
Created by Kenneth Ly 

This program can caluclate the area of any polygon given the coordiante points
of each vertex using a dynamic 3d array and stores all of these areas within a linked list 
that can be sorted or searched through. The purpose of this program is to compare
different delivery drivers by using the calculated area from the polygons created by their 
delivery routes.

The program creates the linked list by reading from a given file inputted by the user that 
must be formatted like so:

NAME X1,Y1 X2,Y2 X3,Y3 Xn,Yn X1,Y1

(The included test file is titled sample_routes.txt and can be edited for further testing)

The program can read any amount of drivers and coordinates due to the 3d array being dynamic. 
The line must end in the starting vertex to indicate the end of the polygon and to 
perform the calculation.The coordinate points can consist of integers, floating points,
positive, and negative values. Names must be one word and consist of alphanumeric characters
and "-" or "/".

The program will output the results into a linked list that will display in the console. From there,
it will then read the second user inputted file on how to sort or search through the linked list. 
The valid commands for the command files are the following:

sort [area/driver] [asc/dsc] - will sort the linked list based on either the names of the driver
or the area of the polygon created by the driver then display the sorted list
in either ascending or descending order to the console.

[number] - if just a number is present within a line of the command file, the program will search
the linked list for any driver whose area matches that number and will display that driver object to the console.

[name] - if just a string is present within a line of the command file, the program will search
the linked list for any driver whose name matches that string and will display that driver object to the console.

