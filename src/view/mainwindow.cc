#include "mainwindow.h"

#include <QVBoxLayout>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setWindowTitle("3D Viewer");
  GLWidget* glWidget = new GLWidget(this);
  QWidget* centralWidget = new QWidget(this);
  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget(glWidget);
  centralWidget->setLayout(layout);
  setCentralWidget(centralWidget);
  glWidget->mainWindow = this;
  timer = new (QTimer);
  gif_images = new QImage[50];
  connect(timer, SIGNAL(timeout()), this, SLOT(save_frame()));
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete timer;
  delete[] gif_images;
  delete ui;
}

void MainWindow::on_loadModel_triggered() {
  QString file_name = QFileDialog::getOpenFileName(this, "Open a file");
  QFileInfo file_info(file_name);
  QString fileName = file_info.fileName();

  on_pb_reset_clicked();
  ui->widget->InitModel(file_name.toStdString());

  ui->lb_name->setText("Name: " + fileName);
  ui->lb_vertices->setText("Vertexes: " +
                           QString::number(ui->widget->getCountOfVertexesGL()));
  ui->lb_edges->setText("Facets: " +
                        QString::number(ui->widget->getCountOfFacetsGL()));
  ui->widget->setNameFile(file_name.toStdString());
  setWindowTitle(fileName);
  ui->widget->update();
}

void MainWindow::on_x_move_slider_valueChanged(int value) {
  ui->le_move_x->setText(QString::number(value));
  ui->widget->MoveX((double)(value) / 10);
  ui->widget->update();
}

void MainWindow::on_y_move_slider_valueChanged(int value) {
  ui->le_move_y->setText(QString::number(value));
  ui->widget->MoveY((double)(value) / 10);
  ui->widget->update();
}

void MainWindow::on_z_move_slider_valueChanged(int value) {
  ui->le_move_z->setText(QString::number(value));
  ui->widget->MoveZ((double)(value) / 10);
  ui->widget->update();
}

void MainWindow::on_x_rotate_slider_valueChanged(int value) {
  ui->le_rotate_x->setText(QString::number(value));
  ui->widget->RotateX((double)value);
  ui->widget->update();
}

void MainWindow::on_y_rotate_slider_valueChanged(int value) {
  ui->le_rotate_y->setText(QString::number(value));
  ui->widget->RotateY((double)value);
  ui->widget->update();
}

void MainWindow::on_z_rotate_slider_valueChanged(int value) {
  ui->le_rotate_z->setText(QString::number(value));
  ui->widget->RotateZ((double)value);
  ui->widget->update();
}

void MainWindow::on_scale_slider_valueChanged(int value) {
  ui->le_scale->setText(QString::number(value));
  ui->widget->Scale((double)value / 100);
  ui->widget->update();
}

void MainWindow::on_pb_bcolor_clicked() {
  QColorDialog dialog(this);
  dialog.exec();
  ui->widget->setColorBack(dialog.currentColor());
  ui->widget->update();
}

void MainWindow::on_cb_parallel_toggled(bool checked) {
  if (checked == false) {
    ui->cb_central->setChecked(true);
  } else {
    ui->cb_central->setChecked(false);
    ui->widget->setCentral(false);
    ui->widget->update();
  }
}

void MainWindow::on_cb_central_toggled(bool checked) {
  if (checked == false) {
    ui->cb_parallel->setChecked(true);
  } else {
    ui->cb_parallel->setChecked(false);
    ui->widget->setCentral(true);
    ui->widget->update();
  }
}

void MainWindow::on_exit_triggered() { QApplication::quit(); }

void MainWindow::on_pb_reset_clicked() {
  ui->x_move_slider->setSliderPosition(0);
  ui->le_move_x->setText(QString::number(0));
  ui->y_move_slider->setSliderPosition(0);
  ui->le_move_y->setText(QString::number(0));
  ui->z_move_slider->setSliderPosition(0);
  ui->le_move_z->setText(QString::number(0));
  ui->x_rotate_slider->setSliderPosition(0);
  ui->le_rotate_x->setText(QString::number(0));
  ui->y_rotate_slider->setSliderPosition(0);
  ui->le_rotate_y->setText(QString::number(0));
  ui->z_rotate_slider->setSliderPosition(0);
  ui->le_rotate_z->setText(QString::number(0));
  ui->scale_slider->setSliderPosition(100);
  ui->le_scale->setText(QString::number(100));
  ui->cb_solid->setChecked(true);
  ui->widget->setDashLine(false);
  ui->thicknesss_slider->setSliderPosition(0);
  ui->widget->setThicknessLine(1);
  ui->widget->setColorLine(Qt::red);
  ui->size_slider->setSliderPosition(0);
  ui->widget->setSizePoint(0);
  ui->widget->setColorPoint(Qt::white);
  ui->cb_none->setChecked(true);
  ui->cb_circle->setChecked(false);
  ui->cb_square->setChecked(false);
  ui->widget->setCustumPoint(0);
  ui->cb_parallel->setChecked(true);
  ui->widget->setCentral(false);
  ui->widget->setColorBack(Qt::black);
  ui->widget->ResetVertexes();
  ui->widget->update();
}

