#include "mainview.h"
#include "math.h"
#include "vertex.h"
#include "triangle.h"
#include "cube.h"
#include "QMatrix4x4"

#include <QDateTime>
#include <cmath>

/**
 * @brief MainView::MainView
 *
 * Constructor of MainView
 *
 * @param parent
 */
MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    qDebug() << "MainView constructor";
    connect(&timer, SIGNAL(timeout()), this, SLOT(update())); // For timer
}

/**
 * @brief MainView::~MainView
 *
 * Destructor of MainView
 * This is the last function called, before exit of the program
 * Use this to clean up your variables, buffers etc.
 *
 */
MainView::~MainView() {
    debugLogger->stopLogging();

    // Empty buffers...
    glDeleteBuffers(models, VBO);
    glDeleteVertexArrays(models, VAB);
    glDeleteTextures(models, textures);

    qDebug() << "MainView destructor";
}

// --- OpenGL initialization

/**
 * @brief MainView::initializeGL
 *
 * Called upon OpenGL initialization
 * Attaches a debugger and calls other init functions
 */
void MainView::initializeGL() {
    qDebug() << ":: Initializing OpenGL";
    initializeOpenGLFunctions();

    debugLogger = new QOpenGLDebugLogger();
    connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ),
             this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

    if ( debugLogger->initialize() ) {
        qDebug() << ":: Logging initialized";
        debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
        debugLogger->enableMessages();
    }

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    glEnable(GL_CULL_FACE);

    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    // Set the color of the screen to be black on clear (new frame)
    glClearColor(0.2f, 0.5f, 0.7f, 0.0f);

    createShaderProgram();


    // Init
    scalingFactor = 4.0f;
    for (unsigned i = 0; i < shapesDrawn; i++){
        individualRotationX[i] = 0.0f;
        individualRotationY[i] = 0.0f;
        individualRotationZ[i] = 0.0f;
        individualScalingFactors[i] = 0.0f;
    }

    timeIndicator = 0;

    // Waves
    float amplitudesVals[] = {0.08, 0.05, 0.02};
    float frequenciesVals[] = {0.08, 0.05, 0.02};
    float phasesVals[] = {0.08, 0.05, 0.02};

    *amplitudes = amplitudesVals;
    *frequencies = frequenciesVals;
    *phases = phasesVals;

    resetView();
    resetZoom();

    /* --------------------------------- CAT MESH -------------------------------------- */

    readInMesh(0, ":/models/cat.obj", ":/textures/cat_diff.png");

    /* --------------------------------- CUBE MESH -------------------------------------- */

    readInMesh(1, ":/models/cube.obj", ":/textures/rug_logo.png");

    /* --------------------------------- PLANE MESH -------------------------------------- */

    readInMesh(2, ":/models/grid.obj", ":/textures/rug_logo.png");

    // Related to timer: starts calling paintGL()function 60 times per second
    timer.start(1000.0 / 60.0);
}

