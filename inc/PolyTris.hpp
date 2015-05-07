#ifndef POLYTRIS_HPP
#define POLYTRIS_HPP

#include "implicit/ImplicitSystem.hpp"
#include "Polygonizer.hpp"
#include "PolyTris.hpp"
#include "PolyFront.hpp"
#include "Mesh.hpp"
#include "utils/GeoCore.hpp"
#include "implicit/Aabb.hpp"
#include "nanoflann.hpp"


// Curvature Dependent Marching Triangles Polygonizer

class TrisPoly : public Polygonizer
{
public:
	TrisPoly(Implicit::Object& o);


protected:
	virtual Mesh polygonize();
private:


private:
	// Variables
	Mesh m_mesh;
	std::stack<Front*> m_fronts;

};


#endif//POLYTRIS_HPP
