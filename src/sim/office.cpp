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

#include "office.h"
#include "person.h"
using namespace SimuFaith;

/*************************************************************************
 *                                 Worker                                *
 *************************************************************************/
Office::Worker::Worker(Person* person, Office::WorkerLevel level, 
      Office* office)
{
   this->person = person;
   this->level = level;
   this->office = office;
}

/*************************************************************************
 *                                ~Worker                                *
 *************************************************************************/
Office::Worker::~Worker()
{
}

/*************************************************************************
 *                                getPerson                              *
 *************************************************************************/
Person* Office::Worker::getPerson()
{
   return person;
}

/*************************************************************************
 *                                getLevel                               *
 *************************************************************************/
Office::WorkerLevel Office::Worker::getLevel()
{
   return level;
}

/*************************************************************************
 *                                getOffice                              *
 *************************************************************************/
Office* Office::Worker::getOffice()
{
   return office;
}

/*************************************************************************
 *                                 Office                                *
 *************************************************************************/
Office::Office(Ogre::SceneManager* sceneManager, Kobold::String filename)
       :Building(sceneManager, filename)
{
}
         
/*************************************************************************
 *                                ~Office                                *
 *************************************************************************/
Office::~Office()
{
}

/*************************************************************************
 *                               addWorker                               *
 *************************************************************************/
void Office::addWorker(Person* person, Office::WorkerLevel level)
{
   Worker* worker = new Worker(person, level, this);
   person->setAsWorker(worker);
   personnel.insert(worker);
}

/*************************************************************************
 *                             removeWorker                              *
 *************************************************************************/
void Office::removeWorker(Worker* worker)
{
   worker->getPerson()->setAsWorker(NULL);
   personnel.remove(worker);
}

/*************************************************************************
 *                                 step                                  *
 *************************************************************************/
void Office::step()
{
   Worker* worker = (Worker*) personnel.getFirst();
   for(int i = 0; i < personnel.getTotal(); i++)
   {
      //TODO!
      worker = (Worker*) worker->getNext();
   }
}

