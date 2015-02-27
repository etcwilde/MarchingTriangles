Marching Triangles
==================

Evan Wilde | University of Victoria

Program Description
-------------------

This program implements the marching triangles polygonization algorithm. Given
an implicit surface, it generates triangle mesh, which the computer can render
quickly and easily. The other method of drawing an implicit surface is using a
ray tracer, which is slow. One approach to polygonization is using the marching
cubes algorithm, which finds intersections of voxels and the implicit surface,
then attempts to determine how the surface intersects each voxel. The
intersection creates a triangle, which approximates the surface within the
voxel. There are two major issues with this approach: if the voxels are too
large, features of the surface will be missing in the triangle-mesh
approximation; It is slow.

The answer to downfall of the marching cubes algorithm is the marching
triangles algorithm. The marching triangles algorithm is not susceptible to the
same issues as the marching cubes algorithm, as it works completely
differently.

### Marching Triangles Algorithm

The first step in the marching triangles algorithm is to find a vertex on the
surface. Then using the gradient, finding two other points nearby on the
surface. The three points generate a seed triangle. We add the three new edges
to an edge pool. Then we select an edge at random and feel along the gradient
at the centre of the edge until the curvature of the surface becomes too great,
then we set a new point. The two points forming the selected edge and the new
point form a new triangle. The selected edge is removed from the edge pool and
the two new edges are added to the edge pool. This process continues until the
surface is covered.


### Implementation Details

Given that the surface is close, since we know some point within the surface,
we can fire a ray in any direction and at some point the ray will intersect the
surface. This is the easiest way of finding the surface without generating many
random numbers and simply testing to see if any of the random numbers hit the
surface, as done in Bloomenthal "An Implicit Surface Polygonizer". This only
works for closed surfaces, however, if we intelligently aim the ray, it is
possible that it will hit the surface in a bounded time.


