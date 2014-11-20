#ifndef SLOW_VECTORCOMPONENT_HPP
#define SLOW_VECTORCOMPONENT_HPP

#include "Component.hpp"

class VectorComponent : public Component {
public:
  VectorComponent(Messageable *e, Messageable *r) : Component(e, r) { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case MOVE:
        std::cout << "Moving " << _self->name << "." << std::endl;
        _room->message(Message(_self, MOVEMENT));
        break;

      default:
        break;
    }
  }
};

#endif
