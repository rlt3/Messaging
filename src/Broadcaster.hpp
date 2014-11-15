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
  typedef typename std::vector<T>::iterator iterator;

  Broadcaster() { }
  virtual ~Broadcaster() { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case UPDATE:
        _broadcast(msg);
        break;

      default:
        break;
    }
  }

protected:
  std::vector<T> _messageables;

  void _broadcast(const Message &msg)
  {
    iterator m;
    for(m = _messageables.begin(); m != _messageables.end(); ++m) {
      /* Do message the sender */
      if (msg.sender != &(*m)) {
        m->message(msg);
      }
    }
  }

  /* might need to make these pointers */
  void _add(T &m);
  void _remove(T &m);
};

#endif
