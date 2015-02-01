/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector3.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 15:05:34 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/01/30 22:14:21 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector3.class.hpp"

Vector3::~Vector3() {}

Vector3::Vector3() : _x(0), _y(0), _z(0) {}

Vector3::Vector3(float x, float y, float z) {

   this->_x = x;
   this->_y = y;
   this->_z = z;
}

Vector3::Vector3(Vector3 const &src) {

   this->_x = src.getX();
   this->_y = src.getY();
   this->_z = src.getZ();
}

Vector3 &   Vector3::operator=(Vector3 const &rhs) {

   this->_x = rhs.getX();
   this->_y = rhs.getY();
   this->_z = rhs.getZ();
   return (*this);
}

/* ------------------------------------------------------------------------ */
Vector3 const   Vector3::operator+(Vector3 const &rhs) {

   float x = this->_x + rhs.getX();
   float y = this->_y + rhs.getY();
   float z = this->_z + rhs.getZ();

   return Vector3(x, y, z);
}

Vector3 &   Vector3::operator+=(Vector3 const &rhs) {

   this->_x += rhs.getX();
   this->_y += rhs.getY();
   this->_z += rhs.getZ();
   return (*this);
}

Vector3 const   Vector3::operator-(Vector3 const &rhs) {

   float x = this->_x - rhs.getX();
   float y = this->_y - rhs.getY();
   float z = this->_z - rhs.getZ();

   return Vector3(x, y, z);
}

Vector3 &   Vector3::operator-=(Vector3 const &rhs) {

   this->_x -= rhs.getX();
   this->_y -= rhs.getY();
   this->_z -= rhs.getZ();

   return (*this);
}

Vector3 const   Vector3::operator*(Vector3 const &rhs) {

   float x = this->_x * rhs.getX();
   float y = this->_y * rhs.getY();
   float z = this->_z * rhs.getZ();

   return Vector3(x, y, z);
}

Vector3 &   Vector3::operator*=(Vector3 const &rhs) {

   this->_x *= rhs.getX();
   this->_y *= rhs.getY();
   this->_z *= rhs.getZ();
   return (*this);
}

Vector3 const   Vector3::operator/(Vector3 const &rhs) {

	float x = 0;
	float y = 0;
	float z = 0;

	if (rhs.getX())
		x = this->_x / rhs.getX();
	if (rhs.getY())
		y = this->_y / rhs.getY();
	if (rhs.getZ())
		z = this->_z / rhs.getZ();

   return Vector3(x, y, z);
}

Vector3 &   Vector3::operator/=(Vector3 const &rhs) {

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
	return (*this);
}

bool      Vector3::operator!=(Vector3 const &rhs) const {

   if (this->_x == rhs.getX() && this->_y == rhs.getY() && this->_z == rhs.getZ())
      return false;
   return true;
}

bool      Vector3::operator==(Vector3 const &rhs) const {
   if (*this != rhs)
      return false;
   return true;
}

/* ------------------------------------------------------------------------- */
Vector3 const   Vector3::operator+(float const &rhs) {

   float x = this->_x + rhs;
   float y = this->_y + rhs;
   float z = this->_z + rhs;

   return Vector3(x, y, z);
}

Vector3 &   Vector3::operator+=(float const &rhs) {

   this->_x += rhs;
   this->_y += rhs;
   this->_z += rhs;
   return (*this);
}

Vector3 const   Vector3::operator-(float const &rhs) {

   float x = this->_x - rhs;
   float y = this->_y - rhs;
   float z = this->_z - rhs;

   return Vector3(x, y, z);
}

Vector3 &   Vector3::operator-=(float const &rhs) {

   this->_x -= rhs;
   this->_y -= rhs;
   this->_z -= rhs;
   return (*this);
}

Vector3 const   Vector3::operator*(float const &rhs) {

   float x = this->_x * rhs;
   float y = this->_y * rhs;
   float z = this->_z * rhs;

   return Vector3(x, y, z);
}

Vector3 &   Vector3::operator*=(float const &rhs) {

   this->_x *= rhs;
   this->_y *= rhs;
   this->_z *= rhs;
   return (*this);
}

Vector3 const   Vector3::operator/(float const &rhs) {

	float x = 0;
	float y = 0;
	float z = 0;
	if (rhs)
	{
		x = this->_x / rhs;
		y = this->_y / rhs;
		z = this->_z / rhs;
	}

   return Vector3(x, y, z);
}

Vector3 &   Vector3::operator/=(float const &rhs) {

	if (rhs)
	{
		this->_x /= rhs;
		this->_y /= rhs;
		this->_z /= rhs;
	}
	else
	{
		this->_x = 0;
		this->_y = 0;
		this->_z = 0;
	}
	return (*this);
}

/* --------------------------- Setters & Getters --------------------------- */
float   Vector3::getX() const {return this->_x;}
float   Vector3::getY() const {return this->_y;}
float   Vector3::getZ() const {return this->_z;}

void   Vector3::setX(float const x) {this->_x = x;}
void   Vector3::setY(float const y) {this->_y = y;}
void   Vector3::setZ(float const z) {this->_z = z;}

/* ------------------------------ ToString() ------------------------------ */
std::ostream &   operator<<(std::ostream &a, Vector3 const &vec) {

   a << "Vector3(" << vec.getX() << ", " << vec.getY() << ", " << vec.getZ() << ")";
   return a;
}
