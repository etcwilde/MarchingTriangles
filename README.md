# Marching Triangles
## Introduction
Implementing the Marching Triangles Algorithm

The marching triangles algorithm is a polygonization algorithm for implict surfaces.
It takes an implicit surface and generates a triangle mesh, which can be rendered 
more quickly than the original implicit surface. A good polygonization algorithm will result
in a mesh that accurately describes the implicit surfaces, without distorted triangles, and
the resulting mesh is homeomorphic to the orginal shape. It also does not have ambiguous cases.

This implementation works with the blob model of implicit objects. A blob is defined by a central vertex, a field falloff function where the value at the central point is 1, and at some distance R drops to 0, and an iso value. Where the function evaluates to the iso value, the surface is defined.

This implementation includes a viewing window, a polygonizer, and the implicit system.

## Requirements
To build the program you must have installed;
 - g++ with c++11
 - make

To run the program you must have installed;
 - OpenGL
 - GLFW3
