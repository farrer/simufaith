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

#ifndef _simufaith_test_person_h
#define _simufaith_test_person_h

#include "testcase.h"
#include "../src/sim/person.h"
#include "../src/sim/world.h"

namespace SimuFaithTests
{

   /*! Suite with tests related to person implementation. */
   class TestPerson : public TestSuite
   {
      public:
         /*! Test for function Person#Mind#defineCurrentFaith */
         class TestDefineCurrentFaith : public TestCase
         {
            public:
               void doBeforeTest();
               void doAfterTest();
               void run(TestSuite* suite) throw();

            private:
               SimuFaith::Person* person;
         };

         /*! Test for function Person#Mind#applyInfluence */
         class TestApplyInfluence : public TestCase
         {
            public:
               void doBeforeTest();
               void doAfterTest();
               void run(TestSuite* suite) throw();
         };

         /*! Test for parent Faith propagation on simulation. This TestCase
          * will make sure that parent's Faith, by themselves, are sufficient
          * for its children conversion with no other influences involved. */
         class TestParentFaithOnSimulation : public TestCase
         {
            public:
               void doBeforeTest();
               void doAfterTest();
               void run(TestSuite* suite) throw();
            private:
               /* Family 1 */
               SimuFaith::Person* parentA1;
               SimuFaith::Person* parentB1;
               SimuFaith::Person* child1A;
               SimuFaith::Person* child1B;
               /* Family 2 */
               SimuFaith::Person* parentA2;
               SimuFaith::Person* parentB2;
               SimuFaith::Person* child2A;
               SimuFaith::Person* child2B;
         };

         TestPerson();
         ~TestPerson();

         /* Our created faiths. Public, as we are at a test and lazy to
          * write some getters. */
         SimuFaith::Faith* faithA;
         SimuFaith::Faith* faithB;
         SimuFaith::Faith* faithC;

      protected:
         Kobold::List* getTests();
         void doCreateScenario();
         void doFinishScenario();

      private:
         Kobold::List tests;  /**< List with our test cases */
   };

}

#endif

