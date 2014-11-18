#ifndef SLOW_VECTORCOMPONENT_HPP
#define SLOW_VECTORCOMPONENT_HPP

#include "Component.hpp"

class VectorComponent : public Component {
public:
  VectorComponent(Messageable *m) : Component(m) { }

  void message(const Message &msg)
  {
    switch(msg.type) {
      case MOVE:
        std::cout << "Moving " << _entity->name << "." << std::endl;
        broadcast(Message(_entity, MOVEMENT));
        break;

      default:
        break;
    }
  }
};

#endif
