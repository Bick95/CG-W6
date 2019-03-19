######Readme Open GL Assignment 3 (see below for Readme of 'OpenGL Assignment 2')

# Rotating a model

To start out with, a function (MainView::drawShape) was created to draw meshes. Meshes are stored in a model-array, and hence each mesh is a model. Textures per mesh/model are stored in a textures-array, where a texture at array-position X, hence texture[X], corresponds to model[X]. While it was implemented that a model could potentially have no texture assigned, it was decided to assign the RUG-logo-texture to all models in the code which had no other texture available, since then each model could be equally well presented in all 4 shading modes: Phong, Normal, Gouraud, and Water. The draw function takes as arguments the index of a model/texture, the center-position of of an object to be drawn, the rotational speed in the x-, y-, and z-directions respectively of the object, the objects's scale-value, and an object-index, which indicates the how many'th object is to be drawn, since possibly all models may be drawn multiple times, such that the object-index of an object can be different from the mesh/model index corresponding to the model an object is an instance of. 

To implement rotation, each object drawn got its own (individual) current rotational angle in the x-, y- , and z-direction respectively assigned. For that, three arrays were created, storing objects' current rotational angles in the x-, y-, and z-direction respectively. For example, individualRotationX[4] contains the current rotational angle in the x-direction of objct 4 to be drawn, where the angle starts at 0, is in [0, 360) degrees, and increases proportionally to an objects rotational speed in a given direction. For updating this value (individual rotaional angle), it gets incremented each time that paintGL() is called by the magnitude of an object's rotational speed in the given direction times pi, but at most by 2pi at a time, where the latter implementation serves as a speed limit. To bound the rotational angles to the given interval, 'mod 360' is applied to rotational angles. In our current implementation, the speed by which an object rotates in a given direction, is specified in the call of MainView::drawShape for a given object. Working with fractions of pi here, was supposed to make rotations smoother opposed to taking arbitrary int/float values. We are aware, however, that inputs to the rotation function are considered in degrees. Still, using a small fraction of pi gave a smooth and flawless rotation around a given axis, such that we sticked to this implementation. Since it was decided to keep the originally provided dials responsible for rotating all the objects shown in a model, in each iteration of the paintGL call, the individual rotational angle of an object gets added to the angle given as user-input by a certain dial-setting, such that the sum of both finally determines the exact orientation of an object at a given moment in time. 

# Animating a complete scene

The general approach to handling multiple instances to be drawn of the same mesh/model has been outlined above already. To add on to this, in our implementation, multiple instances of the same model are drawn by commanding a given model to be drawn multiple times, each time passing different arguments to the MainView::drawShape function (leading to concurrent different animations of the same models), such as different positions (depending on translations) or scaling-factors or rotational angles, as discussed above, for example. It is worth mentioning that drawing the same object multiple times is not different than drawing any other object after all. As was implemented for the last assignment already, all the model-, (new) view-, projection-, and normal-matrices get reset and re-computed for each object individually in each iteration of the paintGL-call. Passing the proper uniform-inputs to the shaders is handled by SWITCH-statements, which take the selected shading-mode as a selection criterion. 

For the rotation of the camera, a second set of dials (labeled accordingly) was added, allowing for rotation of the camera in x-, y-, and z-direction respectively. The specified angles via these dials get inserted into a second kind of transformation matrix, being called transformationMatrixView. Since the camera position in OpenGL is fixed to the origin-position (0,0,0), the inverted transformationMatrixView gets applied to the objects drawn in the respective shaders to simulate the movement of the camera. The order of the application of the various transformation matrices looks as follows:
new_Position = projectionTransform * viewTransform * modelTransform * original_Position.


As an additional extra, it has been implemented that two of the animated objects circulate around on the screen in various directions. This has been implemented by making the position of an object in the (x,y,z)-directions time-dependent, where time is modelled by a counter which gets incremented each time that the paintGL() function is called. Again, each time, the counter is incremented by a small fraction of pi and modulus 2pi is applied to the counter each iteration. Then, to get a circular motion, the counter gets plugged into sin- and cosine functions and the values of the results get added to the positions of the selected objects when calling the draw-function. This functionality works accross all shaders.  

