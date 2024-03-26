#ifndef VIEW_MAINWINDOW_H
#define VIEW_MAINWINDOW_H

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>

#include "../QtGifImage/src/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_loadModel_triggered();
  void on_x_move_slider_valueChanged(int value);
  void on_y_move_slider_valueChanged(int value);
  void on_z_move_slider_valueChanged(int value);
  void on_x_rotate_slider_valueChanged(int value);
  void on_y_rotate_slider_valueChanged(int value);
  void on_z_rotate_slider_valueChanged(int value);
  void on_scale_slider_valueChanged(int value);
  void on_pb_bcolor_clicked();
  void on_cb_parallel_toggled(bool checked);
  void on_cb_central_toggled(bool checked);
  void on_exit_triggered();
  void on_pb_reset_clicked();

  void on_size_slider_valueChanged(int value);
  void on_pb_vcolor_clicked();
  void on_cb_none_clicked();
  void on_cb_circle_clicked();
  void on_cb_square_clicked();

  void on_thicknesss_slider_valueChanged(int value);
  void on_pb_fcolor_clicked();
  void on_cb_solid_toggled(bool checked);
  void on_cb_dashed_toggled(bool checked);

  void on_actionbmp_triggered();
  void on_actionjpeg_triggered();
  void on_pb_gif_clicked();

 public slots:
  void save_frame();

 private:
  Ui::MainWindow *ui;

  QTimer *timer{};
  QGifImage *gif{};
  QImage *gif_images{};
  int gif_time{};

  void closeEvent(QCloseEvent *event);
  void showEvent(QShowEvent *event);
};

#endif  // VIEW_MAINWINDOW_H
