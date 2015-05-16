#include "gougoutte_glass.hpp"

gougoutte_glass::gougoutte_glass() : chut(0) {}

gougoutte_glass::gougoutte_glass(Vector3 p, char t) : type(t), pos(p), chut(0) {

   perc = 0;
   if (type == 1 || type == -1)
      perc = 100;
}

gougoutte_glass::~gougoutte_glass() {}

void   gougoutte_glass::setType(char p) {

   type = p;
   if (type == 0)
      perc = 0;
   else if (type == 1 || type == -1 || type == 5)
      perc = 200;
}

void   gougoutte_glass::setPerc(int p) {

   this->perc=p;
   if (this->perc <= 0)
   {
      this->perc = 0;
      this->type = 0;
   }
}

void   gougoutte_glass::addPerc(int p) {

   perc+=p;
   if (perc <= 0)
   {
      perc = 0;
      type = 0;
   }
}

int   gougoutte_glass::getPerc() const {return perc;}
char   gougoutte_glass::getType() {return type;}
Vector3 gougoutte_glass::getV3() {return pos;}

bool gougoutte_glass::operator<(gougoutte_glass const &rhs) const {

   if (this->perc < rhs.getPerc())
      return true;
   return false;
}

bool gougoutte_glass::operator>(gougoutte_glass const &rhs) const {

   if (this->perc > rhs.getPerc())
      return true;
   return false;
}
