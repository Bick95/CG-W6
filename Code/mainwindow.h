#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ResetRotationButton_clicked(bool checked);
    void on_RotationDialX_sliderMoved(int value);
    void on_RotationDialY_sliderMoved(int value);
    void on_RotationDialZ_sliderMoved(int value);

    void on_ResetScaleButton_clicked(bool checked);
    void on_ScaleSlider_sliderMoved(int value);

    void on_PhongButton_toggled(bool checked);
    void on_NormalButton_toggled(bool checked);
    void on_GouraudButton_toggled(bool checked);

    // Change light position
    void on_ResetOriginButton_clicked(bool checked);
    void on_X_Slider_sliderMoved(int value);
    void on_Y_Slider_sliderMoved(int value);
    void on_Z_Slider_sliderMoved(int value);

    // Change light color
    void on_ResetColorButton_clicked(bool checked);
    void on_Light_Red_Slider_sliderMoved(int value);
    void on_Light_Green_Slider_sliderMoved(int value);
    void on_Light_Blue_Slider_sliderMoved(int value);

    // Pretend changing view location
    void on_ResetViewButton_clicked(bool checked);
    void on_ViewRotationDialX_sliderMoved(int value);
    void on_ViewRotationDialY_sliderMoved(int value);
    void on_ViewRotationDialZ_sliderMoved(int value);

    // Manage zoom
    void on_ZoomSlider_sliderMoved(int value);
    void on_ResetZoomButton_clicked(bool checked);


};

#endif // MAINWINDOW_H
