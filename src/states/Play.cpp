#include <algorithm>
#include <cmath>

#include <glade/Context.h>
#include <glade/math/util.h>
#include <thatworld/blocks/Gold.h>
#include <thatworld/controls/ThatworldController.h>
#include <thatworld/states/Play.h>

#define DEBUG_GENERATOR 0

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
          playState.movingDirection.z = -1;
          handled = true;
          break;
        case ThatworldController::BUTTON_DOWN:
          playState.movingDirection.z =  1;
          handled = true;
          break;
        case ThatworldController::BUTTON_FORWARD:
          playState.lookDirection.x =  -1;
          handled = true;
          break;
        case ThatworldController::BUTTON_BACKWARD:
          playState.lookDirection.x =  1;
          handled = true;
          break;
        case ThatworldController::BUTTON_FIRE:
          handled = true;
          break;
        case ThatworldController::BUTTON_STRAFE_LEFT:
          playState.lookDirection.y = -1;
          handled = true;
          break;
        case ThatworldController::BUTTON_STRAFE_RIGHT:
          playState.lookDirection.y =  1;
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
        case ThatworldController::BUTTON_RIGHT:
          playState.movingDirection.x = 0;
          handled = true;
          break;
        case ThatworldController::BUTTON_UP:
        case ThatworldController::BUTTON_DOWN:
          playState.movingDirection.z = 0;
          handled = true;
          break;
        case ThatworldController::BUTTON_FORWARD:
        case ThatworldController::BUTTON_BACKWARD:
          playState.lookDirection.x = 0;
          handled = true;
          break;
        case ThatworldController::BUTTON_STRAFE_LEFT:
        case ThatworldController::BUTTON_STRAFE_RIGHT:
          playState.lookDirection.y = 0;
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
  controller(NULL),
  cube(NULL)
{}

Play::~Play()
{
}

void Play::init(Context &context)
{
  context.renderer->setBackgroundColor(0.0f, 0.0f, 0.0f);
  context.renderer->setSceneProjectionMode(Glade::Renderer::PERSPECTIVE);

  cube = new Gold();
  cube->setName("Gold");
  cube->initialize("cave", 1.0f, 1.0f);
  context.add(cube);

  controller = new ThatworldPlayController(context, *this);
  context.setController(*controller);
}

void Play::applyRules(Context &context)
{
  ;
  // Moving player character
  context.renderer->camera.position->x += movingDirection.x * BASE_RUNNING_SPEED * context.timer.getDeltaTime() * ::cosf(::degrees_to_radians(context.renderer->camera.rotation->y));
  context.renderer->camera.position->x -= movingDirection.z * BASE_RUNNING_SPEED * context.timer.getDeltaTime() * ::sinf(::degrees_to_radians(context.renderer->camera.rotation->y));

  context.renderer->camera.position->y += movingDirection.y * BASE_RUNNING_SPEED * context.timer.getDeltaTime();

  context.renderer->camera.position->z += movingDirection.z * BASE_RUNNING_SPEED * context.timer.getDeltaTime() * ::cosf(::degrees_to_radians(context.renderer->camera.rotation->y));
  context.renderer->camera.position->z += movingDirection.x * BASE_RUNNING_SPEED * context.timer.getDeltaTime() * ::sinf(::degrees_to_radians(context.renderer->camera.rotation->y));

  // Rotating player character
  context.renderer->camera.rotation->x += lookDirection.x * 20.0 * BASE_RUNNING_SPEED * context.timer.getDeltaTime();
  context.renderer->camera.rotation->y += lookDirection.y * 20.0 * BASE_RUNNING_SPEED * context.timer.getDeltaTime();

  //Collectable::cubeRotation->set(30.0f, Collectable::cubeRotation->y + 5.0f, 0.0f);
}

void Play::shutdown(Context &context)
{
  // TODO free level and other memory
  
  //context.setController(NULL);
  
  if (controller) {
    delete controller;
  }
}
