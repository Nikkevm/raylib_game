#include "entity.h"

int alloc_entity(int type)
{
	for(int i = 1; i < MAX_ENTS; ++i){
		if(ent[i].type == E_none){
			ent[i].type = type;
			return i;
		}
	}
	assert(0);
	return 0;
}

void free_entity(int id)
{
	ent[id].type = E_none;
}

void physics()
{
	for(int i = 1; i <= MAX_ENTS; ++i){
		Entity *e = &ent[i];
		if(e->type == E_none) continue;

		e->pos.x += e->velocity.x * GetFrameTime();
		e->pos.y += e->velocity.y * GetFrameTime();
	}
}
