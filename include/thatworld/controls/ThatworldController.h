#pragma once

#include <glade/controls/VirtualController.h>

class ThatworldController : public VirtualController
{
  public:
    // Virtual controls
    static const int BUTTON_ESCAPE       = 1;
    static const int BUTTON_FIRE         = 2;
    static const int BUTTON_LEFT         = 3;
    static const int BUTTON_RIGHT        = 4;
    static const int BUTTON_UP           = 5;
    static const int BUTTON_DOWN         = 6;
    static const int BUTTON_USE          = 7;
    static const int BUTTON_FORWARD      = 8;
    static const int BUTTON_BACKWARD     = 9;
    static const int BUTTON_STRAFE_LEFT  = 10;
    static const int BUTTON_STRAFE_RIGHT = 11;
    static const int POINTER_MOVE        = 100;
    static const int POINTER_POINT       = 101;
    
    virtual bool buttonPress(int controlId, int terminalId)
    {
      return false;
    }
    
    virtual bool buttonRelease(int controlId, int terminalId)
    {
      return false;
    }
    
    virtual bool pointerMove(float axisX, float axisY, float axisZ, int controlId, int terminalId)
    {
      return false;
    }

    virtual bool pointerDown(float axisX, float axisY, float axisZ, int controlId, int terminalId)
    {
      return false;
    }

    virtual bool pointerUp(float axisX, float axisY, float axisZ, int controlId, int terminalId)
    {
      return false;
    }
    
    virtual void init()
    {
    }
};
