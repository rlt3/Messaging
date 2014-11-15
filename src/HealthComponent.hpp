#ifndef SLOW_HEALTHCOMPONENT_HPP
#define SLOW_HEALTHCOMPONENT_HPP

#include "Component.hpp"

class HealthComponent : public Component {
public:
  HealthComponent(Messageable *m) : _entity(m) { }

  void message(const Message &msg)
  {
    int d;

    switch(msg.type) {
      case DAMAGE:
        d = msg.data<int>();
        std::cout << _entity->name << " was dealt " << d << " damage by " << msg.sender->name << "." << std::endl;

      default:
        break;
    }
  }

protected:
  Messageable *_entity;

};

#endif

