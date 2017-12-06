#include "lib/timer.hh"
#include "blender/multiband.hh"

#define MULTIBAND 3

using namespace blender;


int main() 
{
	GuardedTimer tm("blender");

	if (MULTIBAND > 0)
		MultiBandBlender blender(MULTIBAND);
	else
		LinearBlender blender();
	
	// blender.add_image();
	// blender.run();

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
