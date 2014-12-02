#ifndef SLOW_HEALTHCOMPONENT_HPP
#define SLOW_HEALTHCOMPONENT_HPP

#include "Component.hpp"

class HealthComponent : public Component {
public:
  HealthComponent(Messageable *e, Messageable *r)
    : Component(e, r) 
    , _health(50)
  { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case DAMAGE:
        _health -= msg.data<int>();

        if (_health <= 0) {
          _room->message(Message(_self, DEATH));
        }

        break;

      default:
        break;
    }
  }

protected:
  int _health;

};

#endif

