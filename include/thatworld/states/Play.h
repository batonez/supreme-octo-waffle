#pragma once

#include <glade/GladeObject.h>
#include <glade/Scene.h>
#include <glade/debug/log.h>

class Context;
class Block;
class ThatworldController;
class Collectable;
class Terrain;
class Perception;

class Play: public Scene
{
  friend class ThatworldPlayController;
  
  private:
    static const float BASE_RUNNING_SPEED;
    static const float MOUSE_SENSITIVITY;

    ThatworldController *controller;
    Vector3i movingDirection;
    Vector2f mouseLook;

    Collectable *cube;
    Terrain  *terrain;
    Perception *perception;

  public:
    Play();
    ~Play();

    virtual void init(Context &context);
    virtual void shutdown(Context &context);
    virtual void applyRules(Context &context);
};