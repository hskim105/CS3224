#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void head(int fd, char *name, int limit)
{
  int i, n;
  int l, c;

  l = c = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      c++;
      printf(1, "%c", buf[i]);
      if(buf[i] == '\n')
        l++;
      if(l == limit)
exit();
    }
  }
  if(n < 0){
    printf(1, "head: read error\n");
    exit();
  }
}

int main(int argc, char *argv[])
{
  int fd, i;
  int limit = 10;

  if(argc <= 1){
    head(0, "", 10);
    exit();
  }

  char *p = argv[1];

  for(i = 1; i < argc; i++){
    if(p[0] == '-'){
      limit = atoi(++p);
      i++;
    }
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "head: cannot open %s\n", argv[i]);
      exit();
    }
    head(fd, argv[i], limit);
    close(fd);
  }
  exit();
}
