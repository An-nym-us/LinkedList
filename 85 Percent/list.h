/***********************************************************************
 * Header:
 *    LIST
 * Summary:
 *    Our custom implementation of std::list
 *        ____     _______        __
 *      .' __ '.  |  _____|   _  / /
 *      | (__) |  | |____    (_)/ /
 *      .`____'.  '_.____''.   / / _
 *     | (____) | | \____) |  / / (_)
 *     `.______.'  \______.' /_/
 *
 *
 *    This will contain the class definition of:
 *        List         : A class that represents a List
 *        ListIterator : An iterator through List
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once
#include <cassert>     // for ASSERT
#include <iostream>    // for nullptr
#include <new>         // std::bad_alloc
#include <memory>      // for std::allocator

class TestList;        // forward declaration for unit tests
class TestHash;

namespace custom
{
/**************************************************
 * LIST
 * Just like std::list
 **************************************************/
class list
{
   friend class ::TestList; // give unit tests access to the privates
   friend class ::TestHash;
   friend void swap(list& lhs, list& rhs);
public:
   
   //
   // Construct
   //

   list();
   // Copy Constructor
   list(list & rhs);
   // Move Constructor
   list(list && rhs);
   list(size_t num, const int & t);
   list(size_t num);
   list(const std::initializer_list<int>& il);
    template <class Iterator>
   list(Iterator first, Iterator last);
   ~list()
   { 
     
   }

   //
   // Assign
   //

   list & operator = (list &  rhs);
   list & operator = (list && rhs);
   list & operator = (const std::initializer_list<int>& il);

   //
   // Access
   //

   int& front();
   int& back();

   //
   // Iterator
   //

   class iterator;
   iterator begin();
   iterator end();

   //
   // Insert
   //

   void push_front(const int& data);
   void push_front(int&& data);
   void push_back(const int& data);
   void push_back(int&& data);
   iterator insert(iterator it, const int& data);
   iterator insert(iterator it, int&& data);

   //
   // Remove
   //

   void clear();
   void pop_back();
   void pop_front();
   iterator erase(const iterator& it);

   // 
   // Status
   //

   bool empty()  const { return numElements < 0; }
   size_t size() const { return numElements; }
     
private:
   // nested linked list class
   class Node;
   
   // member variables
   size_t numElements; // though we could count, it is faster to keep a variable
   Node * pHead;    // pointer to the beginning of the list
   Node * pTail;    // pointer to the ending of the list
};

void swap(list & lhs, list & rhs);
/*************************************************
 * NODE
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
class list :: Node
{
public:
   //
   // Construct
   //
   Node()
   {
      pNext = pPrev = nullptr;
   }
   Node(const int & data)
   {
       this -> data = data;
       pNext = pPrev = nullptr;

   }
   Node(int && data)
   {
      this -> data = data;
      pNext = pPrev = nullptr;
   }
   
   //
   // DATA
   //
   
   int data;                 // user data
   Node * pNext;       // pointer to next node
   Node * pPrev;       // pointer to previous node
};


/*************************************************
 * LIST ITERATOR
 * Iterate through a List, non-constant version
 ************************************************/
class list :: iterator
{
   friend class ::TestList; // give unit tests access to the privates
   friend class ::TestHash;
   friend class custom::list;
public:
   // constructors, destructors, and assignment operator
   iterator( ) 
   {
      p = new list::Node;
   }
   iterator(Node * p) 
   {
      p = new list::Node;
   }
   iterator(const iterator  & rhs) 
   { 
      p = new list::Node;
   }
   iterator & operator = (const iterator & rhs)
   {
      return *this;
   }
   
   // equals, not equals operator
   bool operator == (const iterator & rhs) const { return true; }
   bool operator != (const iterator & rhs) const { return true; }
   
   // dereference operator, fetch a node
   int & operator * ()
   {
      return *(new int(99));
   }
   
   // postfix increment
   iterator operator ++ (int postfix)
   {
      return *this;
   }
   
   // prefix increment
   iterator & operator ++ ()
   {
      return *this;
   }
   
   // postfix decrement
   iterator operator -- (int postfix)
   {
      return *this;
   }
   
   // prefix decrement
   iterator & operator -- ()
   {
      return *this;
   }
   
private:
   
   typename list :: Node * p;
};


