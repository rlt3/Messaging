#ifndef SLOW_INPUTCOMPONENT_HPP
#define SLOW_INPUTCOMPONENT_HPP

#include "Component.hpp"

class InputComponent : public Component {
public:
  InputComponent(Messageable *m) : _entity(m) { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case UPDATE:
        std::cout << "(Moving " << _entity->name << ".)" << std::endl;
        _entity->message(Message(this, MOVE));

      default:
        break;
    }
  }

protected:
  Messageable *_entity;

};

#endif
