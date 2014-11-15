#ifndef SLOW_VECTORCOMPONENT_HPP
#define SLOW_VECTORCOMPONENT_HPP

#include "Component.hpp"

class VectorComponent : public Component {
public:
  VectorComponent(Messageable *m) : _entity(m) { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case MOVE:
        std::cout << "Moving " << _entity->name << "." << std::endl;
        broadcast(_entity, Message(_entity, MOVEMENT));

      default:
        break;
    }
  }

protected:
  Messageable *_entity;

};

#endif