# Water shader

## Height map

The height is implemented as follows: the third coordinate of the vertex is recalculated to be the output of a wave function. The wave function takes the first coordinate of the vertex, along with an amplitude, frequency and phase. These are defined in a wave class, and the wave is constructed in the mainview header and then the values are passed as a uniform to the shader in the mainview.cpp. The wave function is as follows:
coordinate3 = amplitude * sin(2pi * (frequency * coordinate1 + phase))

## Normals

The normals are calculated similarly to the height, but here we need the derivative of the function. It uses the same parameters, and the derivative of the above function is the following:

derivative = amplitude * cos(2pi * (frequency * coordinate1 + phase)) * frequency * 2pi

This derivative value is then plugged into the function normal = normalize([-derivative, 0, 1]) to get the normals. The normals are passed to the fragment shader and used for coloring in this step.

## Multiple waves
the sin and cosine functions can be simply added for height and normal calculation. We define 3 wave in the mainview, pass them all as uniform, and then calculate the hieght and derivative separately (in separate functions) and then sum up the individual components. The sum of height is then set to be the z coordinate, and the sum of derivatives is plugged into the normal calculation expression shown above. 

The phong shading is copied from the phong shader and implemented in the fragment shader. Since the normals are passed, we only need to access the material and light uniforms (set them at the mainvew) and we can calculate the phong shading in the same manner. The color is chosen to be a mix between a water blue (R:0, G:0.467, B:0.745) and white, with a smoothstep with parameters 0.6 and 0.95 to ensure that the surface is mostly blue, and only the high waves are close to white, so the whole surface is more water-like.

## Animating water
For the water animation, we needed to extend both the wave and its derivative function with a time component:
coordinate3 = amplitude * sin(2pi * (frequency * coordinate1 + phase + timeComponent))

derivative = amplitude * cos(2pi * (frequency * coordinate1 + phase + timeComponent)) * frequency * 2pi

This time component is a uniform set in the mainview. The value of this uniform is always set to be the timeIndicator value, that we also use for the rotation animations of the other objects. Since it is constantly growing (and the trigonometric functions are periodical), this produces wave behavior for both position and derivative.

##########################
Readme Open GL Assignment 2 (see below for Readme of 'OpenGL Assignment 1')


For this assignment, we built up on our code submitted for the Open GL Assignment 1, since the code worked without any problems. 

In the first step of this assignment, we implemented the three illumination models Normal-, Gouraud-, and Phong shading in the respective shader-files contained in the code. 

In addition to the three variables passed to all 3 vertex shaders, which are modelTransform (transformation matrix for transformation of the model displayed), projectionTransform (responsible for transforming the projection), preserveNormals (to preserve the original relative angles of the normals of the model displayed after the model transformation), we also included the uniform-variables lightPos, lightColor, materialColor, and coeffs as inputs to both the vertex shaders of the Gouraud and Phong illumination models, giving the position of the (unique) light source, the color of the light source, the material color, and the 3 illumination coefficients (= ka, kd, and ks; combined in a struct) respectively. 

While for the Gouraud model, most computations to be implemented happen in the vertex shader, most of the computations to be implemnted for the Phong model happen in the respective (Phong) fragment shader, since in this model the color values are computed per pixel instead of receiving them already interpolated from the vertex shader, as is the case in the Gouraud model.  Therefore the Gouraud fragment shader basically takes the calculated light value from the vertex and outputs it (with the addition of the texture, but that comes later).

In the Normal illumination model, the interpolated normals per pixel arrive in the Normal fragment shader, after the adjusted normals per vertex get determined in the Normal vertex shader. Normals get 'adjusted' by applying the normal matrix to them. Finally, a mapping of the interpolated normals per fragment happens in the Normal fragment shader, mapping values from [-1,1] to [0,1], so to make them interpretable as color values.

