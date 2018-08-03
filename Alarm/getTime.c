#include <stdlib.h>
#include <time.h>

struct tm * getTime ()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  return timeinfo;
}
