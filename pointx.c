  int xs[4];
  int* xp[4];
  int i;

  for (i = 0; i < 4; ++i)  {
    printf("&x[%d] = %p\n", i, &xs[i]);
  }

  printf("Address of array xs: %p\n", xs);
  printf("Address of array xs: %p\n", &xs);
  printf("Address of array xp: %p\n", xp);

  for (i = 0; i < 4; ++i)  {
    printf("&xp[%d] = %p\n", i, &xp[i]);
  }