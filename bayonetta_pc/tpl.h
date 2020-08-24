#pragma once
// Implements:
// http://wiki.tockdom.com/wiki/TPL_%28File_Format%29
// And:
// http://wiki.tockdom.com/wiki/Image_Formats
// With help from
// https://github.com/Zheneq/Noesis-Plugins/blob/master/lib_zq_nintendo_tex.py

typedef enum tplFormats_e {
	I4 = 0,
	I8,
	IA4,
	IA8,
	RGB565,
	RGB5A3,
	RGBA32,
	C4 = 8,
	C8,
	C14X2,
	CMPR = 0xE //BC1
} tplFormats;

typedef enum tplPaletteFormats_e {
	PIA8 = 0,
	PRGB565,
	PRGB5A3
} tplPaletteFormats;

static constexpr tplFormats tplPaletteFormatTable[] = {
	IA8,
	RGB565,
	RGB5A3
};

static constexpr int tplBPP[] = {
	 4,
	 8,
	 8,
	16,
	16,
	16,
	32,
	-1,
	 4,
	 8,
	16,
	-1,
	-1,
	-1,
	 4
};

static constexpr int tplBlockWidth[] = {
	 8,
	 8,
	 8,
	 4,
	 4,
	 4,
	 4,
	-1,
	 8,
	 8,
	 4,
	-1,
	-1,
	-1,
	 8
};

static constexpr int tplBlockHeight[] = {
	 8,
	 4,
	 4,
	 4,
	 4,
	 4,
	 4,
	-1,
	 8,
	 4,
	 4,
	-1,
	-1,
	-1,
	 8,
};

static constexpr int tplBlockSize[] = {
	32,
	32,
	32,
	32,
	32,
	32,
	64,
	-1,
	32,
	32,
	32,
	-1,
	-1,
	-1,
	32
};

template<int bpp, int blockWidth>
inline void tplComputePixelAddress(void * &pPixel, void * src, unsigned int i, unsigned int j) {
	unsigned int offset;
	if (bpp == 4)
		offset = i * (blockWidth >> 1) + (j >> 1);
	else
		offset = i * blockWidth * (bpp / 8) + j * (bpp / 8);
	pPixel = (void*)((BYTE*)src + offset);
}

template<int bpp>
inline void tplExtractPixelBits(unsigned int &v, void *src, bool even = true) {
	unsigned char  tuc;
	unsigned short tus;
	unsigned int   tui;
	switch (bpp) {
	case 32:
		tui = *(unsigned int *)src;
		LITTLE_BIG_SWAP(tui);
		v = tui;
		break;
	case 16:
		tus = *(unsigned short *)src;
		LITTLE_BIG_SWAP(tus);
		v = tus;
		break;
	case 8:
		tuc = *(unsigned char *)src;
		v = tuc;
		break;
	case 4:
		tuc = *(unsigned char *)src;
		if (even)
			tuc >>= 4;
		v = tuc & 0xf;
		break;
	}
}

template <tplFormats f>
inline void tplReadPixelValue(unsigned int v, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a);

template <>
inline void tplReadPixelValue<I4>(unsigned int v, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a) {
	r = g = b = v * 0xff / 0xf;;
	a = 0xff;
}

template <>
inline void tplReadPixelValue<I8>(unsigned int v, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a) {
	r = g = b = v;
	a = 0xff;
}

template <>
inline void tplReadPixelValue<IA4>(unsigned int v, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a) {
	r = g = b = (v & 0xf) * 0xff / 0xf;
	a = (v >> 4) * 0xff / 0xf;
}

template <>
inline void tplReadPixelValue<IA8>(unsigned int v, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a) {
	r = g = b = v & 0xff;
	a = v >> 8;
}

template <>
inline void tplReadPixelValue<RGB565>(unsigned int v, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a) {
	r = ((v >> 11) & 0x1f) * 0xff / 0x1f;
	g = ((v >>  5) & 0x3f) * 0xff / 0x3f;
	b = ((v >>  0) & 0x1f) * 0xff / 0x1f;
	a = 0xff;
}

template <>
inline void tplReadPixelValue<RGB5A3>(unsigned int v, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a) {
	if (v & 0x8000) {
		r = ((v >> 10) & 0x1f) * 0xff / 0x1f;
		g = ((v >>  5) & 0x1f) * 0xff / 0x1f;
		b = ((v >>  0) & 0x1f) * 0xff / 0x1f;
		a = 0xff;
	}
	else {
		a = ((v >> 12) & 0x7) * 0xff / 0x7; //contradictory information between sources here
		r = ((v >>  8) & 0xf) * 0xff / 0xf;
		g = ((v >>  4) & 0xf) * 0xff / 0xf;
		b = ((v >>  0) & 0xf) * 0xff / 0xf;
	}
}

