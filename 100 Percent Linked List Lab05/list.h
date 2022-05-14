/***********************************************************************
 * Header:
 *    LIST
 * Summary:
 *    Our custom implementation of std::list
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        List         : A class that represents a List
 *        ListIterator : An iterator through List
 * Author
 *    Jonathan Gunderson and Sulav Dahal
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
template <typename T>
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
   list(list <T> & rhs);
   list(list <T>&& rhs);
   list(size_t num, const T & t);
   list(size_t num);
   list(const std::initializer_list<T>& il);
   template <class Iterator>
   list(Iterator first, Iterator last);
  ~list() 
   {
      pHead = pTail = nullptr;
      numElements= 0;
   }

   // 
   // Assign
   //

   list <T> & operator = (list &  rhs);
   list <T> & operator = (list && rhs);
   list <T> & operator = (const std::initializer_list<T>& il);

   //
   // Iterator
   //

   class  iterator;
   iterator begin()  { return iterator(pHead); }
   iterator rbegin() { return iterator(nullptr); }
   iterator end()    { return iterator(nullptr); }

   //
   // Access
   //

   T& front();
   T& back();

   //
   // Insert
   //

   void push_front(const T&  data);
   void push_front(      T&& data);
   void push_back (const T&  data);
   void push_back (      T&& data);
   iterator insert(iterator it, const T& data);
   iterator insert(iterator it, T&& data);

   //
   // Remove
   //

   void pop_back();
   void pop_front();
   void clear();
   iterator erase(const iterator& it);

   // 
   // Status
   //

   bool empty()  const { return numElements ==0; }
   size_t size() const { return numElements;   }


private:
   // nested linked list class
   class Node;

   // member variables
   size_t numElements; // though we could count, it is faster to keep a variable
   Node * pHead;    // pointer to the beginning of the list
   Node * pTail;    // pointer to the ending of the list
};

/*************************************************
 * NODE
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
template <typename T>
class list <T> :: Node
{
public:
   //
   // Construct
   //
   Node()  
   {
      this->data = 0;
      pNext = pPrev = nullptr;
   }
   Node(const T &  data)  
   {
      this->data = data;
      pNext = pPrev = nullptr;
   }
   Node(      T && data)  
   {
      this->data = std::move(data);
      pNext = pPrev = nullptr;
   }

   //
   // Data
   //

   T data;                 // user data
   Node * pNext;       // pointer to next node
   Node * pPrev;       // pointer to previous node
};

/*************************************************
 * LIST ITERATOR
 * Iterate through a List, non-constant version
 ************************************************/
template <typename T>
class list <T> :: iterator
{
   friend class ::TestList; // give unit tests access to the privates
   friend class ::TestHash;
   template <typename TT>
   friend class custom::list;
public:
   // constructors, destructors, and assignment operator
   iterator() 
   {
      p = nullptr;
   }
   iterator(Node * p) 
   {
      this->p = p;
   }
   iterator(const iterator  & rhs) 
   {
      *this = rhs;
   }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }
   
   // equals, not equals operator
    bool operator == (const iterator & rhs) const { return this->p == rhs.p; }
    bool operator != (const iterator & rhs) const { return this->p != rhs.p; }

   // dereference operator, fetch a node
   T & operator * ()
   {
      return p->data;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator itOld = *this;
      p = p->pNext;
      return itOld;
   }

   // prefix increment
   iterator & operator ++ ()
   {
      p = p->pNext;
      return *this;
   }
   
   // postfix decrement
   iterator operator -- (int postfix)
   {
      iterator temp(*this);
      p= p->pPrev;
      return temp;
   }

   // prefix decrement
   iterator & operator -- ()
   {
      p = p->pPrev;
      return *this;
   } 

   // two friends who need to access p directly
   friend iterator list <T> :: insert(iterator it, const T &  data);
   friend iterator list <T> :: insert(iterator it,       T && data);
   friend iterator list <T> :: erase(const iterator & it);

private:

   typename list <T> :: Node * p;
};

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
template <typename T>
list <T> ::list(size_t num, const T & t):pHead(nullptr), pTail(nullptr), numElements(num)
{
   if(num >= 0)
   {
      pHead = pTail = new list::Node(t);  // Create a New Node

      // Current Head
      Node *currentHead = pHead;
         
      for (size_t it = 0; (it != num - 1) && currentHead; it++)
      {
         // Create a Node
         Node* newNode = new list::Node(t);  

         currentHead->pNext = newNode; // Assing currenthead next to new node

         // Assign currenthead prev to currentHead
         newNode->pPrev = currentHead;

         // Update Tail
         pTail = newNode;

         // Update Pointers
         currentHead = currentHead->pNext;
      }

      // Assign Null pointers
      pHead->pPrev = pTail->pNext = nullptr;
   }

   numElements = num;
}

