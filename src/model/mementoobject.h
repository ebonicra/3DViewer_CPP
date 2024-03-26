#ifndef MODEL_MEMENTOOBJECT_H_
#define MODEL_MEMENTOOBJECT_H_

#include <QSettings>

#include "model.h"

namespace s21 {

// Реализован принцип Memento
class MementoObject {
 public:
  MementoObject() = default;
  ~MementoObject() = default;

  void CreateMemento(std::string& file_name,
                     const std::vector<Vertex>& vertexes, double old_move_x,
                     double old_move_y, double old_move_z, double old_rotate_x,
                     double old_rotate_y, double old_rotate_z,
                     double old_scale);

  void WriteSettings(QSettings& settings);
  void ReadSettings(const QSettings& settings);

  const std::string getFileName() { return file_name_; }
  std::vector<Vertex> getVertexes() const { return vertexes_; }
  double getOldMoveX() const { return old_move_x_; }
  double getOldMoveY() const { return old_move_y_; }
  double getOldMoveZ() const { return old_move_z_; }
  double getOldRotateX() const { return old_rotate_x_; }
  double getOldRotateY() const { return old_rotate_y_; }
  double getOldRotateZ() const { return old_rotate_z_; }
  double getOldScale() const { return old_scale_; }

 private:
  std::string file_name_;
  std::vector<Vertex> vertexes_{};
  double old_move_x_{};
  double old_move_y_{};
  double old_move_z_{};
  double old_rotate_x_{};
  double old_rotate_y_{};
  double old_rotate_z_{};
  double old_scale_{};
};

}  // namespace s21

#endif  // MODEL_MEMENTOOBJECT_H_
