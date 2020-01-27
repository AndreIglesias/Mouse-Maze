#pragma once
#include <iostream>

#define Operators \
	X(Add, +)\
	X(Sub, -)\
	X(Mul, *)\
	X(Div, /)

class vec2D
{
public:
	float x, y;
	vec2D() { x = 0.0f; y = 0.0f; }
	vec2D(float X, float Y) { x=X; y=Y; }
	~vec2D(){}

	/* non-member function "friend" of the class, meaning it can access the private and protected members of the class  */

	//Opera los componentes y retorna el vector
	vec2D& Add(const vec2D v) { x +=v.x; y +=v.y; return *this; }
	vec2D& Sub(const vec2D v) { x -=v.x; y -=v.y; return *this; }
	vec2D& Mul(const vec2D v) { x *=v.x; y *=v.y; return *this; }
	vec2D& Div(const vec2D v) { x -=v.x; y -=v.y; return *this; }
	friend vec2D& operator+(vec2D& v1, const vec2D& v2) { return v1.Add(v2); }
	friend vec2D& operator-(vec2D& v1, const vec2D& v2) { return v1.Sub(v2); }
	friend vec2D& operator*(vec2D& v1, const vec2D& v2) { return v1.Mul(v2); }
	friend vec2D& operator/(vec2D& v1, const vec2D& v2) { return v1.Div(v2); }
	vec2D& operator+=(vec2D& v) { return this->Add(v); }
	vec2D& operator-=(vec2D& v) { return this->Sub(v); }
	vec2D& operator*=(vec2D& v) { return this->Mul(v); }
	vec2D& operator/=(vec2D& v) { return this->Div(v); }

	vec2D& zero(){ x=0; y=0; return *this; }
	vec2D& invs(){ x=-x; y=-y; return *this; }
	
	/*
	#define X(Name, op)\
		vec2D& Name(const vec2D v) { x op=v.x; y op=v.y; return *this; };\
		friend vec2D& operator##op(vec2D& v1, const vec2D& v2) { return v1.Name(v2); };\
		vec2D& operator##op=(vec2D& v) { return this->Name(v); };
	Operators
	#undef X
	*/
	
};