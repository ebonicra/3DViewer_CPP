#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <sys/stat.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

class Vertex {
 public:
  double getX() const noexcept { return x_; };
  double getY() const noexcept { return y_; };
  double getZ() const noexcept { return z_; };

  void setX(double change) { x_ = change; };
  void setY(double change) { y_ = change; };
  void setZ(double change) { z_ = change; };

 private:
  double x_{};
  double y_{};
  double z_{};

  friend class Model;
};

class Facet {
 public:
  std::vector<unsigned int> getVertexIndices() const noexcept {
    return vertex_indices_;
  };
  void setVertexIndices(std::vector<unsigned int> indices) {
    vertex_indices_ = indices;
  }

 private:
  std::vector<unsigned int> vertex_indices_{};
  unsigned int facet_size_{};

  friend class Model;
};

// Реализован принцип Singleton
class Model {
 public:
  static Model& getInstance();
  bool FileIsValid() const noexcept { return file_is_valid_; };
  std::vector<Vertex> getVertexes() const noexcept { return vertexes_; };
  std::vector<Facet> getFacets() const noexcept { return facets_; };
  unsigned int getCountOfVertexes() const noexcept {
    return count_of_vertexes_;
  };
  unsigned int getCountOfFacets() const noexcept { return count_of_facets_; };
  void OpenFile(const std::string& file_name);

 private:
  explicit Model() = default;
  Model(const Model& other) = delete;
  Model& operator=(const Model& other) = delete;
  ~Model() = default;

  std::ifstream file_{};
  bool file_is_valid_{};
  std::vector<Vertex> vertexes_{};
  std::vector<Facet> facets_{};
  unsigned int count_of_vertexes_{};
  unsigned int count_of_facets_{};

  long getFileSize(std::string file_name);
  void Parse();
  void ReadVertex(std::istringstream& iss);
  void ReadFacet(std::istringstream& iss);
  void ResetValues();
};

}  // namespace s21

#endif  // MODEL_MODEL_H_
