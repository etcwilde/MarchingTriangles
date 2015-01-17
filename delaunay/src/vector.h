#ifndef VECTOR_H
#define VECTOR_H

/*!\brief Two-dimensional vector class
 */
template<typename T>
class Vector2
{
	public:
		Vector2<T>(): x(0), y(0){}
		Vector2<T>(T x_, T y_):
			x(x_), y(y_){}

		/*!\brief X coordinate
		 */
		T x;

		/*!\brief Y coordinate
		 */
		T y;
		Vector2<T> operator+(const Vector2<T> &right)
		{return Vector2<T>(x+right.x, y+right.y);}

		Vector2<T> operator+(const T right)
		{return Vector2<T>(x+right, y+right);}

		Vector2<T> operator+=(const Vector2<T> &right)
		{x += right.x; y += right.y;}
		Vector2<T> operator+=(const T right)
		{x += right; y += right;}

		Vector2<T> operator-(const Vector2<T> &right)
		{return Vector2<T>(x-right.x, y-right.y);}
		Vector2<T> operator-(const T right)
		{return Vector2<T>(x-right, y-right);}
		Vector2<T> operator-=(const Vector2<T> &right)
		{x -= right.x; y -= right.y;}
		Vector2<T> operator-=(const T right)
		{x -= right; y -= right;}

		Vector2<T> operator*(const Vector2<T> &right)
		{return Vector2<T>(x*right.x, y*right.y);}
		Vector2<T> operator*(const T right)
		{return Vector2<T>(x*right, y*right);}
		Vector2<T> operator*=(const Vector2<T> &right)
		{x *= right.x; y *= right.y;}
		Vector2<T> operator*=(const T right)
		{x *= right; y *= right;}

		Vector2<T> operator/(const Vector2<T> &right)
		{return Vector2<T>(x/right.x, y/right.y);}
		Vector2<T> operator/(const T right)
		{return Vector2<T>(x/right, y/right);}
		Vector2<T> operator/=(const Vector2<T> &right)
		{x /= right.x; y /= right.y;}
		Vector2<T> operator/=(const T right)
		{x /= right; y /= right;}
};

template<typename T>
class Vector3
{
	public:
		Vector3<T>(): x(0), y(0), z(0){}
		Vector3<T>(T x_, T y_, T z_):
			x(x_), y(y_), z(z_){}

		/*!\brief X coordinate
		 */
		T x;

		/*!\brief Y coordinate
		 */
		T y;

		/*!\brief Z coordinate
		 */
		T z;
		Vector3<T> operator+(const Vector3<T> &right)
		{return Vector3<T>(x+right.x, y+right.y, z+right.z);}

		Vector3<T> operator+(const T right)
		{return Vector3<T>(x+right, y+right, z+right);}

		Vector3<T> operator+=(const Vector3<T> &right)
		{x += right.x; y += right.y; z += right.z;}
		Vector3<T> operator+=(const T right)
		{x += right; y += right; z += right;}

		Vector3<T> operator-(const Vector3<T> &right)
		{return Vector2<T>(x-right.x, y-right.y, z - right.z);}
		Vector3<T> operator-(const T right)
		{return Vector3<T>(x-right, y-right, z - right);}
		Vector3<T> operator-=(const Vector3<T> &right)
		{x -= right.x; y -= right.y; z -= right.z;}
		Vector3<T> operator-=(const T right)
		{x -= right; y -= right; z -= right;}

		Vector3<T> operator*(const Vector3<T> &right)
		{return Vector3<T>(x*right.x, y*right.y, z*right.z);}
		Vector3<T> operator*(const T right)
		{return Vector3<T>(x*right, y*right, z*right);}
		Vector3<T> operator*=(const Vector3<T> &right)
		{x *= right.x; y *= right.y; z *= right.z;}
		Vector3<T> operator*=(const T right)
		{x *= right; y *= right; z *= right;}

		Vector3<T> operator/(const Vector3<T> &right)
		{return Vector2<T>(x/right.x, y/right.y, z/right.z);}
		Vector3<T> operator/(const T right)
		{return Vector2<T>(x/right, y/right, z/right);}
		Vector3<T> operator/=(const Vector3<T> &right)
		{x /= right.x; y /= right.y; z /= right;}
		Vector3<T> operator/=(const T right)
		{x /= right; y /= right; z /= right;}
};
#endif // VECTOR_H
