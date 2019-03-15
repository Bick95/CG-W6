#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "math.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// --- Functions that listen for widget events
// forewards to the mainview

void MainWindow::on_ResetRotationButton_clicked(bool checked)
{
    Q_UNUSED(checked);
    ui->RotationDialX->setValue(0);
    ui->RotationDialY->setValue(0);
    ui->RotationDialZ->setValue(0);
    ui->mainView->setRotation(0, 0, 0);
}

void MainWindow::on_RotationDialX_sliderMoved(int value)
{
    ui->mainView->setRotation(value,
                              ui->RotationDialY->value(),
                              ui->RotationDialZ->value());
}

void MainWindow::on_RotationDialY_sliderMoved(int value)
{
    ui->mainView->setRotation(ui->RotationDialX->value(),
                              value,
                              ui->RotationDialZ->value());
}

void MainWindow::on_RotationDialZ_sliderMoved(int value)
{
    ui->mainView->setRotation(ui->RotationDialX->value(),
                              ui->RotationDialY->value(),
                              value);
}

void MainWindow::on_ResetScaleButton_clicked(bool checked)
{
    Q_UNUSED(checked);
    ui->ScaleSlider->setValue(100);
    ui->mainView->setScale(100);
}

void MainWindow::on_ScaleSlider_sliderMoved(int value)
{
    ui->mainView->setScale(value);
}

void MainWindow::on_PhongButton_toggled(bool checked)
{
    if (checked)
    {
        ui->mainView->setShadingMode(MainView::PHONG);
        ui->mainView->update();
    }
}

void MainWindow::on_NormalButton_toggled(bool checked)
{
    if (checked)
    {
        ui->mainView->setShadingMode(MainView::NORMAL);
        ui->mainView->update();
    }
}

void MainWindow::on_GouraudButton_toggled(bool checked)
{
    if (checked)
    {
        ui->mainView->setShadingMode(MainView::GOURAUD);
        ui->mainView->update();
    }
}

void MainWindow::on_ResetOriginButton_clicked(bool checked)
{
    Q_UNUSED(checked);
    ui->X_Slider->setValue(0);
    ui->Y_Slider->setValue(0);
    ui->Z_Slider->setValue(0);
    ui->mainView->setLightPosition(0,0,0);
}

void MainWindow::on_X_Slider_sliderMoved(int value)
{
    ui->mainView->setLightX(value);
}

void MainWindow::on_Y_Slider_sliderMoved(int value)
{
    ui->mainView->setLightY(value);
}

void MainWindow::on_Z_Slider_sliderMoved(int value)
{
    ui->mainView->setLightZ(value);
}

void MainWindow::on_ResetColorButton_clicked(bool checked)
{
    Q_UNUSED(checked);
    ui->Light_Red_Slider->setValue(100);
    ui->Light_Blue_Slider->setValue(100);
    ui->Light_Green_Slider->setValue(100);
    ui->mainView->resetLightColor();

}

void MainWindow::on_Light_Red_Slider_sliderMoved(int value)
{
    ui->mainView->setLightRed(value);
}

void MainWindow::on_Light_Green_Slider_sliderMoved(int value)
{
    ui->mainView->setLightGreen(value);
}

void MainWindow::on_Light_Blue_Slider_sliderMoved(int value)
{
    ui->mainView->setLightBlue(value);
}


// Pretend changing view location
void MainWindow::on_ResetViewButton_clicked(bool checked)
{
    ui->mainView->resetView();
};

void MainWindow::on_ViewRotationDialX_sliderMoved(int value)
{
    ui->mainView->setViewX(value);
};

void MainWindow::on_ViewRotationDialY_sliderMoved(int value)
{
    ui->mainView->setViewY(value);
};

void MainWindow::on_ViewRotationDialZ_sliderMoved(int value)
{
    ui->mainView->setViewZ(value);
};

void MainWindow::on_ZoomSlider_sliderMoved(int value)
{
    ui->mainView->setZoom(value);
};

void MainWindow::on_ResetZoomButton_clicked(bool checked)
{
    ui->mainView->resetZoom();
};
