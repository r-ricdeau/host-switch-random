void remove_loop (int, int*);

void fully_random (void) //fully random
{
  int i, j, k, l;
  int u, v;
  int *loop;

  if ((M * R - N) % 2 != 0) {
	fprintf(stderr, "Number of free ports must be even.\n");
	exit(EXIT_FAILURE);
  }
  init_genrand((unsigned int)time(NULL));

  loop = new int[M];
  
  /* STEP1: randomly add edges */
  // connect host-switch
  for (i = 0; i < N; i++) {
	u = genrand_int31() % M;
	if (degree[u] >= R) {
	  i--;
	  continue;
	}
	hnode[i] = u;
	snode[u][degree[u]] = i;
	degree[u]++;
	hdegree[u]++;
  }

  // connect switch-switch
  for (i = 0; i < (M * R - N) / 2; i++) {
	u = genrand_int31() % M;
	v = genrand_int31() % M;
	if (degree[u] == R || degree[v] == R || ((u == v) && (degree[u] > R - 2))) {
		i--;
		continue;
	}
	if (u == v) loop[u]++;
	snode[u][degree[u]] = v + N;
	degree[u]++;
	snode[v][degree[v]] = u + N;
	degree[v]++;
  }

  /* STEP2: remove loops */
  for (i = 0; i < M; i++) {	
  	while (loop[i] > 0) {
  	  remove_loop(i, loop);
  	}
  }

  delete[] loop;

  return;
}

void remove_loop (int u, int* loop)
{
  int v1, v2;
  int i, j;

  if (loop[u] <= 0) {
	fprintf(stderr, "Error in remove_loop\n");
	exit(EXIT_FAILURE);
  }
  for (;;) {
	v1 = genrand_int31() % M;
	v2 = snode[v1][genrand_int31() % R] - N;
	if (v1 != u && v2 >= 0 && v2 != u) break;
  }

  for (i = 0; i < R; i++) {
	if (snode[v1][i] == v2 + N) {
	  snode[v1][i] = u + N;
	  break;
	}
  }
  for (i = 0; i < R; i++) {
	if (snode[v2][i] == v1 + N) {
	  snode[v2][i] = u + N;
	  break;
	}
  }
  for (i = 0; i < R; i++) {
	if (snode[u][i] == u + N) {
	  snode[u][i] = v1 + N;
	  break;
	}
  }
  for (i = 0; i < R; i++) {
	if (snode[u][i] == u + N) {
	  snode[u][i] = v2 + N;
	  break;
	}
  }
  //printf("u %d v1 %d v2 %d\n", u, v1, v2);
  loop[u] -= 2;
  if (v1 == v2) loop[v1] -= 2;
}
