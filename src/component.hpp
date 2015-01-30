#ifndef SLOW_COMPONENT_HPP
#define SLOW_COMPONENT_HPP

#include "message.hpp"

#include <algorithm>
#include <vector>

enum MessageType {
  START,
  PAUSE,
  QUIT,

  UPDATE,
  DRAW,

  POSITION,  // x,y
  BODY,      // w,h
  STATE,

  MOVE,
  STOP,

  cATTACK,   // from self, as a command

  eATTACK,   // from entity
  HIT,
  DAMAGE,
  DEATH,

  ANIMATE,
  ANIMATION_DONE,

  INPUT,
  DEPUT,

  MOUSE_HOVER,
  MOUSE_CLICK,
  MOUSE_UNCLICK,

  IS_COLLISION,
  COLLISION_TRUE,
  COLLISION_FALSE,

  CLICKED,
  UNCLICKED,
  HOVER,
  UNHOVER,

  PLACE
};

class Component {
public:
  typedef typename std::vector<Component*>::iterator iterator;

  Component(Component* self) : _self(self) { }
  Component() : _self(NULL) { }

  virtual ~Component() 
  { 
    for (size_t i = 0; i < _components.size(); i++) {
      delete _components[i];
    }
    _components.clear();
  }

  virtual void message(const Message &msg)
  {
    _broadcast(msg);
  }

protected:
  Component* _self;

  std::vector<Component*> _components;

  void _broadcast(const Message &msg)
  {
    for (size_t i = 0; i < _components.size(); i++) {
      if (msg.sender != _components[i]) {
        _components[i]->message(msg);
      }
    }
  }

  void _add(Component* e)
  {
    _components.push_back(e);
  }
  
  /* TODO: free the pointer before removing it from vector */
  void _remove(Component* e)
  {
    _components.erase(find(_components.begin(), _components.end(), e));
  }
};

#endif
