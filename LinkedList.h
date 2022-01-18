#include <iostream>
#include <string>
#include "Node.h"
#ifndef LinkedList_h_
#define LinkedList_h_

//templated linked list class
template <typename T> 
class LinkedList
{
    protected:
        Node<T> *head, *tail;
    public: 
        
        LinkedList(){head = nullptr; tail = nullptr;}
        LinkedList(Node<T>* n){head = n; tail = n;} 
        void setHead(Node<T>* n){head = n;}
        void setTail(Node<T>* n){tail = n;}
        Node<T>* getHead(){return head;}
        Node<T>* getTail(){return tail;}
        void insert(Node<T>*);
        void Remove(Node<T>);
        void insertAfter(Node<T>*, Node<T>*);
        void prepend(Node<T>*);
        Node<T>* search(double);
        Node<T>* search(std::string);
        void sort();
        friend std::ostream& operator<<(std::ostream& out, LinkedList<T>& list)
        {
            Node<T>* temp = list.getHead();
            while(temp != nullptr)
            {
            out << temp->getData() << std::endl;
            temp = temp->getNext();
            }
                    
            
              return out;
            }
    
};
#endif

//inserts a node at the end of the linked list
template <typename T> 
void LinkedList<T>::insert(Node<T>* n)
{
    if (!head)
    {
        head = n;
        tail = n;
    }
    else
    {
        tail->setNext(n);
        n->setPrev(tail);
        tail = n;
    }
}

//searches for a double within the linked list and returns the node contating that double
template <typename T> 
Node<T>* LinkedList<T>::search(double key)
{
    Node<T>* temp = head;
    while(temp != nullptr)
    {
        if(temp->getData() == key)
        {
            std::cout << temp->getData() << std::endl;
            return temp;
        }
        else
            temp = temp->getNext();
    }
    std::cout << key << " not found" << std::endl << std::endl;
    return temp;
}

//searchs the linked list for a string and returns the node contating that string
template <typename T> 
Node<T>* LinkedList<T>::search(std::string key)
{
    Node<T>* temp = head;
    while(temp != nullptr)
    {
        if(temp->getData() == key)
        {
            std::cout << temp->getData() << std::endl;
            return temp;
        }
        else
            temp = temp->getNext();
    }
    std::cout << key << " not found" << std::endl << std::endl;
    return temp;
    
}


//removes a node from the linked list
template <typename T> 
void LinkedList<T>::Remove(Node<T> n)
{

    Node<T>* store = nullptr;
        //empty list
        if (head)
        {
            //beginning of list
            if (*head == n)
            {
                
                store = head;
                head = head->getNext();
                store->setNext(nullptr);
                head->setPrev(nullptr);

            }
            //middle of list
            //end of list
            else
            {
                Node<T>* temp = head;
                while(temp->getNext() &&  *temp->getNext() != n )
                {
                    temp = temp->getNext();
                }

                if (temp->getNext() != nullptr)
                {
                    store = temp->getNext();
                    temp->setNext(temp->getNext()->getNext());
                    if(temp->getNext())
                        temp->getNext()->setPrev(temp);
                    else 
                    {
                        tail = temp;
                    }

                    store->setNext(nullptr);
                    store->setPrev(nullptr);
                }
            }
        }
}

//inserts a node after a specific node within the linked list
template <typename T> 
void LinkedList<T>::insertAfter(Node<T>* n1, Node<T>* n2)
{
    Node<T>* temp = head;
    while(temp != nullptr && temp != n1)
    {
            temp = temp->getNext();
    }
    if(temp == nullptr)
        return;
    n2->setNext(temp->getNext());
    if(temp->getNext())
        temp->getNext()->setPrev(n2);
    else
        tail = n2;
    temp->setNext(n2);
    n2->setPrev(temp);
}

//inserts a node at the beginning of the linked list
template <typename T> 
void LinkedList<T>::prepend(Node<T>* n)
{
    if (!head)
    {
        head = n;
        tail = n;
    }
    else
    {
        n->setNext(head);
        n->setPrev(nullptr);
        head->setPrev(n);
        head = n;
    }

}
 
//insertion sort for the linked list      
template <typename T> 
void LinkedList<T>::sort()
{
     Node<T>* temp = head->getNext();
     
   while (temp != nullptr) 
   {
      Node<T>* next = temp->getNext();
      Node<T>* search = temp->getPrev();
      while (search != nullptr && search->getData() > temp->getData()) 
      {
         search = search->getPrev();
      }
      // Remove and re-insert temp

      Remove(*temp);
      if (search == nullptr) {
         temp->setPrev(nullptr);
         prepend(temp);
      }
      else {
         insertAfter(search, temp);
      }
      // Advance to next node
      temp = next;

   }
           
}



