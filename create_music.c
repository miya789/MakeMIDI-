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

  int bs = 28000;
  int qw = bs / 4;
  int hf = bs / 2;
  int vol = atoi(argv[1]);
  makeTune(qw,'B',NULL,vol);
  makeTune(qw,'A',NULL,vol);
  makeTune(qw,'G'-7,s,vol);
  makeTune(qw,'A',NULL,vol);
  makeTune(hf,'C',NULL,vol);
  makeTune(hf,-1,NULL,vol);
  makeTune(qw,'D',NULL,vol);
  makeTune(qw,'C',NULL,vol);
  makeTune(qw,'B',NULL,vol);
  makeTune(qw,'C',NULL,vol);
  makeTune(hf,'E',NULL,vol);
  makeTune(hf,-1,NULL,vol);
  makeTune(qw,'F',NULL,vol);
  makeTune(qw,'E',NULL,vol);
  makeTune(qw,'D',s,vol);
  makeTune(qw,'E',NULL,vol);
  makeTune(qw,'B'+7,NULL,vol);
  makeTune(qw,'A'+7,NULL,vol);
  makeTune(qw,'G',s,vol);
  makeTune(qw,'A'+7,NULL,vol);
  makeTune(qw,'B'+7,NULL,vol);
  makeTune(qw,'A'+7,NULL,vol);
  makeTune(qw,'G',s,vol);
  makeTune(qw,'A'+7,NULL,vol);
  makeTune(bs,'C'+7,NULL,vol);
  makeTune(hf,'A'+7,NULL,vol);
  makeTune(hf,'C'+7,NULL,vol);
  makeTune(hf,'B'+7,NULL,vol);
  makeTune(hf,'A'+7,NULL,vol);
  makeTune(hf,'G',NULL,vol);
  makeTune(hf,'A'+7,NULL,vol);
  makeTune(hf,'B'+7,NULL,vol);
  makeTune(hf,'A'+7,NULL,vol);
  makeTune(hf,'G',NULL,vol);
  makeTune(hf,'A'+7,NULL,vol);
  makeTune(hf,'B'+7,NULL,vol);
  makeTune(hf,'A'+7,NULL,vol);
  makeTune(hf,'G',NULL,vol);
  makeTune(hf,'F',s,vol);
  makeTune(bs,'E',NULL,vol);
}
