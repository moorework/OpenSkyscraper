#include <cassert>
#include <iostream>
#include "game.h"
#include "item.h"
#include "sprite.h"
#include "tower.h"


Item::Item(Tower * tower, const char * className)
: tower(tower), LuaExposable<Item>(tower->game->lua, className)
{
}

Item::~Item()
{
	//Remove the sprites.
	for (std::set<Sprite *>::iterator s = sprites.begin(); s != sprites.end(); s++) {
		delete *s;
	}
	sprites.clear();
}

void Item::expose(lua_State * L)
{
	//Create the Item class and expose the base functions.
	LuaClass::make(L, "Item");
	LuaExposable<Item>::expose(L);
	
	//Register the exposed functions.
	const static luaL_Reg functions[] = {
		{"addSprite", lua_addSprite},
		{"removeSprite", lua_removeSprite},
		{NULL, NULL}
	};
	luaL_register(L, 0, functions);
	
	//Clean up.
	lua_pop(L, 1);
}

void Item::animate(double dt)
{
	callFunction("animate", "n", 0, dt);
}

void Item::simulate(double dt)
{
	callFunction("simulate", "n", 0, dt);
}

void Item::addSprite(Sprite * s)
{
	s->owner = this;
	sprites.insert(s);
	tower->game->addEntity(s);
}

void Item::removeSprite(Sprite * s)
{
	if (s->owner != this)
		return;
	s->owner = NULL;
	tower->game->removeEntity(s);
	sprites.erase(s);
	delete s;
}



/*int Item::lua_new(lua_State * L)
{
	new Item(L);
	return 1;
}*/



int Item::lua_addSprite(lua_State * L)
{
	int n = lua_gettop(L);
	if (n == 2) {
		Item * item = fromStack(L, 1);
		Sprite * sprite = Sprite::fromStack(L, 2);
		assert(item && sprite);
		item->addSprite(sprite);
	} else {
		luaL_error(L, "Got %d arguments, expected 2 (self, sprite)", n);
	}
	return 0;
}

int Item::lua_removeSprite(lua_State * L)
{
	int n = lua_gettop(L);
	if (n == 2) {
		Item * item = fromStack(L, 1);
		Sprite * sprite = Sprite::fromStack(L, 2);
		assert(item && sprite);
		item->removeSprite(sprite);
	} else {
		luaL_error(L, "Got %d arguments, expected 2 (self, sprite)", n);
	}
	return 0;
}
