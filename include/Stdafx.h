#ifndef _STDAFX_H
#define _STDAFX_H

#undef __DEPRECATED
//#define DEBUG

#ifdef DEBUG
#include <debug.h>
#endif
#include <vector>
#include <set>
#include <map>
#include <list>
//#include <algorithm>
//Windows
//#include <hash_map>
#include <ext/hash_map>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <dirent.h>
#include <MLlib.h>
#include <FreeTypeGX.h>

#include "Common.h"
#include "Singleton.h"
#include "Resources.h"
#include "MersenneTwister.h"

//Lua Scripting
extern "C" 
{
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
};

//GameMonkey Scripting
#include "gm/gmThread.h"

//Physics Part
#include "Physics/Defines.h"
#include "Physics/Vector3.h"
#include "Physics/Quaternion.h"
#include "Physics/Matrix3.h"
#include "Physics/Matrix4.h"
#include "Physics/Random.h"
#include "Physics/PhysicObject.h"
#include "Physics/Particle.h"
#include "Physics/ParticleForceGenerator.h"
#include "Physics/FireworkRule.h"
#include "Physics/Firework.h"
#include "Physics/ParticleContacts.h"
#include "Physics/ParticleLink.h"
#include "Physics/Body.h"
#include "Physics/CollideCoarse.h"
#include "Physics/CollideFine.h"
#include "Physics/Contacts.h"
#include "Physics/Joints.h"
#include "Physics/RigidBodyForceGenerator.h"
#include "Physics/PhysicsMgr.h"

//Threading part
#include "Callback.h"
#include "Threading/pthread.h"
#include "Threading/Threading.h"
#include "Threading/Mutex.h"
#include "Threading/RWLock.h"
#include "Threading/Condition.h"
#include "Threading/Task.h"
#include "Threading/TaskList.h"
#include "Threading/TaskExecutor.h"
#include "Threading/CThreads.h"

#include "Log.h"

//Event part
//#include "EventRunnable.h"
#include "EventMgr.h"
#include "ResourceMgr.h"
#include "FontMgr.h"
#include "SoundMgr.h"

#include "GUI/GUIItem.h"
#include "GUI/GUILabel.h"
#include "GUI/GUIProgressBar.h"
#include "GUIMgr.h"

#include "Faction.h"

#include "Map.h"

#include "AIInterface.h"

#include "Object.h"
#include "TimedObject.h"
#include "Projectile.h"
#include "Weapon.h"
#include "MapObject.h"
#include "ScriptObject.h"
#include "SoundObject.h"
#include "Gameobject.h"
#include "Unit.h"
#include "Creature.h"
#include "Pet.h"
#include "Player.h"

//ScriptEngines
#include "ScriptEngine/ScriptDefines.h"

//Lua
#include "ScriptEngine/LUAObjects.h"
#include "ScriptEngine/LUAEngine.h"
#include "ScriptEngine/LUAFunctions.h"

//GameMonkey
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptEngine/ScriptFunctions.h"

#endif
