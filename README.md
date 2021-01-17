# Rearrengine

This engine is been developed with the objective of learning game development. The main functionality of the engine so far is to render scenes containing 3D models with diffuse and specular textures. Implementing the graphic user interface is crucial for facilitating the user all the information related to the model that's been rendered.

## Developers

Juan Carlos Sánchez Guzmán [GitHub](https://github.com/jcarlos0305)
Álvaro Hinojal [Github](https://github.com/AHinojal)

## Usage

The camera controls to navigate in the viewport are Unity-like.

- Right-click to rotate the camera freely.
- Right-click + W,A,S,D,Q,E to move around.
- Up, Down, Left & Right to rotate the camera in that direction.
- Mouse wheel to zoom in and out.
- Holding SHIFT duplicates the camera movement speed

- Possibility to save and load scenes
- Phong PBR implemented
- Game object pattern implemented
- Editable scene with the GUI
- Static source of light

Dragging and dropping models: Add the dropped model to the current scene.

Dragging and dropping textures: apply the new texture to the existing model.

## Libraries used

- [Glew](https://github.com/nigels-com/glew)
- [SDL](https://www.libsdl.org/download-2.0.php)
- [MathGeoLib](https://github.com/juj/MathGeoLib)
- [ImGui](https://github.com/ocornut/imgui)
- [DevIL](http://openil.sourceforge.net/download.php)
- [Assimp](https://www.assimp.org/index.php/downloads)
- [Jsoncpp](https://github.com/open-source-parsers/jsoncpp)

## License
[MIT](https://choosealicense.com/licenses/mit/)