void MainView::readInMesh(unsigned meshIdx, QString path, QString texture){
    // Read in model
    model[meshIdx] = Model(path);

    // Get unitized Mesh vertices, normals, and texture coods
    model[meshIdx].unitize();
    QVector<QVector3D> meshQ = model[meshIdx].getVertices();
    QVector<QVector3D> normals = model[meshIdx].getNormals();
    QVector<QVector2D> texture_coords = model[meshIdx].getTextureCoords();
    lenMeshes[meshIdx] = meshQ.size();

    // Transform Mesh-QVector3D to Vertex-array to be stored in buffer
    Vertex mesh[lenMeshes[meshIdx]];
    for (int i = 0; i < lenMeshes[meshIdx]; i++){
        mesh[i] = {meshQ[i].x(), meshQ[i].y(), meshQ[i].z(), normals[i].x(), normals[i].y(), normals[i].z(), texture_coords[i].x(), texture_coords[i].y()};
        //qDebug() << "Mesh: (" << mesh[i].x << "," << mesh[i].y << "," << mesh[i].z << "), Normals: " << mesh[i].nx << "," << mesh[i].ny << "," << mesh[i].nz << " and Texture coords: " << mesh[i].tx << ", " << mesh[i].ty << "\n";
    }

    // Create buffer objects
    glGenVertexArrays(1, &VAB[meshIdx]);
    glGenBuffers(1, &VBO[meshIdx]);

    // Bind buffer
    glBindVertexArray(VAB[meshIdx]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[meshIdx]);

    // Bind mesh-array (to be drawn) to corresponding buffer
    glBufferData(GL_ARRAY_BUFFER, lenMeshes[meshIdx] * sizeof (Vertex), mesh, GL_STATIC_DRAW);

    // Declare the attributes of a vertex (in compliance with order defined in vertex-shader-file)
    glEnableVertexAttribArray(0); // 0: location
    glEnableVertexAttribArray(1); // 1: rgb
    glEnableVertexAttribArray(2); // mesh-texture-coords

    // Specify how to draw Mesh
    // Coordinates
    glVertexAttribPointer(0, // Specifies the index of the generic vertex attribute to be modified.
                          3, // Specifies the number of components per generic vertex attribute
                          GL_FLOAT, // Specifies the data type of each component in the array
                          GL_FALSE, // specifies whether fixed-point data values should be normalized
                          8 * sizeof(GL_FLOAT), // Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
                          (GLvoid*) 0); // Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
    // Normals
    glVertexAttribPointer(1, // Specifies the index of the generic vertex attribute to be modified.
                          3, // Specifies the number of components per generic vertex attribute
                          GL_FLOAT, // Specifies the data type of each component in the array
                          GL_FALSE, // specifies whether fixed-point data values should be normalized
                          8 * sizeof(GL_FLOAT), // Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
                          (GLvoid*) (3 * sizeof(float))); // Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
    // Texture-coordinates
    glVertexAttribPointer(2, // Specifies the index of the generic vertex attribute to be modified.
                          2, // Specifies the number of components per generic vertex attribute
                          GL_FLOAT, // Specifies the data type of each component in the array
                          GL_FALSE, // specifies whether fixed-point data values should be normalized
                          8 * sizeof(GL_FLOAT), // Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
                          (GLvoid*) (6 * sizeof(float))); // Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.

    if (texture != nullptr){
        // Generate and set ptr to texture
        glGenTextures(1, &textures[meshIdx]);
        // Reading in & binding texture
        loadTexture(texture, textures[meshIdx]);
    }
}

void MainView::loadTexture(QString file, GLuint texturePtr){
    // Read in texture file
    QImage image = QImage(file);
    QVector<quint8> texture = imageToBytes(image);
    // Bind texture
    glBindTexture(GL_TEXTURE_2D, texturePtr);
    // Set parameters for how to interpret texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Make texture from image bytes
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.data());
    // Safety measure for Mipmapping
    glGenerateMipmap(GL_TEXTURE_2D);
}

