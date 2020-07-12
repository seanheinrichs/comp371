# COMP 371 - Section CC Practical Assignment #1

Author & Contributor List
-----------
Benjamin Therien (40034572)

Sean Heinrichs (40075789)

Wayne St Amand (40074423)

Isabelle Gourchette (40008121)

Ziming Wang (40041601)

Implementation Specifications
---------------------------------------
* Creates a 100x100 square grid (ground surface) in the XZ plane centred at the origin.
* Creates a set of three lines 5 grid units in length, in 3 different colors, representing each coordinate axis in virtual world space, centered at the origin.
* Creates an alphabet and a digit model as described earlier and like the one depicted in the figure by suitably transforming a unit cube. There must be one model by each of the team members based on their name and student ID.
* Four models are to be placed in the four corners of the grid, and the fifth model is initially positioned at the center of the grid facing along X axis.
* The model should consist of independent parts so they can be rotated/moved on their own. We recommend that you use hierarchical modelling, so that a single transformation applied to a model’s origin will apply it to a complete model.
* Places a virtual camera with the world space origin as the point of focus. For display and animation:
  * Create a GLFW window of size 1024x768 with double buffering support.
  * Render the coordinate axis, ground and all the models in the window.
  * The application should use a perspective view to display all the objects and enable hidden surface removal.
* The user can incrementally size up the model by pressing ‘U’ to scale-up and ‘J’ to scale-down. Each key press should result in a small size change.
* The user can control the model position and orientation using keyboard input, i.e., A → move left, D → move right, W → move up, S → move down, a → rotate left 5 degrees about Y axis, d → rotate right 5 degrees about Y axis. You may add other rotations about other axis, if you want.
  * You may defined keys ‘1’ to ‘5‘ to allow you to select which model to manipulate.
  * You may predefine cameras as well accordingly with the default position in front of each model, or use a singe FPS-like camera to move around to each model under your control.
* The world orientation is changed by using keyboard input i.e. left arrow → Rx, right arrow → R-x, up arrow → Ry, down arrow → R-y. (Rx denotes a small anti-clockwise rotation about positive x axis, R-x about negative x axis, etc.) Pressing Home button should reset to the initial world position and orientation.
* The user can change rendering mode for the model, i.e. points, lines, triangles based on keyboard input, namely, key ‘P’ for points, key ‘L’ for lines, key ‘T’ for triangles.
* The user can pan and tilt the camera as follows:
  * While right button is pressed → use mouse movement in x direction to pan.
  * While middle button is pressed → use mouse movement in y direction to tilt.
* The user can zoom in and out of the scene - while left button is pressed → use mouse movement to move into/out of the scene.
 
---

Libraries:
---------------------------------------
* FreeImage.lib
* opengl32.lib
* glew32s.lib
* glfw3.lib
* kernel32.lib
* user32.lib
* gdi32.lib
* winspool.lib
* comdlg32.lib
* advapi32.lib
* shell32.lib
* ole32.lib
* oleaut32.lib
* uuid.lib
* odbc32.lib
* odbccp32.lib

---

Included ThirdParty:
---------------------------------------
* GLEW - 2.1.0
* GLFW - 3.3
* FreeImage - 3170
* GLM

---

Compilation Information
---------------------------------------
Compiled using Visual Studio 2017 on Windows.

GLEW, GLFW, and GLM have been configured to be in the project folder for compilation, for both lib and header files.

---

Sources:
---------------------------------------
* https://www.youtube.com/watch?v=FBbPWSOQ0-w&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=10
* https://learnopengl.com/?fbclid=IwAR1bqkHtImRamrNihlHn2LQSd9sZBEM9MpjwzWFb8B19jKZm6FMC4fmgrt0

---

Project source can be downloaded from https://github.com/bentherien/comp371.git





















