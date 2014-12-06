#ifndef SLOW_BALL_HPP
#define SLOW_BALL_HPP

/*
 * The ball, which bounces off the paddles. Its initial direction is determined
 * randomly.
 *
 * Score is determined if the `wall' on any given player's side receives a 
 * collision message.
 *
 * The Score entity has a collision component which is basically a long box. But
 * its graphics component is literally just the score.
 *
 * When it reaches a certain point (first to 5, let's say) it sends a win 
 * message to the Room (table in this case).
 *
 * With a body component, we don't need to have a special collision component
 * for each type of object. It simply looks at the body's dimensions and 
 * compares to the other body's dimensions. Now, what we might do with that
 * collision information (from the opposing object) is special. In the goal's
 * case, we want to increment the score.
 *
 * The Vector component might also be the same, too. For the ball, there is 
 * no input component, but there might be a component which initializes the 
 * velocity by simulating input.
 *
 * The same for the Paddles. We only want input to work in 2 directions (up and
 * down), so we just have to limit input to those keys. The vector component
 * can be the same for both paddles and the ball.
 */

#include "Entity.hpp"

#include "GraphicsComponent.hpp"
#include "CollisionComponent.hpp"
#include "VectorComponent.hpp"
#include "ProjectileComponent.hpp"

#include "InputComponent.hpp"

class Ball : public Entity {
public:
  Ball(Messageable *room, Body b) 
    : Entity(room, "Ball")
  { 
    _messageables.push_back(new GraphicsComponent(b, 255, 255, 255, this, room));
    _messageables.push_back(new CollisionComponent(b, this, room));
    _messageables.push_back(new ProjectileComponent(b, 10, this, room));
  }
};

#endif
