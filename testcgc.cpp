#include "interaction/interaction.h"
#include <cmath> // exp(); pow(); sqrt()
#include <gsl/gsl_sf_coupling.h>
#include <algorithm> // max() and min()
#include <boost/math/special_functions/binomial.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <iostream>


int main()
{
   using namespace std;
 
   int j1,j2,j3, m1, m2, m3;  
  
   j3=2; j2=1; j1=2; 
   m3=-1; m1=2; m2=-1;

   for (int i=0; i<3; i++)
      { 
  
         double cg=0;
         cg = gsl_sf_coupling_3j(j1*2,j2*2,j3*2,2*m1,2*m2,2*m3 ) * pow(-1, j1-j2+m3) * sqrt(2*j3+1);
    //    cout << "ohoh" <<  gsl_sf_coupling_3j(j1*2,j2*2,j3*2,2*m1,2*m2,2*m3 ) << endl;
         m1--;
         m2++;
         cout << "cg_" << i << " = " << cg << endl; 
      }
   return 0;
}
