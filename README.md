# Marching Triangles
Implementing the Marching Triangles Algorithm

The marching triangles algorithm is a polygonization algorithm for implict surfaces.
It takes an implicit surface and generates a triangle mesh, which can be rendered 
more quickly than the original triangle mesh. A good polygonization algorithm will result
in a mesh that accurately describes the implicit surfaces, without distorted triangles, and
the resulting mesh is homeomorphic to the orginal shape. It also does not have ambiguous cases.

## Game Plan
At this time, I'm working on the window and supporting structure.
Next I will be working on implementing the implicit system, or fininding one and fitting it into
the program.
Eventually the system will have a "polygonize" function, which will run the implemented marching
triangles algorithm on the implicit system.

## The controls
  <ul>
    <li>w - Dolly Camera in</l>
    <li>s - Dolly Camera out</li>
    <li>i - Increment fov</li>
    <li>j - Decrement fov</li>
  </ul>

Additional controls will be implemented.
  
  
  


