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

#include "testperson.h"
#include "../src/sim/util.h"
using namespace SimuFaithTests;

/*************************************************************************
 *                       TestDefineCurrentFaith                          *
 *************************************************************************/
void TestPerson::TestDefineCurrentFaith::doBeforeTest()
{
   person = new SimuFaith::Person("Persona", 30, NULL, NULL, "", NULL);
}

/*************************************************************************
 *                       TestDefineCurrentFaith                          *
 *************************************************************************/
void TestPerson::TestDefineCurrentFaith::doAfterTest()
{
   /* Must remove our created person */
   delete person;
}

/*************************************************************************
 *                       TestDefineCurrentFaith                          *
 *************************************************************************/
void TestPerson::TestDefineCurrentFaith::run(TestSuite* suite) throw()
{
   TestPerson* testPerson = (TestPerson*) suite;

   /* Let's define each Faith with insufficient likeness to be person's 
    * current, and check it */
   person->getMind()->getFaithInfo(testPerson->faithA)->set(
         FAITH_OPINION_HALF_VALUE - 1, 0);
   person->getMind()->getFaithInfo(testPerson->faithB)->set(
         FAITH_OPINION_HALF_VALUE - 1, 0);
   person->getMind()->getFaithInfo(testPerson->faithC)->set(
         FAITH_OPINION_HALF_VALUE - 1, 0);
   /* Try to define and check if none is defined as current */
   person->getMind()->defineCurrentFaith();
   assertNULL(person->getMind()->getFaith());

   /* Now, add a likeness to one Faith and expect it to be the person's one */
   person->getMind()->getFaithInfo(testPerson->faithA)->set(
         FAITH_OPINION_HALF_VALUE + 1, 0);
   person->getMind()->defineCurrentFaith();
   assertTrue(person->getMind()->getFaith() == testPerson->faithA);

   /* Change to a Faith with more likeness than current */
   person->getMind()->getFaithInfo(testPerson->faithB)->set(
         FAITH_OPINION_HALF_VALUE + 4, 40);
   person->getMind()->defineCurrentFaith();
   assertTrue(person->getMind()->getFaith() == testPerson->faithB);

   /* Change to a Faith with less dislikeness than current */
   person->getMind()->getFaithInfo(testPerson->faithC)->set(
         FAITH_OPINION_HALF_VALUE + 4, 39);
   person->getMind()->defineCurrentFaith();
   assertTrue(person->getMind()->getFaith() == testPerson->faithC);
}

/*************************************************************************
 *                        TestApplyInfluence                             *
 *************************************************************************/
void TestPerson::TestApplyInfluence::doBeforeTest()
{
   personA = new SimuFaith::Person("Persona", 30, NULL, NULL, "", NULL);
   personB = new SimuFaith::Person("Personb", 30, NULL, NULL, "", NULL);
}

/*************************************************************************
 *                        TestApplyInfluence                             *
 *************************************************************************/
void TestPerson::TestApplyInfluence::doAfterTest()
{
   delete personA;
   delete personB;
}

/*************************************************************************
 *                        TestApplyInfluence                             *
 *************************************************************************/
