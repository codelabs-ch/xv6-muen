#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  static const char hex_chars[] = "0123456789abcdef";
  int i, n, size, fd;
  char h[32];
  char buffer[2048];
  if(argc != 2){
    printf(2, "usage: %s [file]\n", argv[0]);
    exit();
  }
  if((fd = open(argv[1], 0)) < 0){
    printf(1, "%s: cannot open '%s'\n", argv[0], argv[1]);
    exit();
  }

  while((n = read(fd, buffer, sizeof(buffer))) > 0)
    size = +n;

  close(fd);

  n = hash(&buffer, &h, size);
  if(n == -1){
    printf(2, "hashing failed\n");
    exit();
  }

  for(i = 0; i < 32; ++i){
    printf (1, "%c", hex_chars[0xf & h[i] >> 4]);
    printf (1, "%c", hex_chars[0xf & h[i]]);
  }
  printf(1, " - %s\n", argv[1]);

  exit();
}
