#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "../Utils/Point.hpp"
#include "../Utils/Utils.hpp"
#include "../Utils/Vector3.hpp"
#pragma once

class Graphics
{
private:
public:
  Graphics();
  void DrawTriangle(const Vec3f& v0, const Vec3f& v1, const Vec3f& v2);
  void DrawFlatTopTriangle(const Vec3f& v0, const Vec3f& v1, const Vec3f& v2);
  void DrawFlatBottomTriangle(const Vec3f& v0, const Vec3f& v1, const Vec3f& v2);
  ~Graphics();
};

#endif
