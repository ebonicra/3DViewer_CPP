#include "mementoobject.h"

void s21::MementoObject::CreateMemento(std::string& file_name,
                                       const std::vector<Vertex>& vertexes,
                                       double old_move_x, double old_move_y,
                                       double old_move_z, double old_rotate_x,
                                       double old_rotate_y, double old_rotate_z,
                                       double old_scale) {
  file_name_ = file_name;
  vertexes_ = vertexes;
  old_move_x_ = old_move_x;
  old_move_y_ = old_move_y;
  old_move_z_ = old_move_z;
  old_rotate_x_ = old_rotate_x;
  old_rotate_y_ = old_rotate_y;
  old_rotate_z_ = old_rotate_z;
  old_scale_ = old_scale;
}

void s21::MementoObject::WriteSettings(QSettings& settings) {
  settings.setValue("file_name", QString::fromStdString(file_name_));
  settings.setValue("old_move_x", old_move_x_);
  settings.setValue("old_move_y", old_move_y_);
  settings.setValue("old_move_z", old_move_z_);
  settings.setValue("old_rotate_x", old_rotate_x_);
  settings.setValue("old_rotate_y", old_rotate_y_);
  settings.setValue("old_rotate_z", old_rotate_z_);
  settings.setValue("old_scale", old_scale_);

  settings.setValue("vertex_count", static_cast<int>(vertexes_.size()));
  for (size_t i = 0; i < vertexes_.size(); ++i) {
    settings.setValue(QString("vertex_%1_x").arg(i), vertexes_[i].getX());
    settings.setValue(QString("vertex_%1_y").arg(i), vertexes_[i].getY());
    settings.setValue(QString("vertex_%1_z").arg(i), vertexes_[i].getZ());
  }
}

void s21::MementoObject::ReadSettings(const QSettings& settings) {
  file_name_ = settings.value("file_name").toString().toStdString();
  old_move_x_ = settings.value("old_move_x", 0.0).toDouble();
  old_move_y_ = settings.value("old_move_y", 0.0).toDouble();
  old_move_z_ = settings.value("old_move_z", 0.0).toDouble();
  old_rotate_x_ = settings.value("old_rotate_x", 0.0).toDouble();
  old_rotate_y_ = settings.value("old_rotate_y", 0.0).toDouble();
  old_rotate_z_ = settings.value("old_rotate_z", 0.0).toDouble();
  old_scale_ = settings.value("old_scale", 1.0).toDouble();

  size_t vertex_count = settings.value("vertex_count", 0).toUInt();
  for (size_t i = 0; i < vertex_count; ++i) {
    Vertex vertex;
    vertex.setX(settings.value(QString("vertex_%1_x").arg(i), 0.0).toDouble());
    vertex.setY(settings.value(QString("vertex_%1_y").arg(i), 0.0).toDouble());
    vertex.setZ(settings.value(QString("vertex_%1_z").arg(i), 0.0).toDouble());
    vertexes_.push_back(vertex);
  }
}