void TestPerson::TestApplyInfluence::run(TestSuite* suite) throw()
{
   TestPerson* testPerson = (TestPerson*) suite;
   SimuFaith::Person::FaithInfo* faithApA =  personA->getMind()->getFaithInfo(
         testPerson->faithA);
   SimuFaith::Person::FaithInfo* faithApB =  personB->getMind()->getFaithInfo(
         testPerson->faithA);
   SimuFaith::Person::FaithInfo* faithBpA =  personA->getMind()->getFaithInfo(
         testPerson->faithB);
   SimuFaith::Person::FaithInfo* faithBpB =  personB->getMind()->getFaithInfo(
         testPerson->faithB);
   SimuFaith::Person::FaithInfo* faithCpA =  personA->getMind()->getFaithInfo(
         testPerson->faithC);
   SimuFaith::Person::FaithInfo* faithCpB =  personB->getMind()->getFaithInfo(
         testPerson->faithC);


   /* Sequence of getRandom will be: 31740, 18524, 28681, 45884, 38824, 
    * 26439 */
   srand(153);

   /* Let's try to apply influence of a target with Faith likeness
    * greater than same Faith likenes of 'influencer' (and check no influence
    * happen) */
   faithApA->set(FAITH_OPINION_HALF_VALUE + 20, 21);
   faithApB->set(FAITH_OPINION_HALF_VALUE + 30, 31);
   personA->getMind()->defineCurrentFaith();
   personB->getMind()->defineCurrentFaith();
   personA->getMind()->applyInfluence(personB, 100);
   assertTrue(faithApB->getLikeness() == FAITH_OPINION_HALF_VALUE + 30);
   assertTrue(faithApB->getDislikeness() == 31);

   /* Let's influence a current Faith, check if no dislikeness happens, and
    * also check other faiths one that should happen, and one that shouldn't */
   srand(153);
   faithApA->set(FAITH_OPINION_HALF_VALUE + 30, 31);
   faithApB->set(FAITH_OPINION_HALF_VALUE + 20, 21);
   faithBpA->set(46300, 310);
   faithBpB->set(20, 21);
   faithCpA->set(46300, 31);
   faithCpB->set(40, 21);
   personA->getMind()->defineCurrentFaith();
   personB->getMind()->defineCurrentFaith();

   personA->getMind()->applyInfluence(personB, 100);

   /* Check current faith likeness applyed, but without dislikeness */
   assertTrue(faithApB->getLikeness() == FAITH_OPINION_HALF_VALUE + 120);
   assertTrue(faithApB->getDislikeness() == 21);

   /* FaithB should have likeness and dislikeness applyed */
   assertTrue(faithBpB->getLikeness() == 120);
   assertTrue(faithBpB->getDislikeness() == 121);

   /* Faith C should only have likeness applyed (as it like it more than
    * personA dislikes it). */
   assertTrue(faithCpB->getLikeness() == 140);
   assertTrue(faithCpB->getDislikeness() == 21);
}

/*************************************************************************
 *                    TestParentFaithOnSimulation                        *
 *************************************************************************/
void TestPerson::TestParentFaithOnSimulation::doBeforeTest()
{
   /* Create Family 1 */
   parentA1 = new SimuFaith::Person("ParentA1", 38, NULL, NULL, "", NULL);
   parentB1 = new SimuFaith::Person("ParentB1", 34, NULL, NULL, "", NULL);
   child1A = new SimuFaith::Person("Child1A", 8, parentA1, parentB1, "", NULL);
   child1B = new SimuFaith::Person("Child1B", 11, parentA1, parentB1, "", NULL);

   /* Create Family 2 */
   parentA2 = new SimuFaith::Person("ParentA2", 38, NULL, NULL, "", NULL);
   parentB2 = new SimuFaith::Person("ParentB2", 34, NULL, NULL, "", NULL);
   child2A = new SimuFaith::Person("Child2A", 8, parentA2, parentB2, "", NULL);
   child2B = new SimuFaith::Person("Child2B", 11, parentA2, parentB2, "", NULL);
}

/*************************************************************************
 *                    TestParentFaithOnSimulation                        *
 *************************************************************************/
void TestPerson::TestParentFaithOnSimulation::doAfterTest()
{
   /* Must remove all created persons */
   delete parentA1;
   delete parentB1;
   delete child1A;
   delete child1B;
   delete parentA2;
   delete parentB2;
   delete child2A;
   delete child2B;
}

/*************************************************************************
 *                    TestParentFaithOnSimulation                        *
 *************************************************************************/
