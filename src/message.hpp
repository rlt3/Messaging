#ifndef SLOW_MESSAGE_HPP
#define SLOW_MESSAGE_HPP

#include "Types.hpp"
#include <memory>

/*
 * Message is a class that attempts type erasure by using templates and some
 * cleverly nested classes to hold nearly any type of data.
 *
 * Data is derived by context. So, the type of message it is should give clue
 * enough to pull out the data like msg.data<Coordinate>();
 *
 * Our message class makes it so where our Message can be accepted anywhere and
 * then, after looking at what kind of message it is, be used however it needs
 * to be.
 *
 * Some scenarios on messages (for our one data member):
 *
 * (To Room) Entity A: Attack, Location (10, 10)
 *           Entity B: Hit
 *           Entity A: Damage, 10
 *
 * (To Room) Entity A: Moving, Location (5, 5)
 *           Entity B: Collide
 *
 */

class Messageable;

class Message {
private:
  /* a common base class for a base pointer */
  class DataCore
  {
  public:
    virtual ~DataCore() { }
  };

  /* template class inheriting our base pointer type */
  template <typename T>
  class Data : public DataCore
  {
  public:
    explicit Data(T v) : _value(v) { }
    T value() { return _value; }
  private:
    T _value;
  };

public:
  /* constructor for any non-pointer data */
  template <typename T> 
  explicit Message(Messageable *m, message_t t, T d) 
    : sender(m), type(t), _data(new Data<T>(d)) 
  { }

  /* constructor for messages with no data (message itself is the data) */
  explicit Message(Messageable *m, message_t t) 
    : sender(m), type(t) 
  { }

  /* cast into the correct type and our data here is constant */
  template <typename T> T data() const {
    return static_cast<Data<T>*>(_data.get())->value();
  }

  Messageable *sender;
  message_t    type;

private:
  std::shared_ptr<DataCore> _data;
};

#endif
