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
using namespace SimuFaithTests;

/*************************************************************************
 *                       TestDefineCurrentFaith                          *
 *************************************************************************/
void TestPerson::TestDefineCurrentFaith::doBeforeTest()
{
   person = new SimuFaith::Person("Persona", 30, NULL, NULL, "", NULL);
   SimuFaith::World::addPerson(person);
}

/*************************************************************************
 *                       TestDefineCurrentFaith                          *
 *************************************************************************/
void TestPerson::TestDefineCurrentFaith::doAfterTest()
{
   /* Must remove our created person */
   SimuFaith::World::removePerson(person);
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

void TestPerson::TestApplyInfluence::doBeforeTest()
{
}

void TestPerson::TestApplyInfluence::doAfterTest()
{
}

void TestPerson::TestApplyInfluence::run(TestSuite* suite) throw()
{
}
         
void TestPerson::TestParentFaithOnSimulation::doBeforeTest()
{
}

void TestPerson::TestParentFaithOnSimulation::doAfterTest()
{
}

void TestPerson::TestParentFaithOnSimulation::run(TestSuite* suite) throw()
{
}

TestPerson::TestPerson()
{
   tests.insert(new TestDefineCurrentFaith());
   tests.insert(new TestApplyInfluence());
   tests.insert(new TestParentFaithOnSimulation());
}

TestPerson::~TestPerson()
{
}

Kobold::List* TestPerson::getTests()
{
   return &tests;
}

void TestPerson::doCreateScenario()
{
   /* Init the world with 3 Faiths */
   SimuFaith::World::init();

   faithA = SimuFaith::World::createFaith("Faith A");
   faithB = SimuFaith::World::createFaith("Faith B");
   faithC = SimuFaith::World::createFaith("Faith C");
}

void TestPerson::doFinishScenario()
{
   /* Done with our world */
   SimuFaith::World::end();
}

