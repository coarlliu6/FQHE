#include "interaction/interaction.h"
#include <cmath> // exp(); pow(); sqrt()
#include <gsl/gsl_integration.h>
#include <algorithm> // max() and min()
#include <boost/math/special_functions/binomial.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <iostream>

int main()
{
  using namespace std;
  int n = 3;
  gsl_function F;  // a struc having fxn and *param
  double result, error;
  int p[2];
  int m=2;
  p[0] = n;
  p[1] = m;      //?
  gsl_integration_workspace* w = gsl_integration_workspace_alloc(1000);  //referto  the size of the space to hold the 1000 double intervals, their integ. results and error estimates 
 // F.function = &vmIntegrand;
 // F.params = &p;
 // gsl_integration_qagiu(&F, 0, 1e-13, 0, 1000, w, &result, &error);    //Compute the integral of F from +- infinity
 // gsl_integration_workspace_free(w);
  return 0;
}

