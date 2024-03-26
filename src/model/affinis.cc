#include "affinis.h"

void s21::XStrategy::MoveCalculate(std::vector<Vertex>& vertexes,
                                   double change) {
  for (size_t i = 0; i < vertexes.size(); ++i) {
    vertexes[i].setX(vertexes[i].getX() + change);
  }
}

void s21::XStrategy::RotateCalculate(std::vector<Vertex>& vertexes,
                                     double change) {
  change = Converter(change);
  for (size_t i = 0; i < vertexes.size(); ++i) {
    double y = vertexes[i].getY();
    double z = vertexes[i].getZ();
    vertexes[i].setY(y * cos(change) + z * sin(change));
    vertexes[i].setZ(-y * sin(change) + z * cos(change));
  }
}

void s21::YStrategy::MoveCalculate(std::vector<Vertex>& vertexes,
                                   double change) {
  for (size_t i = 0; i < vertexes.size(); ++i) {
    vertexes[i].setY(vertexes[i].getY() + change);
  }
}

void s21::YStrategy::RotateCalculate(std::vector<Vertex>& vertexes,
                                     double change) {
  change = Converter(change);
  for (size_t i = 0; i < vertexes.size(); ++i) {
    double x = vertexes[i].getX();
    double z = vertexes[i].getZ();
    vertexes[i].setX(x * cos(change) + z * sin(change));
    vertexes[i].setZ(-x * sin(change) + z * cos(change));
  }
}

void s21::ZStrategy::MoveCalculate(std::vector<Vertex>& vertexes,
                                   double change) {
  for (size_t i = 0; i < vertexes.size(); ++i) {
    vertexes[i].setZ(vertexes[i].getZ() + change);
  }
}

void s21::ZStrategy::RotateCalculate(std::vector<Vertex>& vertexes,
                                     double change) {
  change = Converter(change);
  for (size_t i = 0; i < vertexes.size(); ++i) {
    double x = vertexes[i].getX();
    double y = vertexes[i].getY();
    vertexes[i].setX(x * cos(change) + y * sin(change));
    vertexes[i].setY(-x * sin(change) + y * cos(change));
  }
}

void s21::AffinisOperation::Move(std::vector<Vertex>& vertexes, double change) {
  strategy_->MoveCalculate(vertexes, change);
}

void s21::AffinisOperation::Rotate(std::vector<Vertex>& vertexes,
                                   double change) {
  strategy_->RotateCalculate(vertexes, change);
}

void s21::AffinisOperation::Scaling(std::vector<Vertex>& vertexes,
                                    double change) {
  for (size_t i = 0; i < vertexes.size(); ++i) {
    vertexes[i].setX(vertexes[i].getX() * change);
    vertexes[i].setY(vertexes[i].getY() * change);
    vertexes[i].setZ(vertexes[i].getZ() * change);
  }
}
