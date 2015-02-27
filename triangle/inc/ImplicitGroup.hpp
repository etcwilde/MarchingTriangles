#ifndef IMPLICIT_GROUP_H
#define IMPLICIT_GROUP_H

#include <list>

#include <glm/glm.hpp>

#include "ImplicitObject.hpp"

#include <float.h>

namespace Implicit
{
	class Group : public Object
	{
	public:
		Group();
		Group(int max_depth);

		void addBaseObject(Object* obj);
		void addRecursiveObject(Object* obj);

		float getFieldValue(glm::vec3 point);
		PointFlavour getFlavour(glm::vec3 point);
		bool contains(glm::vec3 point, float errorMargin);
		std::list<glm::vec3> getPointsInObject();

		virtual float getFieldFromObjects(std::list<Object*> objects,
				glm::vec3 point)=0;

		virtual PointFlavour getFlavourFromObjects(
				std::list<Object*> objects, glm::vec3 point);
		virtual bool containedInObjects(std::list<Object*> objects,
				glm::vec3 point, float errorMargin);
		virtual std::list<glm::vec3> getPointsInObjects(
				std::list<Object*> objects);

	private:
		std::list<Object*> m_recursiveObjects;
		std::list<Object*> m_baseObjects;
		int m_maxDepth;
		int m_depth;
	};

	class Blend : public Group
	{
	public:
		Blend() : Group() {}
		Blend(int maxDepth) : Group(maxDepth) {}
		float getFieldFromObjects(std::list <Object*> objects, glm::vec3 point);
	};

	class RicciBlend : public Group
	{
	public:
		RicciBlend(float power) :
			Group(),
			m_power(power),
			m_invPower(1.f / power)
		{}

		RicciBlend(float power, float maxDepth) :
			Group(maxDepth),
			m_power(power),
			m_invPower(1.f / power)
		{}

		float getFieldFromObjects(std::list<Object*> objects,
				glm::vec3 point);

	private:
		float m_power;
		float m_invPower;

	};

	class Union : public Group
	{
	public:
		Union() : Group() {}
		Union(int maxDepth) : Group(maxDepth) {}

		float getFieldFromObjects(std::list<Object*> objects,
				glm::vec3 point);
		PointFlavour getFlavourFromObjects(std::list<Object*> objects,
				glm::vec3 point);
	};

	class Intersect : public Group
	{
	public:
		Intersect() : Group() {}
		Intersect(int maxDepth) : Group(maxDepth) {}

		float getFieldFromObjects(std::list<Object*> objects, glm::vec3 point);
		PointFlavour getFlavourFromObjects(std::list<Object*> objects, glm::vec3 point);
		std::list<glm::vec3> getPointsInObjects(std::list<Object*> objects);
	};

	class Difference : public Group
	{
	public:
		Difference(float iso) :
			Group(),
			m_iso(iso)
		{}

		Difference(float iso, int maxDepth) :
			Group(maxDepth),
			m_iso(iso)
		{}

		float getFieldFromObjects(std::list<Object*> objects, glm::vec3 point);
		PointFlavour getFlavourFromObjects(std::list<Object*> objects, glm::vec3 point);
		std::list<glm::vec3> getPointsInObjects(std::list<Object*> objects);
		bool containedInObjects(std::list<Object*> objects,
				glm::vec3 point, float errorMargin);

	private:
		float m_iso;

	};
};

#endif
