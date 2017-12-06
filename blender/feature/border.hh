#ifndef BORDER_HH
#define BORDER_HH

/*
 *   image:
 *      0, 1, 2, 3
 *      4, 5, 6, 7
 * 
 *   image padded:
 *      0, 0, 0, 1, 2, 3, 3, 3,
 *      0, 0, 0, 1, 2, 3, 3, 3,
 *      0, 0, 0, 1, 2, 3, 3, 3,
 *      4, 4, 4, 5, 6, 7, 7, 7,
 *      4, 4, 4, 5, 6, 7, 7, 7,
 *      4, 4, 4, 5, 6, 7, 7, 7
 */
template <typename T>
void border_padding(T * h_img, const T * img, const int w, const int h, const int center)
{
	T * cur_line = (T*)malloc(sizeof(T)*w);
	T * h_img_index;
	memcpy(cur_line, img, sizeof(T)*w);
	for (int i = 0; i < center; ++i)
	{
		h_img_index = h_img + i * (w + 2 * center);
		for (int j = 0; j < center; ++j)
			*(h_img_index + j) = cur_line[0];
		memcpy(h_img_index + center, cur_line, sizeof(T)*w);
		for (int j = 0; j < center; ++j)
			*(h_img_index + center + w + j) = cur_line[w-1];
	}
	for (int i = 0; i < h; ++i)
	{
		h_img_index = h_img + (w + 2 * center) * center + i * (w + 2 * center);
		for (int j = 0; j < center; ++j)
			*(h_img_index + j) = *(img + i * w);
		memcpy(h_img_index + center, img + i * w, sizeof(T)*w);
		for (int j = 0; j < center; ++j)
			*(h_img_index + center + w +j) = *(img + i * w + w - 1);
	}
	for (int i = 0; i < center; ++i)
	{
		h_img_index = h_img + (w + 2 * center) * center + (w + 2 * center) * h + i * (w + 2 * center);
		for (int j = 0; j < center; ++j)
			*(h_img_index + j) = *(img + (h-1)*w);
		memcpy(h_img_index + center, img + (h-1)*w, sizeof(T)*w);
		for (int j = 0; j < center; ++j)
			*(h_img_index + center + w + j) = *(img + (h-1)*w + w - 1);
	}
}

#endif // BORDER_HH

