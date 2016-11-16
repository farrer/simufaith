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

#ifndef _simufaith_person_h
#define _simufaith_person_h

#include "faith.h"
#include "house.h"
#include "office.h"

#include <kobold/list.h>
#include <goblin/model3d.h>

namespace SimuFaith
{

/*! Max value likeness or dislikeness could be */
#define FAITH_OPINION_MAX_VALUE       100000
/*! Median value for likeness or dislikeness */
#define FAITH_OPINION_HALF_VALUE (FAITH_OPINION_MAX_VALUE / 2)

   /*! A single person - potentially a faith follower - in the game */
   class Person
   {
      public:
         /*! Personal info about a Faith. */
         class FaithInfo : public Kobold::ListElement
         {
            public:
               /*! Constructor 
                * \param faith pointer to Faith of this info is related to */
               FaithInfo(Faith* faith);
               /*! Destructor */
               ~FaithInfo();

               /*! \return Faith related to this info */
               Faith* getFaith();

               /*! \return [0 .. FAITH_OPINION_MAX_VALUE] of how much 
                * like related Faith */
               int getLikeness();

               /*! \return [0 .. FAITH_OPINION_MAX_VALUE] of how much dislike 
                * related Faith */
               int getDislikeness();

               /*! Set how much like and dislike related Faith */
               void set(int likeness, int dislikeness);

               /*! Add a value to the likeness, limited to 
                * [0 .. FAITH_OPINION_MAX_VALUE].
                * \param value to add. Obviously, if negative, will dec. */
               void addLikeness(int value);

               /*! Add a value to the dislikeness, limited to 
                * [0 .. FAITH_OPINION_MAX_VALUE].
                * \param value to add. Obviously, if negative, will dec. */
               void addDislikeness(int value);

            private:
               Faith* faith; /**< Faith which this info is related to */
               int likeness;  /**< [0 .. FAITH_OPINION_MAX_VALUE] of how 
                                   much like it  */
               int dislikeness; /**< [0 .. FAITH_OPINION_MAX_VALUE] of how 
                                     much dislike it */
         };

         /*! What is inside a person's mind. Faiths, faiths everywhere. */
         class Mind
         {
            public:
               /*! Constructor */
               Mind();
               /*! Destructor */
               ~Mind();

               /*! Get personal information about a Faith
                * \param faith pointer to faith to get info
                * \return FaithInfo found or NULL if none. */
               FaithInfo* getFaithInfo(Faith* faith);

               /*! Define current person's faith (which one person's 
                * must like). */
               void defineCurrentFaith();

               /*! \return current person's Faith, or NULL, if none choosed
                * by the person. */
               Faith* getFaith();

            private:
               Kobold::List faiths; /**< Each faith info */
               FaithInfo* curFaith; /**< Info about current adopted faith */
         };

         /*! A person's child representation. Usually, parent's faith have
          * an important role on children's faith definition. */
         class Child : public Kobold::ListElement
         {
            public:
               /*! Constructor */
               Child(Person* person);
               /*! Destructor */
               ~Child();
               /*! \return person of the child */
               Person* getPerson();
            private:
               Person* person; /**< The child's person */
         };

         /*! Constructor */
         Person(Kobold::String name, int age, Person* parentA, Person* parentB,
                Kobold::String filename, Ogre::SceneManager* sceneManager);
         /*! Destructor */
         virtual ~Person();

         /*! \return pointer to current person's Faith */
         Faith* getFaith();

         /*! \return first person's parent pointer (could be NULL) */
         Person* getParentA();
         /*! \return second person's parent pointer (could be NULL) */
         Person* getParentB();

         /*! Set worker of the person (if NULL -> unemployed).
          * \param worker worker pointer */
         void setAsWorker(Office::Worker* worker);

         /*! \return worker info, NULL if person is unemployed */
         Office::Worker* getWorker();

         /*! Set person as an inhabitant (NULL -> homeless)
          * \param inhabitant pointer to its nhabitant information */
         void setAsInhabitant(House::Inhabitant* inhabitant);

         /*! \return inhabitant info. NULL if person is homeless. */
         House::Inhabitant* getInhabitant();

         /*! Add a person a a child of this one 
          * \param child person to be child of this one */
         void addChild(Person* child);

         /*! Remove a person's child (usually due to death
          * \param child pointer to the person to remove. */
         void removeChild(Person* child);

      private:
         Mind mind;            /**< Person's mind */
         int age;              /**< Person's age */
         Kobold::String name;  /**< Person's name */

         Person* parentA;      /**< Person's first parent */
         Person* parentB;      /**< Person's second parent */

         House::Inhabitant* inhabitant; /**< Home information */
         Office::Worker* worker; /**< Job information */

         Goblin::Model3d* model; /**< Person's model */

         Kobold::List children; /**< Person's children */

         static int count;
         //TODO: portrait? 
   };

}

#endif

