#ifndef DataType_
#define DataType_
#include<iostream>
using namespace std;
class DataType {
   friend int main();
   friend ostream& operator<<(ostream&, DataType);
   public:
      operator int() const {return key;}
   private:
      int key;  // element key
      char ID;  // element identifier
};

ostream& operator<<(ostream& out, DataType x)
   {out << x.key << ' ' << x.ID << ' '; return out;}

#endif
