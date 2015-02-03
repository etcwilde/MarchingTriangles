#ifndef MAT_H
#define MAT_H

#include "floatlibs.hpp"
#include "Vector.hpp"

#include <iostream>

#include <cmath>

template <typename T>
class Matrix2x2
{
	public:

		// Create identity matrix
		Matrix2x2();

		// Create matrix
		Matrix2x2(T _m11, T _m12, T _m21, T _m22);

		// Rotation matrix
		Matrix2x2(float rot);

		//  Index
		T m11() const;
		T m12() const;
		T m21() const;
		T m22() const;

		T Determinant() const;


		// If matrix is non-invertible, returns identity matrix
		// If matrix is invertible, invertible is set to 1
		Matrix2x2<T> invert(bool* invertible=0) const;
		bool isIdentity() const;

		/* Operators */
		Matrix2x2<T> operator *(Matrix2x2<T>& mat) const;
		friend Vector2D<T> operator *(const Vector2D<T>& vec,
				const Matrix2x2<T>& mat)
		{
			T x = (vec.x * mat.m11()) + (vec.y * mat.m12());
			T y = (vec.x * mat.m21()) + (vec.y * mat.m22());
			Vector2D<T> ret_vec(x, y);
			return ret_vec;
		}


		friend std::ostream& operator <<(std::ostream& os,
				Matrix2x2<T>& m)
		{
			os << "| " << m.m11() << ' ' << m.m12() << " |\n" <<
			      "| " << m.m21() << ' ' << m.m22() << " |\n";
			return os;
		}

		void  operator *= (const Matrix2x2<T>& mat);

		friend void operator*= (Vector2D<T>& vec, const Matrix2x2<T>& mat)
		{
			T x = (vec.x * mat.m11()) + (vec.y * mat.m12());
			T y = (vec.x * mat.m21()) + (vec.y * mat.m22());
			vec.Set(x, y);
		}

	private:
		union
		{
			struct{ T m_m11; T m_m12; T m_m21; T m_m22;};
			T m_vals[4];
		};


};

/* Implementations */
// Matrix2x2


template <typename T>
Matrix2x2<T>::Matrix2x2()
	: m_m11(1), m_m12(0), m_m21(0), m_m22(1)
{}

template <typename T>
Matrix2x2<T>::Matrix2x2(T _m11, T _m12, T _m21, T _m22)
	: m_m11(_m11), m_m12(_m12), m_m21(_m21), m_m22(_m22)
{}

template <typename T>
Matrix2x2<T>::Matrix2x2(float rot)
{
	m_m22 = m_m11 = (T)cos(rot);
	// Try something here
	m_m12 = -(T)sin(rot);
	m_m21 = -m_m12;
}

template <typename T>
T Matrix2x2<T>::m11() const
{
	return m_m11;
}

template <typename T>
T Matrix2x2<T>::m12() const
{
	return m_m12;
}

template <typename T>
T Matrix2x2<T>::m21() const
{
	return m_m21;
}

template <typename T>
T Matrix2x2<T>::m22() const
{
	return m_m22;
}

template <typename T>
T Matrix2x2<T>::Determinant() const
{
	return (m_m11 * m22) - (m_m12 * m_m21);
}

template <typename T>
Matrix2x2<T> Matrix2x2<T>::operator * (Matrix2x2<T>& mat) const
{
	Matrix2x2<T> ret_mat(
	m_m11 * mat.m11() + m_m12 * mat.m21(),
	m_m11 * mat.m12() + m_m12 * mat.m22(),
	m_m21 * mat.m11() + m_m22 * mat.m21(),
	m_m22 * mat.m12() + m_m22 * mat.m22()
	);
	return ret_mat;
}

template <typename T>
void Matrix2x2<T>::operator *= (const Matrix2x2<T>& mat)
{
	T m11, m12, m21, m22;
	m11 = m_m11 * mat.m11() + m_m12 * mat.m21();
	m12 = m_m11 * mat.m12() + m_m12 * mat.m22();
	m21 = m_m21 * mat.m11() + m_m22 * mat.m21();
	m22 = m_m22 * mat.m12() + m_m22 * mat.m22();

	m_m11 = m11; m_m12 = m12; m_m21 = m21; m_m22 = m22;
}


/*template <typename T>
Vector2D<T> operator*= (Vector2D<T>& vec, const Matrix2x2<T>& mat)
{
	T x = (vec.x * mat.m11()) + (vec.y * mat.m12());
	T y = (vec.x * mat.m21()) + (vec.y * mat.m22());
	vec.Set(x, y);
} */


#endif // MAT_H
