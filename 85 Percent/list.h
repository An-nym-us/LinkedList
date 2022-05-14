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

   bool empty()  const { return numElements == 0; }
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
      data= 0;
      pNext = pPrev = nullptr;
   }
   Node(const int & data)
   {

         this->data = data;
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
       this -> p = rhs.p;
      return *this;
   }
   
   // equals, not equals operator
    bool operator == (const iterator & rhs) const { return rhs.p == this->p; }
    bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   
   // dereference operator, fetch a node
   int & operator * ()
   {
       return p->data;
   }
   
   // postfix increment it++
   iterator operator ++ (int postfix)
   {
      iterator itOld = *this;
      p = p->pNext;
      return itOld;
   }
   
   // prefix increment ++it
   iterator & operator ++ ()
   {
      p = p->pNext;
      return *this;
   }
   
   // postfix decrement it--
   iterator operator -- (int postfix)
   {
       iterator tmp(*this);
       p= p-> pPrev;
      return tmp;
  
   }
   
   // prefix decrement --it
   iterator & operator -- ()
   {
       p = p->pPrev;
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
       while (count!= num-1 && currentHead)
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
        pHead =pTail = new list::Node();

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
inline list::list() :numElements(0), pHead(nullptr), pTail(nullptr) 
{
   pHead = nullptr;
   pTail = nullptr;
   numElements = 0;


}

/*****************************************
 * LIST :: COPY constructor
 ****************************************/
inline list::list(list& rhs): pHead(nullptr), numElements(0), pTail(nullptr)
{
//      if(rhs.pHead)
//      {
//          pHead = pTail = new list::Node(rhs.pHead->data);
//          Node * currentRhsHead = rhs.pHead-> pNext;
//
//          Node * currentHead = pHead;
//
//          while(currentRhsHead != NULL)
//          {
//              Node * newNode = new list::Node(currentRhsHead->data);
//              currentHead->pNext = newNode;
//              newNode->pPrev = currentHead;
//
//              pTail = newNode;
//
//            currentRhsHead = currentRhsHead -> pNext;
//            currentHead = currentHead -> pNext;
//          }
//
//          pHead->pPrev = nullptr;
//          pTail->pNext = nullptr;
//      }
   //*this = rhs;

  
   this->pTail = rhs.pTail;
   if (rhs.pHead == nullptr)
   {
      this->pHead = nullptr;;
   }
   else
   {
      *this = rhs;
   }
   
   this->numElements = rhs.numElements;

    
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
      auto it = il.begin();
      for(++it; it != il.end(); ++it)
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
    
    
    for(auto it= first+1; it!= last-2; ++it)
    {


          headNode->data = *it;
       

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
inline list ::list(list && rhs): numElements(0), pHead(nullptr), pTail(nullptr)
{

//    if(rhs.pHead)
//    {
//
//        pHead = pTail = new list::Node(rhs.pHead->data);
//        Node * currentRhsHead = rhs.pHead-> pNext;
//
//        Node * currentHead = pHead;
//
//        while(currentRhsHead != NULL)
//        {
//            Node * newNode = new list::Node(currentRhsHead->data);
//            currentHead->pNext = newNode;
//            newNode->pPrev = currentHead;
//
//            pTail = newNode;
//
//          currentRhsHead = currentRhsHead -> pNext;
//          currentHead = currentHead -> pNext;
//        }
//
//        pHead->pPrev = nullptr;
//        pTail->pNext = nullptr;
//
//    }
//
//    rhs.pHead = nullptr;
//    rhs.pTail = nullptr;
//
//
//    numElements = rhs.numElements;
//    rhs.numElements = 0;



   *this = std::move(rhs);
   
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
   if (!rhs.pHead && !pHead)
   {
      return *this;
   }
   if (!rhs.pHead)
   {
      pHead = nullptr;
      pTail = nullptr;
      numElements = 0;
      return *this;
   }


    pHead = new list::Node(rhs.pHead->data);
    pTail = pHead;
    
    Node *currentHeadRhs = rhs.pHead->pNext;
    Node *currentHead = pHead;
    
    while(currentHeadRhs!= NULL)
    {
        Node * newNode = new list::Node(currentHeadRhs->data);
        
        currentHead->pNext = newNode;
        newNode->pPrev = currentHead;
        
        pTail= newNode;
        currentHeadRhs = currentHeadRhs->pNext;
        currentHead = currentHead->pNext;
    }
    
    pHead->pPrev =nullptr;
    pTail->pNext = nullptr;
    
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
inline list & list :: operator = (const std::initializer_list<int>& rhs)
{
    if(rhs.size())
    {
        // Çreate a Head Node
        Node * headNode = new list::Node();
        pHead = pTail = headNode;
        
        // Assign Value to First Node
        for(auto it = rhs.begin(); it!= rhs.end()-2 ; ++it)
        {
 //           std::cout << *it<< std::endl;
            headNode-> data = *it;
        }
        // Keep Track of Current Head
        Node * currentHead = headNode;
        
        // Loop Over Remaining Value
        for(auto it=rhs.begin()+1; it!= rhs.end(); ++it)
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
     numElements = rhs.size();
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
   pHead = nullptr;
   pTail = nullptr;
   numElements = 0;
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
    Node *newNode= new list:: Node(data);
    if(pHead == nullptr)
    {
        pHead = newNode;
        pTail = pHead;
    }
    else
    {
        pTail->pNext = newNode;
        newNode-> pPrev = pTail;
        pTail = newNode;
        pTail->pNext = nullptr;
    }
     numElements++;
}

inline void list ::push_back(int && data)
{
    Node *newNode= new list:: Node(data);
    if(pHead == nullptr)
    {
        pHead = newNode;
        pTail = pHead;
    }
    else
    {
        pTail->pNext = newNode;
        newNode-> pPrev = pTail;
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
inline void list :: push_front(const int & data)
{
    Node * newNode = new list:: Node(data);
    
    if(pHead == nullptr)
    {
        pHead = newNode;
        pTail = pHead;
    }
    else
    {
        newNode-> pNext = pHead;
        pHead ->pPrev = newNode;
        pHead = newNode;
        
        pHead-> pPrev = nullptr;
    }
    
    numElements++;


    
}

inline void list ::push_front(int && data)
{
    Node * newNode = new list:: Node(data);
    
    if(pHead == nullptr)
    {
        pHead = newNode;
        pTail = pHead;
    }
    else
    {
        newNode-> pNext = pHead;
        pHead ->pPrev = newNode;
        pHead = newNode;
        
        pHead-> pPrev = nullptr;
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
inline void list ::pop_back()
{
    if(pTail)
    {
        Node *nodeToDelte = pTail;
        pTail = pTail-> pPrev;
        
   
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
inline void list ::pop_front()
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
       pHead = nullptr;
       pTail = nullptr;
       numElements =0;
    }

   // std::cout << "Im called" << std::endl;
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
   if (pHead)
   {
      return pHead->data;
   }
   else
   {
      throw("ERROR: unable to access data from an empty list");
   }

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
    if (pTail)
    {
       return pTail->data;
    }
    else
    {
       throw("ERROR: unable to access data from an empty list");
    }
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
   if (it.p)
   {
      return nullptr;
   }
   
   if (it == begin())
   {

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
inline typename list :: iterator list :: insert(list :: iterator it,
                                                const int & data)
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
      
      pTail->pNext = pNew; // 
      pNew->pPrev = pTail; // 

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
      {
         pNew->pPrev->pNext = pNew;
      }
      else
      {
         pHead = pNew;
      }


      if (pNew->pNext)
      {
         pNew->pNext->pPrev = pNew;
      }
      else
      {
         pTail = pNew;
      }


      numElements++;
      return pNew;
   }



}

inline typename list ::iterator list  ::insert(list ::iterator it,
                                               int && data)
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

      pTail->pNext = pNew; // 
      pNew->pPrev = pTail; // 

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
      {
         pNew->pPrev->pNext = pNew;
      }
      else
      {
         pHead = pNew;
      }


      if (pNew->pNext)
      {
         pNew->pNext->pPrev = pNew;
      }
      else
      {
         pTail = pNew;
      }


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
void swap(list & lhs, list & rhs)
{
    // Swap Head
   std::swap(lhs.pHead, rhs.pHead);
   
   // Swap Tail
   std:: swap(lhs.pTail, rhs.pTail);
   
   // Swap numElements
   std:: swap(lhs.numElements, rhs.numElements);
   
   
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
    

   return iterator(pHead);
   
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
   
   //for (auto it = begin(); it != end(); ++it)
   //{
   //   return (it.p->pNext);;
   //}




   return iterator(nullptr);
}


}; // namespace custom
