#include "../MathUtils.h"

Transform::Transform() :
position(Vector3::Zero()),
rotation(Vector3::Zero()),
scale(Vector3::One())
{ }

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale) :
position(position), 
rotation(rotation), 
scale(scale)
{ }