void MainWindow::on_size_slider_valueChanged(int value) {
  ui->widget->setSizePoint(value);
  ui->widget->update();
}

void MainWindow::on_pb_vcolor_clicked() {
  QColor point_c =
      QColorDialog::getColor(Qt::white, this, "Choose vertices color");
  ui->widget->setColorPoint(point_c);
  ui->widget->update();
}

void MainWindow::on_cb_none_clicked() {
  ui->cb_none->setChecked(true);
  ui->cb_circle->setChecked(false);
  ui->cb_square->setChecked(false);
  ui->widget->setCustumPoint(0);
  ui->widget->update();
}

void MainWindow::on_cb_circle_clicked() {
  if (ui->cb_circle->isChecked() == false) {
    ui->cb_none->setChecked(true);
    on_cb_none_clicked();
  } else {
    ui->cb_none->setChecked(false);
    ui->cb_square->setChecked(false);
    ui->widget->setCustumPoint(1);
    ui->widget->update();
  }
}

void MainWindow::on_cb_square_clicked() {
  if (ui->cb_square->isChecked() == false) {
    ui->cb_none->setChecked(true);
    on_cb_none_clicked();
  } else {
    ui->cb_none->setChecked(false);
    ui->cb_circle->setChecked(false);
    ui->widget->setCustumPoint(2);
    ui->widget->update();
  }
}

void MainWindow::on_thicknesss_slider_valueChanged(int value) {
  ui->widget->setThicknessLine(value);
  ui->widget->update();
}

void MainWindow::on_pb_fcolor_clicked() {
  QColor line_c = QColorDialog::getColor(Qt::white, this, "Choose edges color");
  ui->widget->setColorLine(line_c);
  ui->widget->update();
}

void MainWindow::on_cb_solid_toggled(bool checked) {
  if (checked == false) {
    ui->cb_dashed->setChecked(true);
  } else {
    ui->cb_dashed->setChecked(false);
    ui->widget->setDashLine(false);
    ui->widget->update();
  }
}

void MainWindow::on_cb_dashed_toggled(bool checked) {
  if (checked == false) {
    ui->cb_solid->setChecked(true);
  } else {
    ui->cb_solid->setChecked(false);
    ui->widget->setDashLine(true);
    ui->widget->update();
  }
}

void MainWindow::closeEvent(QCloseEvent* event) {
  QSettings settings("MyApp", "MySettings");
  settings.setValue("file_vertices", ui->lb_vertices->text());
  settings.setValue("file_edges", ui->lb_edges->text());
  settings.setValue("scale_slider", ui->scale_slider->value());
  settings.setValue("size_slider", ui->size_slider->value());
  settings.setValue("thicknes_slider", ui->thicknesss_slider->value());
  settings.setValue("x_move_slider", ui->x_move_slider->value());
  settings.setValue("y_move_slider", ui->y_move_slider->value());
  settings.setValue("z_move_slider", ui->z_move_slider->value());
  settings.setValue("x_rotate_slider", ui->x_rotate_slider->value());
  settings.setValue("y_rotate_slider", ui->y_rotate_slider->value());
  settings.setValue("z_rotate_slider", ui->z_rotate_slider->value());
  settings.setValue("solid_check", ui->cb_solid->isChecked());
  settings.setValue("dashed_check", ui->cb_dashed->isChecked());
  settings.setValue("central_projection", ui->cb_central->isChecked());
  settings.setValue("parallel_projection", ui->cb_parallel->isChecked());
  settings.setValue("color_back", ui->widget->getColorBack());
  settings.setValue("color_line", ui->widget->getColorLine());
  settings.setValue("color_point", ui->widget->getColorPoint());
  settings.setValue("cb_none", ui->cb_none->isChecked());
  settings.setValue("cb_circle", ui->cb_circle->isChecked());
  settings.setValue("cb_square", ui->cb_square->isChecked());

  ui->widget->SaveObjectGL();
  ui->widget->getMementoObject()->WriteSettings(settings);
  QMainWindow::closeEvent(event);
}

