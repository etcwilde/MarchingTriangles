#ifndef VEC_H
#define VEC_H

#include <cmath>

/*
 * TODO
 * Update cached length on:
 * 	Scalar multiplication
 * 	Scalar division
 * 	vector addition
 * 	vector subtraction
 * 	normalization
 */

template <typename T>
class Point2D
{
	public:
		Point2D() : x(), y() {}
		Point2D(T _x, T _y) : x(_x), y(_y) {}

	private:
		T x;
		T y;
};

template <typename T>
class Point3D
{
	public:
		Point3D() : x(), y(), z() {}
		Point3D(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

	private:
		T x;
		T y;
		T z;
};

template <typename T>
class Vector2D
{
	public:
		Vector2D() : x(), y() {}
		Vector2D(T _x, T _y) : x(_x), y(_y) {}

		void Set(T _x, T _y);

		void Normalize();
		Vector2D<T> Normalized();
		Vector2D<T> Normalized() const;

		float Length();
		float Length() const;

		T Dot(const Vector2D<T>& vec) const;

		/* Operators */
		void operator += (const Vector2D<T>& vec);
		void operator -= (const Vector2D<T>& vec);
		void operator *= (T s);
		void operator /= (T s);

		Vector2D<T> operator -() const;
		Vector2D<T> operator +(const Vector2D<T>& vec) const;
		Vector2D<T> operator -(const Vector2D<T>& vec) const;

		template <typename L>
		friend Vector2D<L> operator * (const Vector2D<L>& vec, L s)
		{
			return Vector2D<T>(vec.x * s, vec.y * s);
		}

		template <typename L>
		friend Vector2D<L> operator * (L s, const Vector2D<L>& vec)
		{
			return Vector2D<T>(vec.x * s, vec.y * s);
		}

		template <typename L>
		friend Vector2D<L> operator / (const Vector2D<L>& vec, L s)
		{
			return Vector2D<T>(vec.x / s, vec.y / s);
		}

		/* Comparisons */

		bool operator == (const Vector2D<T>& vec) const;
		bool operator != (const Vector2D<T>& vec) const;
		bool operator <  (const Vector2D<T>& vec) const;
		bool operator <  (const Vector2D<T>& vec);
		bool operator <= (const Vector2D<T>& vec) const;
		bool operator <= (const Vector2D<T>& vec);
		bool operator >  (const Vector2D<T>& vec) const;
		bool operator >  (const Vector2D<T>& vec);
		bool operator >= (const Vector2D<T>& vec) const;
		bool operator >= (const Vector2D<T>& vec);

		inline T operator[] (unsigned int index);

		template <typename L>
		friend std::ostream& operator <<(std::ostream& os,
				const Vector2D<L>& v)
		{
			os << "[ " << v.x << ", " << v.y << " ]";
			return os;
		}


