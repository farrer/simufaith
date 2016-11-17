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

#ifndef _simufaith_house_h
#define _simufaith_house_h

#include "building.h"

namespace SimuFaith
{
   class Person;

   /*! A house is a building where people live. */
   class House: public Building
   {
      public:
         /*! A House inhabitant definition */
         class Inhabitant : public Kobold::ListElement
         {
            public:
               /*! Constructor */
               Inhabitant(Person* person, House* house);
               /*! Destructor */
               ~Inhabitant();

               /*! \return person of this inhabitant */
               Person* getPerson();

               /*! \return house of the inhabitant */
               House* getHouse();

            private:
               Person* person; /**< A single inhabitant */
               House* house; /**< House where it inhabits */
         };

         /*! Constructor */
         House(int capacity, Kobold::String filename, 
               Ogre::SceneManager* sceneManager); 
         /*! Destructor */
         ~House();

         /*! Add a person to inhabit the house.
          * \param person pointer to the person to inhabit the house.
          * \note this function will set person->inhabitant pointer. */
         void addInhabitant(Person* person);

         /*! Remove an inhabitant from the house (ie: the person will no 
          * longer inhabit the house, but still exists as a person).
          * \param inhabitant pointer to the inhabitant to remove. */
         void removeInhabitant(Inhabitant* inhabitant);

         /*! \return max capacity of the house */
         int getCapacity();

         /*! \return total current inhabitants */
         int getTotalInhabitants();

         /*! \return total space left for new inhabitants */
         int getAvailableSpace();

         /*! Do the house simulation step */
         void step();

      private:
         int capacity;             /**< House max capacity */
         Kobold::List inhabitants; /**< Current house inhabitants */
   };

}

#endif

