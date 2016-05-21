#pragma once

#include <glade/util/ResourceManager.h>

class FileManager;

namespace Thatworld
{
  class ResourceManager: public Glade::ResourceManager
  {
    public:
      ResourceManager(FileManager *file_manager);
  };
}