void MainView::createShaderProgram()
{

    // NORMAL
    // Create shader program Normal
    shaderProgram_normal.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_normal.glsl");
    shaderProgram_normal.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_normal.glsl");
    shaderProgram_normal.link();
    shaderProgram_normal.bind();


    // Get locations of where transformation matrices are stored in shader
    transformationLocation_normal = shaderProgram_normal.uniformLocation("modelTransform");
    projectionTransformationLocation_normal = shaderProgram_normal.uniformLocation("projectionTransform");
    viewTransformationLocation_normal = shaderProgram_normal.uniformLocation("viewTransform");
    preserveNormalsLocation_normal = shaderProgram_normal.uniformLocation("preserveNormals");

    // GOURAUD
    // Create shader program Gouraud
    shaderProgram_gouraud.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_gouraud.glsl");
    shaderProgram_gouraud.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_gouraud.glsl");

    // Bind for initialization
    shaderProgram_gouraud.link();
    shaderProgram_gouraud.bind();

    // Get locations of where transformation matrices are stored in shader
    // General
    transformationLocation_gouraud = shaderProgram_gouraud.uniformLocation("modelTransform");
    projectionTransformationLocation_gouraud = shaderProgram_gouraud.uniformLocation("projectionTransform");
    viewTransformationLocation_gouraud = shaderProgram_gouraud.uniformLocation("viewTransform");
    preserveNormalsLocation_gouraud = shaderProgram_gouraud.uniformLocation("preserveNormals");
    // Specific
    lightPosLocation_gouraud = shaderProgram_gouraud.uniformLocation("lightPos");
    lightColLocation_gouraud = shaderProgram_gouraud.uniformLocation("lightColor");
    materialColLocation_gouraud = shaderProgram_gouraud.uniformLocation("materialColor");
    illuminationCoeffsLocation_gouraud = shaderProgram_gouraud.uniformLocation("coeffs"); // Illumination coefficients (ka, kd, ks)
    sampler2Dgouraud_Location = shaderProgram_gouraud.uniformLocation("sampler"); // For texture painting: location of sampler-uniform in Gouraud Frag-shader


    // PHONG
    // Create shader program Phong
    shaderProgram_phong.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_phong.glsl");
    shaderProgram_phong.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_phong.glsl");

    // Bind for initialization
    shaderProgram_phong.link();
    shaderProgram_phong.bind();

    // Get locations of where transformation matrices are stored in shader
    transformationLocation_phong = shaderProgram_phong.uniformLocation("modelTransform");
    projectionTransformationLocation_phong = shaderProgram_phong.uniformLocation("projectionTransform");
    viewTransformationLocation_phong = shaderProgram_phong.uniformLocation("viewTransform");
    preserveNormalsLocation_phong = shaderProgram_phong.uniformLocation("preserveNormals");
    // Specific
    materialColor_phong = shaderProgram_phong.uniformLocation("materialColor");
    materialCoefficients_phong = shaderProgram_phong.uniformLocation("materialCoeffs");
    lightPosLocation_phong = shaderProgram_phong.uniformLocation("lightPos");
    lightColLocation_phong = shaderProgram_phong.uniformLocation("lightColor");
    width_phong = shaderProgram_phong.uniformLocation("width");
    height_phong = shaderProgram_phong.uniformLocation("height");

    // WATER
    // Create shader program Water
    shaderProgram_water.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_water.glsl");
    shaderProgram_water.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_water.glsl");
    shaderProgram_water.link();
    shaderProgram_water.bind();


    // Get locations of where transformation matrices are stored in shader
    transformationLocation_water = shaderProgram_water.uniformLocation("modelTransform");
    projectionTransformationLocation_water = shaderProgram_water.uniformLocation("projectionTransform");
    viewTransformationLocation_water = shaderProgram_water.uniformLocation("viewTransform");
    preserveNormalsLocation_water = shaderProgram_water.uniformLocation("preserveNormals");

    // SPECIFIC FOR WATER
    timeCoefficient = shaderProgram_water.uniformLocation("timeCoeff");
    wave1location = shaderProgram_water.uniformLocation("wave1");
    wave2location = shaderProgram_water.uniformLocation("wave2");
    wave3location = shaderProgram_water.uniformLocation("wave3");
    materialColor_water = shaderProgram_water.uniformLocation("color");
    materialCoefficients_water = shaderProgram_water.uniformLocation("coeffs");
    lightPosLocation_water = shaderProgram_water.uniformLocation("lPos");
    lightColLocation_water = shaderProgram_water.uniformLocation("lColor");
    amplitudesLocation_water = shaderProgram_water.uniformLocation("amplitudes");
    frequenciesLocation_water = shaderProgram_water.uniformLocation("frequencies");
    phasesLocation_water = shaderProgram_water.uniformLocation("phases");


}

// --- OpenGL drawing

/**
 * @brief MainView::paintGL
 *
 * Actual function used for drawing to the screen
 *
 */
