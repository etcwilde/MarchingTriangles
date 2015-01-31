#ifndef VEC_H
#define VEC_H
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

	private:
		T x;
		T y;
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

		float Dot(const Vector3D<T>& vec) const;

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

		Vector3D<T> operator +(const Vector3D<T>& vec);
		Vector3D<T> operator -(const Vector3D<T>& vec);

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
		bool operator <= (const Vector3D<T>& vec) const;
		bool operator >  (const Vector3D<T>& vec) const;
		bool operator >= (const Vector3D<T>& vec) const;

		inline T operator[] (unsigned int index);

		template<typename L>
		friend std::ostream& operator <<(std::ostream& os, const Vector3D<L>& v)
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

// Vector3D
template <typename T>
void Vector3D<T>::Set(T x, T y, T z)
{
	m_vals[0] = x;
	m_vals[1] = y;
	m_vals[2] = z;
}

template <typename T>
Vector3D<T> Vector3D<T>::operator + (const Vector3D<T>& vec)
{
	return Vector3D<T> (x + vec.x, y + vec.y, z + vec.z);
}

template <typename T>
Vector3D<T> Vector3D<T>::operator - (const Vector3D<T>& vec)
{
	return Vector3D<T> (x - vec.x, y - vec.y, z - vec.z);
}




#endif // VEC_H
