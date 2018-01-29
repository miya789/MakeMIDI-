#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void makeTune(int n, int s, char *sig, int volume) {
  double smp_frq = 44100;

  int i;
  double t;
  double f = 440;
  short x;

  if (s != -1) {
    int N = (s-'A') + 7;
    for (int tune = 0; tune < N; tune++) {
      if (tune % 7 == 1 || tune % 7 == 4) {
        f = f * pow(2,1.0/12.0);
      } else {
        f = f * pow(2,2.0/12.0);
      }
    }
    if (sig == "sharp") {
      f = f * pow(2,1.0/12.0);
    }
  } else {f = 0;}

  for (i = 0; i <=n; i++) {
    t = i / smp_frq;
    double theta = 2*M_PI*f*t;
    x = volume*sin(theta);
    write(1,&x,2);
  }
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Input is incorrect!");
    exit(1);
  }

  int a = 'C';
  char *s = "sharp";

  int bs = 22100;
  int qw = bs / 4;
  int hf = bs / 2;
  int vol = atoi(argv[1]);
  makeTune(hf,'G'-7,NULL,vol);
  makeTune(hf,'F'-7,NULL,vol);
  makeTune(bs,'E'-7,NULL,vol);
  makeTune(hf,'G'-7,NULL,vol);
  makeTune(hf,'C',NULL,vol);
  makeTune(bs,'B',NULL,vol);
  makeTune(hf,'G'-7,NULL,vol);
  makeTune(hf,'D',NULL,vol);
  makeTune(bs,'C',NULL,vol);
  makeTune(bs,'E',NULL,vol);
  makeTune(bs,-1,NULL,vol);

  makeTune(hf,'C',NULL,vol);
  makeTune(hf,'B',NULL,vol);
  makeTune(bs,'A',NULL,vol);
  makeTune(hf,'F',NULL,vol);
  makeTune(hf,'D',NULL,vol);
  makeTune(bs,'C',NULL,vol);
  makeTune(bs,'B',NULL,vol);
  makeTune(hf,'C',NULL,vol);
  makeTune(hf-100,'G',NULL,vol);
  makeTune(100,-1,NULL,vol);
  makeTune(hf,'G',NULL,vol);
  makeTune(hf,'F',NULL,vol);
  makeTune(bs,'E',NULL,vol);
}
