#ifndef GOUGOUTTE_GLASS_HPP
# define GOUGOUTTE_GLASS_HPP

#include "tools/Vector3.class.hpp"

class gougoutte_glass
{

private:
   int      perc;
   char     type;
   Vector3  pos;
public:
   gougoutte_glass();
   gougoutte_glass(Vector3 pos, char type);
   ~gougoutte_glass();

   void   setPerc(int p);
   void   setType(char p);
   void   addPerc(int p);

   int   getPerc() const;
   char   getType();
   Vector3 getV3();

   bool        operator<(gougoutte_glass const &rhs) const;
   bool        operator>(gougoutte_glass const &rhs) const;
};

#endif
