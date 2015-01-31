#ifndef VECTOR_UNIT_TEST_H
#define VECTOR_UNIT_TEST_H

#include <fstream>
#include <iostream>

#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>

#include <string>

#include "Vector.hpp"

// TODO
//
// Dot products
// Cross product
//

using namespace CppUnit;
class Vector2DTest: public TestFixture
{
	public:
	static Test *suite()
	{
		TestSuite * suiteOfTests = new TestSuite("Vector2D Test");

		suiteOfTests->addTest(
				new TestCaller<Vector2DTest>(
					"Vector2D -- Construction and Index",
					&Vector2DTest::TestConstruct)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector2DTest>(
					"Vector2D -- Set",
					&Vector2DTest::TestSet)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector2DTest>(
					"Vector2D -- Comparisons",
					&Vector2DTest::TestComparisons)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector2DTest>(
					"Vector2D -- Operators",
					&Vector2DTest::TestOperators)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector2DTest>(
					"Vector2D -- Length",
					&Vector2DTest::TestLength)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector2DTest>(
					"Vector2D -- Normalize",
					&Vector2DTest::TestNormalize)
				);
		return suiteOfTests;
	}

	void setUp(){}
	void tearDown(){}

	protected:

	void TestConstruct()
	{
		Vector2D<int> a(0, 1);
		CPPUNIT_ASSERT(a[0] == 0);
		CPPUNIT_ASSERT(a[1] == 1);
		CPPUNIT_ASSERT(a[2] == 0);
	}

	void TestSet()
	{
		Vector2D<int> a(0, 1);
		a.Set(2, 3);
		CPPUNIT_ASSERT(a[0] == 2);
		CPPUNIT_ASSERT(a[1] == 3);
	}

	void TestLength()
	{
		Vector2D<int> a(0, 2);
		CPPUNIT_ASSERT(a.Length() == 2);
		CPPUNIT_ASSERT(a.Length() == 2);
		a.Set(2, 3);
		CPPUNIT_ASSERT(a.Length() != 2);
	}

	void TestComparisons()
	{
		Vector2D<int> a(0, 1);
		Vector2D<int> b(0, 1);

		// Equality
		CPPUNIT_ASSERT(a == a);
		CPPUNIT_ASSERT(a == b);
		CPPUNIT_ASSERT(a >= b);
		CPPUNIT_ASSERT(a <= b);

		b *= 2;
		CPPUNIT_ASSERT(b[0] == 0 && b[1] == 2);
		// Inequalities
		CPPUNIT_ASSERT(a < b);
		CPPUNIT_ASSERT(a <= b);
		CPPUNIT_ASSERT(b > a);
		CPPUNIT_ASSERT(b >= a);
		CPPUNIT_ASSERT(b != a);
		CPPUNIT_ASSERT(a != b);
	}

	void TestOperators()
	{
		Vector2D<int> a(0, 1);
		Vector2D<int> b(0, 2);

		// addition
		Vector2D<int> c = a + b;
		// Subtraction
		Vector2D<int> d = c - b;

		CPPUNIT_ASSERT(a != b);
		CPPUNIT_ASSERT(a == b/2);
		CPPUNIT_ASSERT(a * 2 == b);
		CPPUNIT_ASSERT(a + b == b + a);
		CPPUNIT_ASSERT(c == a + b);
		CPPUNIT_ASSERT(d == a);

		// Increment
		b /= 2;
		CPPUNIT_ASSERT(b.Length() == 1);
		b *= 2;
		CPPUNIT_ASSERT(b.Length() == 2);
		a += b;
		// (0, 1) + (0, 2)
		CPPUNIT_ASSERT(a == Vector2D<int>(0, 3));
		a -= b;
		CPPUNIT_ASSERT(a == Vector2D<int>(0, 1));
		Vector2D<int> e = -a;
		CPPUNIT_ASSERT(-e == a);
		CPPUNIT_ASSERT(e == -a);
		CPPUNIT_ASSERT(e[0] == 0 && e[1] == -1);

		c = a * 2;
		CPPUNIT_ASSERT(c[0] == 0 && c[1] == 2);
		c = a / 1;
		CPPUNIT_ASSERT(c[0] == 0 && c[1] == 1);
	}

