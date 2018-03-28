#include "lib/mat.h"
#include "lib/timer.hh"
#include "blender/imageref.hh"
#include "blender/multiband.hh"

#define MULTIBAND 3

using namespace blender;


int main() 
{
	GuardedTimer tm("blender");

	const Coor top_left = Coor(457, 17);
	const Coor bottom_right = Coor(1848, 114);
	ImageRef imgptr = {"data/example-data/CMU0/medium03.JPG"};
	imgptr.load();

	if (MULTIBAND > 0)
		MultiBandBlender blender(MULTIBAND);
	else
		LinearBlender blender();

	blender.add_image(top_left, bottom_right, imgptr, [](Coor t) -> Vec2D { return Vec2D{-10, -10}; });
	blender.run();

/*
    Coor top_left = scale_coor_to_img_coor(cur.range.min);
    Coor bottom_right = scale_coor_to_img_coor(cur.range.max);

    blender->add_image(top_left, bottom_right, *cur.imgptr,
        [=,&cur](Coor t) -> Vec2D {
          Vec2D c = Vec2D(t.x, t.y) * resolution + proj_range.min;
          Vec homo = proj2homo(Vec2D(c.x, c.y));
          Vec ret = cur.homo_inv.trans(homo);
          if (ret.z < 0)
            return Vec2D{-10, -10};  // was projected to the other side of the lens, discard
          double denom = 1.0 / ret.z;
          return Vec2D{ret.x*denom, ret.y*denom}
                + cur.imgptr->shape().center();
        });
  }
  //dynamic_cast<LinearBlender*>(blender.get())->debug_run(size.x, size.y);  // for debug
  return blender->run();
*/

	return 0;
}
