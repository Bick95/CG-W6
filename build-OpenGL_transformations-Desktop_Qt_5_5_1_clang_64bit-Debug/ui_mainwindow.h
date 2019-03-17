/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mainview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *settingsBox;
    QFormLayout *formLayout;
    QGroupBox *rotationBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QDial *RotationDialX;
    QDial *RotationDialY;
    QDial *RotationDialZ;
    QPushButton *ResetRotationButton;
    QGroupBox *scalingBox;
    QVBoxLayout *verticalLayout_4;
    QSlider *ScaleSlider;
    QPushButton *ResetScaleButton;
    QGroupBox *shadingBox;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *PhongButton;
    QRadioButton *NormalButton;
    QRadioButton *GouraudButton;
    QRadioButton *WaterButton;
    QLabel *vrLabel;
    QFrame *vrBox;
    QVBoxLayout *verticalLayout_6;
    QFrame *viewRotationBox;
    QHBoxLayout *horizontalLayout_6;
    QDial *ViewRotationDialX;
    QDial *ViewRotationDialY;
    QDial *ViewRotationDialZ;
    QPushButton *ResetViewButton;
    QLabel *zoomLabel;
    QLabel *label;
    QFrame *LightPosBox;
    QGridLayout *gridLayout;
    QLabel *Z_Label;
    QSlider *Z_Slider;
    QLabel *x_Label;
    QSlider *X_Slider;
    QLabel *label_3;
    QPushButton *ResetOriginButton;
    QLabel *y_Label;
    QLabel *label_2;
    QSlider *Y_Slider;
    QLabel *label_4;
    QGroupBox *groupBox;
    QFrame *LightPosBox_2;
    QGridLayout *gridLayout_2;
    QSlider *Light_Red_Slider;
    QLabel *x_Label_2;
    QLabel *Z_Label_2;
    QSlider *Light_Green_Slider;
    QSlider *Light_Blue_Slider;
    QLabel *y_Label_2;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *ResetColorButton;
    QFrame *zoomBox;
    QVBoxLayout *verticalLayout_5;
    QFrame *innerZoomSliderBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *zeroPercentLabel;
    QSlider *ZoomSlider;
    QLabel *hundredPercentLabel;
    QPushButton *ResetZoomButton;
    MainView *mainView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1048, 1060);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        settingsBox = new QGroupBox(centralWidget);
        settingsBox->setObjectName(QStringLiteral("settingsBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(settingsBox->sizePolicy().hasHeightForWidth());
        settingsBox->setSizePolicy(sizePolicy);
        settingsBox->setMinimumSize(QSize(220, 0));
        settingsBox->setMaximumSize(QSize(220, 16777215));
        formLayout = new QFormLayout(settingsBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        rotationBox = new QGroupBox(settingsBox);
        rotationBox->setObjectName(QStringLiteral("rotationBox"));
        sizePolicy.setHeightForWidth(rotationBox->sizePolicy().hasHeightForWidth());
        rotationBox->setSizePolicy(sizePolicy);
        rotationBox->setMinimumSize(QSize(205, 0));
        rotationBox->setMaximumSize(QSize(205, 16777215));
        verticalLayout = new QVBoxLayout(rotationBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        RotationDialX = new QDial(rotationBox);
        RotationDialX->setObjectName(QStringLiteral("RotationDialX"));
        RotationDialX->setMaximum(359);
        RotationDialX->setWrapping(true);
        RotationDialX->setNotchTarget(12);
        RotationDialX->setNotchesVisible(true);

        horizontalLayout_2->addWidget(RotationDialX);

        RotationDialY = new QDial(rotationBox);
        RotationDialY->setObjectName(QStringLiteral("RotationDialY"));
        RotationDialY->setMaximum(359);
        RotationDialY->setWrapping(true);
        RotationDialY->setNotchTarget(12);
        RotationDialY->setNotchesVisible(true);

        horizontalLayout_2->addWidget(RotationDialY);

        RotationDialZ = new QDial(rotationBox);
        RotationDialZ->setObjectName(QStringLiteral("RotationDialZ"));
        RotationDialZ->setMaximum(359);
        RotationDialZ->setWrapping(true);
        RotationDialZ->setNotchTarget(12);
        RotationDialZ->setNotchesVisible(true);

        horizontalLayout_2->addWidget(RotationDialZ);


        verticalLayout->addLayout(horizontalLayout_2);

        ResetRotationButton = new QPushButton(rotationBox);
        ResetRotationButton->setObjectName(QStringLiteral("ResetRotationButton"));

        verticalLayout->addWidget(ResetRotationButton);


        formLayout->setWidget(0, QFormLayout::LabelRole, rotationBox);

        scalingBox = new QGroupBox(settingsBox);
        scalingBox->setObjectName(QStringLiteral("scalingBox"));
        sizePolicy.setHeightForWidth(scalingBox->sizePolicy().hasHeightForWidth());
        scalingBox->setSizePolicy(sizePolicy);
        scalingBox->setMinimumSize(QSize(205, 0));
        scalingBox->setMaximumSize(QSize(205, 16777215));
        verticalLayout_4 = new QVBoxLayout(scalingBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        ScaleSlider = new QSlider(scalingBox);
        ScaleSlider->setObjectName(QStringLiteral("ScaleSlider"));
        ScaleSlider->setMinimum(1);
        ScaleSlider->setMaximum(200);
        ScaleSlider->setValue(100);
        ScaleSlider->setOrientation(Qt::Horizontal);
        ScaleSlider->setInvertedAppearance(false);
        ScaleSlider->setInvertedControls(false);
        ScaleSlider->setTickPosition(QSlider::NoTicks);

        verticalLayout_4->addWidget(ScaleSlider);

        ResetScaleButton = new QPushButton(scalingBox);
        ResetScaleButton->setObjectName(QStringLiteral("ResetScaleButton"));

        verticalLayout_4->addWidget(ResetScaleButton);


        formLayout->setWidget(1, QFormLayout::LabelRole, scalingBox);

        shadingBox = new QGroupBox(settingsBox);
        shadingBox->setObjectName(QStringLiteral("shadingBox"));
        sizePolicy.setHeightForWidth(shadingBox->sizePolicy().hasHeightForWidth());
        shadingBox->setSizePolicy(sizePolicy);
        shadingBox->setMinimumSize(QSize(205, 0));
        shadingBox->setMaximumSize(QSize(205, 16777215));
        verticalLayout_2 = new QVBoxLayout(shadingBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        PhongButton = new QRadioButton(shadingBox);
        PhongButton->setObjectName(QStringLiteral("PhongButton"));
        PhongButton->setChecked(true);

        verticalLayout_2->addWidget(PhongButton);

        NormalButton = new QRadioButton(shadingBox);
        NormalButton->setObjectName(QStringLiteral("NormalButton"));

        verticalLayout_2->addWidget(NormalButton);

        GouraudButton = new QRadioButton(shadingBox);
        GouraudButton->setObjectName(QStringLiteral("GouraudButton"));

        verticalLayout_2->addWidget(GouraudButton);

        WaterButton = new QRadioButton(shadingBox);
        WaterButton->setObjectName(QStringLiteral("WaterButton"));

        verticalLayout_2->addWidget(WaterButton);


        formLayout->setWidget(2, QFormLayout::LabelRole, shadingBox);

        vrLabel = new QLabel(settingsBox);
        vrLabel->setObjectName(QStringLiteral("vrLabel"));

        formLayout->setWidget(4, QFormLayout::FieldRole, vrLabel);

        vrBox = new QFrame(settingsBox);
        vrBox->setObjectName(QStringLiteral("vrBox"));
        vrBox->setFrameShape(QFrame::StyledPanel);
        verticalLayout_6 = new QVBoxLayout(vrBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        viewRotationBox = new QFrame(vrBox);
        viewRotationBox->setObjectName(QStringLiteral("viewRotationBox"));
        horizontalLayout_6 = new QHBoxLayout(viewRotationBox);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        ViewRotationDialX = new QDial(viewRotationBox);
        ViewRotationDialX->setObjectName(QStringLiteral("ViewRotationDialX"));
        ViewRotationDialX->setMaximum(359);
        ViewRotationDialX->setWrapping(true);
        ViewRotationDialX->setNotchTarget(12);
        ViewRotationDialX->setNotchesVisible(true);

        horizontalLayout_6->addWidget(ViewRotationDialX);

        ViewRotationDialY = new QDial(viewRotationBox);
        ViewRotationDialY->setObjectName(QStringLiteral("ViewRotationDialY"));
        ViewRotationDialY->setMaximum(359);
        ViewRotationDialY->setWrapping(true);
        ViewRotationDialY->setNotchTarget(12);
        ViewRotationDialY->setNotchesVisible(true);

        horizontalLayout_6->addWidget(ViewRotationDialY);

        ViewRotationDialZ = new QDial(viewRotationBox);
        ViewRotationDialZ->setObjectName(QStringLiteral("ViewRotationDialZ"));
        ViewRotationDialZ->setMaximum(359);
        ViewRotationDialZ->setWrapping(true);
        ViewRotationDialZ->setNotchTarget(12);
        ViewRotationDialZ->setNotchesVisible(true);

        horizontalLayout_6->addWidget(ViewRotationDialZ);


        verticalLayout_6->addWidget(viewRotationBox);

        ResetViewButton = new QPushButton(vrBox);
        ResetViewButton->setObjectName(QStringLiteral("ResetViewButton"));

        verticalLayout_6->addWidget(ResetViewButton);


        formLayout->setWidget(6, QFormLayout::FieldRole, vrBox);

        zoomLabel = new QLabel(settingsBox);
        zoomLabel->setObjectName(QStringLiteral("zoomLabel"));

        formLayout->setWidget(8, QFormLayout::FieldRole, zoomLabel);

        label = new QLabel(settingsBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(15, QFormLayout::FieldRole, label);

        LightPosBox = new QFrame(settingsBox);
        LightPosBox->setObjectName(QStringLiteral("LightPosBox"));
        gridLayout = new QGridLayout(LightPosBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Z_Label = new QLabel(LightPosBox);
        Z_Label->setObjectName(QStringLiteral("Z_Label"));

        gridLayout->addWidget(Z_Label, 4, 0, 1, 1);

        Z_Slider = new QSlider(LightPosBox);
        Z_Slider->setObjectName(QStringLiteral("Z_Slider"));
        Z_Slider->setMinimum(-100);
        Z_Slider->setMaximum(100);
        Z_Slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Z_Slider, 4, 1, 1, 1);

        x_Label = new QLabel(LightPosBox);
        x_Label->setObjectName(QStringLiteral("x_Label"));

        gridLayout->addWidget(x_Label, 2, 0, 1, 1);

        X_Slider = new QSlider(LightPosBox);
        X_Slider->setObjectName(QStringLiteral("X_Slider"));
        X_Slider->setMinimum(-100);
        X_Slider->setMaximum(100);
        X_Slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(X_Slider, 2, 1, 1, 1);

        label_3 = new QLabel(LightPosBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 2, 1, 1);

        ResetOriginButton = new QPushButton(LightPosBox);
        ResetOriginButton->setObjectName(QStringLiteral("ResetOriginButton"));

        gridLayout->addWidget(ResetOriginButton, 5, 1, 1, 2);

        y_Label = new QLabel(LightPosBox);
        y_Label->setObjectName(QStringLiteral("y_Label"));

        gridLayout->addWidget(y_Label, 3, 0, 1, 1);

        label_2 = new QLabel(LightPosBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 2, 1, 1);

        Y_Slider = new QSlider(LightPosBox);
        Y_Slider->setObjectName(QStringLiteral("Y_Slider"));
        Y_Slider->setMinimum(-100);
        Y_Slider->setMaximum(100);
        Y_Slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Y_Slider, 3, 1, 1, 1);

        label_4 = new QLabel(LightPosBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 2, 1, 1);


        formLayout->setWidget(17, QFormLayout::FieldRole, LightPosBox);

        groupBox = new QGroupBox(settingsBox);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(180, 180));
        LightPosBox_2 = new QFrame(groupBox);
        LightPosBox_2->setObjectName(QStringLiteral("LightPosBox_2"));
        LightPosBox_2->setGeometry(QRect(1, 10, 171, 148));
        gridLayout_2 = new QGridLayout(LightPosBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        Light_Red_Slider = new QSlider(LightPosBox_2);
        Light_Red_Slider->setObjectName(QStringLiteral("Light_Red_Slider"));
        Light_Red_Slider->setMinimum(0);
        Light_Red_Slider->setMaximum(100);
        Light_Red_Slider->setPageStep(1);
        Light_Red_Slider->setValue(100);
        Light_Red_Slider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(Light_Red_Slider, 2, 1, 1, 1);

        x_Label_2 = new QLabel(LightPosBox_2);
        x_Label_2->setObjectName(QStringLiteral("x_Label_2"));

        gridLayout_2->addWidget(x_Label_2, 2, 0, 1, 1);

        Z_Label_2 = new QLabel(LightPosBox_2);
        Z_Label_2->setObjectName(QStringLiteral("Z_Label_2"));

        gridLayout_2->addWidget(Z_Label_2, 4, 0, 1, 1);

        Light_Green_Slider = new QSlider(LightPosBox_2);
        Light_Green_Slider->setObjectName(QStringLiteral("Light_Green_Slider"));
        Light_Green_Slider->setMinimum(0);
        Light_Green_Slider->setMaximum(100);
        Light_Green_Slider->setPageStep(1);
        Light_Green_Slider->setValue(100);
        Light_Green_Slider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(Light_Green_Slider, 3, 1, 1, 1);

        Light_Blue_Slider = new QSlider(LightPosBox_2);
        Light_Blue_Slider->setObjectName(QStringLiteral("Light_Blue_Slider"));
        Light_Blue_Slider->setMinimum(0);
        Light_Blue_Slider->setMaximum(100);
        Light_Blue_Slider->setPageStep(1);
        Light_Blue_Slider->setValue(100);
        Light_Blue_Slider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(Light_Blue_Slider, 4, 1, 1, 1);

        y_Label_2 = new QLabel(LightPosBox_2);
        y_Label_2->setObjectName(QStringLiteral("y_Label_2"));

        gridLayout_2->addWidget(y_Label_2, 3, 0, 1, 1);

        label_5 = new QLabel(LightPosBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 2, 2, 1, 1);

        label_6 = new QLabel(LightPosBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 3, 2, 1, 1);

        label_7 = new QLabel(LightPosBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 4, 2, 1, 1);

        ResetColorButton = new QPushButton(LightPosBox_2);
        ResetColorButton->setObjectName(QStringLiteral("ResetColorButton"));

        gridLayout_2->addWidget(ResetColorButton, 5, 1, 1, 2);


        formLayout->setWidget(18, QFormLayout::FieldRole, groupBox);

        zoomBox = new QFrame(settingsBox);
        zoomBox->setObjectName(QStringLiteral("zoomBox"));
        zoomBox->setFrameShape(QFrame::StyledPanel);
        verticalLayout_5 = new QVBoxLayout(zoomBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        innerZoomSliderBox = new QFrame(zoomBox);
        innerZoomSliderBox->setObjectName(QStringLiteral("innerZoomSliderBox"));
        horizontalLayout_3 = new QHBoxLayout(innerZoomSliderBox);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        zeroPercentLabel = new QLabel(innerZoomSliderBox);
        zeroPercentLabel->setObjectName(QStringLiteral("zeroPercentLabel"));

        horizontalLayout_3->addWidget(zeroPercentLabel);

        ZoomSlider = new QSlider(innerZoomSliderBox);
        ZoomSlider->setObjectName(QStringLiteral("ZoomSlider"));
        ZoomSlider->setMaximum(100);
        ZoomSlider->setValue(50);
        ZoomSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(ZoomSlider);

        hundredPercentLabel = new QLabel(innerZoomSliderBox);
        hundredPercentLabel->setObjectName(QStringLiteral("hundredPercentLabel"));

        horizontalLayout_3->addWidget(hundredPercentLabel);


        verticalLayout_5->addWidget(innerZoomSliderBox);

        ResetZoomButton = new QPushButton(zoomBox);
        ResetZoomButton->setObjectName(QStringLiteral("ResetZoomButton"));

        verticalLayout_5->addWidget(ResetZoomButton);


        formLayout->setWidget(10, QFormLayout::FieldRole, zoomBox);


        horizontalLayout->addWidget(settingsBox);

        mainView = new MainView(centralWidget);
        mainView->setObjectName(QStringLiteral("mainView"));

        horizontalLayout->addWidget(mainView);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        settingsBox->setTitle(QApplication::translate("MainWindow", "Settings", 0));
        rotationBox->setTitle(QApplication::translate("MainWindow", "Object rotation", 0));
#ifndef QT_NO_TOOLTIP
        RotationDialX->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the X-axis</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        RotationDialY->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the Y-axis</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        RotationDialZ->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the Z-axis</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        ResetRotationButton->setText(QApplication::translate("MainWindow", "Reset Rotation", 0));
        scalingBox->setTitle(QApplication::translate("MainWindow", "Object scaling", 0));
        ResetScaleButton->setText(QApplication::translate("MainWindow", "Reset Scaling", 0));
        shadingBox->setTitle(QApplication::translate("MainWindow", "Shading", 0));
        PhongButton->setText(QApplication::translate("MainWindow", "Pho&ng", 0));
        NormalButton->setText(QApplication::translate("MainWindow", "Nor&mal", 0));
        GouraudButton->setText(QApplication::translate("MainWindow", "&Gouraud", 0));
        WaterButton->setText(QApplication::translate("MainWindow", "Water", 0));
        vrLabel->setText(QApplication::translate("MainWindow", "View rotation", 0));
        ResetViewButton->setText(QApplication::translate("MainWindow", "Reset view", 0));
        zoomLabel->setText(QApplication::translate("MainWindow", "Zoom", 0));
        label->setText(QApplication::translate("MainWindow", "Light position [-10,10]", 0));
        Z_Label->setText(QApplication::translate("MainWindow", "Z:  -", 0));
        x_Label->setText(QApplication::translate("MainWindow", "X:  -", 0));
        label_3->setText(QApplication::translate("MainWindow", "+", 0));
        ResetOriginButton->setText(QApplication::translate("MainWindow", "Reset to Origin", 0));
        y_Label->setText(QApplication::translate("MainWindow", "Y:  -", 0));
        label_2->setText(QApplication::translate("MainWindow", "+", 0));
        label_4->setText(QApplication::translate("MainWindow", "+", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Light color [0,1]", 0));
        x_Label_2->setText(QApplication::translate("MainWindow", "R:  -", 0));
        Z_Label_2->setText(QApplication::translate("MainWindow", "B:  -", 0));
        y_Label_2->setText(QApplication::translate("MainWindow", "G:  -", 0));
        label_5->setText(QApplication::translate("MainWindow", "+", 0));
        label_6->setText(QApplication::translate("MainWindow", "+", 0));
        label_7->setText(QApplication::translate("MainWindow", "+", 0));
        ResetColorButton->setText(QApplication::translate("MainWindow", "Reset to white", 0));
        zeroPercentLabel->setText(QApplication::translate("MainWindow", "0%", 0));
        hundredPercentLabel->setText(QApplication::translate("MainWindow", "100%", 0));
        ResetZoomButton->setText(QApplication::translate("MainWindow", "Reset zoom", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
