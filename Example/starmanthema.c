#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SMP_FRQ 44100.0
#define A_PITCH 110

double makePitch(int s, char *sig) {
  double f = A_PITCH; //pitch of "A"
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

void addTri(short x[], int A, double f, int start, int goal) {
  for (int i=start; i<goal; i++) {
    double t = i / SMP_FRQ;
    for (int k=0; k<5; k++) {
      x[i] += (short)(A/pow((2*k+1),2) *pow(-1,k) * sin(2*M_PI*f*(2*k+1)*t));  // NOT integer!!!
    }
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

  int bs = 20000;
  int hf = bs / 2;
  int qr = bs / 4;

  int ct = 0;
  while (ct != N) {
    // 1
    int n1 = bs * 4;
    short x1[n1];
    for (int i=0; i<n1; i++) {
      x1[i] = 0;
    }
    addTri(x1,5000,F  ,0,qr-1);
    addTri(x1,5000,C*2,0,qr-1);
    addTri(x1,5000,0  ,qr,2*qr-1);
    addTri(x1,5000,F  ,2*qr,3*qr-1);
    addTri(x1,5000,C*2,2*qr,3*qr-1);
    addTri(x1,5000,0  ,3*qr,4*qr-1);
    addTri(x1,5000,F  ,4*qr,5*qr-1);
    addTri(x1,5000,C*2,4*qr,5*qr-1);
    addTri(x1,5000,0  ,5*qr,6*qr-1);
    addTri(x1,5000,D  ,6*qr,7*qr-1);
    addTri(x1,5000,F  ,7*qr,8*qr-1);
    addTri(x1,5000,C*2,7*qr,8*qr-1);
    addTri(x1,5000,0  ,8*qr,9*qr-1);
    addTri(x1,5000,F  ,9*qr,10*qr-1);
    addTri(x1,5000,C*2,9*qr,10*qr-1);
    addTri(x1,5000,0  ,10*qr,11*qr-1);
    addTri(x1,5000,D  ,11*qr,12*qr-1);
    addTri(x1,5000,F  ,12*qr,13*qr-1);
    addTri(x1,5000,C*2,12*qr,13*qr-1);
    addTri(x1,5000,D  ,13*qr,14*qr-1);
    addTri(x1,5000,F  ,14*qr,15*qr-1);
    addTri(x1,5000,C*2,14*qr,15*qr-1);
    addTri(x1,5000,0  ,15*qr,16*qr-1);

    addTri(x1,3000,D/2,0,qr-1);
    addTri(x1,3000,0  ,qr,4*qr-1);
    addTri(x1,3000,A  ,4*qr,5*qr-1);
    addTri(x1,3000,0  ,5*qr,7*qr-1);
    addTri(x1,3000,D  ,6*qr,8*qr-1);
    addTri(x1,3000,0  ,8*qr,12*qr-1);
    addTri(x1,3000,A  ,12*qr,13*qr-1);
    addTri(x1,3000,0  ,13*qr,14*qr-1);
    addTri(x1,3000,D  ,14*qr,15*qr-1);
    addTri(x1,3000,0  ,15*qr,16*qr-1);

    writeNote(x1,n1);

    // 2
    int n2 = bs * 4;
    short x2[n2];                               // NOT redifinition of arrays!
    for (int i=0; i<n2; i++) {
      x2[i] = 0;
    }
    addTri(x2,5000,E  ,0,qr-1);
    addTri(x2,5000,B*2,0,qr-1);
    addTri(x2,5000,0  ,qr,2*qr-1);
    addTri(x2,5000,E  ,2*qr,3*qr-1);
    addTri(x2,5000,B*2,2*qr,3*qr-1);
    addTri(x2,5000,0  ,3*qr,4*qr-1);
    addTri(x2,5000,E  ,4*qr,5*qr-1);
    addTri(x2,5000,B*2,4*qr,5*qr-1);
    addTri(x2,5000,0  ,5*qr,6*qr-1);
    addTri(x2,5000,C  ,6*qr,7*qr-1);
    addTri(x2,5000,E  ,7*qr,8*qr-1);
    addTri(x2,5000,B*2,7*qr,8*qr-1);
    addTri(x2,5000,0  ,8*qr,9*qr-1);
    addTri(x2,5000,E  ,9*qr,10*qr-1);
    addTri(x2,5000,B*2,9*qr,10*qr-1);
    addTri(x2,5000,0  ,10*qr,11*qr-1);
    addTri(x2,5000,C  ,11*qr,12*qr-1);
    addTri(x2,5000,E  ,12*qr,13*qr-1);
    addTri(x2,5000,B*2,12*qr,13*qr-1);
    addTri(x2,5000,C  ,13*qr,14*qr-1);
    addTri(x2,5000,E  ,14*qr,15*qr-1);
    addTri(x2,5000,B*2,14*qr,15*qr-1);
    addTri(x2,5000,0  ,15*qr,16*qr-1);

    addTri(x2,3000,C/2,0,qr-1);
    addTri(x2,3000,0  ,qr,4*qr-1);
    addTri(x2,3000,G/2,4*qr,5*qr-1);
    addTri(x2,3000,0  ,5*qr,7*qr-1);
    addTri(x2,3000,C  ,6*qr,8*qr-1);
    addTri(x2,3000,0  ,8*qr,12*qr-1);
    addTri(x2,3000,G/2,12*qr,13*qr-1);
    addTri(x2,3000,0  ,13*qr,14*qr-1);
    addTri(x2,3000,C  ,14*qr,15*qr-1);
    addTri(x2,3000,0  ,15*qr,16*qr-1);

    writeNote(x2,n2);

    ct++;
  }
}
