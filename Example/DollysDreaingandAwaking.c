#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SMP_FRQ 44100.0

double makePitch(int s, char *sig) {
  double f = 440; //pitch of "A"
  if (s != -1) { //sound
    int N = (s-'A') + 7; //how many times to move
    for (int tune = 0; tune < N; tune++) { //move to goal tune
      if (tune % 7 == 1 || tune % 7 == 4) {
        f = f * pow(2,1.0/12.0);
      }
      else {
        f = f * pow(2,2.0/12.0);
      }
    }
    if (sig == "sharp") { //additional condition about sharp
      f = f * pow(2,1.0/12.0);
    }
  }
  else { //rest
    f = 0;
  }

  return f;
}

void addSin(short x[], int A, double f, int start, int goal) {
  for (int i=start; i<goal; i++) {
    double t = i / SMP_FRQ;
    x[i] += (short)(A * sin(2*M_PI*f*t));  // NOT integer!!!
  }
}

void addCreSin(short x[], int A, double f, int start, int goal) {
  for (int i=start; i<goal; i++) {
    double t = i / SMP_FRQ;
    x[i] += (short)(A * sin(2*M_PI*f*t) * exp((i-start)*(log(2) / (goal-start))));
  }
}

void addDecreSin(short x[], int A, double f, int start, int goal) {
  for (int i=start; i<goal; i++) {
    double t = i / SMP_FRQ;
    x[i] += (short)(A * 1.2 * sin(2*M_PI*f*t) * exp((i-start)*(-log(2) / (goal-start))));
  }
}