/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
inline list ::list(size_t num, const int & t): pHead(nullptr),pTail(nullptr), numElements(num)
{
  if(num>=0)
   {
       // Create a New Node
       pHead = pTail = new list::Node(t);

       // Current Head
       Node *currentHead = pHead;
       
       size_t count = 0;
       // Loop
       while(count!= num-1 && currentHead)
       {
           // Create a Node
           Node * newNode = new list::Node(t);
//           newNode -> data = t;
           // Assing currenthead next to new node
           currentHead -> pNext = newNode;
           
           // Assign currenthead prev to currentHead
           newNode-> pPrev = currentHead;
           
           // Update Tail
           pTail = newNode;
           
           // Update Pointers
           currentHead = currentHead-> pNext;
           count++;
       }
       // Assign Null pointers
       pHead -> pPrev = nullptr;
       pTail -> pNext = nullptr;
   }
    numElements = num;
}

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
inline list ::list(size_t num)
{
    // Check if size was less than Zero
    if(num <= 0)
    {
        pHead = pTail = nullptr;
    } else {
        // Create a New Node
        pHead =pTail = new list::Node(0);

        // Current Head
        Node *currentHead = pHead;
        // Track Count
        size_t count = 0;
        // Loop
        while(count != num-1 && currentHead)
        {
            // Create a Node
            Node * newNode = new list::Node(0);
            // Assign Currenthead next to new Node
            currentHead-> pNext = newNode;
            // Assing newNode prev to currentHead
            newNode -> pPrev = currentHead;

            // Update the Tail
            pTail = newNode;

            // Update the Head
            currentHead = currentHead -> pNext;
            // Increment the Counter
            count++;
        }
        // Assign to Null Pointers
        pHead -> pPrev = nullptr;
        pTail -> pNext = nullptr;
    }
    
    numElements = num;
}

/*****************************************
 * LIST :: DEFAULT constructor
 ****************************************/
inline list::list() :numElements(0), pHead(nullptr), pTail(nullptr) {
//   numElements = 0;
//   pHead = pTail = new list::Node();
}

/*****************************************
 * LIST :: COPY constructor
 ****************************************/
inline list::list(list& rhs): pHead(nullptr)
{
      if(rhs.pHead)
      {
          pHead = pTail = new list::Node(rhs.pHead->data);
          Node * currentRhsHead = rhs.pHead-> pNext;

          Node * currentHead = pHead;

          while(currentRhsHead != NULL)
          {
              Node * newNode = new list::Node(currentRhsHead->data);
              currentHead->pNext = newNode;
              newNode->pPrev = currentHead;
              
              pTail = newNode;
              
            currentRhsHead = currentRhsHead -> pNext;
            currentHead = currentHead -> pNext;
          }

          pHead->pPrev = nullptr;
          pTail->pNext = nullptr;
      }
    
    numElements = rhs.numElements;

    
}

/*****************************************
 * LIST :: INIT constructor
 ****************************************/
inline list::list(const std::initializer_list<int>& il)
{
   if(il.size())
   {
       // Çreate a Head Node
       Node * headNode = new list::Node();
       pHead = pTail = headNode;
       
       // Assign Value to First Node
       for(auto it = il.begin(); it!= il.end()-2 ; ++it)
       {
//           std::cout << *it<< std::endl;
           headNode-> data = *it;
       }
       // Keep Track of Current Head
       Node * currentHead = headNode;
       
       // Loop Over Remaining Value
       for(auto it=il.begin()+1; it!= il.end(); ++it)
       {
//           std::cout << *it<< std::endl;
           // Create New Node
           Node *newNode = new list::Node();
           
           // Assign Value to newNode
           newNode -> data = *it;
           
           // Update the Pointers
           currentHead-> pNext = newNode;
           newNode-> pPrev = currentHead;
           
           // Update the Tail and currentHead
           pTail = newNode;
           currentHead = newNode;
           
       }
       
       // Point next and previous to NULL
       pHead -> pPrev = nullptr;
       pTail -> pNext = nullptr;
       
   }
    
    // Change the numElements
    numElements = il.size();
}

/*****************************************
 * LIST :: RANGEconstructor
 ****************************************/
template <class Iterator>
inline list::list(Iterator first, Iterator last)
{

    int count =0;
    // Çreate a Head Node
    Node * headNode = new list::Node();
    pHead = pTail = headNode;
    
    
    for(auto it= first; it!= last-2; ++it)
    {
        headNode-> data = *it;
        count++;
    }
    // Keep Track of Current Head
    Node * currentHead = headNode;
    
    // Loop Over Remaining Value
    for(auto it=first+1; it!= last; ++it)
    {
//           std::cout << *it<< std::endl;
        // Create New Node
        Node *newNode = new list::Node();
        
        // Assign Value to newNode
        newNode -> data = *it;
        
        // Update the Pointers
        currentHead-> pNext = newNode;
        newNode-> pPrev = currentHead;
        
        // Update the Tail and currentHead
        pTail = newNode;
        currentHead = newNode;
        
        count++;
    }
    
    // Point next and previous to NULL
    pHead -> pPrev = nullptr;
    pTail -> pNext = nullptr;
    
    numElements = count;
    
}

