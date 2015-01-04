#include "matrix.h"
#include <iostream>
#include "basis/basis.h"
#include "interaction/interaction.h"
#include <boost/math/special_functions/binomial.hpp>
#include <algorithm>
//#include <omp.h>
#include <time.h>

matrix::matrix(basis b_, interaction itrA_, interaction itrR_, char matrixType_, char sizeCountType_, int t_, int s_)
{
  using namespace std;
  // parameters and data asked from basis class
  n1 = b_.n1;
  n2 = b_.n2;
  nOrb = b_.nOrb;
  type[0] = b_.type;
  matrixType = matrixType_;
  N = b_.N;
  q = b_.q;
  dim = b_.dim;
  bases = b_.bases;
  tStSetNo = b_.tStSetNo;
  // parameters and data asked from interaction class
  switch (type[0])
    {
    case 'D':
      itrA = itrA_.itr;
      itrR = itrR_.itr;
      break;
    case 'S':
      itrA = itrA_.itr;
      itrR = itrR_.itr;
      break;
    case 'T':
      itrAC = itrA_.itrC;
      itrRC = itrR_.itrC;
      break;
    }
  type[1] = sizeCountType_;
  t = t_;
  s = s_;
}

void matrix::mGen()
{
  using namespace std;
  const double timeDivider = 60.0 * 60;
  clock_t timeStart;
  timeStart = clock();
  cout << "matrix code start time: " << (double)(timeStart)/CLOCKS_PER_SEC/timeDivider << "hr" << endl;

  // decide the size of the matrix, and allocate space for the matrix
  pcol = new int[dim + 1];
  long sizeCounted;
  std::cout << "type[0]: " << type[0] << std::endl;
  std::cout << "type[1]: " << type[1] << std::endl;
  switch (type[1])  // type[1] here represent the type of counting matrix size, estimate or exact count.
    {
    case 'E': 
      sizeCounted = estimateSize();
      std::cout << "size estimated = " << sizeCounted << std::endl;
      break;
    case 'C': 
      sizeCounted = countSize();
      std::cout << "size couted = " << sizeCounted << std::endl;
      break;
    }

  clock_t timeSize;
  timeSize = clock();
  cout << "matrix known or estimated at: " << (double)(timeSize)/CLOCKS_PER_SEC/timeDivider << "hr" << endl;

  row = new int[sizeCounted + 1];
  switch (type[0])
    {
    case 'D': A = new double[sizeCounted + 1];
      break;
    case 'S': A = new double [sizeCounted +1];
      break;
    case 'T': AC = new std::complex<double>[sizeCounted + 1];
      break;
    }
  // generate the matrix
  size = 0;
  // generate the temporary space to store matrix elements and row numbers
  using namespace boost::math;
  int rowNo, nn;
  if (n1 == 0 || n2 == 0)
    {
      nn = std::max(n1, n2);
      rowNo = binomial_coefficient<double>(nn, 2) * (nOrb - nn);
    }
  else
    rowNo = (binomial_coefficient<double>(n1, 2) * (nOrb - n1) 
		+ binomial_coefficient<double>(n2, 2) * (nOrb - n2) 
		+ n1 * n2 * (nOrb - n1));
    
  int rowTemp[rowNo];
  std::complex<double> ACTemp[rowNo];
  double ATemp[rowNo];
  //  omp_set_num_threads(4);
  //  int th_id;
  int pB1[n1], antiPB1[nOrb - n1], oB1[nOrb],
    pB2[n2], antiPB2[nOrb - n2], oB2[nOrb];
  int rNo; //real nonzero matrix elements' no of a colum;
  long ss = 0;
  //#pragma omp parallel for default(shared) private(th_id, rNo, pB1, antiPB1, oB1, pB2, antiPB2, oB2, rowTemp, ACTemp) reduction(+:ss) 
  for (int j = 0; j < dim; j++)
    {
      if (j % 100000 == 0)
	{
	  std::cout << j << std::endl;
	  //	  th_id = omp_get_thread_num();
	  //std::cout << "Hello World from thread " << th_id << '\n';
	}
      basisSctNo[j] = 0;
      // low part
      if (n1 == 0 || n2 == 0)
	deciToPOS(bases[j], pB2, antiPB2, oB2, max(n1, n2));
      else
	deciToPOB(bases[j], pB1, antiPB1, oB1, pB2, antiPB2, oB2, n1, n2);

      switch (type[0])
	{
	case 'D': 
	  diaMED(j, bases[j], pB1, pB2, rowTemp, ATemp);
	  ATemp[0] += 100;
	  rowTemp[0] = j;
	  rNo = dOffME(j, bases[j], pB1, antiPB1, oB1, pB2, antiPB2, oB2, 'O', rowTemp, ATemp);
	  dStoreValue(j, rowTemp, ATemp, rNo);
 	  break;
        case 'S':
          diaMED(j, bases[j], pB1, pB2, rowTemp, ATemp);
          ATemp[0] += 100;
          rowTemp[0] = j;
          rNo = dOffME(j, bases[j], pB1, antiPB1, oB1, pB2, antiPB2, oB2, 'O', rowTemp, ATemp);
          dStoreValue(j, rowTemp, ATemp, rNo);
          break;
	case 'T': 
	  diaMET(j, bases[j], pB1, pB2, rowTemp, ACTemp);
	  ACTemp[0] += 100;
	  rNo = tOffME(j, bases[j], pB1, antiPB1, oB1, pB2, antiPB2, oB2, 'O', rowTemp, ACTemp);
	  tStoreValue(j, rowTemp, ACTemp, rNo);
	  break;
	}
      //      cout << j << ": " << basisSctNo[j] << endl;
      pcol[j + 1] = pcol[j] + basisSctNo[j];
      ss = ss + rNo;
    }
  size = ss;
  cout << "ss = " << ss << endl;
  std::cout << "dim = " << dim << ", size = " << size << std::endl;
  clock_t timeGen;
  timeGen = clock();
  cout << "matrix generated at: " << (double)(timeGen)/CLOCKS_PER_SEC/timeDivider << "hr" << endl;
}

void matrix::print()
{
  using namespace std;
  cout << "dim = " << dim << ", size = " << size << endl;
  for (int i = 0; i <= dim; i++)
    cout << pcol[i] << " ";
  cout << endl;

  switch (type[0])
    {
    case 'D': 
      for (long j = 0; j < size; j++)
	cout << row[j] << " ";
      cout << endl;
      for (long j = 0; j < size; j++)
	cout << A[j] << " ";
      cout << endl;
      break;

    case 'S':
      for (long j=0; j < size; j++)
         cout << row[j] << " ";
      cout << endl;
      for (long j = 0; j < size; j++)
         cout << A[j] << " ";
      cout << endl;
      break; 

    case 'T': 
      int i = 0;
      for (long j = 0; j < size ; j++)
 	{
	  if (j == pcol[i] && row[j - 1] != i - 1)
	    {
	      i++;
	      cout << endl;
	    }
	  cout << row[j] << " " << AC[j] << " ";
	}
      cout << endl;
      //      for (int i = 0; i < dim; i++)
      //	cout << AC[pcol[i]] << endl;
      break;
    }
}
