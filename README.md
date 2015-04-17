# Marching Triangles
## Introduction
Implementing the Marching Triangles Algorithm

The marching triangles algorithm is a polygonization algorithm for implicit
surfaces. It takes an implicit surface and generates a triangle mesh, which can 
be rendered more quickly than the original implicit surface. A good
polygonization algorithm will result in a mesh that accurately describes the
implicit surfaces, without distorted triangles, and the resulting mesh is
homeomorphic to the original shape. It also does not have ambiguous cases.

## Requirements
To build the program you must have installed;
 - g++ with c++11
 - make
 - `lib/libImplicit.a`

To run the program you must have installed;
 - OpenGL
 - GLFW3

