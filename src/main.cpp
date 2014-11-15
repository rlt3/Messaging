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
    : Broadcaster<Component>(), _broadcaster(b)
  { 
    name = s; 
    _messageables.push_back(InputComponent(this));
    _messageables.push_back(VectorComponent(this));
    _messageables.push_back(HealthComponent(this));
    _messageables.push_back(CollisionComponent(this));
  }

  ~Entity() { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case BROADCAST:
        _broadcaster->message(msg.data<Message>());
        break;

      default:
        _broadcast(msg);
        break;
    }
  }

protected:
  Broadcaster<Entity> *_broadcaster;
};

class Room : public Broadcaster<Entity> {
public:
  Room() : Broadcaster<Entity>()
  { 
    _messageables.push_back(Entity(this, "John"));
    _messageables.push_back(Entity(this, "Erin"));
  }

  ~Room() { }
};

int main()
{
  Room room;

  room.message(Message(&room, UPDATE));

  return 0;
}