/*****************************************
 * LIST :: ITERATOR constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
template <class Iterator>
list <T> ::list(Iterator first, Iterator last)
{
   if(first)
   {
      int count = 0;

      // Çreate a Head Node
      Node * headNode = new list::Node();
      pHead = pTail = headNode;
          
      for(auto it = first; it != last-2; ++it)
      {
         headNode->data = *it;
         count++;
      }

      Node * currentHead = headNode;   // Keep Track of Current Head
        
      // Loop Over Remaining Value
      for(auto it = first + 1; it != last; ++it)
      {
         Node *newNode = new list::Node();   // Create New Node
            
         newNode->data = *it;  // Assign Value to newNode
            
         // Update the Pointers
         currentHead->pNext = newNode;
         newNode->pPrev = currentHead;
            
         // Update the Tail and currentHead
         currentHead = pTail = newNode;
            
         count++;
      }
        
      // Point next and previous to NULL
      pHead->pPrev = pTail->pNext = nullptr;
        
      numElements = count;
   }
   else
   {
      pHead = pTail = nullptr;
      numElements = 0;
   }
}

/*****************************************
 * LIST :: INITIALIZER constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
list <T> ::list(const std::initializer_list<T>& il)
{
   if(il.size())
   {
      // Create a Head Node
      Node * headNode = new list::Node();
      pHead = pTail = headNode;
        
      // Assign Value to First Node
      for(auto it = il.begin(); it!= il.end()-2 ; ++it)
         headNode->data = *it;


      Node * currentHead = headNode;
        
      // Loop Over Remaining Value
      for(auto it = il.begin() + 1; it != il.end(); ++it)
      {
         // Create New Node
         Node *newNode = new list::Node();
            
         // Assign Value to newNode
         newNode->data = *it;
            
         // Update the Pointers
         currentHead->pNext = newNode;
         newNode->pPrev = currentHead;
            
         // Update the Tail and currentHead
         pTail = newNode;
         currentHead = newNode;
            
      }
        
      // Point next and previous to NULL
      pHead->pPrev = nullptr;
      pTail->pNext = nullptr;
        
   }
     
   // Change the numElements
   numElements = il.size();
}

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
template <typename T>
list <T> ::list(size_t num)
{
   // Check if size was less than Zero
   if(num <= 0)
   {
      pHead = pTail = nullptr;
   } 
   else 
   {
      // Create a New Node
      pHead = pTail = new list::Node();

      // Current Head
      Node *currentHead = pHead;

      for (size_t it = 0; (it != num - 1) && currentHead; it++)
      {
         // Create a Node
         Node* newNode = new list::Node(0);

         // Assign Currenthead next to new Node
         currentHead->pNext = newNode;
         newNode->pPrev = currentHead;

         // Update the Tail
         pTail = newNode;

         // Update the Head
         currentHead = currentHead->pNext;
      }

      // Assign to Null Pointers
      pHead->pPrev = pTail->pNext = nullptr;
   }
    
   numElements = num;
}

/*****************************************
 * LIST :: DEFAULT constructors
 ****************************************/
template <typename T>
list <T> ::list():numElements(0), pHead(nullptr), pTail(nullptr)
{
   pHead = pTail = nullptr;
   numElements = 0;
}

/*****************************************
 * LIST :: COPY constructors
 ****************************************/
template <typename T>
list <T> ::list(list& rhs) :pHead(nullptr), pTail(nullptr), numElements(0)
{
   if(!rhs.pHead)
      this->pHead = nullptr;
   else
      *this = rhs;
    
   numElements = rhs.numElements;
}

/*****************************************
 * LIST :: MOVE constructors
 * Steal the values from the RHS
 ****************************************/
