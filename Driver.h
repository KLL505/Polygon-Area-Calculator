#include <iostream>
#include <string>
#ifndef Driver_h_
#define Driver_h_

//driver object used to store driver names and areas 
class Driver
{
    private: 
        std::string name;
        double area;
    public:
        //static variable to determine how to sort driver objects baased off area or name
        static bool sort;
        
        Driver(){name = ""; area = 0;}
        Driver(std::string str,double num){name = str; area = num;}
        void setName(std::string str){name = str;}
        void setArea(double num){area = num;}
        std::string getName(){return name;}
        double getArea(){return area;}
        bool operator<(Driver);
        bool operator>(Driver);
        bool operator==(Driver);
        bool operator== (double);
        bool operator== (std::string);
        friend std::ostream& operator<<(std::ostream& out, const Driver& d);

    
};
#endif