#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(0));
  int a = rand();
  int b = rand();

  if (a > b) return 1;
  else if (a < b) return 2;
  else return 0;
}