template <typename T>
list <T> ::list(list <T>&& rhs): numElements(0), pHead(nullptr), pTail(nullptr)
{
   pHead = rhs.pHead;
   pTail = rhs.pTail;
    
   rhs.pHead = rhs.pTail = nullptr;
    
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
template <typename T>
list <T>& list <T> :: operator = (list <T> && rhs)
{
   pHead = rhs.pHead;
   pTail = rhs.pTail;

   rhs.pHead  = rhs.pTail = nullptr;
    
   numElements = rhs.numElements;
   rhs.numElements = 0;

   return *this;
}

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
list <T> & list <T> :: operator = (list <T> & rhs)
{

   if (!rhs.pHead && !pHead)
   {
      return *this;
   }
   if (!rhs.pHead)
   {
      pHead = pTail = nullptr;
      numElements = 0;
      return *this;
   }

   pHead = new list::Node(rhs.pHead->data);
   pTail = pHead;
       
   Node *currentHeadRhs = rhs.pHead->pNext;
   Node *currentHead = pHead;
       
   for (;currentHeadRhs != 0; currentHeadRhs = currentHeadRhs->pNext)
   {
      Node* newNode = new list::Node(currentHeadRhs->data);

      currentHead->pNext = newNode;
      newNode->pPrev = currentHead;

      pTail = newNode;
      currentHead = currentHead->pNext;          
   }


       
   pHead->pPrev = pTail->pNext = nullptr;
   numElements = rhs.numElements;
    
   return *this;
}

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
list <T>& list <T> :: operator = (const std::initializer_list<T>& rhs)
{
   if(rhs.begin())
   {
      if(numElements == rhs.size())
      {
         Node *currentHead = pHead;

         for(auto it = rhs.begin(); it != rhs.end(); ++it)
         {
            currentHead->data = *it;
            currentHead = currentHead->pNext;
         }
      }
        
   else
   {  
      Node *currentHead = pHead;
      this->clear();

      for(auto it = rhs.begin(); it != rhs.end(); ++it)
      {
         Node* newNode = new list::Node(*it);
                
         if(!pHead)
         {
            pHead = newNode;
            currentHead = pTail = pHead;
         }
         else
         {
            currentHead->pNext = newNode;
            newNode->pPrev = currentHead;

            pTail = newNode;
            currentHead = currentHead->pNext;
         }
      }
      numElements = rhs.size();
   }
        
   }
   else
   {
      pHead = pTail = nullptr;
   }
 
   return *this;
}

/**********************************************
 * LIST :: CLEAR
 * Remove all the items currently in the linked list
 *     INPUT  :
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
void list <T> :: clear()
{
   pHead = pTail = nullptr;
   numElements = 0;
}

/*********************************************
 * LIST :: PUSH BACK
 * add an item to the end of the list
 *    INPUT  : data to be added to the list
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> :: push_back(const T & data)
{
   Node *newNode= new list:: Node(data);

   if(!pHead)
   {
      pHead = pTail = newNode;
   }
   else
   {
      pTail->pNext = newNode;
      newNode->pPrev = pTail;

      pTail = newNode;
      pTail->pNext = nullptr;
   }

   numElements++;
}

template <typename T>
void list <T> ::push_back(T && data)
{
   Node *newNode= new list:: Node(data);

   if(!pHead)
   {
      pTail = pHead = newNode;;
   }
   else
   {
      pTail->pNext = newNode;
      newNode->pPrev = pTail;

      pTail = newNode;
      pTail->pNext = nullptr;
   }
 
   numElements++;
}

/*********************************************
 * LIST :: PUSH FRONT
 * add an item to the head of the list
 *     INPUT  : data to be added to the list
 *     OUTPUT :
 *     COST   : O(1)
 *********************************************/
template <typename T>
void list <T> :: push_front(const T & data)
{
   Node * newNode = new list:: Node(data);
    
   if(!pHead)
   {
      pTail = pHead = newNode;;
   }
   else
   {
      newNode->pNext = pHead;
      pHead->pPrev = newNode;

      pHead = newNode;
      pHead->pPrev = nullptr;
   }
    
   numElements++;
}

template <typename T>
void list <T> ::push_front(T && data)
{
   Node * newNode = new list:: Node(data);
    
   if(!pHead)
   {
      pHead = pTail = newNode;
   }
   else
   {
      newNode->pNext = pHead;
      pHead->pPrev = newNode;

      pHead = newNode;
      pHead->pPrev = nullptr;
   }
    
   numElements++;
}


/*********************************************
 * LIST :: POP BACK
 * remove an item from the end of the list
 *    INPUT  : 
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> ::pop_back()
{
   if(pTail)
   {
      Node *nodeToDelte = pTail;
      pTail = pTail->pPrev;
           
      pTail->pNext = nullptr;
    
      delete nodeToDelte;
      numElements--;
   }
}

/*********************************************
 * LIST :: POP FRONT
 * remove an item from the front of the list
 *    INPUT  :
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> ::pop_front()
{
   if(pHead)
   {
      Node *nodeToDelete = pHead;
        
      pHead = pHead->pNext;
      pHead->pPrev = nullptr;
        
      delete nodeToDelete;
      numElements--;
   }
   else
   {
      pHead = pTail = nullptr;
      numElements = 0;
   }
}

/*********************************************
 * LIST :: FRONT
 * retrieves the first element in the list
 *     INPUT  : 
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
template <typename T>
T & list <T> :: front()
{
   if (pHead)
      return pHead->data;
   else
      throw("ERROR: unable to access data from an empty list");
}

/*********************************************
 * LIST :: BACK
 * retrieves the last element in the list
 *     INPUT  : 
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
template <typename T>
T & list <T> :: back()
{
   if (pTail)
      return pTail->data;
   else
      throw("ERROR: unable to access data from an empty list");
}

/******************************************
 * LIST :: REMOVE
 * remove an item from the middle of the list
 *     INPUT  : an iterator to the item being removed
 *     OUTPUT : iterator to the new location 
 *     COST   : O(1)
 ******************************************/
template <typename T>
typename list <T> :: iterator  list <T> :: erase(const list <T> :: iterator & it)
{
   if (empty())
   {
      return nullptr;
   }
   else
   {
      Node* tempNode = it.p->pNext;

      if (it.p->pNext)
      {
         it.p->pNext->pPrev = it.p->pPrev;
         tempNode = it.p->pNext;
      }
      else
      {
         pTail = pTail->pPrev;
      }


      if (it.p->pPrev)
      {
         it.p->pPrev->pNext = it.p->pNext;
      }
      else
      {
         pHead = pHead->pNext;
      }


      delete it.p;
      numElements--;
      return tempNode;
   }
}

/******************************************
 * LIST :: INSERT
 * add an item to the middle of the list
 *     INPUT  : data to be added to the list
 *              an iterator to the location where it is to be inserted
 *     OUTPUT : iterator to the new item
 *     COST   : O(1)
 ******************************************/
template <typename T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator it, const T & data) 
{
   if (empty())
   {
      Node* pNew = new Node(data); // create new node.
      pHead = pTail = pNew; // because the lsit is empty, this node is both the head andd tail.
      
      numElements++; // it is the only element in the node list.
      return begin();
   }
   else if (it == end())
   {
      Node* pNew = new Node(data);
       
      pTail->pNext = pNew; 
      pNew->pPrev = pTail; 

      pTail = pNew;

      numElements++;
      return iterator(pNew);
   }
   else if (it == begin())
   {
      Node* pNew = new Node(data);
      pNew->pNext = pHead;

      pHead = pNew;

      pHead->pNext->pPrev = pHead;;

      numElements++;
      return pNew;
   }
   else
   {
      Node* pNew = new Node(data);

      pNew->pPrev = it.p->pPrev;
      pNew->pNext = it.p;
       
      if (pNew->pPrev)
         pNew->pPrev->pNext = pNew;
      else
         pHead = pNew;


      if (pNew->pNext)
         pNew->pNext->pPrev = pNew;
      else
         pTail = pNew;


      numElements++;
      return pNew;
   }
}

