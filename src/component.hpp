#ifndef SLOW_COMPONENT_HPP
#define SLOW_COMPONENT_HPP

#include "Messageable.hpp"

/*
 * Components are an entity. So, they can message the room as that entity.
 * They can also send messages to self.
 *
 * Does the entity need to `take up space'? Add a collision component. Does it
 * need to be autonomous? Go ahead, throw in an AI component. Want it to be
 * renderer? Gotta have that graphics component.
 */

class Component : public Messageable {
public:
  Component(Messageable *e, Messageable *r) : _self(e), _room(r) { }
  virtual ~Component() { }

protected:
  Messageable *_self;
  Messageable *_room;
};

#endif