	private:
		union
		{
			struct {T x; T y;};
			T m_vals[2];
		};
		bool m_good_len_cache;
		float m_cached_length;
};

template <typename T>
class Vector3D
{
	public:
		Vector3D() : x(), y(), z() {}
		Vector3D(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

		void Set(T x, T y, T z);
		void Normalize();

		Vector3D<T> Normalized();
		Vector3D<T> Normalized() const;

		float Length();
		float Length() const;

		T Dot(const Vector3D<T>& vec) const;

		Vector3D<T> Cross(const Vector3D<T>& vec) const;

		/* Operators */
		// Vector addition
		void operator += (const Vector3D<T>& vec);

		// Vector subtraction
		void operator -= (const Vector3D<T>& vec);

		// Scalar multiplications
		void operator *= (T s);

		// Scalar division
		void operator /= (T s);

		Vector3D<T> operator -() const;

		Vector3D<T> operator +(const Vector3D<T>& vec) const;
		Vector3D<T> operator -(const Vector3D<T>& vec) const;

		template<typename L>
		friend Vector3D<L> operator*(const Vector3D<L>& vec, L s)
		{
			return Vector3D<T>(vec.x * s, vec.y * s, vec.z * s);
		}

		template<typename L>
		friend Vector3D<L> operator*(L s, const Vector3D<L>&vec)
		{
			return Vector3D<T>(vec.x * s, vec.y * s, vec.z * s);
		}

		template<typename L>
		friend Vector3D<L> operator/(const Vector3D<L>& vec, L s)
		{
			return Vector3D<T>(vec.x / s, vec.y / s, vec.z / s);
		}

		/* Comparisons */

		bool operator == (const Vector3D<T>& vec) const;
		bool operator != (const Vector3D<T>& vec) const;
		bool operator <  (const Vector3D<T>& vec) const;
		bool operator <  (const Vector3D<T>& vec);
		bool operator <= (const Vector3D<T>& vec) const;
		bool operator <= (const Vector3D<T>& vec);
		bool operator >  (const Vector3D<T>& vec) const;
		bool operator >  (const Vector3D<T>& vec);
		bool operator >= (const Vector3D<T>& vec) const;
		bool operator >= (const Vector3D<T>& vec);

		inline T operator[] (unsigned int index);

		template<typename L>
		friend std::ostream& operator <<(std::ostream& os,
				const Vector3D<L>& v)
		{
			os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
			return os;
		}

	private:

		union
		{
			struct {T x; T y; T z;};
			T m_vals[3];
		};

		bool m_good_len_cache;
		float m_cached_length;

};



// Implementations

// Vector2D

template <typename T>
void Vector2D<T>::Set(T x, T y)
{
	m_vals[0] = x;
	m_vals[1] = y;
}

template <typename T>
void Vector2D<T>::Normalize()
{
	float l = 1.0f / Length();
	m_vals[0] = (T)m_vals[0] * l;
	m_vals[1] = (T)m_vals[1] * l;
	m_vals[2] = (T)m_vals[2] * l;
}

template <typename T>
Vector2D<T> Vector2D<T>::Normalized()
{
	float l = 1.0f / Length();
	return Vector2D<T>(x * l, y * l);
}

template <typename T>
Vector2D<T> Vector2D<T>::Normalized() const
{
	float l = 1.0f / Length();
	return Vector2D<T>(x * l, y * l);

}

template <typename T>
float Vector2D<T>::Length()
{
	if (!m_good_len_cache)
		m_cached_length = (float)sqrt(x * x + y * y);
	return m_cached_length;
}

template <typename T>
float Vector2D<T>::Length() const
{
	if (m_good_len_cache) return m_cached_length;
	return (float)sqrt(x * x + y * y);
}

template <typename T>
T Vector2D<T>::Dot(const Vector2D<T>& vec) const
{
	return (x * vec.x + y * vec.y);
}

// Operators
template <typename T>
void Vector2D<T>::operator += (const Vector2D<T>& vec)
{
	x += vec.x;
	y += vec.y;
}

template <typename T>
void Vector2D<T>::operator -= (const Vector2D<T>& vec)
{
	x -= vec.x;
	y -= vec.y;
}

template <typename T>
void Vector2D<T>::operator *= (T s)
{
	x *= s;
	y *= s;
}

template <typename T>
void Vector2D<T>::operator /=(T s)
{
	x /= s;
	y /= s;
}

template <typename T>
Vector2D<T> Vector2D<T>::operator -() const
{
	return Vector2D<T>(-x, -y);
}

template <typename T>
Vector2D<T> Vector2D<T>::operator +(const Vector2D<T>& vec) const
{
	return Vector2D<T>(x + vec.x, y + vec.y);
}

template <typename T>
Vector2D<T> Vector2D<T>::operator -(const Vector2D<T>& vec) const
{
	return Vector2D<T>(x - vec.x, y - vec.y);
}

// Comparisons

template <typename T>
bool Vector2D<T>::operator == (const Vector2D<T>& vec) const
{
	return (x == vec.x && y == vec.y);
}

template <typename T>
bool Vector2D<T>::operator != (const Vector2D<T>&vec) const
{
	return (x != vec.x || y != vec.y);
}

template <typename T>
bool Vector2D<T>::operator < (const Vector2D<T>& vec) const
{
	if (*this == vec) return false;
	return (Length() < vec.Length());
}

template <typename T>
bool Vector2D<T>::operator < (const Vector2D<T>& vec)
{
	if (*this == vec) return false;
	return(Length() < vec.Length());
}

template <typename T>
bool Vector2D<T>::operator <= (const Vector2D<T>& vec) const
{
	if (*this == vec) return true;
	return (Length() <= vec.Length());
}

template <typename T>
bool Vector2D<T>::operator <= (const Vector2D<T>& vec)
{
	if (*this == vec) return true;
	return(Length() <= vec.Length());
}


template <typename T>
bool Vector2D<T>::operator > (const Vector2D<T>& vec) const
{
	if (*this == vec) return false;
	return (Length() > vec.Length());
}

template <typename T>
bool Vector2D<T>::operator > (const Vector2D<T>& vec)
{
	if (*this == vec) return false;
	return(Length() > vec.Length());
}

template <typename T>
bool Vector2D<T>::operator >= (const Vector2D<T>& vec) const
{
	if (*this == vec) return true;
	return (Length() >= vec.Length());
}

template <typename T>
bool Vector2D<T>::operator >= (const Vector2D<T>& vec)
{
	if (*this == vec) return true;
	return(Length() >= vec.Length());
}
// Vector3D
template <typename T>
void Vector3D<T>::Set(T x, T y, T z)
{
	m_vals[0] = x;
	m_vals[1] = y;
	m_vals[2] = z;
}

template<typename T>
void Vector3D<T>::Normalize()
{
	float l = 1.0f / Length();
	m_vals[0] = (T)m_vals[0] * l;
	m_vals[1] = (T)m_vals[1] * l;
	m_vals[2] = (T)m_vals[2] * l;
}

template<typename T>
Vector3D<T> Vector3D<T>::Normalized()
{
	float l = 1.0f / Length();
	Vector3D<T> ret_vec(
		(T)m_vals[0] * l,
		(T)m_vals[1] * l,
		(T)m_vals[2] * l);
	return ret_vec;
}

template <typename T>
Vector3D<T> Vector3D<T>::Normalized() const
{
	float l = 1.0f / Length();
	Vector3D<T> ret_vec(
			(T)m_vals[0] * l,
			(T)m_vals[1] * l,
			(T)m_vals[2] * l);
	return ret_vec;
}

template <typename T>
float Vector3D<T>::Length()
{
	if (!m_good_len_cache)
		m_cached_length = (float)sqrt(x * x + y * y + z * z);
	return m_cached_length;
}

template <typename T>
float Vector3D<T>::Length() const
{
	if (m_good_len_cache) return m_cached_length;
	return (float)sqrt(x * x + y * y + z * z);
}

template <typename T>
T Vector3D<T>::Dot(const Vector3D<T>& vec) const
{
	return (m_vals[0] * vec[0] + m_vals[1] * vec[1] + m_vals[2] * vec[2]);
}

template <typename T>
Vector3D<T> Vector3D<T>::Cross(const Vector3D<T>& vec) const
{
	return Vector3D<T>(y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x);
}

template <typename T>
void Vector3D<T>::operator += (const Vector3D<T>& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
}

template <typename T>
void Vector3D<T>::operator -= (const Vector3D<T>& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
}

template <typename T>
void Vector3D<T>::operator *= (T s)
{
	x *= s;
	y *= s;
	z *= s;
}

template <typename T>
void Vector3D<T>::operator /= (T s)
{
	x /= s;
	y /= s;
	z /= s;
}

template <typename T>
Vector3D<T> Vector3D<T>::operator -() const
{
	return Vector3D<T>(-x, -y, -z);
}

template <typename T>
Vector3D<T> Vector3D<T>::operator + (const Vector3D<T>& vec) const
{
	return Vector3D<T>(x + vec.x, y + vec.y, z + vec.z);
}

template <typename T>
Vector3D<T> Vector3D<T>::operator - (const Vector3D<T>& vec) const
{
	return Vector3D<T>(x - vec.x, y - vec.y, z - vec.z);
}

template <typename T>
bool Vector3D<T>::operator == (const Vector3D<T>& vec) const
{
	// same values
	return x == vec.x && y == vec.y && z == vec.z;
}

template <typename T>
bool Vector3D<T>::operator != (const Vector3D<T>& vec) const
{
	// Not same values
	return (x != vec.x || y != vec.y || z != vec.z);
}

template <typename T>
bool Vector3D<T>::operator < (const Vector3D<T>& vec) const
{
	if (*this == vec) return false;
	return (Length() < vec.Length());
}

template <typename T>
bool Vector3D<T>::operator < (const Vector3D<T>& vec)
{
	if (*this == vec) return false;
	return (Length() < vec.Length());
}

template <typename T>
bool Vector3D<T>::operator <= (const Vector3D<T>& vec) const
{
	if (*this == vec) return true;
	return (Length() <= vec.Length());
}

template <typename T>
bool Vector3D<T>::operator <= (const Vector3D<T>& vec)
{
	if (*this == vec) return true;
	return (Length() <= vec.Length());
}

template <typename T>
bool Vector3D<T>::operator > (const Vector3D<T>& vec) const
{
	if (*this == vec) return false;
	return (Length() > vec.Length());
}

template <typename T>
bool Vector3D<T>::operator > (const Vector3D<T>& vec)
{
	if (*this == vec) return false;
	return (Length() > vec.Length());
}

template <typename T>
bool Vector3D<T>::operator >= (const Vector3D<T>& vec) const
{
	if (*this == vec) return true;
	return (Length() >= vec.Length());
}

template <typename T>
bool Vector3D<T>::operator >= (const Vector3D<T>& vec)
{
	if (*this == vec) return true;
	return (Length() >= vec.Length());
}

template <typename T>
inline T Vector3D<T>::operator [] (unsigned int index)
{
	return m_vals[index % 3];
}

#endif // VEC_H
