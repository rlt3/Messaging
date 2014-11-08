#ifndef SLOW_MESSAGE_HPP
#define SLOW_MESSAGE_HPP

#include "coordinate.hpp"
#include "types.hpp"

/*
 * The message is the most basic form of information for this system. It is the
 * fuel of the engine.
 *
 * Maybe the message is extensible into something like Attack_Message which
 * then we just use Unions to pass around messages.
 *
 * Another idea: Query_Message type and have the message method for each Entity
 * always return a message. Sometimes a response is needed, other times it
 * doesn't matter.
 */

class Messageable;

struct Message {
  Message_Type type;
  Messageable *sender;
  Coordinate location;

  /* 
   * payload could be a void pointer to a function, or void pointer to a certain
   * object. Right now the int can be cast to a enum based on the message type.
   *
   * So, it can be the range (aoe) of damage, or actual damage, or what have
   * you.
   */
  int payload;

  Message(Message_Type t, Messageable *m, Coordinate l, int p)
    : type(t), sender(m), location(l), payload(p) 
  { }
};

#endif
