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

		/*!\brief X coordiante
		 */
		T x;

		/*!\brief Y coordiante
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

#endif // VECTOR_H