The Phong shader is very similar in calculation to the Gouraud, but besides the normal calculation, everything happens in the fragment shader. The normal and the variables 
lightPos, lightColor, materialColor, and coeffs are simply passed further to the fragment shader, alongside with the relative position, as in the fragment we can only access position in terms of pixels.

Notes for the shaders: the shaders only work with 1 light source. The eye position is assumed to be at [0,0,0], and hard coded to that. The p exponent for the specular reflection is selected to be 3, also hard coded in the corresponding shaders. For Phong, the light position is automatically normalized when passing from the vertex to the fragment, so we multiply it by 10 to obtain the same position as in Gouraud. Also here, the uniforms height and width are included, but not used in the final model. The shaders produce the outputs with the textures, but the original color-outputs are still there as comments.

Selecting shaders happens by receiving action events whenever the user clicks on a respective Radio button for chosing another shader, which results in our implementation in a shading-mode index to be assigned to a dedicated variable which always stores the current shading mode index. Consequentially, the chosen shader (indicated by the variable) gets assigned to a shader pointer in a switch-statement, and the shader-object the pointer points to is then used for the shading the resulting image of the model to be displayed in the scene after the switch of the shading mode. 

As an extra, we implemented the possibility to change the position and the color of the light-source. One can change the position in the scene within the bounds [-10,10], where 0 is the center of the screen in all three directions: x, y, and z respectively through the manipulation of slider values. -/+ signs next to the sliders indicate in which direction the user is moving the light-source.  For the color, the values red, green and blue of the light source can be change by the corresponding sliders in the range of [0,1].

Speaking about extras, also the unitization-function has been updated to be universally applicable to all kinds of meshes/shapes now. Now, the function finds the max value from the set of all x-, y-, and z-coordinates in an object and divides afterwards all coordinate values belonging to the object by the previously determined maximal coordinate value. 

For implementing the texture mapping, we exactly followed the instructions from the slides. So there is not much to be reported about that part. One point to be mentioned, though, is how we decided to include the additional 2D coordinates for the texture mapping into our previous implementation. We included them as additional x- and y-coordinates in the vertex structure. Consequentially, the formatting of how to interpret the data stored in the VBO had to be adjusted to start a new vertex every 8 floats now. Also, we introduced a third location in all vertex shaders, being called mesh_coords, which is used for retrieving the appropriate 2D coordinates of where to look up the texture value for a given 3D position on a mesh.  

In both, the Gouraud and the Phong fragment shaders, we compute the final shading of a fragment/pixel by multiplying the corresponding texture value retrieved from the texture map for a given pixel by the computed illumination value at the same pixel.

This concludes the descriptions of new implementations and changes made to the code. The project has been tested on the university computers on Linux.


 

##########################
Readme OpenGL Assignment 1

For this assignment, we enabled passing transformation-matrices from the MainView-object, where they get updated, to the shader-object, where the transformations get applies to the vertex-positions.
Also, vertices had to be created for representing both the cube and the pyramid shapes. For simplicity, the same vertices are shared between both shapes (only in different combinations and being translated to different positions).

The global variables scalingFactor and rotationX, rotationY, rotationZ have been introduced to to store the user inputs commanded via the Q-Widgets globally. When repainting the shapes, the updated values of these variables are retrieved to generate an updated transformation matrix for each shape respectively. 

Also, a Mesh can be read in by now. "Unitization" (Normalization) has been implemented in the model by applying the QVector3D::normalize() function to each vertex stored in the model. A pseudo-random generator was included to the MainView to generate the random numbers specifying the Sphere's colors.  

Also, since multiple buffers had to be used for multiple shapes, the VBO and VAB have been changed to being arrays, where index = 0 refers to cube, index = 1 refers to pyramid, and index = 2 refers to sphere. These global arrays get freed in the MainView's destructor again.

For further information, please see the comments in the code.

The largest problem encountered was understanding the various aspects of how the VertexShader and the MainView communicate. We however, by now, understand how this mechanism works. 
Also, understanding the working of the QMatrix4x4 object was not easy in the beginning. Furthermore, initially not putting vertices in the "right" (counter-clockwise) order when defining shapes caused problems.

The project can be run by building and running it in the Qt environment.