void MainView::paintGL() {

    // Clear the screen before rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Select shading mode
    switch (shadingMode) {
        case ShadingMode::PHONG:{
            //qDebug() << "shading mode Phong = " << shadingMode;
            temp = &shaderProgram_phong;
            projectionTransformationLocation_ptr = projectionTransformationLocation_phong;
            viewTransformationLocation_ptr = viewTransformationLocation_phong;
            transformationLocation_ptr = transformationLocation_phong;
            preserveNormalsLocation_ptr = preserveNormalsLocation_phong;
            break;
        }
        case ShadingMode::NORMAL:{
            //qDebug() << "shading mode Normal = " << shadingMode;
            temp = &shaderProgram_normal;
            projectionTransformationLocation_ptr = projectionTransformationLocation_normal;
            viewTransformationLocation_ptr = viewTransformationLocation_normal;
            transformationLocation_ptr = transformationLocation_normal;
            preserveNormalsLocation_ptr = preserveNormalsLocation_normal;
            break;
        }
        case ShadingMode::GOURAUD:{
            //qDebug() << "shading mode Gouraud = " << shadingMode;
            temp = &shaderProgram_gouraud;
            projectionTransformationLocation_ptr = projectionTransformationLocation_gouraud;
            viewTransformationLocation_ptr = viewTransformationLocation_gouraud;
            transformationLocation_ptr = transformationLocation_gouraud;
            preserveNormalsLocation_ptr = preserveNormalsLocation_gouraud;
            break;
        }
        case ShadingMode::WATER:{
            //qDebug() << "shading mode Water = " << shadingMode;
            temp = &shaderProgram_water;
            projectionTransformationLocation_ptr = projectionTransformationLocation_water;
            viewTransformationLocation_ptr = viewTransformationLocation_water;
            transformationLocation_ptr = transformationLocation_water;
            preserveNormalsLocation_ptr = preserveNormalsLocation_water;
            break;
        }
    }

    temp->bind(); // Bind shader

    /* ---------------- DRAWING CAT -------------------- */

    //drawShape(0, 0, 3.7f, 0, -10, 0.1f, 0.1f, 0.3f, scalingFactor);

    /* ---------------- DRAWING CUBE -------------------- */

    //drawShape(1, 1, -3.7f, 0, -10, 0.2f, 0.2f, 0.1f, scalingFactor/4);

    /* ---------------- DRAWING FLOATING CUBE -------------------- */

    drawShape(1, 2, 0 + cos(timeIndicator), 0, -10 + sin(timeIndicator), 0.2f, 1.0f, 0.05f, (scalingFactor/5 + individualScalingFactors[2])); // individualScalingFactors has no meaning yet. It's rather a placeholder

    /* ---------------- DRAWING FLOATING CAT -------------------- */

    drawShape(0, 3, 3.2f + 2 * cos(timeIndicator), -2 + 3 * sin(timeIndicator),-10, 0.1f, 0.2f, 0.05f, scalingFactor+individualScalingFactors[3]);

    /* ---------------- DRAWING QUAD -------------------- */

    drawShape(2, 4, 2.0f, -2,-10, 0.0f, 0.0f, 0.0f, scalingFactor);


    timeIndicator += fmod(0.005 * M_PI, 2 * M_PI); // Let objects float around by using this 'angle' in [0,2pi)

    temp->release();
}


