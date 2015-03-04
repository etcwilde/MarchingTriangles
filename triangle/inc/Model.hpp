#ifndef MODEL_H
#define MODEL_H
#include <vector>
using std::vector;

#include "Color.hpp"



namespace Mesh
{

	class Material
	{
	public:
		ColorRGB AmbientColor();
		ColorRGB DiffuseColor();
		ColorRGB SpecularColor();
		unsigned int SpecularExponent();
		float Transparency();

	private:
		unsigned int type; // not sure
		ColorRGB Ka;
		ColorRGB kd;
		ColorRGB ks;
		float Ns;
		float Trans;

	};

	class Index_Triangle
	{
	public:
		Index_Triangle();

		void push_vertex(unsigned int vertex_index);
		void push_uv(unsigned int uv_index);
		void push_normal(unsigned int normal_index);

		unsigned int get_vertex(unsigned int index);
		unsigned int get_uv(unsigned int index);
		unsigned int get_normal(unsigned int index);
		unsigned int get_material();

	private:
		unsigned int m_vert_index;
		unsigned int m_verts[3];

		unsigned int m_uv_index;
		unsigned int m_uv[3];

		unsigned int m_normal_index;
		unsigned int m_normals[3];

		unsigned int m_material_index;
	};

	class Mesh
	{
	public:
		Mesh();
	};

};


/*class Mesh
{
public:
	Mesh();
	void push_vertex(unsigned int vertex);
	void push_normal(unsigned int normal);
	void set_material(unsigned int material);

	std::vector<unsigned int> get_vertices();
	std::vector<unsigned int> get_normals();

private:
	std::vector<unsigned int> vertex_index;
	std::vector<unsigned int> normal_index;
}; */

#endif
