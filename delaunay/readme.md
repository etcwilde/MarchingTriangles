Delaunay Triangulation
======================

Evan Wilde | University of Victoria

Program Description
-------------------

The program generates a triangulation from a point cloud defined in a .poly
file. The polygon file contains one or more polygons and the color data for
each vertex in the polygon. The program will take the information and generate
a triangulation for the polygon that it represents.

Program Purpose
---------------

This is to give me an understanding of how triangulation of arbitrary point
clouds works. It is also to help me get a feeling for what data structures I
may need in order to generalize it for the third dimension.

Invocation
----------

The program is invoked from the root directory of the Delaunay project. If it
is invoked elsewhere, it will not find the gflw-cxx library I have linked
against. The root is the path where the makefile resides. In this directory,
you will see bin/, build/, inc/, libs/, makefile, example\_file.poly, and this
readme.md.

`./bin/delaunay polyfile.poly`

Polyfile is any polygon file.

Polygon File Definitions:
-------------------------

```
c 	-- Color (r g b)
p	-- polygon separation
v	-- Vertex in a polygon
#	-- Comment
```

If a vertex is defined before a polygon, it will be added to the implied
polygon. Any vertices that follow will also be added to the implied first
polygon until the first polygon separator.

Colors are defined in rgb from 0 to 255. 
Vertices are integers x, y.




