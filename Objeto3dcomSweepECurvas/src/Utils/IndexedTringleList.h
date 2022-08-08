#pragma once

#include <vector>
#include "./Vector3.hpp"

struct IndexedTringuleList
{
  IndexedTringuleList(std::vector<Vec3f> verts_in, std::vector<size_t> indices_in)
      : vertices(std::move(verts_in)),
        indices(std::move(indices_in))
  {
    cullFlags.resize(indices.size() / 3);
  }
  std::vector<Vec3f> vertices;
  std::vector<size_t> indices;
  std::vector<bool> cullFlags;
};