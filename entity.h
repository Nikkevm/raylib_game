#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

#define MAX_ENTS 1024

enum
{
	E_none,
	E_player
};

typedef struct Entity Entity;
struct Entity{
	int type;
	Vector2 pos;
	Vector2 velocity;
};

Entity ent[MAX_ENTS];

int alloc_entity(int type);
void free_entity(int id);
void physics();

#endif