/*****************************************
 * LIST :: MOVE constructors
 * Steal the values from the RHS
 ****************************************/
inline list ::list(list && rhs) 
{

    if(rhs.pHead)
    {
   
        pHead = pTail = new list::Node(rhs.pHead->data);
        Node * currentRhsHead = rhs.pHead-> pNext;

        Node * currentHead = pHead;

        while(currentRhsHead != NULL)
        {
            Node * newNode = new list::Node(currentRhsHead->data);
            currentHead->pNext = newNode;
            newNode->pPrev = currentHead;
            
            pTail = newNode;
            
          currentRhsHead = currentRhsHead -> pNext;
          currentHead = currentHead -> pNext;
        }

        pHead->pPrev = nullptr;
        pTail->pNext = nullptr;
        
    }
    
    rhs.pHead = nullptr;
    rhs.pTail = nullptr;
    
    
    numElements = rhs.numElements;
    rhs.numElements = 0;
}

/**********************************************
 * LIST :: assignment operator - MOVE
 * Copy one list onto another
 *     INPUT  : a list to be moved
 *     OUTPUT :
 *     COST   : O(n) with respect to the size of the LHS
 *********************************************/
inline list & list  :: operator = (list && rhs)
{
   return *this;
}

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
inline list & list :: operator = (list & rhs)
{
   return *this;
}

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
inline list & list :: operator = (const std::initializer_list<int>& rhs)
{
   return *this;
}

/**********************************************
 * LIST :: CLEAR
 * Remove all the items currently in the linked list
 *     INPUT  :
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
inline void list :: clear()
{

}

/*********************************************
 * LIST :: PUSH BACK
 * add an item to the end of the list
 *    INPUT  : data to be added to the list
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
inline void list :: push_back(const int & data)
{

}

inline void list ::push_back(int && data)
{

}

/*********************************************
 * LIST :: PUSH FRONT
 * add an item to the head of the list
 *     INPUT  : data to be added to the list
 *     OUTPUT :
 *     COST   : O(1)
 *********************************************/
inline void list :: push_front(const int & data)
{

}

inline void list ::push_front(int && data)
{

}


/*********************************************
 * LIST :: POP BACK
 * remove an item from the end of the list
 *    INPUT  :
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
inline void list ::pop_back()
{

}

/*********************************************
 * LIST :: POP FRONT
 * remove an item from the front of the list
 *    INPUT  :
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
inline void list ::pop_front()
{

}

/*********************************************
 * LIST :: FRONT
 * retrieves the first element in the list
 *     INPUT  :
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
inline int & list :: front()
{
   return *(new int(99));
}

/*********************************************
 * LIST :: BACK
 * retrieves the last element in the list
 *     INPUT  :
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
inline int & list :: back()
{
   return *(new int(99));
}


/******************************************
 * LIST :: REMOVE
 * remove an item from the middle of the list
 *     INPUT  : an iterator to the item being removed
 *     OUTPUT : iterator to the new location
 *     COST   : O(1)
 ******************************************/
inline typename list :: iterator  list :: erase(const list :: iterator & it)
{
   return end();
}

/******************************************
 * LIST :: INSERT
 * add an item to the middle of the list
 *     INPUT  : data to be added to the list
 *              an iterator to the location where it is to be inserted
 *     OUTPUT : iterator to the new item
 *     COST   : O(1)
 ******************************************/
inline typename list :: iterator list :: insert(list :: iterator it,
                                                const int & data)
{
   return end();
}

inline typename list ::iterator list  ::insert(list ::iterator it,
                                               int && data)
{
   return end();
}


/**********************************************
 * LIST :: assignment operator - MOVE
 * Copy one list onto another
 *     INPUT  : a list to be moved
 *     OUTPUT :
 *     COST   : O(n) with respect to the size of the LHS
 *********************************************/
void swap(list & lhs, list & rhs)
{

}

/*********************************************
 * LIST :: begin
 * returns the first slot of the list
 *     INPUT  :
 *     OUTPUT : teratator
 *     COST   : O(1)
 *********************************************/
inline typename list::iterator list::begin()
{
   return list::iterator ();
   
}

/*********************************************
 * LIST :: end
 * returns the first slot off the end of the list
 *     INPUT  :
 *     OUTPUT : iteratator
 *     COST   : O(1)
 *********************************************/
inline typename list::iterator list::end()
{
   return list::iterator ();
}


}; // namespace custom