	void TestNormalize()
	{
		Vector2D<int> a(0, 2);
		Vector2D<int> b = a.Normalized();

		CPPUNIT_ASSERT(a.Length() != 1);
		a.Normalize();
		CPPUNIT_ASSERT(a.Length() == 1);
		CPPUNIT_ASSERT(b.Length() == 1);
	}
};

class Vector3DTest: public TestFixture
{
	public:
	static Test *suite()
	{
		TestSuite* suiteOfTests = new TestSuite("Vector3D Test");
		suiteOfTests->addTest(
				new TestCaller<Vector3DTest>(
					"Vector3D -- Construction and Index",
					&Vector3DTest::TestConstruct)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector3DTest>(
					"Vector3D -- Set",
					&Vector3DTest::TestSet)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector3DTest>(
					"Vector3D -- Comparisons",
					&Vector3DTest::TestComparisons)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector3DTest>(
					"Vector3D -- Operators",
					&Vector3DTest::TestOperators)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector3DTest>(
					"Vector3D -- Length",
					&Vector3DTest::TestLength)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector3DTest>(
					"Vector3D -- Normalize",
					&Vector3DTest::TestNormalize)
				);
		return suiteOfTests;


	}

	protected:
	void TestConstruct()
	{
		Vector3D<int> a(0, 1, 2);
		CPPUNIT_ASSERT(a[0] == 0);
		CPPUNIT_ASSERT(a[1] == 1);
		CPPUNIT_ASSERT(a[2] == 2);
		CPPUNIT_ASSERT(a[3] == 0); // Wrap around
	}

	void TestSet()
	{
		Vector3D<int> a(0, 1, 2);
		CPPUNIT_ASSERT(a[0] == 0);
		CPPUNIT_ASSERT(a[1] == 1);
		CPPUNIT_ASSERT(a[2] == 2);

		a.Set(2, 3, 4);
		CPPUNIT_ASSERT(a[0] == 2);
		CPPUNIT_ASSERT(a[1] == 3);
		CPPUNIT_ASSERT(a[2] == 4);
	}

	void TestLength()
	{
		Vector3D<int> a(0, 2, 0);
		CPPUNIT_ASSERT(a.Length() == 2);
		CPPUNIT_ASSERT(a.Length() == 2);
		a.Set(2, 3, 1);
		CPPUNIT_ASSERT(a.Length() != 2);
	}

	void TestComparisons()
	{
		Vector3D<int> a(0, 1, 1);
		Vector3D<int> b(0, 1, 1);

		// Equality
		CPPUNIT_ASSERT(a == a);
		CPPUNIT_ASSERT(a == b);
		CPPUNIT_ASSERT(a >= b);
		CPPUNIT_ASSERT(a <= b);

		b *= 2;
		CPPUNIT_ASSERT(b[0] == 0 && b[1] == 2 && b[2] == 2);
		// Inequalities
		CPPUNIT_ASSERT(a < b);
		CPPUNIT_ASSERT(a <= b);
		CPPUNIT_ASSERT(b > a);
		CPPUNIT_ASSERT(b >= a);
		CPPUNIT_ASSERT(b != a);
		CPPUNIT_ASSERT(a != b);
	}

	void TestOperators()
	{
		Vector3D<int> a(0, 1, 1);
		Vector3D<int> b(0, 2, 2);

		// addition
		Vector3D<int> c = a + b;
		// Subtraction
		Vector3D<int> d = c - b;

		CPPUNIT_ASSERT(a != b);
		CPPUNIT_ASSERT(a == b/2);
		CPPUNIT_ASSERT(a * 2 == b);
		CPPUNIT_ASSERT(a + b == b + a);
		CPPUNIT_ASSERT(c == a + b);
		CPPUNIT_ASSERT(d == a);

		// Increment
		// (0, 1) + (0, 2)
	}

	void TestNormalize()
	{
		Vector3D<float> float_test(1, 1, 0);
		CPPUNIT_ASSERT(float_test.Length() != 1);
		float_test.Normalize();
		CPPUNIT_ASSERT(float_test.Length() == 1);
	}

};

#endif //VECTOR_UNIT_TEST_H
