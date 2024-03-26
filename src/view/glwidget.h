#ifndef VIEW_GLWIDGET_H
#define VIEW_GLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "../controller/controller.h"
#include "mainwindow.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit GLWidget(QWidget* parent = nullptr);
  GLWidget(MainWindow* mainWindow);
  MainWindow* mainWindow;

  void InitModel(std::string file);
  unsigned int getCountOfVertexesGL() { return count_of_vertexes_; }
  unsigned int getCountOfFacetsGL() { return count_of_facets_; }
  void setNameFile(std::string name) { name_file_ = name; };

  const std::string getFileName() { return name_file_; }
  const QColor& getColorBack() const { return color_back_; }
  const QColor& getColorPoint() const { return color_point_; }
  const QColor& getColorLine() const { return color_line_; }

  void SaveObjectGL();
  s21::MementoObject* getMementoObject() { return memento_; }
  void RestoreObject();

  void MoveX(double change);
  void MoveY(double change);
  void MoveZ(double change);
  void RotateX(double change);
  void RotateY(double change);
  void RotateZ(double change);
  void Scale(double change);
  void setColorBack(QColor color) { color_back_ = color; }
  void setCentral(bool central) { central_ = central; }
  void ResetVertexes();

  void setSizePoint(int size) { size_point_ = size; }
  void setColorPoint(QColor color) { color_point_ = color; }
  void setCustumPoint(int custum) { custum_point_ = custum; }

  void setThicknessLine(int size) { thickness_line_ = size; }
  void setColorLine(QColor color) { color_line_ = color; }
  void setDashLine(bool checked) { dash_line_ = checked; }

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  s21::Controller controller_;
  s21::AffinisOperation* affinisX_ =
      controller_.AffinisChange(new s21::XStrategy());
  s21::AffinisOperation* affinisY_ =
      controller_.AffinisChange(new s21::YStrategy());
  s21::AffinisOperation* affinisZ_ =
      controller_.AffinisChange(new s21::ZStrategy());
  s21::MementoObject* memento_ = controller_.SaveObject();

  void DrawModel();
  void DrawPoints();
  void DrawLines();
  void CentralizationModel();
  void Projection();

  std::string name_file_;
  std::vector<s21::Vertex> vertexes_{};
  std::vector<s21::Vertex> oringin_vertexes_{};
  std::vector<s21::Facet> facets_{};
  unsigned int count_of_vertexes_{};
  unsigned int count_of_facets_{};
  double old_move_x_{};
  double old_move_y_{};
  double old_move_z_{};
  double old_rotate_x_{};
  double old_rotate_y_{};
  double old_rotate_z_{};
  double old_scale_ = 1;
  QColor color_back_ = (Qt::black);
  bool central_ = false;

  int size_point_ = 1;
  QColor color_point_ = (Qt::white);
  int custum_point_{};

  int thickness_line_ = 1;
  QColor color_line_ = (Qt::red);
  bool dash_line_ = false;
};

#endif  // VIEW_GLWIDGET_H
