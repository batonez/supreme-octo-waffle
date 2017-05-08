#include <algorithm>
#include <cmath>

#include <glade/Context.h>
#include <glade/math/util.h>
#include <glade/render/Perception.h>
#include <glade/render/GladeRenderer.h>
#include <thatworld/blocks/Collectable.h>
#include <thatworld/blocks/Terrain.h>
#include <thatworld/controls/ThatworldController.h>
#include <thatworld/states/Play.h>
#include <thatworld/ResourceManager.h>

#define DEBUG_GENERATOR 0

extern Thatworld::ResourceManager *game_resource_manager;

const float Play::BASE_RUNNING_SPEED = 0.1f;
const float Play::MOUSE_SENSITIVITY = 0.01f;

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
        case ThatworldController::BUTTON_STRAFE_LEFT:
          playState.mouseLook.y = -1;
          handled = true;
          break;
        case ThatworldController::BUTTON_STRAFE_RIGHT:
          playState.mouseLook.y =  1;
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
          playState.movingDirection.y = 0;
          handled = true;
          break;
        case ThatworldController::BUTTON_FORWARD:
        case ThatworldController::BUTTON_BACKWARD:
          playState.movingDirection.z = 0;
          handled = true;
          break;
        case ThatworldController::BUTTON_STRAFE_LEFT:
        case ThatworldController::BUTTON_STRAFE_RIGHT:
          playState.mouseLook.y = 0;
          handled = true;
          break;
      }
      
      return handled;
    }
    
    virtual bool pointerMove(float axisX, float axisY, float axisZ, int controlId, int terminalId)
    {
      playState.mouseLook.x = axisY;
      playState.mouseLook.y = axisX;
      return true;
    }
    
    virtual void init()
    {  
    }
};

Play::Play():
  Scene(),
  controller(NULL),
  cube(NULL),
  perception(NULL),
  terrain(NULL)
{}

Play::~Play()
{
}

void Play::init(Context &context)
{
  context.renderer->setBackgroundColor(0.0f, 0.0f, 0.0f);
  context.renderer->setSceneProjectionMode(Glade::Renderer::PERSPECTIVE);

  cube = new Collectable();
  cube->initialize();
  context.add(cube);

  cube->getTransform()->position->y = 2.0f;
  
  //terrain = new Terrain();
  //terrain->initialize();
  //context.add(terrain);
  
  //terrain->getTransform()->rotation->x = -PI / 2.0f;
  //terrain->getTransform()->position->x = -5.0f;
  //terrain->getTransform()->position->z = -5.0f;
  
  perception = new Perception();
  context.renderer->setPerception(perception);
  
  context.renderer->getCamera()->position->z = 5.0f;
  context.renderer->getCamera()->position->y = 1.0f;
  
  controller = new ThatworldPlayController(context, *this);
  context.setController(*controller);
}

void Play::applyRules(Context &context)
{
  // Moving player character
  context.renderer->getCamera()->position->x += movingDirection.x * BASE_RUNNING_SPEED * ::cosf(context.renderer->getCamera()->rotation->y);
  context.renderer->getCamera()->position->x -= movingDirection.z * BASE_RUNNING_SPEED * ::sinf(context.renderer->getCamera()->rotation->y);

  context.renderer->getCamera()->position->y += movingDirection.y * BASE_RUNNING_SPEED;

  context.renderer->getCamera()->position->z += movingDirection.z * BASE_RUNNING_SPEED * ::cosf(context.renderer->getCamera()->rotation->y);
  context.renderer->getCamera()->position->z += movingDirection.x * BASE_RUNNING_SPEED * ::sinf(context.renderer->getCamera()->rotation->y);

  // Rotating player character
  context.renderer->getCamera()->rotation->x += mouseLook.x * MOUSE_SENSITIVITY;
  context.renderer->getCamera()->rotation->y += mouseLook.y * MOUSE_SENSITIVITY;

  // TODO this should be done in the Transform class
  context.renderer->getCamera()->rotation->x = ::simplify_angle_radians(context.renderer->getCamera()->rotation->x);
  context.renderer->getCamera()->rotation->y = ::simplify_angle_radians(context.renderer->getCamera()->rotation->y);
  mouseLook.x = mouseLook.y = 0;

  Collectable::cubeRotation->y += 0.002f;
  //terrain->getTransform()->rotation->z += 0.01f;
}

void Play::shutdown(Context &context)
{
  // TODO free level and other memory
  
  //context.setController(NULL);
  
  if (controller) {
    delete controller;
  }
}
