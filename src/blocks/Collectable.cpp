#include <glade/render/ShaderProgram.h>
#include <glade/render/Drawable.h>
#include <glade/render/meshes/Cube.h>
#include <glade/util/Path.h>
#include <thatworld/ResourceManager.h>
#include <thatworld/blocks/Collectable.h>

extern Thatworld::ResourceManager *game_resource_manager;

Transform::SharedVector Collectable::cubeRotation(new Vector3f(0.0f, 0.0f, 0.0f));

Collectable::Collectable():
  view(NULL),
  initialized(false)
{
  setName("An object");
}

Collectable::~Collectable()
{
  if (view) {
    delete view;
    view = NULL;
  }
}

void Collectable::initialize()
{
  if (!initialized ) {
    std::shared_ptr<ShaderProgram> program =
      game_resource_manager->getShaderProgram(
        "lit_shape.vertex.glsl",
        "lit_shape.fragment.glsl"
      );
    
    view = new Drawable(game_resource_manager->getMesh(Glade::ResourceManager::MESH_CUBE), program);

    // TODO Get light direction from the global scene
    // TODO Light direction vector should be rotated by the camera matrix
    view->setUniform("uMaterialAmbient",   Vector4f(0.8f, 0.1f, 0.3f, 1.0f));
    view->setUniform("uMaterialDiffuse",   Vector4f(0.8f, 0.1f, 0.3f, 1.0f));
    view->setUniform("uMaterialSpecular",  Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
    view->setUniform("uMaterialShininess", 128.0f);

    view->getTransform()->setRotation(cubeRotation);
    view->getTransform()->setRotation(0.33f, 0.33f, 0.33f);
    
    addDrawable(view);
    initialized = true;
  }
}
