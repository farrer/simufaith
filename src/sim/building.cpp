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

#include "building.h"
#include "world.h"
using namespace SimuFaith;

/*************************************************************************
 *                                Constructor                            *
 *************************************************************************/
Building::Building(Ogre::SceneManager* sceneManager, Kobold::String filename)
{
   this->name = "building" + Kobold::StringUtil::toString(count);
   this->sceneManager = sceneManager;
   this->filename = filename;
   model = new Goblin::Model3d(this->name, this->filename, this->sceneManager);

   World::addBuilding(this);
   count++;
}

/*************************************************************************
 *                                 Destructor                            *
 *************************************************************************/
Building::~Building()
{
   World::removeBuilding(this);
   delete model;
}

/*************************************************************************
 *                                changeModel                            *
 *************************************************************************/
void Building::changeModel(Kobold::String filename)
{
   /* Only recreate if not the already loaded one */
   if(this->filename != filename)
   {
      delete model;
      this->filename = filename;
      model = new Goblin::Model3d(this->name, filename, this->sceneManager);
   }
}

/*************************************************************************
 *                                 getModel                              *
 *************************************************************************/
Goblin::Model3d* Building::getModel()
{
  return model;
}

int Building::count = 0;