void TestPerson::TestParentFaithOnSimulation::run(TestSuite* suite) throw()
{
   TestPerson* testPerson = (TestPerson*) suite;

   /* Let's define Family 1 Faiths: both parents with same. */
   parentA1->getMind()->getFaithInfo(testPerson->faithA)->set(
         FAITH_OPINION_HALF_VALUE + 1, 100);
   parentB1->getMind()->getFaithInfo(testPerson->faithA)->set(
         FAITH_OPINION_HALF_VALUE + 100, 80);
   parentA1->getMind()->getFaithInfo(testPerson->faithB)->set(100, 80);
   parentB1->getMind()->getFaithInfo(testPerson->faithB)->set(80, 100);
   parentA1->getMind()->defineCurrentFaith();
   parentB1->getMind()->defineCurrentFaith();

   /* And Family 2 Faiths: each parent with a faith. */
   parentA2->getMind()->getFaithInfo(testPerson->faithA)->set(
         FAITH_OPINION_HALF_VALUE + 80, 80);
   parentB2->getMind()->getFaithInfo(testPerson->faithA)->set(100, 100);
   parentA2->getMind()->getFaithInfo(testPerson->faithB)->set(80, 80);
   parentB2->getMind()->getFaithInfo(testPerson->faithB)->set(
         FAITH_OPINION_HALF_VALUE + 100, 100);
   parentA2->getMind()->defineCurrentFaith();
   parentB2->getMind()->defineCurrentFaith();

   for(int i = 0; i < FAITH_OPINION_MAX_VALUE; i++)
   {
      SimuFaith::World::step();
   }

   /* Let's check children's minds. */
   assertTrue(child1A->getFaith() == testPerson->faithA);

   /* Make sure the Faith isn't greater of its parents */
   SimuFaith::Person::FaithInfo* childFaithInfo = 
      child1A->getMind()->getFaithInfo(testPerson->faithA);
   assertTrue(childFaithInfo->getLikeness() == 
         parentB1->getMind()->getFaithInfo(testPerson->faithA)->getLikeness());
   /* Make sure no dislikeness propagated to its own faith */
   assertTrue(childFaithInfo->getDislikeness() == 0);
   /* And that FaithB is equal to its greater parent, both like and dislike */
   childFaithInfo = child1A->getMind()->getFaithInfo(testPerson->faithB);
   assertTrue(childFaithInfo->getLikeness() == 100);
   assertTrue(childFaithInfo->getDislikeness() == 100);

   /* Same for child1B */
   assertTrue(child1B->getFaith() == testPerson->faithA);
   childFaithInfo = child1B->getMind()->getFaithInfo(testPerson->faithA);
   assertTrue(childFaithInfo->getLikeness() == 
         parentB1->getMind()->getFaithInfo(testPerson->faithA)->getLikeness());
   assertTrue(childFaithInfo->getDislikeness() == 0);
   childFaithInfo = child1B->getMind()->getFaithInfo(testPerson->faithB);
   assertTrue(childFaithInfo->getLikeness() == 100);
   assertTrue(childFaithInfo->getDislikeness() == 100);

   /* Now let's check children of family 2 */
   assertTrue(child2A->getFaith() == testPerson->faithB);
   childFaithInfo = child2A->getMind()->getFaithInfo(testPerson->faithB);
   assertTrue(childFaithInfo->getLikeness() == 
         parentB2->getMind()->getFaithInfo(testPerson->faithB)->getLikeness());
   /* Must have the dislikeness of other parent on it */
   assertTrue(childFaithInfo->getDislikeness() == 80);
   /* And other Faith must be of greater likness / dislikeness from parents */
   childFaithInfo = child2A->getMind()->getFaithInfo(testPerson->faithA);
   assertTrue(childFaithInfo->getLikeness() == 
         parentA2->getMind()->getFaithInfo(testPerson->faithA)->getLikeness());
   assertTrue(childFaithInfo->getDislikeness() == 100);

   /* Same for other children */
   assertTrue(child2B->getFaith() == testPerson->faithB);
   childFaithInfo = child2B->getMind()->getFaithInfo(testPerson->faithB);
   assertTrue(childFaithInfo->getLikeness() == 
         parentB2->getMind()->getFaithInfo(testPerson->faithB)->getLikeness());
   assertTrue(childFaithInfo->getDislikeness() == 80);
   childFaithInfo = child2B->getMind()->getFaithInfo(testPerson->faithA);
   assertTrue(childFaithInfo->getLikeness() == 
         parentA2->getMind()->getFaithInfo(testPerson->faithA)->getLikeness());
   assertTrue(childFaithInfo->getDislikeness() == 100);
}

/*************************************************************************
 *                              Constructor                              *
 *************************************************************************/
TestPerson::TestPerson()
{
   tests.insert(new TestDefineCurrentFaith());
   tests.insert(new TestApplyInfluence());
   tests.insert(new TestParentFaithOnSimulation());
}

/*************************************************************************
 *                               Destructor                              *
 *************************************************************************/
TestPerson::~TestPerson()
{
}

/*************************************************************************
 *                               getTests                                *
 *************************************************************************/
Kobold::List* TestPerson::getTests()
{
   return &tests;
}

/*************************************************************************
 *                           doCreateScenario                            *
 *************************************************************************/
void TestPerson::doCreateScenario()
{
   /* Init the world with 3 Faiths */
   SimuFaith::World::init();

   faithA = SimuFaith::World::createFaith("Faith A");
   faithB = SimuFaith::World::createFaith("Faith B");
   faithC = SimuFaith::World::createFaith("Faith C");
}

/*************************************************************************
 *                           doFinishScenario                            *
 *************************************************************************/
void TestPerson::doFinishScenario()
{
   /* Done with our world */
   SimuFaith::World::end();
}

