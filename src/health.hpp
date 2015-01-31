#ifndef SLOW_HEALTH_HPP
#define SLOW_HEALTH_HPP

#include "collision.hpp"

class Health : public Component {
public:
  Health(Component* s) 
    : Component(s)
    , hp(10)
  { 
    _add(new Collision(this));
  }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case eATTACK:
        enemy = msg.sender;
        _broadcast(Message(this, IS_COLLISION, msg.data<Rect>()));
        break;

      case COLLISION_TRUE:
        enemy->message(Message(_self, HIT));
        break;

      case DAMAGE:
        damage(msg.data<int>());
        break;

      case ANIMATION_DONE:
        switch (msg.data<int>())
        {
          case 8: // death animation
            _self->message(Message(_self, REMOVE));
            break;
        }
        break;

      default:
        _broadcast(msg);
        break;
    }
  };

protected:
  Component* enemy;
  int hp;

  void damage(int dmg)
  {
    hp -= dmg;

    if (hp <= 0)
      _self->message(Message(this, DEATH));
  }
};

#endif