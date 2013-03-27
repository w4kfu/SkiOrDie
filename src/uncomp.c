#include "uncomp.h"

int uncomp(unsigned char *buf, unsigned char *buf_end, unsigned char *out_buf, unsigned char *out_buf_end)
{
	unsigned char text_buf[RING_SIZE + MATCH_LENGTH - 1];
	int  i, j, k, r, c;
	unsigned int  flags;

	memset(text_buf, 0x20, RING_SIZE - MATCH_LENGTH);
	r = RING_SIZE - MATCH_LENGTH;
	flags = 0;
	for (;;)
	{
		if (((flags >>= 1) & 256) == 0)
		{
			GET_BYTE(buf, buf_end, c);
			flags = c | 0xff00;
		}
		if (flags & 1)
		{
			GET_BYTE(buf, buf_end, c);
			PUT_BYTE(out_buf, out_buf_end, c);
			text_buf[r++] = c;
			r &= (RING_SIZE - 1);
		}
		else
		{
			GET_BYTE(buf, buf_end, i);
			GET_BYTE(buf, buf_end, j);
			i |= ((j & 0xf0) << 4);
			j = (j & 0x0f) + THRESHOLD;
			for (k = 0; k <= j; k++)
			{
				c = text_buf[(i + k) & (RING_SIZE - 1)];
				PUT_BYTE(out_buf, out_buf_end, c);
				text_buf[r++] = c;
				r &= (RING_SIZE - 1);
			}
		}
	}
	if (out_buf != out_buf_end)
	{
		fprintf(stderr, "[-] Data left ?\n");
		return 0;
	}
	return 1;
}

