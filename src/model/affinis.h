#ifndef MODEL_AFFINIS_H_
#define MODEL_AFFINIS_H_

#include <cmath>
#include <utility>

#include "model.h"

namespace s21 {

// Реализован принцип Strategy вроде
class Strategy {
 public:
  virtual void MoveCalculate(std::vector<Vertex>& vertexes, double change) = 0;
  virtual void RotateCalculate(std::vector<Vertex>& vertexes,
                               double change) = 0;
  double Converter(double angle) { return angle * acos(-1) / 180.0; }
  virtual ~Strategy() {}
};

class XStrategy : public Strategy {
 public:
  void MoveCalculate(std::vector<Vertex>& vertexes, double change) override;
  void RotateCalculate(std::vector<Vertex>& vertexes, double change) override;
};

class YStrategy : public Strategy {
 public:
  void MoveCalculate(std::vector<Vertex>& vertexes, double change) override;
  void RotateCalculate(std::vector<Vertex>& vertexes, double change) override;
};

class ZStrategy : public Strategy {
 public:
  void MoveCalculate(std::vector<Vertex>& vertexes, double change) override;
  void RotateCalculate(std::vector<Vertex>& vertexes, double change) override;
};

class AffinisOperation {
 public:
  AffinisOperation(Strategy* strategy) : strategy_(strategy) {}
  ~AffinisOperation() { delete strategy_; }
  void Move(std::vector<Vertex>& vertexes, double change);
  void Rotate(std::vector<Vertex>& vertexes, double change);
  void Scaling(std::vector<Vertex>& vertexes, double change);

 private:
  Strategy* strategy_;
};

}  // namespace s21

#endif  // MODEL_AFFINIS_H_
