#include "../MathUtils.h"

Matrix4x4::Matrix4x4()
{
  //(*this) = Matrix4x4::Identity();
}

Matrix4x4::Matrix4x4(Vector4 r0, Vector4 r1, Vector4 r2, Vector4 r3)
{
  m00 = r0.x;
  m01 = r0.y;
  m02 = r0.z;
  m03 = r0.w;

  m10 = r1.x;
  m11 = r1.y;
  m12 = r1.z;
  m13 = r1.w;

  m20 = r2.x;
  m21 = r2.y;
  m22 = r2.z;
  m23 = r2.w;

  m30 = r3.x;
  m31 = r3.y;
  m32 = r3.z;
  m33 = r3.w;
}

Matrix4x4 Matrix4x4::Identity()
{
  return Matrix4x4(
    Vector4(1.0f, 0.0f, 0.0f, 0.0f),
    Vector4(0.0f, 1.0f, 0.0f, 0.0f),
    Vector4(0.0f, 0.0f, 1.0f, 0.0f),
    Vector4(0.0f, 0.0f, 0.0f, 1.0f));
}