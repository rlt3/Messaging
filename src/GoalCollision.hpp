#ifndef SLOW_GOAL_COLLISIONCOMPONENT_HPP
#define SLOW_GOAL_COLLISIONCOMPONENT_HPP

#include "CollisionComponent.hpp"

class GoalCollisionComponent : public CollisionComponent {
public:
  GoalCollisionComponent(Body b, Messageable *self, Messageable *room) 
    : CollisionComponent(b, self, room)
  { }

protected:
  void _detect_collision(Messageable *other, Body b) {
    if (_collision(other, b)) {
      other->message(Message(_self, COLLIDE, _body));
      _room->message(Message(_self, SCORE));
    }
  }

};

#endif

