#include "./analysis/analysis.h"
#include <iostream>
#include <string>
#include <sstream>

std::string nameFileTool(std::string, int);
std::string nameFileTool(std::string, double);

int main()
{
  int n1 = 5, n2 = 5,
    nOrb = 20, wn = 35;
  double ratio = 1,
    ratioFlag = 1; // 1 is ratio = 1; 0 is other ratios
  std::string inputName1 = "rawData/TCTPv11/N10/";

  double c0I = -8, c0F = 1, c0Step = 0.2;
  for (double i = c0I; i < c0F + c0Step / 10; i += c0Step)
    {
      double c0 = i;
      std::string inputName2 = nameFileTool("r", ratio);
      inputName2 += nameFileTool("v0", c0);
      std::string outputName = nameFileTool("data/TCTPv11/N10/r1v0", c0);
      std::cout << inputName1 << "; " << outputName << std::endl;
      analysis a(n1, n2, nOrb, ratio, ratioFlag, wn, inputName1, inputName2, outputName);
      a.analyze();
    }
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
