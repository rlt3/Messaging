#ifndef SLOW_COMPONENT_HPP
#define SLOW_COMPONENT_HPP

#include "Messageable.hpp"

/*
 * Components are components of Entities which is why they all take entity
 * pointers.
 *
 * Entities are a broadcaster for Components and accept a broadcaster of 
 * Entities so they can talk to broadcast to other entities.
 */

class Component : public Messageable {
public:
  Component(Messageable *m) : _entity(m) { }
  virtual ~Component() { }
  virtual void message(const Message &m) { }

protected:
  /* Need a way to broadcast always with entity as second message sender 
  virtual void broadcast(Data data)
  {
    _entity->message(Message(this, BROADCAST, Message(_entity, data)));
  }
  */

  virtual void broadcast(const Message &msg)
  {
    _entity->message(Message(this, BROADCAST, msg));
  }

  Messageable *_entity;
};

#endif
