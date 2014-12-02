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
    iterator m;
    for(m = _messageables.begin(); m != _messageables.end(); ++m) {
      delete (*m);
    }
  }

  void add(T *e)
  {
    _messageables.push_back(e);
  }

  virtual void message(const Message &msg)
  {
    _broadcast(msg);
  }

protected:
  std::vector<T*> _messageables;

  void _broadcast(const Message &msg)
  {
    /* use an index instea of iterator because adding elems invalidates iter */
    for (size_t i = 0; i < _messageables.size(); i++) {
      if (msg.sender != _messageables[i]) {
        _messageables[i]->message(msg);
      }
    }
  }

  /* might need to make these pointers */
  //void _add(T &m);
  //void _remove(T &m);
};

#endif
