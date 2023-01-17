# [WIP] GLWE - 2D OpenGL rendering engine optimzed to be compiled to WebAssembly
GLWE is a 2D *OpenGL* rendering engine written in *C++* that can be compiled for Desktop devices or to WebAssembly with [Emscripten](https://github.com/emscripten-core/emscripten). 
The current demo can be downloaded [here](https://github.com/david-palm/glwe/releases/tag/demo).

<p align="center">
  <img src="https://user-images.githubusercontent.com/109848051/212894248-67ce8ade-03d4-4278-9833-066976c0e23c.png" width="75%">
  <br/> 
      <em>Screenshot of the current demo of GLWE showing two vertex arrays with custom shaders as a Windows Desktop application</em>
   </br>
</p>

## Current features
- Easy rendering of simple 2D shape through abstraction of shaders, buffers, and vertex/index arrays
- Event system handles key and mouse inputs
- Code can be easily compiled to Desktop or WebAssembly
