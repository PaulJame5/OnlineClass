/*
	Vec2f handles all of Vector2 float and double implementations for gEngine
	Written by Paul O'Callaghan.
	No Known Bugs

*/
#pragma once

#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#define PI 3.1415926535897932

#include <cmath>
#include <iostream>
#include <string>

namespace ge
{
	template<class T>
	class Vector2
	{
	public:

		T x, y;

		//==============================================================
		// Constructors
		Vector2();
		Vector2(T x, T y);
		Vector2(const Vector2<T>& v);
		~Vector2();
		//==============================================================


		//==============================================================
		// Operators
		template <typename U>
		Vector2<T> operator +(const Vector2<U>& rightVector) const;
		template <typename U>
		Vector2<T> operator -(const Vector2<U>& rightVector) const;
		Vector2<T> operator *(const double scalar) const;
		Vector2<T> operator /(const double divisor) const;

		template <typename U>
		Vector2<T> operator +=(const Vector2<U>& rightVector);
		template <typename U>
		Vector2<T> operator -=(const Vector2<U>& rightVector);
		Vector2<T> operator *=(const double scalar);
		Vector2<T> operator /=(const double divisor) const;

		// Convert to negative
		Vector2<T> operator -() const;
		// Comparison Operators (must be of the same type)
		bool operator==(Vector2<T> v);
		bool operator!=(Vector2<T> v);

		// casts
		operator Vector2<float>() { return Vector2<float>{ static_cast<float>(x), static_cast<float>(y) }; };
		operator Vector2<int>() { return Vector2<int>{ static_cast<int>(x), static_cast<int>(y) }; };
		operator Vector2<unsigned>() { return Vector2<unsigned>{ static_cast<unsigned>(x), static_cast<unsigned>(y) }; };
		operator Vector2<double>() { return Vector2<double>{ static_cast<double>(x), static_cast<double>(y) }; };
		// End Operators
		//==============================================================


		//==============================================================
		// Functions working with self
		double magnitude();
		double squareMagnitude();
		double length();
		double lengthSquared();

		template <typename U>
		double distanceFromSelf(Vector2<U>& v);

		std::string toString();

		void parse(std::string vectorString);

		template <typename U>
		double dot(Vector2<U>& other);

		// Cross product is a 3D Vector operation with 2D Vector returns z component
		template <typename U>
		double crossProduct(Vector2<U>& other);

		template <typename U>
		Vector2<T> projection(Vector2<U>& other);

		template <typename U>
		Vector2<T> rejection(Vector2<U>& other);

		template <typename U>
		Vector2<double> reflectVector(Vector2<U>& direction);

		template <typename U>
		Vector2<T> lerpWith(Vector2<U>& other, double deltaTime);

		// Updates this objects X and Y values of vector to move towards target by deltaTime*speed
		template <typename U>
		void moveSelfTowardsPoint(Vector2<U>& target, double speed, double deltaTime);

		template <typename U>
		Vector2<T> vectorDirection(Vector2<U>& end);

		template <typename U>
		double vectorDirectionAsAngle(Vector2<U>& end);

		template <typename U>
		double angleFromSelf(Vector2<U> target);


		void normalise();
		Vector2<double> normalized();
		Vector2<T> unit();
		// End functions to work with self
		//==============================================================


		//==============================================================
		// Static functions for calculations between vectors where you don't necccessarily want to 
		// affect internal properties
		template <typename U, typename V>
		static double distanceBetween(Vector2<U> v1, Vector2<V> v2);

		template <typename U, typename V>
		static double angleBetween(Vector2<U> from, Vector2<V> to);

		static Vector2<T> lerp(Vector2<T> v1, Vector2<T> v2, double deltaTime);

		static Vector2<T> zero();
		static Vector2<T> left();
		static Vector2<T> right();
		static Vector2<T> up();
		static Vector2<T> down();

		// End static functions
		//======================================================================

	private:
		static Vector2<int> vectorZero;
		static Vector2<int> vectorLeft;
		static Vector2<int> vectorRight;
		static Vector2<int> vectorUp;
		static Vector2<int> vectorDown;

	};

	//======================================================================
	// Initialise our prvate static variables
	template<class T>
	Vector2<int> Vector2<T>::vectorZero = Vector2<int>(0, 0);
	template<class T>
	Vector2<int> Vector2<T>::vectorLeft = Vector2<int>(-1, 0);
	template<class T>
	Vector2<int> Vector2<T>::vectorRight = Vector2<int>(1, 0);
	template<class T>
	Vector2<int> Vector2<T>::vectorUp = Vector2<int>(0, -1);
	template<class T>
	Vector2<int> Vector2<T>::vectorDown = Vector2<int>(0, 1);

