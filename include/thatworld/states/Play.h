#pragma once

#include <glade/GladeObject.h>
#include <glade/State.h>
#include <glade/debug/log.h>
#include <thatworld/Area.h>

class Context;
class Block;
class ThatworldController;
class Player;
class Gold;

class Play: public State
{
  friend class ThatworldPlayController;
  
  private:
    static const float BASE_RUNNING_SPEED;
    static const float BASE_ACCELERATION;

    float runningSpeed;
    float acceleration;
    float blockWidth, blockHeight;
    float screenScaleX, screenScaleY;
    Vector3i movingDirection;
    ThatworldController *controller;
    Player *player;
    Gold *cube;

  public:
    Play();
    ~Play();

    virtual void init(Context &context);
    virtual void shutdown(Context &context);
    virtual void applyRules(Context &context);

    private:
      float blockToWorldCoordX(int blockX)
      {
        return blockX * blockWidth - screenScaleX + blockWidth / 2;
      }

      float blockToWorldCoordY(int blockY)
      {
        return blockY * blockHeight - screenScaleY + blockHeight / 2;
      }

      int getBlockCoordX(Block &object);
      int getBlockCoordY(Block &object);
      int areaCoordFromBlockCoord(int blockCoord);
};