#ifndef ANALYSIS_H_
#define ANALYSIS_H_
#include <string>

struct eLevel
{
  double e;
  int deg;
  int degUniq;
  int repst[20];
  double repK[20];
};

class analysis 
{
 private:
  int n1, n2, N, p, q, nOrb, wn;
  int s0, t0, stNo;
  double ratio;
  int ratioFlag; // 1 is ration = 1; 0 is other ratios
  std::string inputName1, inputName2, outputName;
  // inputName1 = rawData/TCTP/N6/
  // inputName2 = v0-0.5
  // outputName = data/TCTP/N6/v0-0.5
  double*** record;  
  int** ar;
  double* arE;
  eLevel* phD;

  std::string nameFileTool(std::string a, int n);
  std::string nameFileTool(std::string a, double n);
  void input();
  void compare();
  void newForm();
  int degFunRG(int s, int t);
  int degFunR1(int s, int t);
  void output();
 public:
  analysis(int n1_, int n2_, int nOrb_, double ratio_, int ratioFlag_, int wn_, std::string inputName1_, std::string inputName2_, std::string outputName_);
  ~analysis();
  void analyze();
};

#endif
