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
  //Component(Messageable *m) : _entity(m) { }
  Component() { }

  virtual void message(const Message &m) { }

protected:
  void broadcast(Messageable *e, const Message &msg)
  {
    e->message(Message(this, BROADCAST, msg));
  }
};

#endif
