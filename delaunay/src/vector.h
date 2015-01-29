#ifndef VECTOR_H
#define VECTOR_H

#include <ostream>
#include <cmath>
namespace container
{
	template<typename T>
	class P2
	{
		public:
			T x;
			T y;
	};

	template <typename T>
	class P3
	{
		public:
			T x;
			T y;
			T z;
	};

};


/*!\brief Two-dimensional vector class */
template<typename T>
class Vector2
{
	public:
		/* Constructors */
		Vector2<T>(): x(0), y(0){}
		Vector2<T>(T x_, T y_):
			x(x_), y(y_){}

		/* Operations */
		void set(T x_, T y_)
		{x = x_, y = y_;}

		T Length() const
		{
			return (T)sqrt(x * x + y * y);
		}

		void Normalize()
		{
			float l = 1.0f / Length();
			x *= l;
			y *= l;
		}

		Vector2<T> Normalized() const
		{
			float l = 1.0f / Length();
			return  Vector2<T> ((T)(x * l), (T)(y * l));
		}

		Vector2<T> Normalized()
		{
			float l = 1.0f / Length();
			return Vector2<T> ((T)(x * l), (T)(y * l));
		}

		T Dot(const Vector2<T>& b)
		{
			return (T)(x * b.x + y * b.y);
		}

		Vector2<T> operator -() const
		{
			return Vector2<T> (-x, -y);
		}

		friend std::ostream& operator<<(std::ostream& os,
				const Vector2<T>& vec)
		{
			os << "[ " << vec.x << ", " << vec.y << " ]";
			return os;
		}

		/* Operators */
		Vector2<T> operator+(const Vector2<T> &right)
		{
			return Vector2<T>(x+right.x, y+right.y);
		}

		Vector2<T> operator+(const T right)
		{
			return Vector2<T>(x+right, y+right);
		}

		Vector2<T> operator+=(const Vector2<T> &right)
		{
			x += right.x;
			y += right.y;
		}

		Vector2<T> operator+=(const T right)
		{
			x += right;
			y += right;
		}

		Vector2<T> operator-(const Vector2<T> &right)
		{
			return Vector2<T>(x-right.x, y-right.y);
		}

		Vector2<T> operator-(const T right)
		{
			return Vector2<T>(x-right, y-right);
		}

		Vector2<T> operator-=(const Vector2<T> &right)
		{
			x -= right.x;
			y -= right.y;
		}

		Vector2<T> operator-=(const T right)
		{
			x -= right; y -= right;
		}

		Vector2<T> operator*(const Vector2<T> &right)
		{
			return Vector2<T>(x*right.x, y*right.y);
		}

		Vector2<T> operator*(const T right)
		{
			return Vector2<T>(x*right, y*right);
		}

		Vector2<T> operator*=(const Vector2<T> &right)
		{
			x *= right.x;
			y *= right.y;
		}

		Vector2<T> operator*=(const T right)
		{
			x *= right;
			y *= right;
		}

		Vector2<T> operator/(const Vector2<T> &right)
		{
			return Vector2<T>(x/right.x, y/right.y);
		}

		Vector2<T> operator/(const T right)
		{
			return Vector2<T>(x/right, y/right);
		}

		Vector2<T> operator/=(const Vector2<T> &right)
		{
			x /= right.x;
			y /= right.y;
		}

		Vector2<T> operator/=(const T right)
		{
			x /= right;
			y /= right;
		}

		/*!\brief X coordinate
		 */
		T x;

		/*!\brief Y coordinate
		 */
		T y;

};

template<typename T>
class Vector3
{
	public:
		/* Constructors */
		Vector3<T>(): x(0), y(0), z(0){}
		Vector3<T>(T x_, T y_, T z_):
			x(x_), y(y_), z(z_){}

		/* Operations */
		void set(T x_, T y_, T z_)
		{
			x = x_; y = y_; z = z_;
		}

		T Length() const
		{
			return (T) sqrt(x * x + y * y + z * z);
		}

		void Normalize()
		{
			float l = 1.0f / Length();
			x *= l;
			y *= l;
		}

		Vector3<T> Normalized() const
		{
			float l = 1.0f / Length();
			return Vector3<T> ((T)(x * l),
					(T)(y * l),
					(T)(z * l));
		}

		T Dot(const Vector3<T>& b) const
		{
			return (T)( x * b.x + y * b.y + z * b.z);
		}

		Vector3<T> Cross(const Vector3<T>& b) const
		{
			return Vector3<T>
				( y * b.z - z * b.y,
				  z * b.x - x * b.z,
				  x * b.y - y * b.x);
		}

		/* Operators */
		Vector3<T> operator+(const Vector3<T> &right)
		{
			return Vector3<T>(x+right.x, y+right.y, z+right.z);
		}

		Vector3<T> operator+(const T right)
		{
			return Vector3<T>(x+right, y+right, z+right);
		}

		Vector3<T> operator+=(const Vector3<T> &right)
		{
			x += right.x;
			y += right.y;
			z += right.z;
		}

		Vector3<T> operator+=(const T right)
		{
			x += right;
			y += right;
			z += right;
		}

		Vector3<T> operator-(const Vector3<T> &right)
		{
			return Vector2<T>(x-right.x, y-right.y, z - right.z);
		}

		Vector3<T> operator-(const T right)
		{
			return Vector3<T>(x-right, y-right, z - right);
		}

		Vector3<T> operator-=(const Vector3<T> &right)
		{
			x -= right.x;
			y -= right.y;
			z -= right.z;
		}

		Vector3<T> operator-=(const T right)
		{
			x -= right;
			y -= right;
			z -= right;
		}

		Vector3<T> operator*(const Vector3<T> &right)
		{
			return Vector3<T>(x*right.x, y*right.y, z*right.z);
		}

		Vector3<T> operator*(const T right)
		{
			return Vector3<T>(x*right, y*right, z*right);
		}

		Vector3<T> operator*=(const Vector3<T> &right)
		{
			x *= right.x;
			y *= right.y;
			z *= right.z;
		}

		Vector3<T> operator*=(const T right)
		{
			x *= right;
			y *= right;
			z *= right;
		}

		Vector3<T> operator/(const Vector3<T> &right)
		{
			return Vector2<T>(x/right.x, y/right.y, z/right.z);
		}

		Vector3<T> operator/(const T right)
		{
			return Vector2<T>(x/right, y/right, z/right);
		}

		Vector3<T> operator/=(const Vector3<T> &right)
		{
			x /= right.x;
			y /= right.y;
			z /= right.z;
		}
		Vector3<T> operator/=(const T right)
		{
			x /= right;
			y /= right;
			z /= right;
		}

		friend std::ostream& operator<<(std::ostream& os,
				const Vector3<T>& vec)
		{
			os << "[ " << vec.x << ", " << vec.y <<  ", " << vec.z 
				<< " ]";
			return os;
		}



		/* Data storage */
		/*!\brief X coordinate
		 */
		T x;

		/*!\brief Y coordinate
		 */
		T y;

		/*!\brief Z coordinate
		 */
		T z;

};
#endif // VECTOR_H
