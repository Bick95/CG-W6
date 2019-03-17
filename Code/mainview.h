#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "model.h"
#include "material.h"
#include "light.h"
#include "wave.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QVector3D>
#include <memory>

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

    // Material values: {red, green, blue, ambient coeff, diffuse coeff, specular coeff}
    Material mat = {1.0, 1.0, 1.0, 0.3, 0.3, 0.2};

    // Light values: {red, gree, blue, x,y,z}
    Light light = {1,1,1,0.0,0.0,0.0};

    //waves
    Wave wave1 = {0.1, 1.0, 0.0};
    Wave wave2 = {0.08, 3.0, 0.5};
    Wave wave3 = {0.05, 5.0, 1.0};

    const static unsigned models = 3; // Number of different models to be used for drawing

    Model model[models];
    unsigned lenMeshes[models];

    // Texture components
    GLuint textures[models];

    GLuint shadingMode = ShadingMode::PHONG;

    // Factors
    float scalingFactor;
    const static unsigned shapesDrawn = 5; // Total number of instances of models to be drawn
    float individualScalingFactors[shapesDrawn];
    float rotationX;
    float rotationY;
    float rotationZ;
    float viewRotationX;
    float viewRotationY;
    float viewRotationZ;
    float zoom;
    float individualRotationX[shapesDrawn]; // 1 entry per shape to be drawn due to different rotational speeds
    float individualRotationY[shapesDrawn];
    float individualRotationZ[shapesDrawn];
    float timeIndicator = 0.0f;


    // Buffers
    GLuint VBO[models];
    GLuint VAB[models];


    // Various transformations
    QMatrix4x4 transformationMatrixMesh = QMatrix4x4();
    QMatrix4x4 transformationPerspective = QMatrix4x4();
    QMatrix4x4 transformationMatrixView = QMatrix4x4();
    QMatrix4x4 transformationView = QMatrix4x4();

    // Pointers for changing between vertex shaders
    GLint transformationLocation_ptr;
    GLint projectionTransformationLocation_ptr;
    GLint viewTransformationLocation_ptr;
    GLint preserveNormalsLocation_ptr;

    // Info regarding VertexShader Normal
    GLint transformationLocation_normal;
    GLint projectionTransformationLocation_normal;
    GLint preserveNormalsLocation_normal;

    // Info regarding VertexShader Water
    GLint transformationLocation_water;
    GLint projectionTransformationLocation_water;
    GLint viewTransformationLocation_water;
    GLint preserveNormalsLocation_water;

    //To move to water shader later
    GLint timeCoefficient;
    GLint wave1location;
    GLint wave2location;
    GLint wave3location;
    GLint materialColor_water;
    GLint materialCoefficients_water;
    GLint lightPosLocation_water;
    GLint lightColLocation_water;


    // Info regarding VertexShader Gouraud
    GLint transformationLocation_gouraud;
    GLint projectionTransformationLocation_gouraud;
    GLint viewTransformationLocation_gouraud;
    GLint preserveNormalsLocation_gouraud;
    GLint lightPosLocation_gouraud;
    GLint lightColLocation_gouraud;
    GLint materialColLocation_gouraud;
    GLint illuminationCoeffsLocation_gouraud;
    GLint sampler2Dgouraud_Location;

    // Info regarding VertexShader Phong
    GLint transformationLocation_phong;
    GLint projectionTransformationLocation_phong;
    GLint viewTransformationLocation_phong;
    GLint preserveNormalsLocation_phong;
    GLint materialColor_phong;
    GLint materialCoefficients_phong;
    GLint lightPosLocation_phong;
    GLint lightColLocation_phong;
    GLint width_phong;
    GLint height_phong;
    QOpenGLDebugLogger *debugLogger;
    QTimer timer; // timer used for animation

    QOpenGLShaderProgram shaderProgram_normal;
    QOpenGLShaderProgram shaderProgram_gouraud;
    QOpenGLShaderProgram shaderProgram_phong;
    QOpenGLShaderProgram shaderProgram_water;
    QOpenGLShaderProgram* temp;

public:
    enum ShadingMode : GLuint
    {
        PHONG = 0, NORMAL, GOURAUD, WATER
    };

    MainView(QWidget *parent = 0);
    ~MainView();

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void setScale(int scale);
    void setShadingMode(ShadingMode shading);
    void setLightPosition(int x, int y, int z);
    void resetLightColor();
    void setLightX(int x);
    void setLightY(int x);
    void setLightZ(int x);
    void setLightRed(int x);
    void setLightGreen(int x);
    void setLightBlue(int x);
    void setViewX(int x);
    void setViewY(int y);
    void setViewZ(int z);
    void resetView();
    void setZoom(int z);
    void resetZoom();

protected:
    void initializeGL();
    void readInMesh(unsigned meshIdx, QString path, QString texture = nullptr);
    void resizeGL(int newWidth, int newHeight);
    void paintGL();
    void drawShape(int meshIdx, int objectIndex, float x, float y, float z, float speedX, float speedY, float speedZ, float scale);

    // Functions for keyboard input events
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    // Function for mouse input events
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

private slots:
    void onMessageLogged( QOpenGLDebugMessage Message );

private:
    void createShaderProgram();
    QVector<quint8> imageToBytes(QImage image);
    void loadTexture(QString file, GLuint texturePtr);

};

#endif // MAINVIEW_H
