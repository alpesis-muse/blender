#include <algorithm>
#include <cmath>
#include "gaussian.hh"
#include "../config.hh"
#include "../utils/utils.hh"
#include "../utils/timer.hh"
using namespace std;


GaussCache::GaussCache(float sigma) {
	// TODO decide window size ?
	/*
	 *const int kw = round(GAUSS_WINDOW_FACTOR * sigma) + 1;
	 */
	kw = ceil(0.3 * (sigma / 2 - 1) + 0.8) * GAUSS_WINDOW_FACTOR;
	if (kw % 2 == 0) kw ++;
	kernel_buf.reset(new float[kw]);
	const int center = kw / 2;
	kernel = kernel_buf.get() + center;

	// calculate guassian for kernel[i]
	kernel[0] = 1;
	float exp_coeff = -1.0 / (sigma * sigma * 2),
				 wsum = 1;
	for (int i = 1; i <= center; i ++)
		wsum += (kernel[i] = exp(i * i * exp_coeff)) * 2;

	// calculate kernel[i] * fac = kernel[i] * 1/wsum 
	float fac = 1.0 / wsum;
	kernel[0] = fac;
	for (int i = 1; i <= center; i ++)
		kernel[-i] = (kernel[i] *= fac);
}
