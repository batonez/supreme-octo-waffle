#pragma once

#include <glade/render/Drawable.h>

class Perception: public Drawable
{
  private:
    Vector3f halfplane;
    Vector3f lightDirection;
    Vector3f baseLookVector;

  public:
    Perception();
    void adjust();
    virtual ~Perception() {}
};
