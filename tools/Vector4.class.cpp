/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector4.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 15:05:34 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/01/30 22:14:21 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector4.class.hpp"

Vector4::~Vector4() {}

Vector4::Vector4() : _x(0), _y(0), _z(0), _w(0) {}

Vector4::Vector4(Vector3 vec, float w) {

   this->_x = vec.getX();
   this->_y = vec.getY();
   this->_z = vec.getZ();
   this->_w = w;
}

Vector4::Vector4(float x, float y, float z, float w) {

   this->_x = x;
   this->_y = y;
   this->_z = z;
   this->_w = w;
}

Vector4::Vector4(Vector4 const &src) {

   this->_x = src.getX();
   this->_y = src.getY();
   this->_z = src.getZ();
   this->_w = src.getW();
}

Vector4 &   Vector4::operator=(Vector4 const &rhs) {

   this->_x = rhs.getX();
   this->_y = rhs.getY();
   this->_z = rhs.getZ();
   this->_w = rhs.getW();
   return (*this);
}

/* ------------------------------------------------------------------------ */
Vector4 const   Vector4::operator+(Vector4 const &rhs) {

   float x = this->_x + rhs.getX();
   float y = this->_y + rhs.getY();
   float z = this->_z + rhs.getZ();
   float w = this->_w + rhs.getW();

   return Vector4(x, y, z, w);
}

Vector4 &   Vector4::operator+=(Vector4 const &rhs) {

   this->_x += rhs.getX();
   this->_y += rhs.getY();
   this->_z += rhs.getZ();
   this->_w += rhs.getW();
   return (*this);
}

Vector4 const   Vector4::operator-(Vector4 const &rhs) {

   float x = this->_x - rhs.getX();
   float y = this->_y - rhs.getY();
   float z = this->_z - rhs.getZ();
   float w = this->_w - rhs.getW();

   return Vector4(x, y, z, w);
}

Vector4 &   Vector4::operator-=(Vector4 const &rhs) {

   this->_x -= rhs.getX();
   this->_y -= rhs.getY();
   this->_z -= rhs.getZ();
   this->_w -= rhs.getW();

   return (*this);
}

Vector4 const   Vector4::operator*(Vector4 const &rhs) {

   float x = this->_x * rhs.getX();
   float y = this->_y * rhs.getY();
   float z = this->_z * rhs.getZ();
   float w = this->_w * rhs.getW();

   return Vector4(x, y, z, w);
}

Vector4 &   Vector4::operator*=(Vector4 const &rhs) {

   this->_x *= rhs.getX();
   this->_y *= rhs.getY();
   this->_z *= rhs.getZ();
   this->_w *= rhs.getW();

   return (*this);
}

Vector4 const   Vector4::operator/(Vector4 const &rhs) {

	float x = 0;
	float y = 0;
	float z = 0;
   float w = 0;

	if (rhs.getX())
		x = this->_x / rhs.getX();
	if (rhs.getY())
		y = this->_y / rhs.getY();
	if (rhs.getZ())
		z = this->_z / rhs.getZ();
   if (rhs.getW())
      w = this->_w / rhs.getW();


   return Vector4(x, y, z, w);
}

Vector4 &   Vector4::operator/=(Vector4 const &rhs) {

	if (rhs.getX())
		this->_x /= rhs.getX();
	else
		this->_x = 0;
	if (rhs.getY())
		this->_y /= rhs.getY();
	else
		this->_y = 0;
	if (rhs.getZ())
		this->_z /= rhs.getZ();
	else
		this->_z = 0;
   if (rhs.getW())
      this->_w /= rhs.getW();
   else
      this->_w = 0;

	return (*this);
}

bool      Vector4::operator!=(Vector4 const &rhs) const {

   if (this->_x == rhs.getX() && this->_y == rhs.getY() && this->_z == rhs.getZ() && this->_w == rhs.getW())
      return false;
   return true;
}

bool      Vector4::operator==(Vector4 const &rhs) const {
   if (*this != rhs)
      return false;
   return true;
}

/* ------------------------------------------------------------------------- */
Vector4 const   Vector4::operator+(float const &rhs) {

   float x = this->_x + rhs;
   float y = this->_y + rhs;
   float z = this->_z + rhs;
   float w = this->_w + rhs;

   return Vector4(x, y, z, w);
}

Vector4 &   Vector4::operator+=(float const &rhs) {

   this->_x += rhs;
   this->_y += rhs;
   this->_z += rhs;
   this->_w += rhs;

   return (*this);
}

Vector4 const   Vector4::operator-(float const &rhs) {

   float x = this->_x - rhs;
   float y = this->_y - rhs;
   float z = this->_z - rhs;
   float w = this->_w - rhs;

   return Vector4(x, y, z, w);
}

Vector4 &   Vector4::operator-=(float const &rhs) {

   this->_x -= rhs;
   this->_y -= rhs;
   this->_z -= rhs;
   this->_w -= rhs;

   return (*this);
}

Vector4 const   Vector4::operator*(float const &rhs) {

   float x = this->_x * rhs;
   float y = this->_y * rhs;
   float z = this->_z * rhs;
   float w = this->_w * rhs;

   return Vector4(x, y, z, w);
}

Vector4 &   Vector4::operator*=(float const &rhs) {

   this->_x *= rhs;
   this->_y *= rhs;
   this->_z *= rhs;
   this->_w *= rhs;

   return (*this);
}

Vector4 const   Vector4::operator/(float const &rhs) {

	float x = 0;
	float y = 0;
	float z = 0;
   float w = 0;

	if (rhs)
	{
		x = this->_x / rhs;
		y = this->_y / rhs;
		z = this->_z / rhs;
      w = this->_w / rhs;
	}

   return Vector4(x, y, z, w);
}

Vector4 &   Vector4::operator/=(float const &rhs) {

	if (rhs)
	{
		this->_x /= rhs;
		this->_y /= rhs;
		this->_z /= rhs;
      this->_w /= rhs;
	}
	else
	{
		this->_x = 0;
		this->_y = 0;
		this->_z = 0;
      this->_w = 0;
	}
	return (*this);
}

double      Vector4::Length() {

   double res = pow(this->_x, 2) + pow(this->_y, 2) + pow(this->_z, 2) + pow(this->_w, 2);
}

/* --------------------------- Setters & Getters --------------------------- */
float   Vector4::getX() const {return this->_x;}
float   Vector4::getY() const {return this->_y;}
float   Vector4::getZ() const {return this->_z;}
float   Vector4::getW() const {return this->_w;}

Vector3   Vector4::getV3() const {

   Vector3 v = Vector3(this->_x, this->_y, this->_z);
   return v;
}

void   Vector4::setX(float const x) {this->_x = x;}
void   Vector4::setY(float const y) {this->_y = y;}
void   Vector4::setZ(float const z) {this->_z = z;}
void   Vector4::setW(float const w) {this->_w = w;}

/* ------------------------------ ToString() ------------------------------ */
std::ostream &   operator<<(std::ostream &a, Vector4 const &vec) {

   a << "Vector4(" << vec.getX() << ", " << vec.getY() << ", " << vec.getZ() << ", " << vec.getW() << ")";
   return a;
}
