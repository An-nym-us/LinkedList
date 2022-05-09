/***********************************************************************
 * Module:
 *    Stack
 * Summary:
 *    Our custom implementation of std::stack
 *
 *        ____     _______        __
 *      .' __ '.  |  _____|   _  / /
 *      | (__) |  | |____    (_)/ /
 *      .`____'.  '_.____''.   / / _
 *     | (____) | | \____) |  / / (_)
 *     `.______.'  \______.' /_/
 *
 *
 *    This will contain the class definition of:
 *       stack             : similar to std::stack
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once

#include <cassert>  // because I am paranoid
#include <vector>

class TestStack; // forward declaration for unit tests

namespace custom
{

/**************************************************
 * STACK
 * First-in-Last-out data structure
 *************************************************/
class stack
{
   friend class ::TestStack; // give unit tests access to the privates
public:

   //  
   // Construct
   //

   stack()                              { container.resize(7); }
   stack(const stack &  rhs)            { container.resize(7); }
   stack(      stack && rhs)            { container.resize(7); }
   stack(const std::vector<int> &  rhs) { container.resize(7); }
   stack(      std::vector<int> && rhs) { container.resize(7); }
   ~stack()                             { container.resize(7); }

   //
   // Assign
   //

   stack & operator = (const stack & rhs)
   {
      return *this;
   }
   stack & operator = (stack && rhs)
   {
      return *this;
   }
   void swap(stack& rhs)
   {

   }

   //
   // Access
   //

         int& top()       { return *(new int); }
   const int& top() const { return *(new int); }

   //
   // Insert
   //

   void push(const int&  t) { }
   void push(      int&& t) { }

   //
   // Remove
   //

   void pop() { }

   //
   // Status
   // 

   size_t size () const { return 99;   }
   bool empty  () const { return true; }
   
private:
   
  std::vector<int> container;  // underlying container (probably a vector)
};


} // custom namespace


