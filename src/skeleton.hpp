#ifndef SLOW_SKELETON_HPP
#define SLOW_SKELETON_HPP

#include "animation.hpp"
#include "health.hpp"

class Skeleton : public Component {
public:
  Skeleton(Component* s) : Component(s)
  {
    _add(new Animation("enemy.png", this));
    _add(new Health(this));

    _broadcast(Message(this, POSITION, rect(128, 128, 64, 64)));
  }

  void message(const Message &msg)
  {
    switch (msg.type)
    {
      case REMOVE:
        _self->message(msg);
        break;

      default:
        _broadcast(msg);
        break;
    }
  }
};

#endif
