#ifndef SLOW_INPUTCOMPONENT_HPP
#define SLOW_INPUTCOMPONENT_HPP

#include "Component.hpp"

class InputComponent : public Component {
public:
  InputComponent(Messageable *e, Messageable *r) : Component(e, r) { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case UPDATE:
        std::cout << "(Moving " << _self->name << ".)" << std::endl;
        _self->message(Message(_self, MOVE));
        break;

      default:
        break;
    }
  }
};

#endif
