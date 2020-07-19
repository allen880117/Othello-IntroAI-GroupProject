#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int main(int argc, char **argv) {
  FILE * fp = fopen(argv[1], "r");
  double w[64];
  for (int i = 0; i < 64; i++) {
    fscanf(fp, "%lf", &w[i]);
  }
  fclose(fp);

  w[0]  = 1.0;
  w[7]  = w[0];
  w[63] = w[0];
  w[56] = w[0];

  w[1] = (double)(w[1] + w[6] + w[15] + w[55] + w[62] + w[57] + w[48] + w[8]) /
         (double)8.0;
  w[6]  = w[1];
  w[15] = w[1];
  w[55] = w[1];
  w[62] = w[1];
  w[57] = w[1];
  w[48] = w[1];
  w[8]  = w[1];

  w[2] = (double)(w[2] + w[5] + w[23] + w[47] + w[61] + w[58] + w[40] + w[16]) /
         (double)8.0;
  w[5]  = w[2];
  w[23] = w[2];
  w[47] = w[2];
  w[61] = w[2];
  w[58] = w[2];
  w[40] = w[2];
  w[16] = w[2];

  w[3] = (double)(w[3] + w[4] + w[31] + w[39] + w[60] + w[59] + w[32] + w[24]) /
         (double)8.0;
  w[4]  = w[3];
  w[31] = w[3];
  w[39] = w[3];
  w[60] = w[3];
  w[59] = w[3];
  w[32] = w[3];
  w[24] = w[3];

  w[10] =
      (double)(w[10] + w[13] + w[22] + w[46] + w[53] + w[50] + w[41] + w[17]) /
      (double)8.0;
  w[13] = w[10];
  w[22] = w[10];
  w[46] = w[10];
  w[53] = w[10];
  w[50] = w[10];
  w[41] = w[10];
  w[17] = w[10];

  w[11] =
      (double)(w[11] + w[12] + w[30] + w[38] + w[52] + w[51] + w[33] + w[25]) /
      (double)8.0;
  w[12] = w[11];
  w[30] = w[11];
  w[38] = w[11];
  w[52] = w[11];
  w[51] = w[11];
  w[33] = w[11];
  w[25] = w[11];

  w[19] =
      (double)(w[19] + w[20] + w[29] + w[37] + w[44] + w[43] + w[34] + w[26]) /
      (double)8.0;
  w[20] = w[19];
  w[29] = w[19];
  w[37] = w[19];
  w[44] = w[19];
  w[43] = w[19];
  w[34] = w[19];
  w[26] = w[19];

  w[9]  = (double)(w[9] + w[14] + w[54] + w[49]) / (double)4.0;
  w[14] = w[9];
  w[54] = w[9];
  w[49] = w[9];

  w[18] = (double)(w[18] + w[21] + w[45] + w[42]) / (double)4.0;
  w[21] = w[18];
  w[45] = w[18];
  w[42] = w[18];

  w[27] = (double)(w[27] + w[28] + w[36] + w[35]) / (double)4.0;
  w[28] = w[27];
  w[36] = w[27];
  w[35] = w[27];

  // double delta = (double)(w[1]+w[9]) / (double)(2.0);
  // double scale = (double) (0.1) / (w[1] - delta);
  // for(int i=0; i<64; i++){
  //   w[i] = (double)(1.0) + (double)(w[i] -delta) * scale;
  // }

  FILE* after = fopen(argv[2], "w");
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      fprintf(after, "%lf, ", w[i*8+j]);
    }
    fprintf(after, "\n");
  }
  fclose(after);

  sort(w, w+64);
  int iter =0;
  double init = -1.00;
  for(int i=0; i<64; i++){
    if(w[i] != init){
      printf("%lf order: %d\n", w[i], iter);
      init = w[i];
      iter++;
    }
  }
}