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

#ifndef _simufaith_office_h
#define _simufaith_office_h

#include "building.h"
#include <kobold/list.h>

namespace SimuFaith
{
   class Person;

   /*! An office is a building where people work on its jobs. */
   class Office : public Building
   {
      public:
         /*! Constructor 
          * \param sceneManager pointer to the used Ogre::SceneManager
          * \param filename model to load */
         Office(Ogre::SceneManager* sceneManager, Kobold::String filename);
         /*! Destructor */
         virtual ~Office();

         /*! Worker level on office. The higher the level, higher is its 
          * social influence */
         enum WorkerLevel
         {
            WORKER_LEVEL_WORKER,
            WORKER_LEVEL_PROJECT_MANAGER,
            WORKER_LEVEL_CEO,
            WORKER_LEVEL_OWNER
         };

         /*! A person working at an office */
         class Worker : public Kobold::ListElement
         {
            public:
               /*! Constructor 
                * \param person who is the worker
                * \param level its level on office
                * \param office where it works at */
               Worker(Person* person, WorkerLevel level, Office* office);
               /*! Destructor */
               ~Worker();

               /*! \return person related to the worker */
               Person* getPerson();

               /*! \return worker level */
               WorkerLevel getLevel();

               /*! \return office where it works at */
               Office* getOffice();

            private:
               Office* office;       /**< Where work */
               WorkerLevel level;   /**< Worker level */
               Person* person;       /**< Who it is */
         };

         /*! Add a person to be an worker at the office 
          * \param person person to add as worker
          * \param level its worker level */
         void addWorker(Person* person, WorkerLevel level);

         /*! Remove an worker from the office.
          * \param worker to remove from
          * \note this function will delete the worker (but not its person). */
         void removeWorker(Worker* worker);

         /*! Do Office specific step */
         void step();

      private:
         Kobold::List personnel; /**< Workers of the office */
   };

}

#endif

