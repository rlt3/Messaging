#ifndef SLOW_BROADCASTER_HPP
#define SLOW_BROADCASTER_HPP

#include <vector>
#include "Messageable.hpp"

/*
 * Broadcaster to specific types of Messageables 
 */

template <typename T>
class Broadcaster : public Messageable {
public:
  typedef typename std::vector<T*>::iterator iterator;

  Broadcaster() { }
  ~Broadcaster() 
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
  std::vector<T*> _messageables;

  void _broadcast(const Message &msg)
  {
    for (size_t i = 0; i < _messageables.size(); i++) {
      if (msg.sender != _messageables[i]) {
        _messageables[i]->message(msg);
      }
    }
  }

  void _add(T *e)
  {
    _messageables.push_back(e);
  }
  
  void _remove(T *e)
  {
    _messageables.erase(find(_messageables.begin(), _messageables.end(), e));
  }
};

#endif
