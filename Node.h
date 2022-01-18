#include <iostream>
#include "Driver.h"
#ifndef Node_h_
#define Node_h_

//templated node class 
template <typename T> 
class Node
{
    private:
        T data;
        Node<T> *next; 
        Node<T> *prev;
    
    public:

        Node(){data = Driver();}
        Node(T d){data = d;}
        void setData(T d){data = d;}
        void setNext(Node<T>* n){next = n;}
        void setPrev(Node<T>* p){prev = p;}
        Driver getData(){return data;}
        Node<T>* getNext(){return next;}
        Node<T>* getPrev(){return prev;}
        bool operator== (Node<T> n){return (next == n.next&& prev == n.prev)?true:false;}
        bool operator!= (Node<T> n){return (next != n.next&& prev != n.prev)?true:false;}

    
};
#endif