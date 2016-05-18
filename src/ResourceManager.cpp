#pragma once

#include <sstream>

#include <glade/util/CSVReader.h>
#include <glade/debug/log.h>
#include <glade/exception/GladeFileNotFoundException.h>
#include <thatworld/exception/ThatworldException.h>
#include <thatworld/LevelInfo.h>
#include <thatworld/blocks/Block.h>
#include <thatworld/blocks/Terrain.h>
#include <thatworld/blocks/Player.h>
#include <thatworld/ResourceManager.h>

namespace Thatworld
{
  ResourceManager::ResourceManager(FileManager *file_manager):
    Glade::ResourceManager(file_manager),
    LEVELS_SUBDIRECTORY("levels"),
    LEVELS_DESC_FILE_PATH("levels.desc"),
    TEXTURES_SUBDIRECTORY("textures")
  {}

  int ResourceManager::getNumberOfLevelPacks()
  {
    if (levelPacks.empty()) {
      loadLevelPacksInfo();
    }
    
    return levelPacks.size();
  }
  
  std::shared_ptr<LevelPackInfo> ResourceManager::getLevelPackInfo(int index)
  {
    if (levelPacks.empty()) {
      loadLevelPacksInfo();
    }
    
    return levelPacks[index];
  }
  
  void ResourceManager::loadLevelPacksInfo()
  {
    std::ifstream rawLevelsDesc;
    fileManager->getFileContents(LEVELS_SUBDIRECTORY + LEVELS_DESC_FILE_PATH, rawLevelsDesc);
    
    std::vector<std::vector<std::string> > levelsDesc;
    CSVReader::read(rawLevelsDesc, levelsDesc);
    
    std::vector<std::vector<std::string> >::iterator i = levelsDesc.begin();
    std::shared_ptr<LevelPackInfo> pack;
    LevelInfo levelInfo;
    
    while (i != levelsDesc.end()) {
      if ((*i)[0] == "pack") {
        if (pack != nullptr && !pack->levels.empty()) {
          levelPacks.push_back(pack);
        }
        
        pack.reset(new LevelPackInfo);
        pack->title = (*i)[1];
      } else if (pack != nullptr) {
        levelInfo.path = (*i)[0];
        levelInfo.title = (*i)[1];
        pack->levels.push_back(levelInfo);
      }
      
      ++i;
    }
    
    if (pack != nullptr && !pack->levels.empty()) {
      levelPacks.push_back(pack);
    }
  }

  std::shared_ptr<Texture> ResourceManager::getTexture(const std::string texture_pack_name, const Path &image_filename,
    const Path &texture_data_filename, bool use_nulltexture)
  {
    Vector2i frameSize;
    
    Path bar = TEXTURES_SUBDIRECTORY + texture_pack_name + texture_data_filename;
    
    if (texture_data_filename.toString().length()) {
      // FIXME! Since we are loading texture data file without Glade resource manager, we should cache it here
      std::ifstream textureInfoStream;
      std::vector<std::vector<std::string> > textureInfo;
      
      try {
        fileManager->getFileContents(TEXTURES_SUBDIRECTORY + texture_pack_name + texture_data_filename, textureInfoStream);
        CSVReader::read(textureInfoStream, textureInfo);
      } catch (GladeFileNotFoundException &e) {        
        fileManager->getFileContents(TEXTURES_SUBDIRECTORY + "common" + texture_data_filename, textureInfoStream);
        CSVReader::read(textureInfoStream, textureInfo);
      }
     
      try {
        frameSize.x = atoi(textureInfo.at(0).at(0).c_str());
        frameSize.y = atoi(textureInfo.at(0).at(1).c_str());
      } catch (std::out_of_range &e) {
        log("Thatworld ResourceManger: Warning: Texture data is incorrect or was not provided, using zero values");
        frameSize.x = frameSize.y = 0;
      }
    } else {
      frameSize.x = frameSize.y = 0;
    }
    
    std::shared_ptr<Texture> result;
    
    
    Path foo = TEXTURES_SUBDIRECTORY + texture_pack_name + image_filename;
    
    try {
      result = Glade::ResourceManager::getTexture(TEXTURES_SUBDIRECTORY + texture_pack_name + image_filename, frameSize.x, frameSize.y);
    } catch (GladeFileNotFoundException &e) {
      try {
        result = Glade::ResourceManager::getTexture(TEXTURES_SUBDIRECTORY + "common" + image_filename, frameSize.x, frameSize.y);
      } catch (GladeFileNotFoundException &e) {
        if (use_nulltexture) {
          result = Glade::ResourceManager::getTexture(TEXTURES_SUBDIRECTORY + "notexture.png", 0, 0);
        } else {
          throw e;
        }
      }
    }
    
    return result;
  }
}

