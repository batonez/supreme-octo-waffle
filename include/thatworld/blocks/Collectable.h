#pragma once

#include <glade/GladeObject.h>

class Collectable: public GladeObject
{
  protected:
    bool initialized;
    Drawable *view;

  private:
    float halfplaneXZ;
    
  public:
    static Transform::SharedVector cubeRotation;

    Collectable();
    virtual ~Collectable();

    virtual void initialize(const std::string &texture_pack_name, float block_width, float block_height);
};
