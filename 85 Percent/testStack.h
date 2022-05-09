/***********************************************************************
 * Header:
 *    TEST STACK
 * Summary:
 *    Unit tests for stack
 * Author
 *    Br. Helfrich
 ************************************************************************/

#pragma once

#ifdef DEBUG
#include "stack.h"
#include "unitTest.h"

#include <iostream>
#include <cassert>
#include <memory>

#include <stack>
#include <vector>
#include <list>



class TestStack : public UnitTest
{
public:
   void run()
   {
      reset();

      // Construct
      test_construct_default();
      test_constructCopy_empty();
      test_constructCopy_standard();
      test_constructCopy_partiallyFilled();
      test_constructMove_empty();
      test_constructMove_standard();
      test_constructMove_partiallyFilled();
      test_constructInit_empty();
      test_constructInit_standard();
      test_constructInit_emptySTD();
      test_constructInit_standardSTD();
      test_constructInitMove_empty();
      test_constructInitMove_standard();
      test_constructInitMove_emptySTD();
      test_constructInitMove_standardSTD();

      // Assign
      test_assignCopy_emptyToEmpty();
      test_assignCopy_emptyToFull();
      test_assignCopy_fullToEmpty();
      test_assignCopy_fullToFull();
      test_assignMove_emptyToEmpty();
      test_assignMove_emptyToFull();
      test_assignMove_fullToEmpty();
      test_assignMove_fullToFull();
      test_swap_emptyToEmpty();
      test_swap_emptyToFull();
      test_swap_fullToEmpty();

      // Access
      test_top_readOne();
      test_top_readStandard();
      test_top_writeOne();
      test_top_writeStandard();

      // Insert
      test_pushCopy_empty();
      test_pushCopy_standard();
      test_pushCopy_standardList();
      test_pushMove_empty();
      test_pushMove_standard();
      test_pushMove_standardList();

      // Remove


      /* place your pop unit tests here */

      

      // Status
      test_size_empty();
      test_size_standard();
      test_empty_empty();
      test_empty_standard();

      report("Stack");
   }
   
   /***************************************
    * CONSTRUCTOR - Default
    ***************************************/
   
   // default constructor, no allocations
   void test_construct_default()
   {  // setup
      // exercise
      custom::stack s;
      // verify
      assertEmptyFixture(s);
      // teardown
      teardownStandardFixture(s);
   } 


   /***************************************
    * COPY CONSTRUCTOR
    ***************************************/

    // copy constructor of an empty stack
   void test_constructCopy_empty()
   {  // setup
      custom::stack sSrc;
      // exercise
      custom::stack sDest(sSrc);
      // verify
      assertEmptyFixture(sSrc);
      assertEmptyFixture(sDest);
   }  // teardown

