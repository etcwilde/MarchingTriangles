#ifndef POLYGONIZER_HPP
#define POLYGONIZER_HPP
#include "Mesh.hpp"
#include "implicit/ImplicitSystem.hpp"

class Polygonizer
{
public:
	/**
	 * \brief Constructs a new polygonizer
	 *
	 * Polygonizes the scene defined by the implicit Object
	 */
	Polygonizer(Implicit::Object& scene);


	/**
	 * \brief Returns Polygonized Mesh
	 */
	Mesh Polygonize();
protected:
	/**
	 * \brief Returns the polygonized mesh
	 *
	 * This is not necessarily where the polygonization happens
	 * The inputs should be defined by the type of polygonizer used
	 */
	virtual Mesh polygonize()=0;

	Implicit::Object& m_scene;
private:
	bool m_cache_mesh_set;
	Mesh m_cache_mesh;
};


#endif//POLYGONIZER_HPP