void MainView::drawShape(int meshIdx, int objectIndex, float x, float y, float z, float speedX, float speedY, float speedZ, float scale){
    // Reset everything
    QMatrix3x3 preserveNormals = QMatrix3x3();
    transformationMatrixMesh = QMatrix4x4();
    transformationMatrixView = QMatrix4x4();

    // For drawing textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[meshIdx]); // Bind texture: cat

    // Unitized Mesh
    transformationMatrixMesh.translate(x, y, z);
    transformationMatrixMesh.scale(scale);

    // Compute rotation of Mesh in all three directions
    individualRotationX[objectIndex] += std::fmod(speedX*M_PI, 2*M_PI);
    unsigned totalRotationX = rotationX + individualRotationX[objectIndex]; // rotationX = rotation dial input // individualRotationX = causes different rotational speeds between drawn objects

    individualRotationY[objectIndex] += std::fmod(speedY*M_PI, 2*M_PI);
    unsigned totalRotationY = rotationY + individualRotationY[objectIndex]; // rotationY = rotation dial input

    individualRotationZ[objectIndex] += std::fmod(speedZ*M_PI, 2*M_PI);
    unsigned totalRotationZ = rotationZ + individualRotationZ[objectIndex]; // rotationZ = rotation dial input

    // Create rotation matrix
    transformationMatrixMesh.rotate(totalRotationX, QVector3D(1.0, 0.0, 0.0));
    transformationMatrixMesh.rotate(totalRotationY, QVector3D(0.0, 1.0, 0.0));
    transformationMatrixMesh.rotate(totalRotationZ, QVector3D(0.0, 0.0, 1.0));

    // Pass view-transform-information to shader
    glUniformMatrix4fv(projectionTransformationLocation_ptr, 1, GL_FALSE, transformationPerspective.data());

    // Change view - Viewtransform
    transformationMatrixView.rotate(viewRotationX, QVector3D(1.0, 0.0, 0.0));
    transformationMatrixView.rotate(viewRotationY, QVector3D(0.0, 1.0, 0.0));
    transformationMatrixView.rotate(viewRotationZ, QVector3D(0.0, 0.0, 1.0));
    transformationMatrixView = transformationMatrixView.inverted();

    // Pass view-transform-information to shader
    glUniformMatrix4fv(viewTransformationLocation_ptr, 1, GL_FALSE, transformationMatrixView.data());


    // Zooming
    // TODO for competition!

    // Pass shape to be drawn to Vertex-Shader - Mesh
    // Pass transformation matrix for mesh to shader
    glUniformMatrix4fv(transformationLocation_ptr, 1, GL_FALSE, transformationMatrixMesh.data());
    glBindVertexArray(VAB[meshIdx]);


    // Pass normal-preservation-information to shader (Mesh)
    preserveNormals = transformationMatrixMesh.normalMatrix();
    glUniformMatrix3fv(preserveNormalsLocation_ptr, 1, GL_FALSE, preserveNormals.data());

    // Actions specific to shading mode
    switch (shadingMode) {
        case ShadingMode::PHONG:{
            glUniform3f(materialColor_phong, mat.r, mat.g, mat.b);
            glUniform3f(materialCoefficients_phong, mat.ka, mat.ks, mat.kd);
            glUniform3f(lightPosLocation_phong, light.x, light.y, light.z);
            glUniform3f(lightColLocation_phong, light.r, light.g, light.b);
            glUniform1i(width_phong, width());
            glUniform1i(height_phong, height());
            break;
        }
        case ShadingMode::NORMAL:{
            break;
        }
        case ShadingMode::GOURAUD:{
            glUniform3f(lightPosLocation_gouraud, light.x, light.y, light.z);
            glUniform3f(illuminationCoeffsLocation_gouraud, mat.ka, mat.ks, mat.kd);
            glUniform3f(lightColLocation_gouraud, light.r, light.g, light.b);
            glUniform3f(materialColLocation_gouraud, mat.r, mat.g, mat.b);
            glUniform1i(sampler2Dgouraud_Location, 0); // '0' corresponds to 0 in 'glActiveTexture(GL_TEXTURE0);' (above)
            break;
        }
        case ShadingMode::WATER:{
            glUniform1f(timeCoefficient, timeIndicator);
            glUniform3f(wave1location ,wave1.amplitude, wave1.frequency, wave1.phase);
            glUniform3f(wave2location ,wave2.amplitude, wave2.frequency, wave2.phase);
            glUniform3f(wave3location ,wave3.amplitude, wave3.frequency, wave3.phase);
            glUniform3f(materialColor_water, mat.r, mat.g, mat.b);
            glUniform3f(materialCoefficients_water, mat.ka, mat.ks, mat.kd);
            glUniform3f(lightPosLocation_water, light.x, light.y, light.z);
            glUniform3f(lightColLocation_water, light.r, light.g, light.b);
//            glUniform1fv();
            break;
        }
    }
    glDrawArrays(GL_TRIANGLES,0,(int)lenMeshes[meshIdx]*3); // Nr of triangles * nr of vertices per triangle
}

