#pragma once

#include <glade/GladeObject.h>
#include <glade/State.h>
#include <glade/debug/log.h>

class Context;
class Block;
class ThatworldController;
class Collectable;

class Play: public State
{
  friend class ThatworldPlayController;
  
  private:
    static const float BASE_RUNNING_SPEED;
    static const float MOUSE_SENSITIVITY;

    Vector3i movingDirection;
    Vector2f mouseLook;
    ThatworldController *controller;
    Collectable *cube;

  public:
    Play();
    ~Play();

    virtual void init(Context &context);
    virtual void shutdown(Context &context);
    virtual void applyRules(Context &context);
};