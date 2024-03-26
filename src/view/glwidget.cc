#include "glwidget.h"

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

GLWidget::GLWidget(MainWindow* mv) { mainWindow = mv; }

void GLWidget::InitModel(std::string file) {
  controller_.LoadModel(file);
  oringin_vertexes_ = controller_.getModel()->getVertexes();
  if (file != name_file_) vertexes_ = oringin_vertexes_;
  facets_ = controller_.getModel()->getFacets();
  count_of_vertexes_ = controller_.getModel()->getCountOfVertexes();
  count_of_facets_ = controller_.getModel()->getCountOfFacets();
};

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void GLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GLWidget::paintGL() {
  Projection();
  glClearColor(color_back_.redF(), color_back_.greenF(), color_back_.blueF(),
               color_back_.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  DrawModel();
}

void GLWidget::DrawModel() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnableClientState(GL_VERTEX_ARRAY);
  CentralizationModel();
  DrawPoints();
  DrawLines();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::DrawPoints() {
  if (custum_point_ == 0) {
    glPointSize(1);
  } else {
    if (custum_point_ == 1) glEnable(GL_POINT_SMOOTH);
    glPointSize(size_point_);
    glColor3f(color_point_.redF(), color_point_.greenF(), color_point_.blueF());
  }
  glVertexPointer(3, GL_DOUBLE, sizeof(s21::Vertex), vertexes_.data());
  glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(vertexes_.size()));
  glDisable(GL_POINT_SMOOTH);
}

void GLWidget::DrawLines() {
  std::vector<GLuint> lineIndices;
  for (const auto& facet : facets_) {
    auto facetLineIndices = facet.getVertexIndices();
    lineIndices.insert(lineIndices.end(), facetLineIndices.begin(),
                       facetLineIndices.end());
  }

  if (dash_line_ == true) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0F0F);
  }
  glLineWidth(thickness_line_);
  glColor3f(color_line_.redF(), color_line_.greenF(), color_line_.blueF());
  glDrawElements(GL_LINES, static_cast<GLsizei>(lineIndices.size()),
                 GL_UNSIGNED_INT, lineIndices.data());
  glDisable(GL_LINE_STIPPLE);
}

void GLWidget::CentralizationModel() {
  double minX = std::numeric_limits<double>::max();
  double minY = std::numeric_limits<double>::max();
  double minZ = std::numeric_limits<double>::max();
  double maxX = std::numeric_limits<double>::lowest();
  double maxY = std::numeric_limits<double>::lowest();
  double maxZ = std::numeric_limits<double>::lowest();
  for (const auto& vertex : oringin_vertexes_) {
    minX = std::min(minX, vertex.getX());
    minY = std::min(minY, vertex.getY());
    minZ = std::min(minZ, vertex.getZ());
    maxX = std::max(maxX, vertex.getX());
    maxY = std::max(maxY, vertex.getY());
    maxZ = std::max(maxZ, vertex.getZ());
  }
  double centerX = (minX + maxX) / 2.0;
  double centerY = (minY + maxY) / 2.0;
  double centerZ = (minZ + maxZ) / 2.0;
  double maxDist =
      std::max(std::max(maxX - centerX, maxY - centerY), maxZ - centerZ);
  double scaleFactor = 1.0 / maxDist;
  glScaled(scaleFactor, scaleFactor, scaleFactor);
  glTranslated(-centerX, -centerY, -centerZ);
}

void GLWidget::Projection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (central_ == true) {
    float fov = 60.0 * M_PI / 180;
    float heapHeight = 1 / (2 * tan(fov / 2));
    glFrustum(-1, 1, -1, 1, heapHeight, 1000);
    glTranslated(0, 0, -heapHeight * 1.5);
  } else {
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
  }
  glMatrixMode(GL_MODELVIEW);
}

void GLWidget::MoveX(double change) {
  affinisX_->Move(vertexes_, change - old_move_x_);
  old_move_x_ = change;
}

void GLWidget::MoveY(double change) {
  affinisY_->Move(vertexes_, change - old_move_y_);
  old_move_y_ = change;
}

void GLWidget::MoveZ(double change) {
  affinisZ_->Move(vertexes_, change - old_move_z_);
  old_move_z_ = change;
}

void GLWidget::RotateX(double change) {
  affinisX_->Rotate(vertexes_, change - old_rotate_x_);
  old_rotate_x_ = change;
}

void GLWidget::RotateY(double change) {
  affinisY_->Rotate(vertexes_, change - old_rotate_y_);
  old_rotate_y_ = change;
}

void GLWidget::RotateZ(double change) {
  affinisZ_->Rotate(vertexes_, change - old_rotate_z_);
  old_rotate_z_ = change;
}

void GLWidget::Scale(double change) {
  affinisX_->Scaling(vertexes_, change / old_scale_);
  old_scale_ = change;
}

void GLWidget::ResetVertexes() { vertexes_ = oringin_vertexes_; }

void GLWidget::SaveObjectGL() {
  memento_->CreateMemento(name_file_, vertexes_, old_move_x_, old_move_y_,
                          old_move_z_, old_rotate_x_, old_rotate_y_,
                          old_rotate_z_, old_scale_);
}

void GLWidget::RestoreObject() {
  name_file_ = memento_->getFileName();
  vertexes_ = memento_->getVertexes();
  old_move_x_ = memento_->getOldMoveX();
  old_move_y_ = memento_->getOldMoveY();
  old_move_z_ = memento_->getOldMoveZ();
  old_rotate_x_ = memento_->getOldRotateX();
  old_rotate_y_ = memento_->getOldRotateY();
  old_rotate_z_ = memento_->getOldRotateZ();
  old_scale_ = memento_->getOldScale();
}
