# Polygon-Area-Calculator
Created by Kenneth Ly 

This program can caluclate the area of any polygon given the coordiante points
of each vertex using a 3d array. 

The program reads from a given file inputted by the user that must be formatted like so:

NAME x1,y1 x2,y2 x3,y3 xn,yn x1,y1

(The included test file is titled sample_routes.txt and can be edited to the viewers liking)

The program can read up to 20 different names and each name can have up to 16 vertexes. 
The line must end in the starting vertex to indicate the end of the polygon and to 
perform the calculation.The coordinate points can consist of integers, floating points,
positive, and negative values. Names must be one word but can be comprised of any character.

The program will output the results into the console and into areas.txt formatted like so:

NAME AREA

