/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector3.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 15:05:46 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/01/30 20:46:49 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_CLASS_HPP
# define VECTOR3_CLASS_HPP

#include <cmath>
#include <iostream>

class Vector3
{
   private :

   /* ---------- Attributes ---------- */


   public :

   /* ---------- Functions ---------- */
   ~Vector3();
   Vector3();
   Vector3(float x, float y, float z);
   Vector3(Vector3 const &src);
   Vector3 &   operator=(Vector3 const &rhs);

   Vector3 const   operator+(Vector3 const &rhs);
   Vector3 &   operator+=(Vector3 const &rhs);
   Vector3 const   operator-(Vector3 const &rhs);
   Vector3 &   operator-=(Vector3 const &rhs);
   Vector3 const   operator*(Vector3 const &rhs);
   Vector3 &   operator*=(Vector3 const &rhs);
   Vector3 const   operator/(Vector3 const &rhs);
   Vector3 &   operator/=(Vector3 const &rhs);

   Vector3 const   operator+(float const &rhs);
   Vector3 &   operator+=(float const &rhs);
   Vector3 const   operator-(float const &rhs);
   Vector3 &   operator-=(float const &rhs);
   Vector3 const   operator*(float const &rhs);
   Vector3 &   operator*=(float const &rhs);
   Vector3 const   operator/(float const &rhs);
   Vector3 &   operator/=(float const &rhs);

   bool        operator==(Vector3 const &rhs) const;
   bool        operator!=(Vector3 const &rhs) const;

   double      Length();

   /* ---------- Setters & Getters ---------- */
   float   getX() const;
   float   getY() const;
   float   getZ() const;

   void   setX(float const x);
   void   setY(float const y);
   void   setZ(float const z);


   float   _x;
   float   _y;
   float   _z;
};

std::ostream &   operator<<(std::ostream &a, Vector3 const &vec);

#endif
