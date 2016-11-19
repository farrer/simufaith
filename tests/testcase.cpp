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

#include "testcase.h"
using namespace SimuFaithTests;

/*************************************************************************
 *                             AssertionException                        *
 *************************************************************************/
const char* AssertionException::what() const throw()
{
   return "Assertion failed!";
}

/*************************************************************************
 *                                TestCase                               *
 *************************************************************************/
TestSuite::TestCase::TestCase()
{
}

/*************************************************************************
 *                               ~TestCase                               *
 *************************************************************************/
TestSuite::TestCase::~TestCase()
{
}

/*************************************************************************
 *                                 assert                                *
 *************************************************************************/
void TestSuite::TestCase::assertTrue(bool expr) throw(AssertionException)
{
   if(!expr)
   {
      throw AssertionException();
   }
}

/*************************************************************************
 *                                 assert                                *
 *************************************************************************/
void TestSuite::TestCase::assertNULL(void* ptr) throw(AssertionException)
{
   if(ptr)
   {
      throw AssertionException();
   }
}

/*************************************************************************
 *                                TestSuite                              *
 *************************************************************************/
TestSuite::TestSuite()
{
}

/*************************************************************************
 *                               ~TestSuite                              *
 *************************************************************************/
TestSuite::~TestSuite()
{
}

/*************************************************************************
 *                                   run                                 *
 *************************************************************************/
void TestSuite::run()
{
   Kobold::List* tests = getTests();

   /* Create our scenario */
   doCreateScenario();

   /*! Let's try to run all tests */
   TestCase* test = (TestCase*) tests->getFirst();
   for(int i = 0; i < tests->getTotal(); i++)
   {
      /* Before test init procedure */
      test->doBeforeTest();

      /* Try to run it */
      try
      {
         test->run(this);
      }
      catch(std::exception e)
      {
         /* Must clean up and rethrow the error. */
         test->doAfterTest();
         doFinishScenario();
         throw;
      }

      /* Test done with success, call after procedure. */
      test->doAfterTest();

      test = (TestCase*) test->getNext();
   }
 
   /* Clean up scenario. All ok. */
   doFinishScenario();
}

