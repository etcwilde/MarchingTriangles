#include "implicit/ImplicitSystem.hpp"
#include "PolyTris.hpp"
#include "Mesh.hpp"

int main()
{
	Implicit::Sphere s(geoffFunction);
	Implicit::Line l(geoffFunction);

	Implicit::Scale line_scale(&l, 2, 1, 1);
	Implicit::Scale sphere_scale(&s, 1.2);
	Implicit::Translate sphere_translate_1(&sphere_scale, 2, 0, 0);
	Implicit::Translate sphere_translate_2(&sphere_scale, -2, 0, 0);
	Implicit::Union caps1(&sphere_translate_1, &sphere_translate_2);
	Implicit::Rotate caps2(&caps1, glm::vec3(0, 1, 0), M_PI/2.f);
	Implicit::Union caps(&caps1, &caps2);

	Implicit::Rotate r1(&line_scale, glm::vec3(0, 1, 0), M_PI/2.f);
	Implicit::Rotate r2(&line_scale, glm::vec3(0, 0, 1), M_PI/2.f);
	Implicit::Union u1(&r1, &r2);
	Implicit::Union u2(&line_scale, &u1);
	Implicit::Union jack(&u2, &caps);

	TrisPoly marching_triangles(jack);
	Mesh m = marching_triangles.Polygonize();
	m.Export("output.obj");
	return 0;
}
