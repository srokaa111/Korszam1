#include <iostream>
#include <math.h> 
template<typename T>
struct Vector2d {
	T x, y;
	Vector2d<T>& operator+=(Vector2d<T> const& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2d<T>& operator-=(Vector2d<T> const& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vector2d<T>& operator*=(T w) {
		x *= w;
		y *= w;
		return *this;
	}
	Vector2d<T>& operator/=(T w) {
		x /= w;
		y /= w;
		return *this;
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& o, Vector2d<T> const& a) {
	o << a.x << " " << a.y;
	return o;
}

template<typename T>
std::istream& operator>>(std::istream& i, Vector2d<T>& a) {
	i >> a.x;
	i >> a.y;
	return i;
}

template<typename T>
Vector2d<T> operator+(Vector2d<T> const& a, Vector2d<T> const& b) {
	return Vector2d<T>{a.x + b.x, a.y + b.y};
}
template<typename T>
Vector2d<T> operator-(Vector2d<T> const& a, Vector2d<T> const& b) {
	return Vector2d<T>{a.x - b.x, a.y - b.y};
}
template<typename T,typename T1>
Vector2d<T> operator*(Vector2d<T> const& a,T1 b) {
	return Vector2d<T>{a.x* b, a.y* b};
}

template<typename T,typename T1>
Vector2d<T> operator*(T1 b,Vector2d<T> const& a) {
	return Vector2d<T>{a.x* b, a.y* b};
}

template<typename T, typename T1>
Vector2d<T> operator/(Vector2d<T> const& a, T1 b) {
	return Vector2d<T>{a.x / b, a.y / b};
}

template<typename T>
auto dotprod(Vector2d<T> const& a, Vector2d<T> const& b) {
	return a.x * b.x + a.y * b.y;
}
	
template<typename T>
Vector2d<T> mirrorvert(Vector2d<T> const& a) {
	return Vector2d<T>{-a.x, a.y};
}

template<typename T>
Vector2d<T> mirrorhor(Vector2d<T> const& a) {
	return Vector2d<T>{a.x, -a.y};
}

template<typename T,typename T1>
Vector2d<T> rot(Vector2d<T> const& a, T1 b) {
	return Vector2d<T> {a.x* cos(b) - a.y * sin(b), a.x* sin(b) + a.y * cos(b)};
}

template<typename T>
auto length(Vector2d<T> a) {
	return sqrt(a.x*a.x + a.y*a.y);
}

template<typename T>
Vector2d<T> norm(Vector2d<T> const& a) {
	return a / length(a);
}