#ifndef SLOW_ENEMY_AI_HPP
#define SLOW_ENEMY_AI_HPP

class EnemyAI : public Component {
public:
  EnemyAI(Component* s) : Component(s)
  { }

  void message(const Message &msg)
  {
    switch (msg.type)
    {
      case PLAYER_MOVEMENT
        update_player_location(msg.data<Rect>());
        break;

      case ANIMATION_DONE:
        /* 
         * Handles many cases:
         *  - Attack is done, attack again?
         *  - Movement is done, move again?
         */
        break;
    }
  }
};

#endif
