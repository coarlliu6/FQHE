#include "./basis/basis.h"
#include "./interaction/interaction.h"
#include "./matrix/matrix.h"
#include "./ED/ED.h"
#include <cmath> // sqrt
#include <gsl/gsl_math.h> // pi
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

std::string nameFileTool(std::string, int);
std::string nameFileTool(std::string, double);


int main()
{
  using namespace std;
  cout << "==============================================================" << endl;
  cout << "=========================== YED ==============================" << endl;
  cout << "==============================================================" << endl;
  const double timeDivider = 60.0 * 60;
  cout << "Feb. 4 version:" << endl;
  clock_t timeStart;
  timeStart = clock();
  cout << "start time: " << (double)(timeStart)/CLOCKS_PER_SEC/timeDivider << "hr" << endl;
  int nOrb;
  int s = 0; // this parameter is for torus, no use here
  // basis:
  int n1 =0, n2, // if it just has one component, make n1 = 0
    qn, qn_org,   // total angular momentum 
    wn;
  double Q = 0; // B field stregth for monople at origin in sphere case.
  int dimbasis;
  char geometry;

  cout << "Geometry? [D(isk), S(phere)]" << endl;
  cin >> geometry;
  cout <<"Orbital number(for S: 2Q+1) = " << endl;
  cin >> nOrb;  
  cout << "Particle number(n1, default=0) = " << endl;
  cin >> n1;
  cout << "Particle number(n2) = " << endl;
  cin >> n2;
  cout << "Total angular momentum = " << endl;
  cin >> qn;
  cout << "The number of lowest energies do you want = " << endl;
  cin >> wn;
 
  qn_org = qn;

  if (geometry == 'S')
    { Q = (nOrb - 1)/2;
      qn_org += (n1 + n2) * (nOrb - 1) / 2; 
    }  
 
  basis bases(n1, n2, nOrb, qn_org, s, geometry);
  dimbasis = bases.bGen();
 // cout <<  "dimbasis = "  << dimbasis << endl;
  clock_t timeBasis;
  timeBasis = clock();
  cout << "basis finished time: " << (double)(timeBasis)/CLOCKS_PER_SEC/timeDivider << "hr" << endl;
  bases.print();

  if (wn < dimbasis)  // due to wn < dim
    {
       cout << "wn = " << wn << endl;
    }
  else 
    { wn = dimbasis - 1;
      cout << "wn >= dim, new wn = dim-1 =" << wn << endl;
    }

 // intra-layer interaction:  
  double a = 0, b = 0, // for torus, no use here
         c0 = 0, c1 = 1,  // for hard core interaction
         param[4] = {a, b, c0, c1};  
  int LLn = 0;
  char type[3];
       type[0]= geometry;
       type[1]='H';
   
  interaction itrA(nOrb, LLn, param, type, Q);
  itrA.itrGen();
  // inter-layer interaction:
  c0 = 0; c1 = 1;
  param[2] = c0; param[3] = c1;
  interaction itrR(nOrb, LLn, param, type, Q);
  itrR.itrGen();

  cout<<"finish interaction"<<endl;
 
 // generate matrix
  char sizeCountType = 'C';
  char matrixType = 'l'; // w: whole; l: low part
  matrix m(bases, itrA, itrR, matrixType, sizeCountType, qn, s);
  m.mGen();
  m.print();

 // cout<< "finish matrix generation"<<endl;

  // ED
  ED ed(m, wn);
  ed.arpackpp();
  ed.terminalOP();
   ed.terminalVectorOP();
  cout << "==============================================================" << endl;
  cout << "==============================================================" << endl;
}

std::string nameFileTool(std::string p, int pn)
{
  using namespace std;
  string output = p;
  string temp;
  ostringstream convert;
  convert << pn;
  temp = convert.str();
  output += temp;
  convert.str("");
  return output;
}

std::string nameFileTool(std::string p, double number)
{
  using namespace std;
  string output = p;
  ostringstream strs;
  strs << number;
  string n = strs.str();
  output += n;
  return output;
}
