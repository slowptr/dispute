#include "ui.h"

#include "bootleg3d.c"

void
g_ui_render ()
{
  b3d_pixels[(b3d_width / 2 - 5) + (b3d_height / 2) * b3d_width] = 0xffffff;
  b3d_pixels[(b3d_width / 2) + (b3d_height / 2) * b3d_width] = 0xffffff;
  b3d_pixels[(b3d_width / 2 + 5) + (b3d_height / 2) * b3d_width] = 0xffffff;
  b3d_pixels[(b3d_width / 2) + (b3d_height / 2 - 5) * b3d_width] = 0xffffff;
  b3d_pixels[(b3d_width / 2) + (b3d_height / 2 + 5) * b3d_width] = 0xffffff;
}
