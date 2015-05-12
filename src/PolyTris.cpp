#include "PolyTris.hpp"
// Protected Methods
//

Mesh TrisPoly::polygonize()
{
	auto begin = std::chrono::high_resolution_clock::now();
	m_container.pushFront(seedHexagon(m_scene.GetCenterVertex()));
	while (m_container.fronts() > 0)
	{
		Front* f0 = m_container.popFront();
		// Build front kdtree
		Front_pt_kdtree front_tree(2, FrontPtAdaptor(m_container, f0),
				nanoflann::KDTreeSingleIndexAdaptorParams(KDTREE_PARAM_SIZE));
		while (f0->size() > 3)
		{

			actualizeAngles(f0);
			const unsigned int min_angle_index = f0->getMinimalAngle();
			const float opening_angle = f0->getOpeningAngle(min_angle_index);
			std::cout << "Front Min Angle Index: " << min_angle_index << '\n';
			const float* selected_point = &m_container.getVertex(f0->getVertex(min_angle_index)).x;
			const float roc = m_container.getRoc(f0->getVertex(min_angle_index)) * SEED_ROC_MULTIPLIER;

			// This may get expensive
			m_mesh_tree.buildIndex();
			front_tree.buildIndex();

			std::vector<std::pair<long unsigned int, float>> danger_points;
			front_tree.radiusSearch(selected_point, roc, danger_points,
					nanoflann::SearchParams(KDTREE_PARAM_SIZE));

#ifdef DEBUG
			std::cout << "Danger Points: " << danger_points.size() << '\n';
#endif

			// The point we tested is the only point in danger, so
			// there is no danger
			if (danger_points.size() == 1)
			{
				std::vector<std::pair<long unsigned int, float>> mesh_points;
				m_mesh_tree.radiusSearch(selected_point, roc, mesh_points,
						nanoflann::SearchParams(KDTREE_PARAM_SIZE));
#ifdef DEBUG
				std::cout << "Mesh Collision Points: " << mesh_points.size() << '\n';
#endif
				if (mesh_points.size() > 1)
				{
					std::cout << "Merge maybe?\n";
				}
				else
				{
					std::cout << "Expand triangle\n";
					expandTriangle(min_angle_index, opening_angle, f0);
				}




				// Perform a front-collision detection
				// This is also difficult
				// Look for collision with the mesh kdtree
				// Get the indecies. Perform a reverse-lookup
				// on all the fronts,
				//
				// If a front collides with this point, merge
				// them
				//
				// Otherwise expand the triangle
				//
				// OH MY GOODNESS! THE END IS IN SIGHT! YEAH!!!
				// (assuming everything works)

			}
			else
			{
				// Split the front
				std::cout << "Split Front!\n";
				break;
			}



			// I may want to use the mesh kd tree for this

			// If no self-intersection
			// 	Check for front collisions
			// 	    Use front-kdtree radius search -- heuristic
			// 	    length
			// 	    	if Collision, get front, and front index
			//     		of vertex
			//
			//
			//We need a mapping from glm::vec3 to vertex index
			//We need a mapping from vertex index to front index
			//



			break;
		}

		// fill front
		// save faces
		// delete front
		delete f0;
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Polygonization Time: " <<
		std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count()
		<<  " ms\n";
	//actualizeAngles(m_co);
	//m_mesh_tree.buildIndex();
	//m_front_tree.buildIndex();

	// Build mesh triangulation

	std::cout << "Building " << m_container.faces() << " faces\n";
	Mesh m;
	for (unsigned int i = 0; i < m_container.faces(); i++)
	{
		m.AddFace(m_container.getVertex(m_container.getFace(i).vert_index[0]),
			m_container.getVertex(m_container.getFace(i).vert_index[1]),
		       	m_container.getVertex(m_container.getFace(i).vert_index[2]),
			m_container.getNormal(m_container.getFace(i).vert_index[0]),
			m_container.getNormal(m_container.getFace(i).vert_index[1]),
		       	m_container.getNormal(m_container.getFace(i).vert_index[2]));

		/*
		m.AddFace(m_container.m_vertices[m_container.m_faces[i].vert_index[0]],
			m_container.m_vertices[m_container.m_faces[i].vert_index[1]],
			m_container.m_vertices[m_container.m_faces[i].vert_index[2]],
			m_container.m_normals[m_container.m_faces[i].vert_index[0]],
			m_container.m_normals[m_container.m_faces[i].vert_index[1]],
			m_container.m_normals[m_container.m_faces[i].vert_index[2]]);
			*/
	}
	return m;
}

// Private Methods
// Given a seed, generates a seed hexagon
Front* TrisPoly::seedHexagon(const glm::vec3& start)
{
	const glm::vec3 seed = m_scene.Project(start);
	const glm::vec3 n = m_scene.Normal(seed);
	glm::vec3 t, b;
	const float roc = rocAtPt(seed);
	TangentSpace(n, t, b);
#ifdef DEBUG
	std::cout << "Seed Value: " << m_scene.Evaluate(seed) << '\n';
	std::cout << "Roc: " << roc << '\n';
#endif
	m_container.pushVertex(seed);
	m_container.pushNormal(n);
	m_container.pushRoc(roc);

	// Generate first front!

	Front* front = new Front();
	for (unsigned int i = 0; i < 6; ++i)
	{
		float x = 2.f * roc * SEED_ROC_MULTIPLIER * std::cos(float(i) * 0.33333333f * M_PI);
		float y = 2.f * roc * SEED_ROC_MULTIPLIER * std::sin(float(i) * 0.33333333f * M_PI);
		glm::vec3 proj_point = m_scene.Project(seed + (x*t) + (y*b));

		m_container.pushVertex(proj_point);
		m_container.pushNormal(m_scene.Normal(proj_point));
		m_container.pushRoc(rocAtPt(proj_point));

		unsigned int f_v_index = 1 + (i % 6);

		front->appendVertex(f_v_index);
		PolyContainer::Face f;
		f.vert_index[0] = 0;
		f.vert_index[1] = 1 + (i % 6);
		f.vert_index[2] = 1 + ((i + 1) % 6);
		m_container.pushFace(f);
	}
	return front;
}


void TrisPoly::actualizeAngles(Front* f)
{
	if (f == NULL) return;
	for (unsigned int i = 0; i < f->size(); ++i)
		f->setOpeningAngle(i, computeOpenAngle(i, f));
}

// Computes open angle from the values in the front
// ith vertex in the top front
// Everything is in radians
// Counter-clockwise
// The left is next
// the right is previous
float TrisPoly::computeOpenAngle(unsigned int i, const Front* f) const
{
	if (f == NULL) return 0;
	const unsigned int vi = f->getVertex(i);
	const glm::vec3 v = m_container.getVertex(vi);
	const glm::vec3 n = m_container.getNormal(vi);
	const unsigned int left_index = f->getLeft(i);
	const unsigned int right_index = f->getRight(i);
	const glm::vec3 vleft = m_container.getVertex(left_index);
	const glm::vec3 vright = m_container.getVertex(right_index);

	glm::vec3 X, Y;
	TangentSpace(n, X, Y);
	glm::vec3 vleft_proj;
	glm::vec3 vright_proj;
	vleft_proj.x = glm::dot((vleft - v), X);
	vright_proj.x = glm::dot((v - vright), X);
	vleft_proj.y = glm::dot((vleft - v), Y);
	vright_proj.y = glm::dot((v - vright), Y);
	vleft_proj.z = 0;
	vright_proj.z = 0;
	vleft_proj = glm::normalize(vleft_proj);
	vright_proj = glm::normalize(vright_proj);


	float dot = clamp<float>(glm::dot(vleft_proj, vright_proj), -1.f, 1.f);
	float opening_angle;
	// Keep it on the exterior
	if ((glm::cross(vleft_proj, vright_proj)).z >= 0.f)
		opening_angle = M_PI + std::acos(dot);
	else opening_angle = M_PI - std::acos(dot);
	return opening_angle;
}

float TrisPoly::rocAtPt(const glm::vec3& v)
{
	float k1, k2;
	m_scene.Curvature(v, k1, k2);
	return 1.f/((std::max(std::abs(k1), std::abs(k2))));
}

// a and b are vertex indices not front indices, they don't exist yet
// Wrong, they are front indices Use F to dereference them
void TrisPoly::splitFronts(Front* F, Front* A, unsigned int a,
		Front* B, unsigned int b)
{
	// a, b, a_prime, and b_prime are all front indices
	// NOT vertex indices
	unsigned int a_prime = a + 1;
	unsigned int b_prime = b + 1;

	A = new Front();
	{
		A->appendVertex(F->getVertex(a));
		unsigned int current = b_prime;
		while (current != a)
		{
			A->appendVertex(F->getVertex(current));
			if (++current == A->size()) current = 0;
		}
	}

	B = new Front();
	{
		B->appendVertex(F->getVertex(b));
		unsigned int current = a_prime;
		while (current != b)
		{
			B->appendVertex(F->getVertex(current));
			if(++current == B->size()) current = 0;
		}
	}
}

Front* TrisPoly::mergeFronts(Front* A, unsigned int a, Front* B, unsigned int b)
{
	unsigned int a_prime = a + 1;
	unsigned int b_prime = b + 1;
	Front* F = new Front();
	F->appendVertex(A->getVertex(a));
	unsigned int current = b_prime;
	while (current != b)
	{
		F->appendVertex(B->getVertex(current));
		if(++current == B->size()) current = 0;
	}

	F->appendVertex(A->getVertex(a_prime));
	current = a_prime + 1;
	while (current !=  a_prime)
	{
		F->appendVertex(A->getVertex(current));
		if (current == A->size()) current = 0;
	}

	return F;
}

// Take front index
void TrisPoly::expandTriangle(unsigned int fi, float angle, Front* F)
{
	const unsigned int n_tris = std::floor(3 * angle / M_PI); // Compute 3/pi by hand
	const float roc = m_container.getRoc(F->getRadiusOfCurvature(fi));
	const glm::vec3 seed = m_container.getVertex(F->getVertex(fi));
	const glm::vec3 n = m_container.getNormal(F->getVertex(fi));
	const glm::vec3 vleft = m_container.getVertex(F->getLeft(fi));
	const glm::vec3 vright = m_container.getVertex(F->getRight(fi));
	glm::vec3 t, b;
	TangentSpace(n, t, b);
#ifdef DEBUG
	std::cout << "Front Index: " << fi << '\n';
	std::cout << "Opening Angle: " << toDegrees<float>(angle) << '\n';
	std::cout << "Generating " << n_tris << " triangles\n";
	std::cout << "Radius of curvature: " << roc << '\n';
	std::cout << "Adjusted Radius of Curvature: " << roc * SEED_ROC_MULTIPLIER << '\n';
	std::cout << "Vertex: " << vleft << " < " << seed <<  " > " << vright <<'\n';
	std::cout << "Normal: " << n << '\n';
#endif

	// Generate new triangles
	for (unsigned int i = 0; i < n_tris; ++i)
	{
		float x = 2.f * roc * SEED_ROC_MULTIPLIER * std::cos(float(i) * 0.33333333f * M_PI);
		float y = 2.f * roc * SEED_ROC_MULTIPLIER * std::sin(float(i) * 0.33333333f * M_PI);
		std::cout << "[" << x << ", " << y << "]" << '\n';

	}


}
