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

  T* add(T *e)
  {
    _messageables.push_back(e);
    return e;
  }

  virtual void message(const Message &msg)
  {
    _broadcast(msg);
  }

protected:
  std::vector<T*> _messageables;

  void _broadcast(const Message &msg)
  {
    iterator m;
    for(m = _messageables.begin(); m != _messageables.end(); ++m) {
      /* Don't message the sender */
      if (msg.sender != (*m)) {
        (*m)->message(msg);
      }
    }
  }

  /* might need to make these pointers */
  //void _add(T &m);
  //void _remove(T &m);
};

#endif
