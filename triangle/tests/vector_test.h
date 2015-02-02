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
#include "floatlibs.hpp"

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

		suiteOfTests->addTest(
				new TestCaller<Vector2DTest>(
					"vector2D -- Products",
					&Vector2DTest::TestProducts)
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

	void TestProducts()
	{
		Vector2D<int> a(2, 3);
		Vector2D<int> b(4, 5);
		Vector2D<int> c(0, 1);
		Vector2D<int> d(1, 0);

		int dot = a.Dot(b);
		int perp = c.Dot(d);
		CPPUNIT_ASSERT(dot == 23);
		CPPUNIT_ASSERT(perp == 0);

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

		suiteOfTests->addTest(
				new TestCaller<Vector3DTest>(
					"Vector3D -- Products",
					&Vector3DTest::TestProducts)
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
	}

	void TestNormalize()
	{
		Vector3D<float> float_test(1, 1, 0);
		CPPUNIT_ASSERT(float_test.Length() != 1);
		float_test.Normalize();
		CPPUNIT_ASSERT(f_equ(1.f, float_test.Length()));
	}

	void TestProducts()
	{
		Vector3D<int> a(1, 2, 3);
		Vector3D<int> b(4, 5, 6);

		Vector3D<int> c(1, 0, 0);
		Vector3D<int> d(0, 1, 0);

		int dot = a.Dot(b);
		int perp = c.Dot(d);
		CPPUNIT_ASSERT(dot == 32);
		CPPUNIT_ASSERT(perp == 0);

		Vector3D<int> cross = a.Cross(b);
		Vector3D<int> cross_correct(-3, 6, -3);
		CPPUNIT_ASSERT(cross == cross_correct);
	}
};

class Vector4DTest: public TestFixture
{
	public:
	static Test *suite()
	{
		TestSuite* suiteOfTests = new TestSuite("Vector4D Test");
		suiteOfTests->addTest(
				new TestCaller<Vector4DTest>(
					"Vector4D -- Construction and Index",
					&Vector4DTest::TestConstruct)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector4DTest>(
					"Vector4D -- Set",
					&Vector4DTest::TestSet)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector4DTest>(
					"Vector4D -- Comparisons",
					&Vector4DTest::TestComparisons)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector4DTest>(
					"Vector4D -- Operators",
					&Vector4DTest::TestOperators)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector4DTest>(
					"Vector4D -- Length",
					&Vector4DTest::TestLength)
				);

		suiteOfTests->addTest(
				new TestCaller<Vector4DTest>(
					"Vector4D -- Normalize",
					&Vector4DTest::TestNormalize)
				);
		suiteOfTests->addTest(
				new TestCaller<Vector4DTest>(
					"Vector4D -- Products",
					&Vector4DTest::TestProducts)
				);
		return suiteOfTests;
	}

	protected:

	void TestConstruct()
	{
		Vector4D<int> def_vec;
		CPPUNIT_ASSERT(def_vec[0] == 0);
		CPPUNIT_ASSERT(def_vec[1] == 0);
		CPPUNIT_ASSERT(def_vec[2] == 0);
		CPPUNIT_ASSERT(def_vec[3] == 0);

		Vector4D<int> a(0, 1, 2, 3);
		CPPUNIT_ASSERT(a[0] == 0);
		CPPUNIT_ASSERT(a[1] == 1);
		CPPUNIT_ASSERT(a[2] == 2);
		CPPUNIT_ASSERT(a[3] == 3);
		CPPUNIT_ASSERT(a[4] == 0);

		Vector4D<long> b(10000, 50000, 1000000, 100000000000);
		CPPUNIT_ASSERT(b[0] == 10000);
		CPPUNIT_ASSERT(b[1] == 50000);
		CPPUNIT_ASSERT(b[2] == 1000000);
		CPPUNIT_ASSERT(b[3] == 100000000000);
		CPPUNIT_ASSERT(b[4] == 10000);
	}

	void TestSet()
	{
		Vector4D<int> a;
		a.Set(1, 2, 3, 4);
		CPPUNIT_ASSERT(a[0] == 1);
		CPPUNIT_ASSERT(a[1] == 2);
		CPPUNIT_ASSERT(a[2] == 3);
		CPPUNIT_ASSERT(a[3] == 4);
	}

	void TestLength()
	{
		Vector4D<int> a(0, 0, 0, 1);
		CPPUNIT_ASSERT(a.Length() == 1);
		a.Set(0, 0, 2, 0);
		CPPUNIT_ASSERT(a.Length() == 2);
		Vector4D<int> b(1, 0, 0, 0);
		CPPUNIT_ASSERT(b.Length() == 1);
	}

	void TestComparisons()
	{
		Vector4D<int> a(0, 0, 0, 1);
		Vector4D<int> b(0, 0, 0, 1);
		Vector4D<int> c(1, 0, 0, 0);
		Vector4D<int> d(0, 0, 0, 2);

		CPPUNIT_ASSERT(a == b);
		CPPUNIT_ASSERT(a != c);

		CPPUNIT_ASSERT(a >= b);
		CPPUNIT_ASSERT(a <= b);

		// While they are not equal, they are not greater nor less
		// Equal magnitude, maybe equal direction
		CPPUNIT_ASSERT(a >= c);
		CPPUNIT_ASSERT(a <= c);

		// Only information on magnitude.
		CPPUNIT_ASSERT(!(a < c));
		CPPUNIT_ASSERT(!(a > c));
		CPPUNIT_ASSERT(!(c < a));
		CPPUNIT_ASSERT(!(c > a));

		a.Set(1, 2, 3, 4);
		b.Set(1, 2, 3, 4);
		CPPUNIT_ASSERT(a == b);


	}

	void TestOperators()
	{
		Vector4D<int> a(1, 2, 3, 4);
		Vector4D<int> b(5, 6, 7, 8);
		Vector4D<int> c = a + b;
		Vector4D<int> d = b - a;
		Vector4D<int> e = c / 2;
		Vector4D<int> f = d * 2;

		CPPUNIT_ASSERT(a != b);
		CPPUNIT_ASSERT(a != c);
		CPPUNIT_ASSERT(a != d);
		CPPUNIT_ASSERT(b != c);
		CPPUNIT_ASSERT(b != d);

		Vector4D<int> c_correct(6, 8, 10, 12);
		Vector4D<int> d_correct(4, 4, 4, 4);
		CPPUNIT_ASSERT(c == c_correct);
		CPPUNIT_ASSERT(d == d_correct);

		Vector4D<int> e_correct(3, 4, 5, 6);
		Vector4D<int> f_correct(8, 8, 8, 8);

		CPPUNIT_ASSERT(e == e_correct);
		CPPUNIT_ASSERT(f == f_correct);
	}

	void TestNormalize()
	{
		Vector4D<float> a(2, 2, 3, 4);
		Vector4D<float> b = a.Normalized();

		CPPUNIT_ASSERT(!f_equ(a.Length(), 1));
		CPPUNIT_ASSERT(f_equ(b.Length(), 1));
		a.Normalize();
		CPPUNIT_ASSERT(f_equ(a.Length(), 1));
	}

	void TestProducts()
	{
		Vector4D<int> a(1, 2, 3, 4);
		Vector4D<int> b(5, 6, 7, 8);

		CPPUNIT_ASSERT(a.Dot(b) == 70);
	}
};
#endif //VECTOR_UNIT_TEST_H
