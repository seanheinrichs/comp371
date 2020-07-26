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

List of Controls:
---------------------------------------
**Model Selection**
* 1 - Select the first model to manipulate
* 2 - Select the second model to manipulate
* 3 - Select the third model to manipulate
* 4 - Select the fourth model to manipulate
* 5 - Select the fifth model to manipulate

**Scale**
* U - Scale up the model (set to 0.2f when less than 0)
* J - Scale down the model (set to 0.2f when less than 0)

**Translation**
* SHIFT + W - Move the selected model up
* SHIFT + S - Move the selected model down
* SHIFT + A - Move the selected model left
* SHIFT + D - Move the selected model right
* SHIFT + Q - Move the selected model
* SHIFT + E - Move the selected model

**Rotation**
* A - Rotate left 5 degrees about y-axis
* D - Rotate right 5 degrees about y-axis

**Camera FPS Movement**
* G - Move camera forward
* V - Move camera backward
* C - Move camera left
* B - Move camera right
* Left mouse botton - Move to zoom in and out of the scene
* Middle mouse botton - Move in y direction to tilt
* Right mouse botton - Move in x direction to pan

**World Rotation**
* Left arrow - Anti-clockwise rotation about positive x axis
* Right arrow - Anti-clockwise rotation about negative x axis
* Up arrow - Anti-clockwise rotation about positive y axis
* Down arrow - Anti-clockwise rotation about negative y axis
* Home botton - Reset to initial world position

**Render Mode**
* SHIFT + P - Change rendering to points
* SHIFT + L - Change rendering to lines
* SHIFT + T - Change rendering to triangles

**Shearing**
* P - Shear horizontal to the left
* O - Shear horizontal to the right

**Texture Toggle**
* X - turn textures OFF
* SHIFT + X - turn textures ON

**Shadow Toggle**
* 

---

Libraries:
---------------------------------------
* opengl32.lib
* glew32s.lib
* glfw3.lib

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
* Objloader.cpp is from lab06 by Jonathan.