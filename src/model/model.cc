#include "model.h"

s21::Model& s21::Model::getInstance() {
  static Model instance_;
  return instance_;
}

void s21::Model::OpenFile(const std::string& file_name) {
  ResetValues();
  file_.open(file_name);
  if (file_.is_open()) {
    file_is_valid_ = true;
    long size_file = getFileSize(file_name);
    vertexes_.reserve(size_file / (sizeof(double) * 3));
    facets_.reserve(size_file / (sizeof(unsigned int) * 3));
    Parse();
    file_.close();
  } else {
    file_is_valid_ = false;
    std::cerr << "Error opening file: " << file_name << std::endl;
  }
}

long s21::Model::getFileSize(std::string file_name) {
  struct stat file_information;
  int res = stat(file_name.c_str(), &file_information);
  return res == 0 ? file_information.st_size : -1;
}

void s21::Model::Parse() {
  std::string line;
  while (std::getline(file_, line) && file_is_valid_) {
    try {
      std::istringstream iss(line);
      std::string token;
      iss >> token;

      if (token == "v") {
        ReadVertex(iss);
        ++count_of_vertexes_;
      } else if (token == "f") {
        ReadFacet(iss);
        ++count_of_facets_;
      }
    } catch (const std::exception& e) {
      file_is_valid_ = false;
      std::cerr << "Error reading line: " << e.what() << std::endl;
    }
  }
  if (!file_is_valid_) ResetValues();
}

void s21::Model::ReadVertex(std::istringstream& iss) {
  Vertex vertex;
  iss >> vertex.x_ >> vertex.y_ >> vertex.z_;
  if (iss.fail()) {
    file_is_valid_ = false;
    std::cerr << "Error reading vertex: Invalid format" << std::endl;
  } else {
    vertexes_.push_back(vertex);
  }
}

void s21::Model::ReadFacet(std::istringstream& iss) {
  Facet facet;
  unsigned int count{}, first_num{};
  long int num_int{};
  std::string token, num_str;
  for (; iss >> token; ++count) {
    for (auto it = token.begin(); it != token.end() && *it != '/'; ++it) {
      num_str += *it;
    }

    num_int = std::stoi(num_str) - 1;
    if (num_int < 0 ||
        static_cast<long unsigned int>(num_int) > vertexes_.size()) {
      file_is_valid_ = false;
      std::cerr << "Error reading facets: Invalid format" << std::endl;
    } else {
      facet.vertex_indices_.push_back(num_int);
      if (count) {
        facet.vertex_indices_.push_back(num_int);
      } else {
        first_num = num_int;
      }
      num_str = "";
    }
  }
  if (count < 3) {
    file_is_valid_ = false;
    std::cerr << "Error reading facets: Invalid format" << std::endl;
  } else {
    facet.vertex_indices_.push_back(first_num);
    facet.facet_size_ = count * 2;
    facets_.push_back(facet);
  }
}

void s21::Model::ResetValues() {
  file_is_valid_ = false;
  vertexes_.clear();
  facets_.clear();
  count_of_vertexes_ = 0;
  count_of_facets_ = 0;
}
