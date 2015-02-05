#ifndef STREAM_HPP
#define STREAM_HPP

#include "message.hpp"
#include "message_types.hpp"

#include <algorithm>
#include <vector>

/*
 * Stream acts as an arbitrary node for message passing. A Stream holds an
 * arbitrary amount of currents which it sends messages to. The currents are
 * themselves Streams and can hold currents themselves.
 *
 * There are 3 ways methods to send messages.
 *
 * The first method, message, is the basic way of sending a message to a stream.
 * This usually intended for "personal" correspondance, e.g. a Monster sending
 * a damage message to the Player.
 *
 * The second is downstream. This sends messages downwards to the currents. This
 * is the main way of sending messages. Most messages are simply filtered down
 * "from the top", e.g the Game is sent a Spacebar Input message which gets 
 * downstreamed all the way to the Player which then translates that message
 * into a Jump message, which is also sent downstream.
 *
 * The third is upstream. Just like with rivers in the real world, going up
 * the stream is a hassle, but not unheard of or bad. While most messages are
 * sent downstream, many of those messages started out upstream at some point.
 * A good example is the Player attacking and sending an Attack message upstream
 * to the Room which will downstream that message to other entities in the Room
 * besides the Player. The other entities may themselves respond to that Attack
 * message by saying they were hit and sending that message upstream.
 *
 * All 3 methods have 3 different overloaded signatures:
 *
 *  - integer type, templated data (any single piece of data -- even objects)
 *  - intger type
 *  - message itself
 *
 * Some examples:
 *   strm->message(msg);
 *   entity->message(DAMAGE, 10);
 *   upstream(MOVING_TO, location);
 *   downstream(IS_COLLISION_AT, location);
 */

/*
 * TODO:
 *  - Instead of Enum types, use strings and have compiled-time hashing for
 *  use of them in switch statements. This is so we don't have to keep a global
 *  list of message types.
 */

class Stream {
public:
  typedef typename std::vector<Stream*>::iterator iterator;

  Stream(Stream* up, Stream* down) : _up(up), _down(down) { }
  Stream(Stream* down) : _up(NULL), _down(down) { }

  virtual ~Stream() 
  { 
    for (size_t i = 0; i < _currents.size(); i++) {
      delete _currents[i];
    }
    _currents.clear();
  }

  /*
   *  Can call message in the three ways, but only the last method needs to be
   *  defined to catch the messages.
   */
  template <typename T>
  void message(int type, T data)
  {
    message(Message(_down, type, data));
  }

  void message(int type)
  {
    message(Message(_down, type));
  }

  virtual void message(const Message &msg)
  {
    downstream(msg);
  }

protected:
  std::vector<Stream*> _currents;

  template <typename T>
  void downstream(int type, T data)
  {
    _broadcast(Message(_down, type, data));
  }

  void downstream(int type)
  {
    _broadcast(Message(_down, type));
  }

  void downstream(const Message &msg)
  {
    _broadcast(msg);
  }

  template <typename T>
  void upstream(int type, T data)
  {
    /*
     * Does signing as parent when sending to parent not cause conflict with
     * sending the message you sent back to yourself?
     *
     * Since we sign as our parent -- our list of currents wasn't going to have
     * our parent in them. It's checking for ourself and not the actual message
     * sender.
     *
     * - NEED the paradigm of a sub-entity of an entity to broadcast to the
     *   entity holding THAT entity.
     *
     *   So, the Weapon stream of the Player stream needs to be able to 
     *   broadcast to the Room holding Player. As in, that Weapon needs to be 
     *   able to act as the Player. I think this is handled per-program and
     *   can be a paradigm or method many might use: make a message type for 
     *   strictly passing the received message one-level up assigned as you.
     */
    _up->message(Message(_down, type, data));
  }

  void upstream(int type)
  {
    _up->message(Message(_down, type));
  }

  void upstream(const Message &msg)
  {
    _up->message(msg);
  }

  template <typename T>
  void passthough(int type, T data)
  {
    //_up->message((Message(
  }

  void _add(Stream* e)
  {
    _currents.push_back(e);
  }
  
  /* TODO: free the pointer before removing it from vector */
  void _remove(Stream* e)
  {
    _currents.erase(find(_currents.begin(), _currents.end(), e));
  }

private:
  Stream* _up;   /* signed for going upstream */
  Stream* _down; /* signed when going downstream */

  void _broadcast(const Message &msg)
  {
    for (size_t i = 0; i < _currents.size(); i++) {
      if (msg.sender != _currents[i]) {
        _currents[i]->message(msg);
      }
    }
  }

};

#endif
