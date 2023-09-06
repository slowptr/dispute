#include "dmap_loader.h"

void
dmap_load (FILE *file, float *wsize, float *wbound)
{
  char line[128];
  while (fgets (line, sizeof (line), file) != NULL)
    {
      if (line[0] == 's')
        {
          sscanf (line, "s %f %f", wsize, wbound);
        }
    }
}
