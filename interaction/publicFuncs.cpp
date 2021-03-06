#include "interaction.h"
#include <complex>
#include <iostream>

interaction::interaction(int nOrb_, int LLn_, double param_[], char type_[], double Q_)
{
  using namespace std;
  nOrb = nOrb_;
  LLn = LLn_;
  Q = Q_;
  int i;
  for (i = 0; i < 4; i++)
    param[i] = param_[i];
  for (i = 0; i < 3; i++)
    type[i] = type_[i];
}

void interaction::itrGen()
{
  using namespace std;
  int m1, m2, m3;
  switch (type[0])
    {
    case 'D':
      itr = new double[nOrb * nOrb * nOrb];
      for (m1 = 0; m1 < nOrb; m1++)
	for (m2 = 0; m2 < nOrb; m2++)
	  for (m3 = 0; m3 < nOrb; m3++)
	    itr[m1 * nOrb * nOrb + m2 * nOrb + m3] = dItr(m1, m2, m3);
      break;
    case 'T':
      itrC = new std::complex<double>[nOrb * nOrb * nOrb];
      for (m1 = 0; m1 < nOrb; m1++)
	for (m2 = 0; m2 < nOrb; m2++)
	  for (m3 = 0; m3 < nOrb; m3++)
	    itrC[m1 * nOrb * nOrb + m2 * nOrb + m3] = tItr(m1, m2, m3);
      break;
     case 'S':
       itr = new double[nOrb * nOrb * nOrb];
       for (m1 =0; m1 < nOrb; m1++)
         for (m2 = 0; m2 < nOrb; m2++)
           for (m3 = 0; m3 < nOrb; m3++)
             itr[m1 * nOrb * nOrb + m2 * nOrb + m3] = sItr(m1, m2, m3, Q);
       break;
    }
}

void interaction::print()
{
  using namespace std;
  for (int i = 0; i < 10; i++)
    cout << itrC[i] << " ";
  cout << endl;
}

void interaction::itrPrint(int m1, int m2, int m3)
{
  using namespace std;
  cout << type[0] << endl;
  switch (type[0])
    {
    case 'D':
      cout << "(" << m1 << ", " << m2 << "|V|" << m3 << ", " << m1 + m2 - m3 << ") = " << dItr(m1, m2, m3) << endl;
      break;
    case 'T':
      cout << "(" << m1 << ", " << m2 << "|V|" << m3 << ", " << (m1 + m2 - m3 + nOrb) % nOrb << ") = " << tItr(m1, m2, m3) << endl;
      cout << "<" << m1 << ", " << m2 << "|V|" << m3 << ", " << m1 + m2 - m3 << "> = " << tItr(m1, m2, m3) - tItr(m1, m2, (m1 + m2 - m3 + nOrb) % nOrb) << endl;
      break;
    default :
      cout << "Wrong input." << endl;
      break;
    }
    cout << "no. 4 diagonalized matrix element is: " << 
    (tItr(0, 2, 0) - tItr(0, 2, 2))
    + (tItr(0, 6, 0) - tItr(0, 6, 6))
    + tItr(0, 0, 0) + tItr(0, 6, 0) + tItr(2, 0, 2) + tItr(2, 6, 2) << endl;
}
