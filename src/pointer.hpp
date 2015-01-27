#ifndef SLOW_POINTER
#define SLOW_POINTER

class Pointer : public Component {
public:
  Pointer(Component* p) : Component(p)
  {
    _add(new Sprite(rect(0, 0, 32, 32), "hand.png", this));
  }

  void message(const Message &msg)
  {
    switch(msg.type)
    {
      case MOUSE_HOVER:
        _broadcast(Message(this, POSITION, msg.data<Rect>()));
        break;

      case MOUSE_CLICK:
        //location = msg.data<Rect>();
        //c = new StaticItem(location.x, location.y, "barrel.png", _parent);
        //_parent->message(Message(this, PLACE, c));
        break;

      default:
        _broadcast(msg);
    }
  }
};

#endif