/**
 * @brief MainView::resizeGL
 *
 * Called upon resizing of the screen
 *
 * @param newWidth
 * @param newHeight
 */
void MainView::resizeGL(int newWidth, int newHeight) 
{
    // Update projection to fit the new aspect ratio

    // Reset transformationPerspective matrix to avoid stacking angles
    transformationPerspective = QMatrix4x4();
    // Update perspective rotation with new width/height values
    transformationPerspective.perspective(60.0f,((float)width()/(float)height()),0.01f,200.0f);
    // Repaint with updated values
    update();
}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ)
{
    qDebug() << "Rotation changed to (" << rotateX << "," << rotateY << "," << rotateZ << ")";
    rotationX = (float)rotateX;
    rotationY = (float)rotateY;
    rotationZ = (float)rotateZ;
    update();
}

void MainView::setLightPosition(int x, int y, int z)
{
    qDebug() << "Reset lightposition to (" << x << "," << y << "," << z << ")";
    light.x = (float)0;
    light.y = (float)0;
    light.z = (float)0;
    update(); // Only using update() here didn't work; also required paintGL() to update reliably
    paintGL();
}

void MainView::resetLightColor()
{
    qDebug() << "Reset light color";
    light.r = (float)1;
    light.g = (float)1;
    light.b = (float)1;
    update(); // Only using update() here didn't work; also required paintGL() to update reliably
    paintGL();
}

void MainView::setLightX(int x)
{
    qDebug() << "Set lightposition to (" << (float)x/10.0f << "," << light.y << "," << light.z << ")";
    light.x = (float)x/10.0f;
    update();
}

void MainView::setLightY(int y)
{
    qDebug() << "Set lightposition to (" << light.x << "," << (float)y/10.0f << "," << light.z << ")";
    light.y = (float)y/10.0f;
    update();
}

void MainView::setLightZ(int z)
{
    qDebug() << "Set lightposition to (" << light.x << "," << light.y << "," << (float)z/10.0f << ")";
    light.z = (float)z/10.0f;
    update();
}

void MainView::setLightRed(int x)
{
    qDebug() << "Set light color red to (" << (float)x/10.0f << "," << light.y << "," << light.z << ")";
    light.r = (float)x/100.0f;
    update();
}

void MainView::setLightGreen(int y)
{
    qDebug() << "Set light color green to (" << light.x << "," << (float)y/10.0f << "," << light.z << ")";
    light.g = (float)y/100.0f;
    update();
}

void MainView::setLightBlue(int z)
{
    qDebug() << "Set light color blue to (" << light.x << "," << light.y << "," << (float)z/10.0f << ")";
    light.b = (float)z/100.0f;
    update();
}

void MainView::setScale(int scale)
{
    qDebug() << "Scale changed to " << scale;
    scalingFactor = ((float)scale*8.f)/200.0f; // Min scaling factor = 20/200; Max scaling factor = 220/200
    update();
}

void MainView::setShadingMode(ShadingMode shading)
{
    qDebug() << "Changed shading to" << shading;
    shadingMode = shading;
    paintGL(); // update() didn't work here
}


void MainView::setViewX(int x)
{
    qDebug() << "Set view x: " << x;
    viewRotationX = (float)x;
    update();
};

void MainView::setViewY(int y)
{
    qDebug() << "Set view y: " << y;
    viewRotationY = (float)y;
    update();
};

void MainView::setViewZ(int z)
{
    qDebug() << "Set view z: " << z;
    viewRotationZ = (float)z;
    update();
};

void MainView::resetView()
{
    qDebug() << "Reset view";
    viewRotationX = 0.0f;
    viewRotationY = 0.0f;
    viewRotationZ = 0.0f;
    update();
};

void MainView::setZoom(int z)
{
    qDebug() << "Set zoom: " << zoom;
    zoom = (float)z;
    update();
};

void MainView::resetZoom()
{
    qDebug() << "Reset zoom";
    zoom = 50.0f;
    update();
};


// --- Private helpers

/**
 * @brief MainView::onMessageLogged
 *
 * OpenGL logging function, do not change
 *
 * @param Message
 */
void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}
