#include <iostream>

#include "Broadcaster.hpp"
#include "Component.hpp"

#include "InputComponent.hpp"
#include "HealthComponent.hpp"
#include "VectorComponent.hpp"
#include "CollisionComponent.hpp"

class Entity : public Broadcaster<Component> {
public:
  Entity(Broadcaster<Entity> *b, std::string s) 
    : Broadcaster<Component>(), _room(b)
  { 
    name = s; 
    _messageables.push_back(new InputComponent(this));
    _messageables.push_back(new VectorComponent(this));
    _messageables.push_back(new HealthComponent(this));
    _messageables.push_back(new CollisionComponent(this));
  }

  ~Entity() { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case BROADCAST:
        _room->message(msg.data<Message>());
        break;

      default:
        _broadcast(msg);
        break;
    }
  }

protected:
  Broadcaster<Entity> *_room;
};

class Room : public Broadcaster<Entity> {
public:
  Room() : Broadcaster<Entity>()
  { 
    //_messageables.push_back(new Entity(this, "John"));
    //_messageables.push_back(new Entity(this, "Erin"));
  }

  Entity* add(std::string name)
  {
    Entity* e = new Entity(this, name);
    _messageables.push_back(e);
    return e;
  }

  ~Room() { }
};

int main()
{
  Room room;
  Entity *john = room.add("John");
  Entity *erin = room.add("Erin");

  john->message(Message(erin, ATTACK));
  
  /*
   * InputComponent is Entity? Seems to be only component sending messages to
   * components (kinda like a Broadcaster<Component>), which seems familiar...
   *
   * All other components just receive messages from outside entities and do
   * actions based on that. No other component tells other component things, 
   * like the entity had collided -- other entities send that message.
   *
   * ---
   *
   * Combat    [ATTACK]
   * Collision [HIT, COLLIDE]
   * Vector    [MOVEMENT]
   * Graphics  [DRAW, HIT (bounce), ATTACK, COLLIDE ...]
   * Health    [DAMAGE, DEATH]
   * Sound     [COLLIDE, HIT, DAMAGE, DEATH]
   *
   */

  return 0;
}

/*
 
class Player : public Entity, protected Input {
};

class Monster : public Entity, protected AI {
};

*/
