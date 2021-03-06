#include "matrix.h"
#include <cmath>
#include <iostream>

void matrix::deciToPOS(long dec, int pB[], int antiPB[], int oB[], int n)
{
  using namespace std;
  int i = n - 1, j = nOrb - n - 1, 
    orb = nOrb - 1;
  do
    {
      switch (dec % 2)
	{
	case 1:
	  pB[i--] = orb;
	  oB[orb--] = 1;
	  break;
	case 0:
	  antiPB[j--] = orb;
	  oB[orb--] = 0;
	  break;
	}
      dec = dec / 2;
    } while (orb >= 0);
  return;
}

void matrix::deciToPOB(long dec, int pB1[], int antiPB1[], int oB1[], int pB2[], int antiPB2[], int oB2[], int n1, int n2)
{
  using namespace std;
  long deciShift = (long) (pow(2, nOrb) + 0.5);
  long dec1 = dec / deciShift, dec2 = dec % deciShift; //dec1 is shifted back because this is the two-layer case. One layer is shifted to higher order when combining the two layers
  int i = n1 - 1, j = nOrb - n1 - 1, 
    orb = nOrb - 1;
  do
    {
      switch (dec1 % 2)
	{
	case 1:
	  pB1[i--] = orb;
	  oB1[orb--] = 1;
	  break;
	case 0:
	  antiPB1[j--] = orb;
	  oB1[orb--] = 0;
	  break;
	}
      dec1 = dec1 / 2;
    } while (orb >= 0);
  i = n2 - 1;
  j = nOrb - n2 - 1;
  orb = nOrb - 1;
  do
    {
      switch (dec2 % 2)
	{
	case 1:
	  pB2[i--] = orb;
	  oB2[orb--] = 1;
	  break;
	case 0:
	  antiPB2[j--] = orb;
	  oB2[orb--] = 0;
	  break;
	}
      dec2 = dec2 / 2;
    } while (orb >= 0);
  return;
}

int matrix::binarySearchBToS(long key, int imin, int imax, long array[])
{
  int imid;
  while (imin <= imax)
    {
      imid = (imin + imax) / 2;
      if (array[imid] < key)
	imax = imid - 1;
      else if (array[imid] > key)
	imin = imid + 1;
      else
	return imid;
    }
  /*
  int imin = 0, imax = dim - 1, imid;
  while (imin <= imax)
    {
      imid = (imin + imax) / 2;
      if (bases[imid] < key)
	imax = imid - 1;
      else if (bases[imid] > key)
	imin = imid + 1;
      else
	return imid;
    }
  */
  return -1; // not found
}

int matrix::binarySearchSToB(int key, int imin, int imax, int array[])
{
  int imid;
  while (imin <= imax)
    {
      imid = (imin + imax) / 2;
      if (array[imid] < key)
	imin = imid + 1;
      else if (array[imid] > key)
	imax = imid - 1;
      else
	return imid;
    }
  return -1; // not found
}

/*
int matrix::tLocateMES(int& deci)
{
  using namespace std;
  int i = 0, movB;
  int b = deci, nb = -1;
  int p = 0, phase;
  while (nb != b)
    {
      // change to another term
      i ++;
      nb = b * (int)(pow(2, i * q) + 0.5);
      if (nb >= (int)(pow(2, nOrb) + 0.5))
	{
	  movB = nb / (int)(pow(2, nOrb) + 0.5);
	  nb = nb - movB * (int)(pow(2, nOrb) + 0.5) + movB;
	}
      // find the larger one
      p++;
      if (nb > b)
	{
	  deci = nb;
	  phase = p;
	}
    }
  return phase;
}
*/
int matrix::tLocateME(long& deci)
{
  using namespace std;
  long b = deci, movB;
  long b1 = b / (long)(pow(2, nOrb) + 0.5),
    b2 = b % (long)(pow(2, nOrb) + 0.5);
  long nb = -1, nb1, nb2;
  int phase = 0, i = 0;
  while (nb != b)
    {
      // change to another term
      i++;
      nb1 = b1 * (long)(pow(2.0, i * q) + 0.5);
      nb2 = b2 * (long)(pow(2.0, i * q) + 0.5);
      if (nb1 >= (long)(pow(2, nOrb) + 0.5))
      {
	movB = nb1 / (long)(pow(2, nOrb) + 0.5);
	nb1 = nb1 - movB * (long)(pow(2, nOrb) + 0.5) + movB;
      }
      if (nb2 >= (long)(pow(2, nOrb) + 0.5))
      {
	movB = nb2 / (long)(pow(2, nOrb) + 0.5);
	nb2 = nb2 - movB * (long)(pow(2, nOrb) + 0.5) + movB;
      } 
      nb = nb1 * (long)(pow(2, nOrb) + 0.5) + nb2;
      // find the larger system
      if (nb > deci)
	{
	  deci = nb;
	  phase = i;
	}
    }
  return phase;
}