   // copy constructor of a 4-element collection
   void test_constructCopy_standard()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack sSrc;
      setupStandardFixture(sSrc);
      // exercise
      custom::stack sDest(sSrc);
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(sSrc);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(sDest);
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDest);
   }

   // copy constructor of a 2-element, 4-capacity collection
   void test_constructCopy_partiallyFilled()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 |    |    |
      //    +----+----+----+----+
      custom::stack sSrc;
      sSrc.container.reserve(4);
      sSrc.container.push_back(int(26));
      sSrc.container.push_back(int(49));
      // exercise
      custom::stack sDest(sSrc);
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 |    |    |
      //    +----+----+----+----+
      assertUnit(sSrc.container[0] == int(26));
      assertUnit(sSrc.container[1] == int(49));
      assertUnit(sSrc.container.size() == 2);
      assertUnit(sSrc.container.capacity() == 4);
      //      0    1
      //    +----+----+
      //    | 26 | 49 |
      //    +----+----+
      assertUnit(sDest.container[0] == int(26));
      assertUnit(sDest.container[1] == int(49));
      assertUnit(sDest.container.size() == 2);
      assertUnit(sDest.container.capacity() == 2);
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDest);
   }


   /***************************************
    * MOVE CONSTRUCTOR
    ***************************************/

    // move constructor of an empty stack
   void test_constructMove_empty()
   {  // setup
      custom::stack sSrc;
      // exercise
      custom::stack sDest(std::move(sSrc));
      // verify
      assertEmptyFixture(sSrc);
      assertEmptyFixture(sDest);
   }  // teardown

   // move constructor of a 4-element collection
   void test_constructMove_standard()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack sSrc;
      setupStandardFixture(sSrc);
      // exercise
      custom::stack sDest(std::move(sSrc));
      // verify      // verify
      assertEmptyFixture(sSrc);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(sDest);
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDest);
   }

   // move constructor of a 2-element, 4-capacity collection
   void test_constructMove_partiallyFilled()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 |    |    |
      //    +----+----+----+----+
      custom::stack sSrc;
      sSrc.container.reserve(4);
      sSrc.container.push_back(int(26));
      sSrc.container.push_back(int(49));
      // exercise
      custom::stack sDest(std::move(sSrc));
      // verify
      assertEmptyFixture(sSrc);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 |    |    |
      //    +----+----+----+----+
      assertUnit(sDest.container[0] == int(26));
      assertUnit(sDest.container[1] == int(49));
      assertUnit(sDest.container.size() == 2);
      assertUnit(sDest.container.capacity() == 4);
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDest);
   }

   /***************************************
    * INITIALIZE CONSTRUCTOR
    ***************************************/

    // initialize constructor of an empty stack
   void test_constructInit_empty()
   {  // setup
      std::vector<int> vSrc;
      // exercise
      custom::stack sDest(vSrc);
      // verify
      assertUnit(vSrc.empty() == true);
      assertEmptyFixture(sDest);
   }  // teardown

   // move constructor of a 4-element collection
   void test_constructInit_standard()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      std::vector<int> vSrc{int(26), int(49), int(67), int(89)};
      // exercise
      custom::stack sDest(vSrc);
      // verify      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertUnit(vSrc.size() == 4);
      assertUnit(vSrc.capacity() == 4);
      if (vSrc.size() == 4)
      {
         assertUnit(vSrc[0] == int(26));
         assertUnit(vSrc[1] == int(49));
         assertUnit(vSrc[2] == int(67));
         assertUnit(vSrc[3] == int(89));
      }
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(sDest);
      // teardown
      teardownStandardFixture(sDest);
   }

   // initialize constructor of an empty stack
   void test_constructInit_emptySTD()
   {  // setup
      std::vector<int> vSrc;
      // exercise
      custom::stack sDest(vSrc);
      // verify
      assertUnit(vSrc.empty() == true);
      assertUnit(sDest.container.size() == 0);
      assertUnit(sDest.container.capacity() == 0);
      assertUnit(vSrc.size() == 0);
      assertUnit(vSrc.capacity() == 0);
   }  // teardown

   // move constructor of a 4-element collection
   void test_constructInit_standardSTD()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      std::vector<int> vSrc{ int(26), int(49), int(67), int(89) };
      // exercise
      custom::stack sDest(vSrc);
      // verify      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertUnit(vSrc.size() == 4);
      assertUnit(vSrc.capacity() == 4);
      if (vSrc.size() == 4)
      {
         assertUnit(vSrc[0] == int(26));
         assertUnit(vSrc[1] == int(49));
         assertUnit(vSrc[2] == int(67));
         assertUnit(vSrc[3] == int(89));
      }
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertUnit(sDest.container.size() == 4);
      assertUnit(sDest.container.capacity() == 4);
      if (sDest.container.size() == 4)
      {
         assertUnit(sDest.container[0] == int(26));
         assertUnit(sDest.container[1] == int(49));
         assertUnit(sDest.container[2] == int(67));
         assertUnit(sDest.container[3] == int(89));
      }
      // teardown
      sDest.container.clear();
   }

   /***************************************
    * INITIALIZE CONSTRUCTOR
    ***************************************/

    // initialize constructor of an empty stack
   void test_constructInitMove_empty()
   {  // setup
      std::vector<int> vSrc;
      // exercise
      custom::stack sDest(std::move(vSrc));
      // verify
      assertUnit(vSrc.empty() == true);
      assertEmptyFixture(sDest);
   }  // teardown

   // move constructor of a 4-element collection
   void test_constructInitMove_standard()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      std::vector<int> vSrc{ int(26), int(49), int(67), int(89) };
      // exercise
      custom::stack sDest(std::move(vSrc));
      // verify      // verify
      assertUnit(vSrc.size() == 0);
      assertUnit(vSrc.capacity() == 0);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(sDest);
      // teardown
      teardownStandardFixture(sDest);
   }

   // initialize constructor of an empty stack
   void test_constructInitMove_emptySTD()
   {  // setup
      std::vector<int> vSrc;
      // exercise
      custom::stack sDest(std::move(vSrc));
      // verify
      assertUnit(vSrc.empty() == true);
      assertUnit(sDest.container.size() == 0);
      assertUnit(sDest.container.capacity() == 0);
      assertUnit(vSrc.size() == 0);
      assertUnit(vSrc.capacity() == 0);
   }  // teardown

   // move constructor of a 4-element collection
   void test_constructInitMove_standardSTD()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      std::vector<int> vSrc{ int(26), int(49), int(67), int(89) };
      // exercise
      custom::stack sDest(std::move(vSrc));
      // verify
      assertUnit(vSrc.size() == 0);
      assertUnit(vSrc.capacity() == 0);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertUnit(sDest.container.size() == 4);
      assertUnit(sDest.container.capacity() == 4);
      if (sDest.container.size() == 4)
      {
         assertUnit(sDest.container[0] == int(26));
         assertUnit(sDest.container[1] == int(49));
         assertUnit(sDest.container[2] == int(67));
         assertUnit(sDest.container[3] == int(89));
      }
      // teardown
      sDest.container.clear();
   }

   /***************************************
    * ASSIGN COPY
    ***************************************/

 // copy an empty stack to an empty stack
   void test_assignCopy_emptyToEmpty()
   {  // Setup
      custom::stack sSrc;
      custom::stack sDes;
      // exercise
      sDes = sSrc;
      // verify
      assertEmptyFixture(sSrc);
      assertEmptyFixture(sDes);
   }  // teardown

   // copy an empty stack onto a full one
   void test_assignCopy_emptyToFull()
   {  // Setup
      custom::stack sSrc;
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack sDes;
      setupStandardFixture(sDes);
      // exercise
      sDes = sSrc;
      // verify
      assertEmptyFixture(sSrc);
      assertUnit(sDes.container.empty());
      assertUnit(sDes.container.size() == 0);
      assertUnit(sDes.container.capacity() == 4);
      // teardown
      teardownStandardFixture(sDes);
   }

   // copy a full stack onto an empty one
   void test_assignCopy_fullToEmpty()
   {  // Setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack sSrc;
      setupStandardFixture(sSrc);
      custom::stack sDes;
      // exercise
      sDes = sSrc;
      // verify
      assertStandardFixture(sSrc);
      assertStandardFixture(sDes);
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDes);
   }  // teardown

   // copy a full stack onto one that is not empty
   void test_assignCopy_fullToFull()
   {  // Setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack sSrc;
      setupStandardFixture(sSrc);
      //    +----+----+----+----+
      //    | 11 | 99 |    |    |
      //    +----+----+----+----+
      custom::stack sDes;
      sDes.container.reserve(4);
      sDes.container.push_back(11);
      sDes.container.push_back(99);
      // exercise
      sDes = sSrc;
      // verify
      assertStandardFixture(sSrc);
      assertStandardFixture(sDes);
      // teardown
      teardownStandardFixture(sSrc);
      teardownStandardFixture(sDes);
   }

   /***************************************
    * ASSIGN MOVE
    ***************************************/

    // copy an empty stack to an empty stack
   void test_assignMove_emptyToEmpty()
   {  // Setup
      custom::stack sSrc;
      custom::stack sDes;
      // exercise
      sDes = std::move(sSrc);
      // verify
      assertEmptyFixture(sSrc);
      assertEmptyFixture(sDes);
   }  // teardown

   // copy an empty stack onto a full one
   void test_assignMove_emptyToFull()
   {  // Setup
      custom::stack sSrc;
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack sDes;
      setupStandardFixture(sDes);
      // exercise
      sDes = std::move(sSrc);
      // verify
      assertEmptyFixture(sSrc);
      assertEmptyFixture(sDes);
   }  // teardown

   // copy a full stack onto an empty one
   void test_assignMove_fullToEmpty()
   {  // Setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack sSrc;
      setupStandardFixture(sSrc);
      custom::stack sDes;
      // exercise
      sDes = std::move(sSrc);
      // verify
      assertEmptyFixture(sSrc);
      assertStandardFixture(sDes);
      // teardown
      teardownStandardFixture(sDes);
   }  // teardown

   // copy a full stack onto one that is not empty
   void test_assignMove_fullToFull()
   {  // Setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack sSrc;
      setupStandardFixture(sSrc);
      //    +----+----+----+----+
      //    | 11 | 99 |    |    |
      //    +----+----+----+----+
      custom::stack sDes;
      sDes.container.reserve(4);
      sDes.container.push_back(11);
      sDes.container.push_back(99);
      // exercise
      sDes = std::move(sSrc);
      // verify
      assertEmptyFixture(sSrc);
      assertStandardFixture(sDes);
      // teardown
      teardownStandardFixture(sDes);
   }

   /***************************************
    * SWAP
    ***************************************/

    // swwap an empty stack to an empty stack
   void test_swap_emptyToEmpty()
   {  // Setup
      custom::stack sSrc;
      custom::stack sDes;
      // exercise
      sDes.swap(sSrc);
      // verify
      assertEmptyFixture(sSrc);
      assertEmptyFixture(sDes);
   }  // teardown

   // swap an empty stack onto a full one
   void test_swap_emptyToFull()
   {  // Setup
      custom::stack sSrc;
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack sDes;
      setupStandardFixture(sDes);
      // exercise
      sDes.swap(sSrc);
      // verify
      assertEmptyFixture(sDes);
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(sSrc);
      // teardown
      teardownStandardFixture(sSrc);
   }  // teardown

   // swap a full stack onto an empty one
   void test_swap_fullToEmpty()
   {  // Setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack sSrc;
      setupStandardFixture(sSrc);
      custom::stack sDes;
      // exercise
      sDes.swap(sSrc);
      // verify
      assertEmptyFixture(sSrc);
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(sDes);
      // teardown
      teardownStandardFixture(sDes);
   }

   // swap a full stack onto one that is not empty
   void test_swap_fullToFull()
   {  // Setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack sSrc;
      setupStandardFixture(sSrc);
      //    +----+----+----+----+
      //    | 11 | 99 |    |    |
      //    +----+----+----+----+
      custom::stack sDes;
      sDes.container.reserve(4);
      sDes.container.push_back(11);
      sDes.container.push_back(99);
      // exercise
      sDes.swap(sSrc);
      // verify
      //    +----+----+----+----+
      //    | 11 | 99 |    |    |
      //    +----+----+----+----+
      assertUnit(sSrc.container.size() == 2);
      assertUnit(sSrc.container.capacity() == 4);
      if (sSrc.container.size() >= 2)
      {
         assertUnit(sSrc.container[0] == 11);
         assertUnit(sSrc.container[1] == 99);
      }
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(sDes);
      // teardown
      teardownStandardFixture(sDes);
   }


   /***************************************
    * SIZE EMPTY CAPACITY
    ***************************************/

   // size of empty stack
   void test_size_empty()
   {  // setup
      custom::stack s;
      // exercise
      size_t size = s.size();
      // verify
      assertUnit(size == 0);
      assertEmptyFixture(s);
   }  // teardown

   // size of standard stack
   void test_size_standard()
   {  // setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack s;
      setupStandardFixture(s);
      // exercise
      size_t size = s.size();
      // verify
      assertUnit(size == 4);
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   } 

   // is an empty stack empty
   void test_empty_empty()
   {  // setup
      custom::stack s;
      // exercise
      bool empty = s.empty();
      // verify
      assertUnit(empty == true);
      assertEmptyFixture(s);
   }  // teardown

   // is a standard stack empty
   void test_empty_standard()
   {  // setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack s;
      setupStandardFixture(s);
      // exercise
      bool empty = s.empty();
      // verify
      assertUnit(empty == false);
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   /***************************************
    * TOP
    ***************************************/

   // read an element from a stack with one element
   void test_top_readOne()
   {  // setup
      //    +----+
      //    | 26 |
      //    +----+
      custom::stack s;
      s.container.push_back(int(26));
      int value(99);
      // exercise
      value = s.top();
      // verify
      //    +----+
      //    | 26 |
      //    +----+
      assertUnit(s.container.size() == 1);
      assertUnit(s.container.capacity() == 1);
      if (s.container.size() == 1)
         assertUnit(s.container[0] == int(26));
      assertUnit(value == int(26));
      // teardown
      teardownStandardFixture(s);
   }

   // read an element from a stack with many elements
   void test_top_readStandard()
   {  // setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack s;
      setupStandardFixture(s);
      int value(99);
      // exercise
      value = s.top();
      // verify
      assertUnit(value == int(89));
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }

   // when there is one element in the stack, write to it
   void test_top_writeOne()
   {  // setup
      //    +----+
      //    | 26 |
      //    +----+
      custom::stack s;
      s.container.push_back(int(26));
      int value(99);
      // exercise
      s.top() = value;
      // verify
      //    +----+
      //    | 99 |
      //    +----+
      assertUnit(s.container.size() == 1);
      assertUnit(s.container.capacity() == 1);
      if (s.container.size() == 1)
         assertUnit(s.container[0] == int(99));
      assertUnit(value == int(99));
      // teardown
      teardownStandardFixture(s);
   }

   // when there are many elements in the stackm write to the top one
   void test_top_writeStandard()
   {  // setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 0  |
      //    +----+----+----+----+
      custom::stack s;
      setupStandardFixture(s);
      s.container[3] = int(0);
      int value(89);
      // exercise
      s.top() = value;
      // verify
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(s);
      // teardown
      teardownStandardFixture(s);
   }


   /***************************************
    * PUSH - COPY
    ***************************************/

    // add an element when the stack is empty
   void test_pushCopy_empty()
   {  // setup
      custom::stack s;
      int value(99);
      // exercise
      s.push(value);
      // verify
      assertUnit(value == int(99));
      //    +----+
      //    | 99 |
      //    +----+
      assertUnit(s.container.size() == 1);
      if (s.container.size() == 1)
         assertUnit(s.container[0] == int(99));
      // teardown
      teardownStandardFixture(s);
   }

   // add an element when there is room. Capacity remains unchanged
   void test_pushCopy_standard()
   {  // setup
      //    +----+----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 |    |    |
      //    +----+----+----+----+----+----+
      custom::stack s;
      setupStandardFixture(s);
      s.container.reserve(6);
      int value(99);
      // exercise
      s.push(value);
      // verify
      assertUnit(value == int(99));
      //    +----+----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 | 99 |    |
      //    +----+----+----+----+----+----+
      assertUnit(s.container.size() == 5);
      if (s.container.size() == 5)
      {
         assertUnit(s.container[0] == int(26));
         assertUnit(s.container[1] == int(49));
         assertUnit(s.container[2] == int(67));
         assertUnit(s.container[3] == int(89));
         assertUnit(s.container[4] == int(99));
      }
      // teardown
      teardownStandardFixture(s);
   }

   // add an element to a std::list stck
   void test_pushCopy_standardList()
   {  // setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack s;
      s.container.push_back(int(26));
      s.container.push_back(int(49));
      s.container.push_back(int(67));
      s.container.push_back(int(89));
      int value(99);
      // exercise
      s.push(value);
      // verify
      assertUnit(value == int(99));
      //    +----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 | 99 |
      //    +----+----+----+----+----+
      assertUnit(s.container.size() == 5);
      if (s.container.size() == 5)
      {
         auto it = s.container.begin();
         assertUnit(*(it++) == int(26));
         assertUnit(*(it++) == int(49));
         assertUnit(*(it++) == int(67));
         assertUnit(*(it++) == int(89));
         assertUnit(*(it++) == int(99));
         assert(it == s.container.end());
      }
      // teardown
      s.container.clear();
   }

   /***************************************
    * PUSH - MOVE
    ***************************************/

    // add an element when the stack is empty
   void test_pushMove_empty()
   {  // setup
      custom::stack s;
      int value(99);
      // exercise
      s.push(std::move(value));
      // verify
      assertUnit(value == 99);
      //    +----+
      //    | 99 |
      //    +----+
      assertUnit(s.container.size() == 1);
      if (s.container.size() == 1)
         assertUnit(s.container[0] == int(99));
      // teardown
      teardownStandardFixture(s);
   }

   // add an element when there is room. Capacity remains unchanged
   void test_pushMove_standard()
   {  // setup
      //    +----+----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 |    |    |
      //    +----+----+----+----+----+----+
      custom::stack s;
      setupStandardFixture(s);
      s.container.reserve(6);
      int value(99);
      // exercise
      s.push(std::move(value));
      // verify
      assertUnit(value == 99);
      //    +----+----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 | 99 |    |
      //    +----+----+----+----+----+----+
      assertUnit(s.container.size() == 5);
      if (s.container.size() == 5)
      {
         assertUnit(s.container[0] == int(26));
         assertUnit(s.container[1] == int(49));
         assertUnit(s.container[2] == int(67));
         assertUnit(s.container[3] == int(89));
         assertUnit(s.container[4] == int(99));
      }
      // teardown
      teardownStandardFixture(s);
   }

   // add an element to a std::list stck
   void test_pushMove_standardList()
   {  // setup
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::stack s;
      s.container.push_back(int(26));
      s.container.push_back(int(49));
      s.container.push_back(int(67));
      s.container.push_back(int(89));
      int value(99);
      // exercise
      s.push(std::move(value));
      // verify
      assertUnit(value == 99);
      //    +----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 | 99 |
      //    +----+----+----+----+----+
      assertUnit(s.container.size() == 5);
      if (s.container.size() == 5)
      {
         auto it = s.container.begin();
         assertUnit(*(it++) == int(26));
         assertUnit(*(it++) == int(49));
         assertUnit(*(it++) == int(67));
         assertUnit(*(it++) == int(89));
         assertUnit(*(it++) == int(99));
         assert(it == s.container.end());
      }
      // teardown
      s.container.clear();
   }

   /***************************************
    * POP
    ***************************************/



   
   /*************************************************************
    * SETUP STANDARD FIXTURE
    *      0    1    2    3
    *    +----+----+----+----+
    *    | 26 | 49 | 67 | 89 |
    *    +----+----+----+----+
    *************************************************************/
   void setupStandardFixture(custom::stack& s)
   {
      s.container.resize(4);
      s.container[0] = int(26);
      s.container[1] = int(49);
      s.container[2] = int(67);
      s.container[3] = int(89);
   }
   
   /*************************************************************
    * TEARDOWN STANDARD FIXTURE
    *      0    1    2    3
    *    +----+----+----+----+
    *    |    |    |    |    |
    *    +----+----+----+----+
    *************************************************************/
   void teardownStandardFixture(custom::stack& s)
   {
      s.container.clear();
   }
   
   /*************************************************************
    * VERIFY EMPTY FIXTURE
    *************************************************************/
   void assertEmptyFixtureParameters(const custom::stack& s, int line, const char* function)
   {
      assertIndirect(s.container.empty());
      assertIndirect(s.container.size() == 0);
      assertIndirect(s.container.capacity() == 0);
   }

   /*************************************************************
    * VERIFY STANDARD FIXTURE
    *      0    1    2    3
    *    +----+----+----+----+
    *    | 26 | 49 | 67 | 89 |
    *    +----+----+----+----+
    *************************************************************/
   void assertStandardFixtureParameters(const custom::stack& s, int line, const char* function)
   {
      assertIndirect(s.container.size() == 4);
      assertIndirect(s.container.capacity() == 4);
      
      if (s.container.size() == 4)
      {
         assertIndirect(s.container[0] == int(26));
         assertIndirect(s.container[1] == int(49));
         assertIndirect(s.container[2] == int(67));
         assertIndirect(s.container[3] == int(89));
      }
   }


};

#endif // DEBUG
