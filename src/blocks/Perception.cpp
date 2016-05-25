#include <glade/math/Vector.h>
#include <thatworld/blocks/Perception.h>

Perception::Perception():
  lightDirection(0.0f, 0.0f, -1.0f),
  baseLookVector(0.0f, 0.0f, -1.0f)
{
  lightDirection.normalize();
  lightDirection.subtract(baseLookVector, halfplane);
  halfplane.normalize();
  
  setUniform("uLightDirection", lightDirection);
  setUniform("uLightAmbient",   Vector4f(0.5f, 0.5f, 0.5f, 1.0f));
  setUniform("uLightDiffuse",   Vector4f(0.5f, 0.5f, 0.5f, 1.0f));
  setUniform("uLightSpecular",  Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
  setUniform("uLightHalfplane", halfplane);
}

void Perception::adjust()
{
  Vector4f rotatedLightDirection4f;
  Vector4f lightDirection4f(lightDirection.x, lightDirection.y, lightDirection.z, 0.0f);

  // FIXME on the drawing stage it may be already different :(
  float viewMatrix[16];
  getTransform()->getCameraMatrix(viewMatrix);

  
  Matrix::multiplyMV(rotatedLightDirection4f, viewMatrix, lightDirection4f);

  Vector3f rotatedLightDirection;
  rotatedLightDirection.x = rotatedLightDirection4f.x;
  rotatedLightDirection.y = rotatedLightDirection4f.y;
  rotatedLightDirection.z = rotatedLightDirection4f.z;
  rotatedLightDirection.normalize();

  halfplane.set(rotatedLightDirection);
  halfplane.subtract(baseLookVector);
  halfplane.normalize();
  
// Something wrong with above calculations
// Two posiible reasons: the above "FIXME" and wrong multiplyMV method.
// Check that method on some well known values
  setUniform("uLightDirection", rotatedLightDirection);
  setUniform("uLightHalfplane", halfplane);
}
