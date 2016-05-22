#pragma once

#include <glade/GladeObject.h>

class Terrain: public GladeObject
{
  protected:
    bool initialized;
    Drawable *view;

  public:
    static Transform::SharedVector cubeRotation;

    Terrain();
    virtual ~Terrain();

    virtual void initialize();
};
