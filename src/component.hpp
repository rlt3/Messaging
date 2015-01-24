#ifndef SLOW_COMPONENT_HPP
#define SLOW_COMPONENT_HPP

#include "message.hpp"
#include <algorithm>
#include <vector>

class Component {
public:
  typedef typename std::vector<Component*>::iterator iterator;

  Component(Component* parent)
    : _parent(parent)
  { }

  Component() : _parent(NULL) { }

  virtual ~Component() 
  { 
    for (size_t i = 0; i < _messageables.size(); i++) {
      delete _messageables[i];
    }
    _messageables.clear();
  }

  virtual void message(const Message &msg)
  {
    _broadcast(msg);
  }

protected:
  std::vector<Component*> _messageables;
  Component* _parent;

  void _broadcast(const Message &msg)
  {
    for (size_t i = 0; i < _messageables.size(); i++) {
      if (msg.sender != _messageables[i]) {
        _messageables[i]->message(msg);
      }
    }
  }

  void _add(Component* e)
  {
    _messageables.push_back(e);
  }
  
  /* TODO: free the pointer before removing it from vector */
  void _remove(Component* e)
  {
    _messageables.erase(find(_messageables.begin(), _messageables.end(), e));
  }
};

#endif
