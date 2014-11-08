#include "entity.hpp"
#include "room.hpp"

Room::Room()
{
  _entities.push_back(new Entity(PLAYER, this, 10, 10));
}

Room::~Room()
{
  Entity_Iterator entity;
  for(entity = _entities.begin(); entity != _entities.end(); ++entity) {
    delete *entity;
  }
}

/* 
 * The room acts as a pool for all entities and shares messages with them.
 * Imagine the phrase, "Speak to the room."
 */
void
Room::message(Message msg)
{
  Entity_Iterator entity;
  for(entity = _entities.begin(); entity != _entities.end(); ++entity) {
    (*entity)->message(msg);
  }
}

void 
Room::add_entity()
{
  /* _entities.push_back(new Monster(*this, 10, 10)); */
}

void 
Room::remove_entity(Entity *entity)
{
  _entities.erase(std::remove( _entities.begin(), _entities.end(), entity), 
      _entities.end());
}