template <tplFormats f>
inline void tplDecodePixel(void *src, unsigned int i, unsigned int j, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a) {
	void *d;
	unsigned int v;
	tplComputePixelAddress<tplBPP[f], tplBlockWidth[f]>(d, src, i, j);
	tplExtractPixelBits<tplBPP[f]>(v, d, !(j & 0x1));
	tplReadPixelValue<f>(v, r, g, b, a);
}

template <>
inline void tplDecodePixel<RGBA32>(void *src, unsigned int i, unsigned int j, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a) {
	unsigned char *ar = (unsigned char *)src +      i * 8 + j * 2;
	unsigned char *gb = (unsigned char *)src + 32 + i * 8 + j * 2;
	a = ar[0];
	r = ar[1];
	g = gb[0];
	b = gb[1];
}

void tplWritePixel(void *dst, unsigned int i, unsigned int j, size_t ld, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	unsigned char *p = (unsigned char *)dst + i * ld + j * 4;
	p[0] = r;
	p[1] = g;
	p[2] = b;
	p[3] = a;
}

template <tplFormats f>
void tplDecodeBlock(void *dst, void *src, unsigned height, unsigned int width, size_t ld) {
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			unsigned char r, g, b, a;
			//DBGLOG("Decoding pixel %i %i, ", i, j);
			tplDecodePixel<f>(src, i, j, r, g, b, a);
			//DBGLOG("r: %02x, g: %02x, b: %02x, a: %02x\n", r, g, b, a);
			tplWritePixel(dst, i, j, ld, r, g, b, a);
		}
	}
}

template <tplFormats f>
inline void tplDecodePaletteIndex(unsigned int &v, void *src, unsigned int i, unsigned int j) {
	void *d;
	tplComputePixelAddress<tplBPP[f], tplBlockWidth[f]>(d, src, i, j);
	//DBGLOG("\t\t\t%p\n", d);
	tplExtractPixelBits<tplBPP[f]>(v, d, !(j & 0x1));
}

inline void tplReadPaletteValue(unsigned int &v, void *palette, unsigned int index) {
	unsigned short int t = *((unsigned short int *)palette + index);
	LITTLE_BIG_SWAP(t);
	v = t;
}

template <tplFormats f, tplPaletteFormats pf>
inline void tplDecodePalettePixel(void *src, void *palette, unsigned int i, unsigned int j, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a) {
	unsigned int v;
	tplDecodePaletteIndex<f>(v, src, i, j);
	//DBGLOG("\t\t\t%d %d: %d\n", i, j, v);
	tplReadPaletteValue(v, palette, v);
	tplReadPixelValue<tplPaletteFormatTable[pf]>(v, r, g, b, a);
}

template <tplFormats f, tplPaletteFormats pf>
void tplDecodePaletteBlock(void *dst, void *src, void *palette, unsigned int height, unsigned int width, size_t ld) {
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			unsigned char r, g, b, a;
			tplDecodePalettePixel<f, pf>(src, palette, i, j, r, g, b, a);
			tplWritePixel(dst, i, j, ld, r, g, b, a);
		}
	}
}

inline void tplDecodeCMPRSubBlock(void *dst, void *src) {
	unsigned short c0 = *((unsigned short *)src + 0);
	unsigned short c1 = *((unsigned short *)src + 1);
	LITTLE_BIG_SWAP(c0);
	LITTLE_BIG_SWAP(c1);
	unsigned char vc[4][4];
	tplReadPixelValue<RGB565>((unsigned int)c0, vc[0][0], vc[0][1], vc[0][2], vc[0][3]);
	tplReadPixelValue<RGB565>((unsigned int)c1, vc[1][0], vc[1][1], vc[1][2], vc[1][3]);
	if (c0 > c1) {
		for (int i = 0; i < 4; i++) {
			vc[2][i] = ((int)vc[1][i] + 2 * vc[0][i]) / 3;
			vc[3][i] = ((int)vc[0][i] + 2 * vc[1][i]) / 3;
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			vc[2][i] = ((int)vc[0][i] + vc[1][i]) / 2;
			vc[3][i] = 0;
		}
	}
	for (int i = 0; i < 4; i++) {
		unsigned char v = *((unsigned char *)src + 4 + i);
		for (int j = 0; j < 4; j++) {
			unsigned char indx = (v >> (6 - 2 * j)) & 0x3;
			memcpy((char*)dst + 8 * 4 * i + 4 * j, &(vc[indx][0]), 4);
		}
	}
}

