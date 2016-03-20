#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include "Math_Headers.h"
#include "Mesh.h"

namespace ObjLoadTypes
{
  using InFile = std::ifstream;

  using StringStream = std::istringstream;

  template <typename T>
  using Container = std::vector<T>;

  template <typename Key, typename Val>
  using AssocContainer = std::map<Key, Val>;

  using String = std::string;

  using Vec3 = glm::vec3;

  using Vec2 = glm::vec2;
}

class ObjLoader
{
  using Index = GLushort;

  //takes the given file and reads the contained mesh data.
  // the results are returned in the two out_* containers.
  //no checking is done that the file is actually a valid .obj, this is simply assumed
  //if there is an error loading the file, we silently fail
public:
  void Load(ObjLoadTypes::String file_path,
    Mesh* mesh);


private:

  void ReadPosition(ObjLoadTypes::StringStream& line);

  void ReadUV(ObjLoadTypes::StringStream& line);

  void ReadNormal(ObjLoadTypes::StringStream& line);

  void ReadFace(ObjLoadTypes::StringStream& line);

  //this will construct a vertex from values looked up from the individual storage containers
  //a positive index is interpreted as a 1-based absolute index
  //a negative index is interpreted as an offset from the back, where -1 is the last element
  //passing 0, or an index that is out of bounds will result in a default value being used
  Vertex MakeVertex(int pos_idx, int uv_idx, int normal_idx);

  //.obj specifies different pieces of vertex data separately and can index them separately.
  //these serve as intermediate storage
  ObjLoadTypes::Container<ObjLoadTypes::Vec3> positions_;
  ObjLoadTypes::Container<ObjLoadTypes::Vec2> uvs_;
  ObjLoadTypes::Container<ObjLoadTypes::Vec3> normals_;

  //this class will help us get the correct indices for our actual complete vertices
  //it also provides us with the full list of unique vertices at the end
  class LoadHelper
  {
  public:
    LoadHelper(){ next_index_ = 0; }
    ObjLoadTypes::Container<Vertex>&& GetVertexList();

    Index GetIndexByVertex(const Vertex& v);

  private:

    //we store the index of each unique vertex here
    ObjLoadTypes::AssocContainer<Vertex, Index> indices_by_vertex_;
    //the actual list of unique vertices
    ObjLoadTypes::Container<Vertex> vertices_;

    //the index for the next unknown vertex
    Index next_index_;

  } helper_;

  //these are the actual indices for our mesh that go together with the vertices returned by LoadHelper
  ObjLoadTypes::Container<Index> indices_;
};