void writeNote(short x[], int n) {
  write(1,x,2*(n-1));
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Input time of play...");
    exit(1);
  }
  /*double f[N];
  for (int i=0; i<N; i++) {
    double f[i] = makePitch();
  }
  //f = {f1, f2, f3, ...};*/
  char *s = "sharp";
  double A  = makePitch('A', NULL);
  double As = makePitch('A', s);
  double B  = makePitch('B', NULL);
  double Bs = makePitch('B', s);
  double C  = makePitch('C', NULL);
  double Cs = makePitch('C', s);
  double D  = makePitch('D', NULL);
  double Ds = makePitch('D', s);
  double E  = makePitch('E', NULL);
  double Es = makePitch('E', s);
  double F  = makePitch('F', NULL);
  double Fs = makePitch('F', s);
  double G  = makePitch('G', NULL);
  double Gs = makePitch('G', s);

  int N = atoi(argv[1]);
  /*
  double **x = (double **)malloc(sizeof(double*)*N);
  for (int i=0; i<N; i++) {
    x[i] = (double *)malloc(sizeof(double));
    x[i] = 0;
  }
  short *x = (short *)malloc(sizeof(short)*N);
  x = 100;*/

  int bs = 30000;
  int hf = bs / 2;
  int qr = bs / 4;

  // 1
  int n1 = bs;
  short x1[n1];
  for (int i=0; i<n1; i++) {
    x1[i] = 0;
  }
  addSin(x1,8000,G  ,0,hf-1);
  addSin(x1,8000,F  ,hf,2*hf-1);
  writeNote(x1,n1);

  // 2
  int n2 = bs * 4;
  short x2[n2];                               // NOT redifinition of arrays!
  for (int i=0; i<n2; i++) {
    x2[i] = 0;
  }
  addSin(x2,8000,E  ,0,bs-1);
  addSin(x2,8000,G  ,bs,bs+hf-1);
  addSin(x2,8000,C*2,bs+hf,2*bs-1);
  addSin(x2,8000,B*2,2*bs,3*bs-1);
  addSin(x2,8000,G  ,3*bs,3*bs+hf-1);
  addSin(x2,8000,D*2,3*bs+hf,4*bs-1);

  addSin(x2,5000,C/2,0,2*bs-1);

  addSin(x2,5000,E/2,hf,2*hf*0.95);
  addSin(x2,5000,G/2,hf,2*hf*0.95);
  addSin(x2,5000,E/2,2*hf,3*hf*0.95);
  addSin(x2,5000,G/2,2*hf,3*hf*0.95);
  addSin(x2,5000,E/2,3*hf,4*hf*0.95);
  addSin(x2,5000,G/2,3*hf,4*hf*0.95);

  addSin(x2,5000,D/2,2*bs,4*bs-1);

  addSin(x2,5000,F/2,2*bs+hf,2*bs+2*hf*0.95);
  addSin(x2,5000,G/2,2*bs+hf,2*bs+2*hf*0.95);
  addSin(x2,5000,F/2,2*bs+2*hf,2*bs+3*hf*0.95);
  addSin(x2,5000,G/2,2*bs+2*hf,2*bs+3*hf*0.95);
  addSin(x2,5000,F/2,2*bs+3*hf,2*bs+4*hf*0.95);
  addSin(x2,5000,G/2,2*bs+3*hf,2*bs+4*hf*0.95);

  writeNote(x2,n2);

  // 3
  int n3 = bs * 4;
  short x3[n3];
  for (int i=0; i<n3; i++) {
    x3[i] = 0;
  }
  addSin(x3,8000,C*2,0,bs-1);
  addSin(x3,8000,E*2,bs,2*bs-1);
  addSin(x3,8000,0  ,2*bs,3*bs-1);
  addSin(x3,8000,C*2,3*bs,3*bs+hf-1);
  addSin(x3,8000,B*2,3*bs+hf,4*bs-1);

  addSin(x3,5000,E/2,0,2*bs-1);

  addSin(x3,5000,G/2,hf,2*hf*0.95);
  addSin(x3,5000,C  ,hf,2*hf*0.95);
  addSin(x3,5000,G/2,2*hf,3*hf*0.95);
  addSin(x3,5000,C  ,2*hf,3*hf*0.95);
  addSin(x3,5000,G/2,3*hf,4*hf*0.95);
  addSin(x3,5000,C  ,3*hf,4*hf*0.95);

  addSin(x3,5000,E/2,2*bs,4*bs-1);

  addSin(x3,5000,G/2,2*bs+hf,2*bs+2*hf*0.95);
  addSin(x3,5000,C  ,2*bs+hf,2*bs+2*hf*0.95);
  addSin(x3,5000,G/2,2*bs+2*hf,2*bs+3*hf*0.95);
  addSin(x3,5000,C  ,2*bs+2*hf,2*bs+3*hf*0.95);
  addSin(x3,5000,G/2,2*bs+3*hf,2*bs+4*hf*0.95);
  addSin(x3,5000,C  ,2*bs+3*hf,2*bs+4*hf*0.95);

  writeNote(x3,n3);

  // 4
  int n4 = bs * 4;
  short x4[n4];
  for (int i=0; i<n4; i++) {
    x4[i] = 0;
  }
  addSin(x4,8000,A*2,0,bs-1);
  addSin(x4,8000,F*2,bs,bs+hf-1);
  addSin(x4,8000,D*2,bs+hf,2*bs-1);
  addSin(x4,8000,C*2,2*bs,3*bs-1);
  addSin(x4,8000,B*2,3*bs,4*bs-1);

  addSin(x4,5000,F/2,0,2*bs-1);

  addSin(x4,5000,A  ,hf,2*hf*0.95);
  addSin(x4,5000,D  ,hf,2*hf*0.95);
  addSin(x4,5000,A  ,2*hf,3*hf*0.95);
  addSin(x4,5000,D  ,2*hf,3*hf*0.95);
  addSin(x4,5000,A  ,3*hf,4*hf*0.95);
  addSin(x4,5000,D  ,3*hf,4*hf*0.95);

  addSin(x4,5000,G/2,2*bs,2*bs+hf-1);

  addSin(x4,5000,C  ,2*bs+hf,2*bs+2*hf*0.95);
  addSin(x4,5000,E  ,2*bs+hf,2*bs+2*hf*0.95);

  addSin(x4,5000,G/2,2*bs+2*hf,2*bs+3*hf-1);

  addSin(x4,5000,D  ,2*bs+3*hf,2*bs+4*hf*0.95);
  addSin(x4,5000,F  ,2*bs+3*hf,2*bs+4*hf*0.95);

  writeNote(x4,n4);

  // 5
  int n5 = bs * 4;
  short x5[n5];
  for (int i=0; i<n5; i++) {
    x5[i] = 0;
  }
  addSin(x5,8000,C*2,0,2*bs-1);

  addSin(x5,5000,C  ,0,bs-1);
  addSin(x5,5000,E  ,hf,2*hf*0.95);
  addSin(x5,5000,G  ,hf,2*hf*0.95);
  addSin(x5,5000,E  ,2*hf,3*hf*0.95);
  addSin(x5,5000,G  ,2*hf,3*hf*0.95);
  addSin(x5,5000,D  ,3*hf,4*hf*0.95);
  addSin(x5,5000,F  ,3*hf,4*hf*0.95);
  addSin(x5,5000,C  ,2*bs,3*bs-1);
  addSin(x5,5000,E  ,2*bs,3*bs-1);
  writeNote(x5,n5);
}
