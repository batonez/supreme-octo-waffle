#include <glade/render/ShaderProgram.h>
#include <glade/render/Drawable.h>
#include <glade/render/meshes/Square.h>
#include <glade/render/meshes/DynamicMesh.h>
#include <glade/render/meshes/DynamicMeshGenerator.h>
#include <glade/util/Path.h>
#include <thatworld/ResourceManager.h>
#include <thatworld/blocks/Terrain.h>

extern Thatworld::ResourceManager *game_resource_manager;

Terrain::Terrain():
  view(NULL),
  initialized(false)
{
  setName("An object");
}

Terrain::~Terrain()
{
  if (view) {
    delete view;
    view = NULL;
  }
}

void Terrain::initialize()
{
  if (!initialized ) {
    std::shared_ptr<ShaderProgram> program =
      game_resource_manager->getShaderProgram(
        "lit_shape.vertex.glsl",
        "lit_shape.fragment.glsl"
      );

    //view = new Drawable(game_resource_manager->getMesh(Glade::ResourceManager::MESH_SQUARE), program);
    
    std::shared_ptr<Glade::Mesh> mesh(new DynamicMesh());
    DynamicMeshGenerator generator;
    generator.generate(*((DynamicMesh*) mesh.get()));
    view = new Drawable(mesh, program);
    
    addDrawable(view);
    initialized = true;
  }
}
