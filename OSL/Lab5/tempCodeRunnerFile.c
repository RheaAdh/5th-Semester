
  if (access(FIFO_NAME, F_OK) == -1) {
    res = mkfifo(FIFO_NAME, 0777);
    if (res != 0) {
      fprintf(stderr, "Could not create file%s\n", FIFO_NAME);
      exit(EXIT_FAILURE);
    }
  }