template <>
inline void tplDecodeBlock<CMPR>(void *dst, void *src, unsigned int height, unsigned int width, size_t ld) {
	unsigned char buff[8][8][4];
	tplDecodeCMPRSubBlock(&(buff[0][0][0]), (unsigned char *)src);
	tplDecodeCMPRSubBlock(&(buff[0][4][0]), (unsigned char *)src + 8);
	tplDecodeCMPRSubBlock(&(buff[4][0][0]), (unsigned char *)src + 16);
	tplDecodeCMPRSubBlock(&(buff[4][4][0]), (unsigned char *)src + 24);
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			tplWritePixel(dst, i, j, ld, buff[i][j][0], buff[i][j][1], buff[i][j][2], buff[i][j][3]);
		}
	}
}

void tplDecodeImage(void *dst, void *src, unsigned int width, unsigned int height, tplFormats f, tplPaletteFormats pf = PIA8, void *palette = NULL) {
	unsigned int block_width = tplBlockWidth[f];
	unsigned int block_height = tplBlockHeight[f];
	unsigned int remainder_width = width % block_width;
	unsigned int remainder_height = height % block_height;
	unsigned int n_block_width = (width + (remainder_width ? block_width - remainder_width : 0)) / block_width;
	unsigned int n_block_height = (height + (remainder_height ? block_height - remainder_height : 0)) / block_height;
	unsigned int last_block_width = remainder_width ? remainder_width : block_width;
	unsigned int last_block_height = remainder_height ? remainder_height : block_height;
	//DBGLOG("dst: %p, src: %p, format: %d, palette: %p, block_height: %d, block_width: %d, n_block_height: %d, n_block_width: %d, remainder_height: %d, remainder_width: %d\n", dst, src, f, palette, block_height, block_width, n_block_height, n_block_width, remainder_height, remainder_width);
	size_t ld = 4 * width;
	for (unsigned int i = 0; i < n_block_height; i++) {
		for (unsigned int j = 0; j < n_block_width; j++) {
			unsigned char *pdst = (unsigned char *)dst + i * block_height * ld + j * block_width * 4;
			unsigned char *psrc = (unsigned char *)src + tplBlockSize[f] * (j + n_block_width * i);
			unsigned int bh = (i == n_block_height - 1 ? last_block_height : block_height);
			unsigned int bw = (j == n_block_width - 1 ? last_block_width : block_width);
			//DBGLOG("Decoding block %d %d, pdst: %p, psrc: %p, block_height: %d, block_width: %d, ld: %d\n", i, j, pdst, psrc, bh, bw, ld);
			switch (f) {
			case I4:
				tplDecodeBlock<I4>(pdst, psrc, bh, bw, ld);
				break;
			case I8:
				tplDecodeBlock<I8>(pdst, psrc, bh, bw, ld);
				break;
			case IA4:
				tplDecodeBlock<IA4>(pdst, psrc, bh, bw, ld);
				break;
			case IA8:
				tplDecodeBlock<IA8>(pdst, psrc, bh, bw, ld);
				break;
			case RGB565:
				tplDecodeBlock<RGB565>(pdst, psrc, bh, bw, ld);
				break;
			case RGB5A3:
				tplDecodeBlock<RGB5A3>(pdst, psrc, bh, bw, ld);
				break;
			case RGBA32:
				tplDecodeBlock<RGBA32>(pdst, psrc, bh, bw, ld);
				break;
			case CMPR:
				tplDecodeBlock<CMPR>(pdst, psrc, bh, bw, ld);
				break;
			case C4:
				switch (pf) {
				case PIA8:
					tplDecodePaletteBlock<C4, PIA8>(pdst, psrc, palette, bh, bw, ld);
					break;
				case PRGB565:
					tplDecodePaletteBlock<C4, PRGB565>(pdst, psrc, palette, bh, bw, ld);
					break;
				case PRGB5A3:
					tplDecodePaletteBlock<C4, PRGB5A3>(pdst, psrc, palette, bh, bw, ld);
					break;
				}
				break;
			case C8:
				switch (pf) {
				case PIA8:
					tplDecodePaletteBlock<C8, PIA8>(pdst, psrc, palette, bh, bw, ld);
					break;
				case PRGB565:
					tplDecodePaletteBlock<C8, PRGB565>(pdst, psrc, palette, bh, bw, ld);
					break;
				case PRGB5A3:
					tplDecodePaletteBlock<C8, PRGB5A3>(pdst, psrc, palette, bh, bw, ld);
					break;
				}
				break;
			case C14X2:
				switch (pf) {
				case PIA8:
					tplDecodePaletteBlock<C14X2, PIA8>(pdst, psrc, palette, bh, bw, ld);
					break;
				case PRGB565:
					tplDecodePaletteBlock<C14X2, PRGB565>(pdst, psrc, palette, bh, bw, ld);
					break;
				case PRGB5A3:
					tplDecodePaletteBlock<C14X2, PRGB5A3>(pdst, psrc, palette, bh, bw, ld);
					break;
				}
				break;
			}
		}
	}
}