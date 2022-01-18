#include "Driver.h"
#include <iostream>

//overloaded greater than variable
bool Driver::operator> (Driver d)
{
  if(sort)
   return (name > d.name);
  else
   return (area > d.area);
}

//overloaded less than variable
bool Driver::operator< (Driver d)
{
  if(sort)
   return (name < d.name);
  else
   return (area < d.area);
}

//overloaded equals to variable comparing two drivers
bool Driver::operator== (Driver d)
{
  return (area == d.area && name == d.name);
}

//overloaded equals to variable comparing a driver and a number
bool Driver::operator== (double num)
{
   return (area == num);
}

//overloaded equals to variable comparing a driver and a string
bool Driver::operator== (std::string str)
{
    return (name == str);
}

//overloaded insertion operator 
std::ostream& operator<< (std::ostream& out, const Driver& d)
{
 
    out << d.name << " " << d.area;
  return out;
}