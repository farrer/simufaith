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

#ifndef _simufaith_building_h
#define _simufaith_building_h

#include <kobold/list.h>
#include <kobold/kstring.h>
#include <goblin/model3d.h>
#include <OGRE/OgreSceneManager.h>

namespace SimuFaith
{
   class Person;

   /*! A basic building class, representing a building in the game. */
   class Building : public Kobold::ListElement
   {
      public:
         /*! Constructor
          * \param sceneManager pointer to ogre scene manager used 
          * \param filename filename of the building model. 
          * \note this function will add the building to the world's list. */
         Building(Ogre::SceneManager* sceneManager, Kobold::String filename);

         /*! Destructor */
         virtual ~Building();

         /*! Change current building model to another one.
          * \param filename of the new model to use */
         void changeModel(Kobold::String filename);

         /*! \return pointer to the used model for the building */
         Goblin::Model3d* getModel();

      private:
         Goblin::Model3d* model;  /**< Model used for the building */
         Ogre::SceneManager* sceneManager; /**< current scene manager */
         Kobold::String name;     /**< Model's name */
         Kobold::String filename; /**< Model's filename */

         static int count; /**< Building counter */
   };

}

#endif

