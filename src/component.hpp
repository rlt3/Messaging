
/*
 * Components are components of Entities which is why they all take entity
 * pointers.
 *
 * Entities are a broadcaster for Components and accept a broadcaster of 
 * Entities so they can talk to broadcast to other entities.
 */

class Component {
public:
  Component(Broadcaster<Component> *_entity)
};
