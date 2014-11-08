#ifndef SLOW_MESSAGEABLE_HPP
#define SLOW_MESSAGEABLE_HPP

#include "message.hpp"

/*
 * The Messageable class is the root class of the game. And the Message struct
 * is the root piece of data on which the game is ran.
 *
 * The design thought-process is this:
 *
 * Every class is pure and only contains one entry-point. Typically a message is
 * sent to multiple entities (through a delegator like Room, which is just a
 * Messageable-based class). Those entities process the message and then can 
 * reply back to the sender individual by just messaging them back.
 *
 * Here is a basic conversation:
 *
 * Player broadcast: I'm moving here.
 *           Entity: I'm already here.
 *           Player: Ok.
 *
 * Components can take advantage of Messageable as well. Entities, which are just
 * containers for different components, take messages and then pass them onto
 * their components.
 *
 * The components then get messages later receiving instructions. Like "draw"
 * or "update" or "move".
 */

class Messageable;

class Messageable {
public:
  Messageable() { }

  /* Not making a virtual destructor and then having Entites (or components)
   * that inherit Messageable into a Messageable pointer causes the destructor for 
   * Messageable to get called instead of that class's.
   *
   * Adding virtual fixes this issue.
   */
  virtual ~Messageable() { }

  virtual void message(Message msg) { }

protected:

  /* notify a singular other messagable */
  virtual void notify(Messageable *e, Message msg) 
  { 
    e->message(msg); 
  }

  /* For broadcast, do you broadcast to a Broadcastable ? 
   *
   * If you are messaging the room, typically you are broadcasting to the room,
   * but the Room might look at the message and hold back SYSTEM messages, let's
   * say.
   */
};

#endif