template <typename T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator it,
   T && data)
{
   // This is called If the list is empty
   if (empty())
   {
      Node* pNew = new Node(data); // create new node.
      pHead = pTail = pNew; // because the lsit is empty, this node is both the head andd tail.

      numElements++; // it is the only element in the node list.
      return begin();
   }
   else if (it == end())
   {
      Node* pNew = new Node(data);

      pTail->pNext = pNew; 
      pNew->pPrev = pTail; 

      pTail = pNew;

      numElements++;
      return iterator(pNew);
   }
   else if (it == begin())
   {
      Node* pNew = new Node(data);  // Create  The New Node
      pNew->pNext = pHead; // Set the Next node for the New node to be the OLD head.

      pHead = pNew;  // Set the OLD Head to be the new node
      pHead->pNext->pPrev = pHead;

      numElements++;
      return pNew;
   }
   else
   {
      Node* pNew = new Node(data);

      pNew->pPrev = it.p->pPrev;
      pNew->pNext = it.p;

      if (pNew->pPrev)
         pNew->pPrev->pNext = pNew;
      else
         pHead = pNew;


      if (pNew->pNext)
         pNew->pNext->pPrev = pNew;
      else
         pTail = pNew;


      numElements++;
      return pNew;
   }
}

/**********************************************
 * LIST :: assignment operator - MOVE
 * Copy one list onto another
 *     INPUT  : a list to be moved
 *     OUTPUT :
 *     COST   : O(n) with respect to the size of the LHS
 *********************************************/
template <typename T>
void swap(list <T> & lhs, list <T> & rhs)
{
   // Swap Head
   std::swap(lhs.pHead, rhs.pHead);
   
   // Swap Tail
   std:: swap(lhs.pTail, rhs.pTail);
   
   // Swap numElements
   std:: swap(lhs.numElements, rhs.numElements);
}


//#endif
}; // namespace custom