	//End Static initialisation
	//======================================================================


	//======================================================================
	// Constructors
	template<class T>
	inline Vector2<T>::Vector2() : x(0), y(0)
	{
	}

	template<class T>
	inline Vector2<T>::Vector2(T x, T y) : x(x), y(y)
	{
	}

	template<class T>
	inline Vector2<T>::Vector2(const Vector2& v) : x(v.x), y(v.y)
	{
	}

	template<class T>
	inline Vector2<T>::~Vector2()
	{
	}
	// End Constructors
	//======================================================================


	//======================================================================
	// Operator Overloads
	template<class T>
	template <typename U>
	inline Vector2<T> Vector2<T>::operator+(const Vector2<U>& vectorRight) const
	{
		return Vector2<T>(x + vectorRight.x, y + vectorRight.y);
	}

	template<class T>
	template <typename U>
	inline Vector2<T> Vector2<T>::operator-(const Vector2<U>& rightVector) const
	{
		return Vector2<T>(x - rightVector.x, y - rightVector.y);
	}

	template<class T>
	inline Vector2<T> Vector2<T>::operator-() const
	{
		return Vector2<T>(-x, -y);
	}

	template<class T>
	inline Vector2<T> Vector2<T>::operator*(const double scalar) const
	{
		return Vector2<T>((x * scalar), (y * scalar));
	}

	template<class T>
	inline Vector2<T> Vector2<T>::operator/(const double divisor) const
	{
		if (x == 0 || divisor == 0 || y == 0)
		{
			return *this;
		}
		return Vector2(x / divisor, y / divisor);
	}

	template<class T>
	template <typename U>
	inline Vector2<T> Vector2<T>::operator+=(const Vector2<U>& rightVector)
	{
		return Vector2<T>(x += rightVector.x, y += rightVector.y);
	}

	template<class T>
	template <typename U>
	inline Vector2<T> Vector2<T>::operator-=(const Vector2<U>& rightVector)
	{
		return Vector2<T>(x -= rightVector.x, y -= rightVector.y);
	}

	template<class T>
	inline Vector2<T> Vector2<T>::operator*=(const double scalar)
	{
		x = x * scalar;
		y = y * scalar;
		return Vector2<T>(x, y);
	}

	template<class T>
	inline Vector2<T> Vector2<T>::operator/=(const double divisor) const
	{
		if (x == 0 || divisor == 0 || y == 0)
		{
			return *this;
		}
		return Vector2<T>(x / divisor, y / divisor);
	}

	template<class T>
	inline bool Vector2<T>::operator==(Vector2<T> v)
	{
		return (x == v.x && y == v.y);
	}

	template<class T>
	inline bool Vector2<T>::operator!=(Vector2<T> v)
	{
		return (x != v.x || y != v.y);
	}
	// End Operator Overloads
	//======================================================================


	//======================================================================
	// Self Calculations
	template<class T>
	inline Vector2<double> Vector2<T>::normalized()
	{
		Vector2<double> v = Vector2<double>(x, y);
		v.normalise();
		return v;
	}

	template<class T>
	inline Vector2<T> Vector2<T>::unit()
	{
		double length = length();
		return Vector2<T>(x / length, y / length);
	}

	template<class T>
	inline double Vector2<T>::magnitude()
	{
		return std::sqrt((x * x) + (y * y));
	}

	template<class T>
	inline double Vector2<T>::squareMagnitude()
	{
		return x * x + y * y;
	}

	template<class T>
	inline double Vector2<T>::length()
	{
		return std::sqrt(x * x + y * y);
	}

	template<class T>
	inline double Vector2<T>::lengthSquared()
	{
		return x * x + y * y;
	}

	template<class T>
	template<typename U>
	inline double Vector2<T>::distanceFromSelf(Vector2<U>& v)
	{
		Vector2<double> d = Vector2<double>(v.x - x, v.y - y);
		return d.length();
	}

	template<class T>
	inline std::string Vector2<T>::toString()
	{
		return "x:[" + std::to_string(x) + "], y:[" + std::to_string(y) + "]";
	}

	template<class T>
	inline void Vector2<T>::parse(std::string vectorString)
	{
		std::string x = "";
		std::string y = "";
		bool first = false;
		bool second = false;
		bool started = false;
		for (int i = 0; i < vectorString.length(); i++)
		{
			if (!started)
			{
				if (vectorString[i] == '[')
				{
					started = true;
				}
				continue;
			}
			if (!first)
			{
				if (vectorString[i] == ']')
				{
					first = true;
					started = false;
					continue;
				}
				x.push_back(vectorString[i]);
				continue;
			}
			if (!second)
			{
				if (vectorString[i] == ']')
				{
					second = true;
					break;
				}
				y.push_back(vectorString[i]);
				continue;
			}
		}
		this->x = std::atoi(x.c_str());
		this->y = std::atoi(y.c_str());
	}

