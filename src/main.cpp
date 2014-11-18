#include <iostream>

#include "Broadcaster.hpp"
#include "Component.hpp"

#include "InputComponent.hpp"
#include "HealthComponent.hpp"
#include "VectorComponent.hpp"
#include "CollisionComponent.hpp"

class Input {
public:
  Input() { }

protected:
  Message _update(Messageable *m) { return Message(m, ATTACK); }
};

class AI : public Messageable {
public:
  AI() { _modular = 0; }

protected:
  Message _action()
  {
    Message v[2] = {
      Message(this, MOVE),
      Message(this, ATTACK)
    };

    return v[++_modular % 2];
  }

  int _modular;
};

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

protected:
  Broadcaster<Entity> *_room;
};

class Player : public Entity, protected Input {
public:
  Player(Broadcaster<Entity> *b, std::string s) 
    : Entity(b, s), Input()
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case UPDATE:
        _broadcast(_update(this));
        break;

      case BROADCAST:
        _room->message(msg.data<Message>());
        break;

      default:
        _broadcast(msg);
        break;
    }
  }
};

class Monster : public Entity, protected AI {
public:
  Monster(Broadcaster<Entity> *b, std::string s) 
    : Entity(b, s), AI()
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case UPDATE:
        //_broadcast(_action());
        break;

      case BROADCAST:
        _room->message(msg.data<Message>());
        break;

      default:
        _broadcast(msg);
        break;
    }
  }
};

class Room : public Broadcaster<Entity> {
public:
  Room() : Broadcaster<Entity>()
  { 
    _messageables.push_back(new Player(this, "Player"));
    _messageables.push_back(new Monster(this, "Monster"));
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

  room.message(Message(&room, UPDATE));

  /*
   * Need Commands, a Message Type from self.
   *
   * Commands are like MOVE, which then the components can interpret on their
   * own (and send messages like MOVEMENT @ LOCATION).
   *
   * There needs to be some sort of system of messages from self which the
   * other components interpret.
   *
   * Components kinda also don't need the entity. They can just broadcast to
   * the room as if they were the entity, which they are. So, we can probably
   * stop the Message(BROADCAST, Message(blah)) paradigm even though it seemed
   * like a clever hack.
   *
   * This way, there is no two-way messaging. If a message needs to be sent to
   * the room then it can be. Otherwise, a message can be internal, just to
   * self.
   */


  return 0;
}
