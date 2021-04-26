#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <sstream>

int *hnode;
int **snode;
int *degree;
int *hdegree;

int N, M, R;
int Diameter;
double ASPL;
#include "MT.h"
#include "bfs.c"
#include "hs_bound.c"
#include "random_gen.cpp"

void graph_file_gen ();

int main (int argc, char **argv) {

  if (argc != 4) {
    fprintf(stderr, "Usage:\n\t./random_gen N M R\n");
    exit(EXIT_FAILURE);
  }
  N = std::stoi(argv[1]);
  M = std::stoi(argv[2]);
  R = std::stoi(argv[3]);

  if ((N < 3) || (M < 1) || (R < 3)) {
    fprintf(stderr, "The values of N, M, or R are too small.\n");
    exit(EXIT_FAILURE);
  }
  if ((N > 65536) || (M > 10000) || (R > 100)) {
    fprintf(stderr, "The value sof N, M, or R are too large.\n");
    exit(EXIT_FAILURE);
  }
  if (M * (R - 1) < N) {
    fprintf(stderr, "The number of switches and/or radix are too small.\n");
    exit(EXIT_FAILURE);
  }

  hnode = new int[N];
  snode = new int*[M];
  for (int i = 0; i < M; i++) {
    snode[i] = new int[R];
  }
  degree = new int[M];
  hdegree = new int[M];

  //fully_random();
  near_regular_random();

  init_queue();
  ASPL = aspl_host_fast();
  free_queue();

  if (ASPL == DBL_MAX) {
    fprintf(stderr, "Random graph generation failed (please review the three parameters N, M, and R)\n");
    exit(EXIT_FAILURE);
  }
  fprintf(stderr, "%f\n", ASPL);
  fprintf(stderr, "%d\n", Diameter);

  hs_bound(N, R);
  graph_file_gen();

  delete[] hnode;
  for (int i = 0; i < M; i++) {
    delete[] snode[i];
  }
  delete[] degree;
  delete[] hdegree;

  return EXIT_SUCCESS;
}

void graph_file_gen ()
{
  printf("%d %d %d\n", N, M , R);
  for (int i = 0; i < N; i++) {
    printf("%d %d\n", i, hnode[i] + N);
  }
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < degree[j]; j++) {
      if ((snode[i][j] >= N) && (i + N < snode[i][j])) {
	printf("%d %d\n", i + N, snode[i][j]);
      }
    }
  }	
}
