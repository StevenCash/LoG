# LoG
Engine for simple exploration

Requires:
SDL2
SDL2_Image
Box2D
GLM
GLEW
tinyxml2

# Visual Studio version 
This version of LoG, contained in the VS2019LoG branch, has been altered to compile in visual studio 2019 (and hopefully any newer VS).
To set up the required dependencies, the following must be done:
The Box2D headers (In the Box2D subfolder "Box2D" that contains the folders "collision", "common", etc. and the Box2D.h header)  Take this
entire folder and copy it into the LoG folder.  
The SDL headers, which are in the "include" folder of SDL.  Copy the "include" folder into the LoG folder and rename it SDL.
GLM, copy the "glm" subfolder of glm into the LoG folder.  This will contain a number of .hpp files and some subfolders.
I placed the tinyxml2 and glew header files into the project folder already, though it might be better to put them in their own folders.
The project requires a number of library files.  Create a subfolder of LoG named "lib".  Place the following files in it:
Box2D.lib
glew32s.lib
SDL2.lib
SDL2_image.lib
SDLmain.lib
I also place the dlls in the output folder, which is currently set to "Debug".  The required dlls are:
SDL2.dll
SDL2_image.dll
glew32.dll
The shader files need to also be placed in the output folder, these are:
ShipFragment.glsl
ShipVertex.glsl
I think that is everything.

