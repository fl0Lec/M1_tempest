/**
 * @file vect2.hpp
 * @brief Two dimensional generic vectors for geometry
 */

#ifndef __VECT2_H__
#define __VECT2_H__

#include <cmath>
#include <iostream>

namespace Engine
{

/**
 * @brief Vector of 2 numeric values
 * 
 * @tparam T Type of vector's values
 */
template<typename T>
struct Vect2
{
    T x;
    T y;

    Vect2(): x(0), y(0) {}
    Vect2(T a): x(a), y(a) {}
    Vect2(T x1, T y1): x(x1), y(y1) {}

    Vect2(const Vect2<T> & v): x(v.x), y(v.y) {}
    Vect2<T>& operator=(const Vect2<T> & v)
    {
        x = v.x;
        y = v.y;
        return *this;
    }

    Vect2<T>& operator+=(const Vect2<T> & v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vect2<T>& operator-=(const Vect2<T> & v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vect2<T>& operator+=(const T & c)
    {
        x += c;
        y += c;
        return *this;
    }

    Vect2<T>& operator-=(const T & c)
    {
        x -= c;
        y -= c;
        return *this;
    }

    Vect2<T>& operator*=(const T & c)
    {
        x *= c;
        y *= c;
        return *this;
    }

    Vect2<T>& operator/=(const T & c)
    {
        x /= c;
        y /= c;
        return *this;
    }

    T norm() const
    {
        return std::sqrt(x * x + y * y);
    }

};

template<typename T>
bool operator==(const Vect2<T> & v1, const Vect2<T> & v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

template<typename T>
bool operator!=(const Vect2<T> & v1, const Vect2<T> & v2)
{
    return !(v1 == v2);
}

template<typename T>
bool operator<(const Vect2<T> & v1, const Vect2<T> & v2)
{
    return v1.x < v2.x || (v1.x == v2.x && v1.y < v2.y);
}

template<typename T>
bool operator>(const Vect2<T> & v1, const Vect2<T> & v2)
{
    return v2 < v1;
}

template<typename T>
bool operator<=(const Vect2<T> & v1, const Vect2<T> & v2)
{
    return !(v1 > v2);
}

template<typename T>
bool operator>=(const Vect2<T> & v1, const Vect2<T> & v2)
{
    return !(v1 < v2);
}

template<typename T>
Vect2<T> operator+(const Vect2<T> & v1, const Vect2<T> & v2)
{
    return Vect2<T>{v1.x + v2.x, v1.y + v2.y};
}

template<typename T>
Vect2<T> operator-(const Vect2<T> & v1, const Vect2<T> & v2)
{
    return Vect2<T>{v1.x - v2.x, v1.y - v2.y};
}

template<typename T>
Vect2<T> operator+(const Vect2<T> & v1, const T & c)
{
    return Vect2<T>{v1.x + c, v1.y + c};
}

template<typename T>
Vect2<T> operator-(const Vect2<T> & v1, const T & c)
{
    return Vect2<T>{v1.x - c, v1.y - c};
}

template<typename T>
Vect2<T> operator*(const Vect2<T> & v1, const T & c)
{
    return Vect2<T>{v1.x * c, v1.y * c};
}

template<typename T>
Vect2<T> operator/(const Vect2<T> & v1, const T & c)
{
    return Vect2<T>{v1.x / c, v1.y / c};
}

template<typename T>
std::ostream& operator<<(std::ostream & os, const Vect2<T> & p)
{
    return os<<"|"<<p.x<<";"<<p.y<<"|";
}

using Vect2f = Vect2<float>;

}

#endif
