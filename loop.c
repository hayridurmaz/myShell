#include <stdio.h>
int main(int argc, char const *argv[]) {
  for (int i = 0; i <100000; i++) {
    printf("%d + %s\n",i, argv[1]);
  }
  return 0;
}
