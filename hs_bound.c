void hs_bound (int arg_n, int arg_p)
{
  int i;
  int leaf_n = arg_n - 1;
  int total_n, total_m = 1;
  int current_layer, next_layer;
  int wiener;

  int d_lb;
  double aspl_lb;
  
  for (i = 1; ; i++) {
	if ((int)pow((arg_p - 1), i) > leaf_n) break;
	total_m += (int)pow((arg_p - 1), i);
  }

  i--;
  total_n = (int)pow((arg_p - 1), i);
  total_m -= (int)pow((arg_p - 1), i);
  current_layer = total_n;

  next_layer = ceil((double)(leaf_n - total_n) / (double)(arg_p - 2));
  current_layer -= next_layer;
  total_m += next_layer;
  next_layer += leaf_n - total_n;
  
  wiener = current_layer * (i + 1) + next_layer * (i + 2);

  aspl_lb = (double)wiener / (double)(arg_n - 1);
  if (next_layer > 0) {
    d_lb = i + 2;
  } else {
    d_lb = i + 1;
  }
  fprintf(stderr, "\nLower bound\n");
  fprintf(stderr, "%f\n", aspl_lb);
  fprintf(stderr, "%d\n", d_lb);
}