void MainWindow::showEvent(QShowEvent* event) {
  QSettings settings("MyApp", "MySettings");

  ui->lb_vertices->setText(settings.value("file_vertices").toString());
  ui->lb_edges->setText(settings.value("file_edges").toString());

  ui->x_move_slider->setValue(settings.value("x_move_slider", 0).toInt());
  ui->y_move_slider->setValue(settings.value("y_move_slider", 0).toInt());
  ui->z_move_slider->setValue(settings.value("z_move_slider", 0).toInt());
  ui->x_rotate_slider->setValue(settings.value("x_rotate_slider", 0).toInt());
  ui->y_rotate_slider->setValue(settings.value("y_rotate_slider", 0).toInt());
  ui->z_rotate_slider->setValue(settings.value("z_rotate_slider", 0).toInt());
  ui->scale_slider->setValue(settings.value("scale_slider", 0).toInt());
  ui->size_slider->setValue(settings.value("size_slider", 0).toInt());
  ui->thicknesss_slider->setValue(settings.value("thicknes_slider", 0).toInt());
  ui->cb_solid->setChecked(settings.value("solid_check", 0).toInt());
  ui->cb_dashed->setChecked(settings.value("dashed_check", 0).toInt());
  ui->cb_central->setChecked(
      settings.value("central_projection", true).toBool());
  ui->cb_parallel->setChecked(
      settings.value("parallel_projection", true).toBool());
  ui->cb_none->setChecked(settings.value("cb_none", false).toBool());
  ui->cb_circle->setChecked(settings.value("cb_circle", false).toBool());
  ui->cb_square->setChecked(settings.value("cb_square", false).toBool());
  if (ui->cb_none->isChecked()) {
    ui->widget->setCustumPoint(0);
  } else if (ui->cb_circle->isChecked()) {
    ui->widget->setCustumPoint(1);
  } else if (ui->cb_square->isChecked()) {
    ui->widget->setCustumPoint(2);
  }
  ui->widget->setColorBack(settings.value("color_back").value<QColor>());
  ui->widget->setColorLine(settings.value("color_line").value<QColor>());
  ui->widget->setColorPoint(settings.value("color_point").value<QColor>());

  ui->widget->getMementoObject()->ReadSettings(settings);
  ui->widget->RestoreObject();

  QString file_name = QString::fromStdString(ui->widget->getFileName());
  QFileInfo file_info(file_name);
  QString fileName = file_info.fileName();
  setWindowTitle(fileName);
  ui->lb_name->setText("Name: " + fileName);
  ui->widget->InitModel(file_name.toStdString());

  ui->widget->update();
  QMainWindow::showEvent(event);
}

void MainWindow::on_actionbmp_triggered() {
  QImage image = ui->widget->grabFramebuffer();
  QString bmp_file =
      QFileDialog::getSaveFileName(this, tr("Save BMP File"), "test",
                                   tr("BMP Files (*.bmp);;All Files (*)"));
  if (!bmp_file.isEmpty()) {
    image.save(bmp_file, "BMP");
  }
}

void MainWindow::on_actionjpeg_triggered() {
  QImage image = ui->widget->grabFramebuffer();
  QString jpeg_file =
      QFileDialog::getSaveFileName(this, tr("Save JPEG File"), ".test",
                                   tr("JPEG Files (*.jpeg);;All Files (*)"));
  if (!jpeg_file.isEmpty()) {
    image.save(jpeg_file, "JPEG");
  }
}

void MainWindow::save_frame() {
  if (gif_time < 50) {
    gif_images[gif_time] = ui->widget->grab().toImage();
    ++gif_time;
  } else {
    gif = new QGifImage;
    for (int i = 0; i < gif_time; i++) {
      gif->addFrame(gif_images[i], 0);
    }
    QString fileName =
        QFileDialog::getSaveFileName(this, "Save GIF", "test", "GIF (*.gif)");
    gif->save(fileName);
    timer->stop();
    delete gif;
    gif_time = 0;
  }
}

void MainWindow::on_pb_gif_clicked() { timer->start(100); }
