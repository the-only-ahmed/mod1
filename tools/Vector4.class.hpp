/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector4.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 15:05:46 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/01/30 20:46:49 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR4_CLASS_HPP
# define VECTOR4_CLASS_HPP

#include <cmath>
#include <iostream>
#include "Vector3.class.hpp"

class Vector4
{
   private :

   /* ---------- Attributes ---------- */
      float   _x;
      float   _y;
      float   _z;
      float   _w;

   public :

   /* ---------- Functions ---------- */
   ~Vector4();
   Vector4();
   Vector4(float x, float y, float z, float w);
   Vector4(Vector3 vec, float w);
   Vector4(Vector4 const &src);
   Vector4 &   operator=(Vector4 const &rhs);

   Vector4 const   operator+(Vector4 const &rhs);
   Vector4 &   operator+=(Vector4 const &rhs);
   Vector4 const   operator-(Vector4 const &rhs);
   Vector4 &   operator-=(Vector4 const &rhs);
   Vector4 const   operator*(Vector4 const &rhs);
   Vector4 &   operator*=(Vector4 const &rhs);
   Vector4 const   operator/(Vector4 const &rhs);
   Vector4 &   operator/=(Vector4 const &rhs);

   Vector4 const   operator+(float const &rhs);
   Vector4 &   operator+=(float const &rhs);
   Vector4 const   operator-(float const &rhs);
   Vector4 &   operator-=(float const &rhs);
   Vector4 const   operator*(float const &rhs);
   Vector4 &   operator*=(float const &rhs);
   Vector4 const   operator/(float const &rhs);
   Vector4 &   operator/=(float const &rhs);

   bool        operator==(Vector4 const &rhs) const;
   bool        operator!=(Vector4 const &rhs) const;

   double      Length();

   /* ---------- Setters & Getters ---------- */
   float   getX() const;
   float   getY() const;
   float   getZ() const;
   float   getW() const;

   Vector3   getV3() const;

   void   setX(float const x);
   void   setY(float const y);
   void   setZ(float const z);
   void   setW(float const w);
};

std::ostream &   operator<<(std::ostream &a, Vector4 const &vec);

#endif
