/* 
   SimuFaith
   Copyright (C) DNTeam <simufaith@dnteam.org>

   This file is part of SimuFaith.

   SimuFaith is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   SimuFaith is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with SimuFaith.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _simufaith_test_test_case_h
#define _simufaith_test_test_case_h

#include <kobold/list.h>
#include <kobold/kstring.h>
#include <exception>

namespace SimuFaithTests
{

   /*! The exception that should be called on an test assertion fails */
   class AssertionException : public std::exception
   {
      public:
         virtual const char* what() const throw();
   };

   /*! A simple test suite, defined by a list of test cases to run on a single
    * scenario. */
   class TestSuite
   {
      public:

         /*! A simple test case definition. */
         class TestCase : public Kobold::ListElement
         {
            public:
               /*! Constructor */ 
               TestCase();

               /*! Destructor */
               virtual ~TestCase();

               /*! Run the specific test case. 
                * \param suite pointer to the TestSuite used. */
               virtual void run(TestSuite* suite) throw() = 0;

               /*! Called before each TestCase run */
               virtual void doBeforeTest() = 0;

               /*! Called after a TestCase run (both on success or failure) */
               virtual void doAfterTest() = 0;

            protected:
               /*! Assert that a expression is true, throwing an exception 
                * if not.
                * \param expr to check. */
               void assertTrue(bool expr) throw(AssertionException);
               /*! Assert that a pointer is NULL, throwing an exception if not.
                * \param ptr pointer to check if NULL. */
               void assertNULL(void* ptr) throw(AssertionException);
         };

         /*! Constructor */
         TestSuite();

         /*! Destructor */
         virtual ~TestSuite();

         /*! Run the test suite, aborting on first failure. */
         void run();

      protected:

         /*! Get the list with all TestCases to run.
          * \note the caller is responsible of list dealocation on its 
          *       destructor. */
         virtual Kobold::List* getTests() = 0;


         /*! Called to create the common scenario of all tests on the suite */
         virtual void doCreateScenario() = 0;

         /*! Called after done with the test (both on success or failure),
          * to finish with the created scenario */
         virtual void doFinishScenario() = 0;

      private:
         Kobold::List* tests; /**< The tests list */
   };

}

#endif