	template<class T>
	template <typename U>
	inline double Vector2<T>::dot(Vector2<U>& other)
	{
		return ((x * other.x) + (y * other.y));
	}

	template<class T>
	template <typename U>
	inline double Vector2<T>::crossProduct(Vector2<U>& other)
	{
		return (x * other.y - y * other.x);
	}

	template<class T>
	template <typename U>
	inline Vector2<T> Vector2<T>::projection(Vector2<U>& other)
	{
		double projectionValue = dot(other) / length();
		return Vector2<T>(this->operator*(projectionValue));
	}

	template<class T>
	template <typename U>
	inline Vector2<T> Vector2<T>::rejection(Vector2<U>& other)
	{
		return (other - projection(other));
	}

	template<class T>
	template <typename U>
	inline Vector2<double> Vector2<T>::reflectVector(Vector2<U>& direction)
	{
		Vector2<double> normal = direction.normalized();
		double factor = 2.0f * normal.dot(direction);
		return Vector2<double>(factor * normal.x + direction.x, factor * normal.y + direction.y);
	}

	template<class T>
	template<typename U>
	inline Vector2<T> Vector2<T>::lerpWith(Vector2<U>& other, double deltaTime)
	{
		return Vector2<T>(x + (other.x - x) * deltaTime, y + (other.y - y) * deltaTime);
	}

	template<class T>
	template<typename U>
	inline void Vector2<T>::moveSelfTowardsPoint(Vector2<U>& target, double speed, double deltaTime)
	{
		Vector2<T> direction = target - this;
		this = direction;

		if (direction.squareMagnitude() == 0)
		{
			this = target;
			return;
		}

		double distance = this->distanceFromSelf(target);

		this += direction / distance * (deltaTime * speed);
	}

	template<class T>
	template<typename U>
	inline Vector2<T> Vector2<T>::vectorDirection(Vector2<U>& end)
	{
		return Vector2<T>(end.x - x, end.y - y);
	}

	///<summary>
	/// Angle Retuurns in Degrees
	///</summary>
	template<class T>
	template<typename U>
	inline double Vector2<T>::vectorDirectionAsAngle(Vector2<U>& end)
	{
		return (std::atan2((double)end.y - y, (double)end.x - x) * 180 / PI);
	}

	///<summary>
	/// Angle Retuurns in Degrees
	///</summary>
	template<class T>
	template<typename U>
	inline double Vector2<T>::angleFromSelf(Vector2<U> target)
	{
		return (std::atan2((double)target.y - y, (double)target.x - x) * 180 / PI);
	}

	template<class T>
	inline void Vector2<T>::normalise()
	{
		double m = magnitude();

		if (m == 0)
		{
			x = 0;
			y = 0;
			return;
		}
		if (x == 0)
		{
			return;
		}
		if (y == 0)
		{
			return;
		}
		(x) /= m;
		(y) /= m;
	}
	// End Self Calculations
	//===========================================================


	//===========================================================
	// Static Functions

	template<class T>
	inline Vector2<T> Vector2<T>::zero()
	{
		return vectorZero;
	}

	template<class T>
	inline Vector2<T> Vector2<T>::left()
	{
		return vectorLeft;
	}

	template<class T>
	inline Vector2<T> Vector2<T>::right()
	{
		return vectorRight;
	}

	template<class T>
	inline Vector2<T> Vector2<T>::up()
	{
		return vectorUp;
	}

	template<class T>
	inline Vector2<T> Vector2<T>::down()
	{
		return vectorDown;
	}

	template<class T>
	template <typename U, typename V>
	inline double Vector2<T>::distanceBetween(Vector2<U> v1, Vector2<V> v2)
	{
		v2 -= v1;
		return v2.length();
	}

	template<class T>
	template<typename U, typename V>
	inline double Vector2<T>::angleBetween(Vector2<U> from, Vector2<V> to)
	{
		return (std::atan2((double)to.y - from.y, (double)to.x - from.x) * 180 / PI);
	}

	template<class T>
	inline Vector2<T> Vector2<T>::lerp(Vector2<T> v1, Vector2<T> v2, double deltaTime)
	{
		return Vector2<T>(v1.x + (v2.x - v1.x) * deltaTime, v1.y + (v2.y - v1.y) * deltaTime);
	}
	// End Static Functions
	//=====================================================================

	// Types this header class supports
	typedef Vector2<float> Vector2f;
	typedef Vector2<double> Vector2d;
	typedef Vector2<int> Vector2i;
	typedef Vector2<unsigned int> Vector2u;
}

#endif //__VECTOR2_H__