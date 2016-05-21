#include <algorithm>

#include <glade/Context.h>
#include <thatworld/Area.h>
#include <thatworld/ResourceManager.h>
#include <thatworld/blocks/Gold.h>
#include <thatworld/blocks/Player.h>
#include <thatworld/controls/ThatworldController.h>
#include <thatworld/states/Play.h>

#define DEBUG_GENERATOR 0

extern Thatworld::ResourceManager *game_resource_manager;

const float Play::BASE_ACCELERATION = 0.00001f;
const float Play::BASE_RUNNING_SPEED = 0.001f;

class ThatworldPlayController: public ThatworldController
{
  private:
    Context &context;
    Play &playState;
    
  public:
    ThatworldPlayController(Context &context_param, Play &play_state):
      ThatworldController(),
      playState(play_state),
      context(context_param)
    {}
    
    virtual bool buttonPress(int id, int terminalId)
    {
      bool handled = false;

      switch (id) {
        case ThatworldController::BUTTON_LEFT:
          playState.movingDirection.x = -1;
          handled = true;
          break;
        case ThatworldController::BUTTON_RIGHT:
          playState.movingDirection.x =  1;
          handled = true;
          break;
        case ThatworldController::BUTTON_UP:
          playState.movingDirection.y = 1;
          handled = true;
          break;
        case ThatworldController::BUTTON_DOWN:
          playState.movingDirection.y =  -1;
          handled = true;
          break;
        case ThatworldController::BUTTON_FORWARD:
          playState.movingDirection.z =  -1;
          handled = true;
          break;
        case ThatworldController::BUTTON_BACKWARD:
          playState.movingDirection.z =  1;
          handled = true;
          break;
        case ThatworldController::BUTTON_FIRE:
          handled = true;
          break;
      }
      
      return handled;
    }
  
    virtual bool buttonRelease(int id, int terminalId)
    {
      bool handled = false;
      
      switch (id) {
        case ThatworldController::BUTTON_LEFT:
          playState.movingDirection.x = 0;
          handled = true;
          break;
        case ThatworldController::BUTTON_RIGHT:
          playState.movingDirection.x = 0;
          handled = true;
          break;
        case ThatworldController::BUTTON_UP:
          playState.movingDirection.y = 0;
          handled = true;
          break;
        case ThatworldController::BUTTON_DOWN:
          playState.movingDirection.y = 0;
          handled = true;
          break;
        case ThatworldController::BUTTON_FORWARD:
          playState.movingDirection.z = 0;
          handled = true;
          break;
        case ThatworldController::BUTTON_BACKWARD:
          playState.movingDirection.z = 0;
          handled = true;
          break;
      }
      
      return handled;
    }
    
    virtual void init()
    {  
    }
};

Play::Play():
  State(),
  screenScaleX(0),
  screenScaleY(0),
  controller(NULL),
  player(NULL),
  cube(NULL)
{}

Play::~Play()
{
}

void Play::init(Context &context)
{
  log("AREA WIDTH BLOCKS: %d", Area::AREA_WIDTH_BLOCKS);
  context.renderer->setBackgroundColor(0.0f, 0.0f, 0.0f);
  context.renderer->setSceneProjectionMode(Glade::Renderer::PERSPECTIVE);
  //context.renderer->setDrawingOrderComparator(new Block.DrawingOrderComparator());
  
  screenScaleX = context.renderer->getViewportWidthCoords()  / 2;
  screenScaleY = context.renderer->getViewportHeightCoords() / 2;
  
  //blockWidth = blockHeight = min(
  //  context.renderer->getViewportWidthCoords()  / Area::AREA_WIDTH_BLOCKS,
  //  context.renderer->getViewportHeightCoords() / Area::AREA_WIDTH_BLOCKS
  //);
  
  blockWidth = blockHeight = 0.1f;
  
  log("BLOCK SIZE: %3.3f, %3.3f", blockWidth, blockHeight);
  
  // set actual speeds
  runningSpeed = BASE_RUNNING_SPEED * blockWidth;
  acceleration = BASE_ACCELERATION * blockWidth;
    
  // Create and initialize the player
  player = new Player();
  player->initialize("common", blockWidth, blockHeight);
  player->setName("Player");
  context.add(player);
  
  cube = new Gold();
  cube->setName("Gold");
  cube->initialize("cave", 1.0f, 1.0f);
  context.add(cube);
  
  controller = new ThatworldPlayController(context, *this);
  context.setController(*controller);
}

void Play::applyRules(Context &context)
{
  // Moving player character
  player->getTransform()->position->x += movingDirection.x * runningSpeed * context.timer.getDeltaTime();
  player->getTransform()->position->y += movingDirection.y * runningSpeed * context.timer.getDeltaTime();
  player->getTransform()->position->z += movingDirection.z * runningSpeed * 10.0 * context.timer.getDeltaTime();

//  player->getPhysicBody()->velocity.x = movingDirection.x * runningSpeed;
//  player->getPhysicBody()->velocity.y = movingDirection.y * runningSpeed;
  
  //player->getPhysicBody()->acceleration.x = movingDirection.x * acceleration;
  //player->getPhysicBody()->acceleration.y = movingDirection.y * acceleration;
  
  context.renderer->camera.position->x = player->getTransform()->position->x;
  context.renderer->camera.position->y = player->getTransform()->position->y;
  context.renderer->camera.position->z = player->getTransform()->position->z;
  
  Collectable::cubeRotation->set(30.0f, Collectable::cubeRotation->y + 5.0f, 0.0f);
}

int Play::getBlockCoordX(Block &object)
{
  return ::floor(((object.getTransform()->position->x + screenScaleX) / blockWidth));
}

int Play::getBlockCoordY(Block &object)
{
  return ::floor(((object.getTransform()->position->y + screenScaleY) / blockHeight));
}

int Play::areaCoordFromBlockCoord(int blockCoord)
{
  return blockCoord ? ::floor((float) blockCoord / Area::AREA_WIDTH_BLOCKS) : 0;
}

void Play::shutdown(Context &context)
{
  // TODO free level and other memory
  
  //context.setController(NULL);
  
  if (controller) {
    delete controller;
  }
}
