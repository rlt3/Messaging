#ifndef SLOW_WEAPON_HPP
#define SLOW_WEAPON_HPP

class Weapon : public Component {
public:
  Weapon(Component* s) : Component(s)
  {
  }
  
  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case ATTACK:
        /* do attack which creates a damage message to other entities */
        break;

      default:
        _broadcast(msg);
        break;
    }
  }
};

#endif
