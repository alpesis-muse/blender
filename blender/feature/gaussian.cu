#define tx threadIdx.x
#define ty threadIdx.y
#define bx blockIdx.x
#define by blockIdx.y
#define bdx blockDim.x
#define bdy blockDim.y

#define MAX_KSIZE_HALF 100

__constant__ float c_gKer[MAX_KSIZE_HALF+1];

__global__ void gaussian_blur_kernel (const int height,
                                      const int width,
                                      const int center,
                                      const T * src,
                                      const T * dst)
{
	const int y = by * bdy + ty;
	const int x = bx * bdx + tx;
	extern __shared__ float smem[];
	volatile float * row = smem + ty * (bdx + 2 * center);
	
	if (y < height)
	{
		for (int i = tx; i < bdx + 2 * center; i += bdx)
		{
			int x_ext = int(bx * bdx) + i - center;
			x_ext = b.idx_col(x_ext);
			row[i] = src(y, x_ext) * c_gKer[0];
			for (int j = 1; j <= center; ++j)
			{
				row[i] += (src(b.idx_row_low(y-j), x_ext) +
                                           src(b.idx_row_high(y+j), x_ext)) * c_gKer[j];
			}
		}

		if (x < width)
		{
			__syncthreads();
			// horizontal pass
			row += tx + center;
			float res = row[0] * c_gKer[0];
			for (int i = 1; i <= center; ++i)
			{
				res += (row[-i] + row[i]) * c_gKer[i];
			}
			dst(y, x) = res;
		}
	} 
}
