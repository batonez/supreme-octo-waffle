#pragma once

#include <glade/GladeObject.h>
#include <glade/State.h>
#include <glade/debug/log.h>

class Context;
class Block;
class ThatworldController;
class Gold;

class Play: public State
{
  friend class ThatworldPlayController;
  
  private:
    static const float BASE_RUNNING_SPEED;

    Vector3i movingDirection;
    Vector2i lookDirection;
    ThatworldController *controller;
    Gold *cube;

  public:
    Play();
    ~Play();

    virtual void init(Context &context);
    virtual void shutdown(Context &context);
    virtual void applyRules(Context &context);
};