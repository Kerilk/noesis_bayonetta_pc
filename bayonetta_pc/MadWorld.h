#pragma once
typedef struct madWorldTPLHdr_s
{
	uint8_t				id[4];
	uint32_t            numImages;
	uint32_t            imageTableOffset;
} madWorldTPLHdr_t;

template <bool big>
struct madWorldTPLHdr : public madWorldTPLHdr_s {
	madWorldTPLHdr(madWorldTPLHdr_t *ptr) : madWorldTPLHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(*((int *)id));
			LITTLE_BIG_SWAP(numImages);
			LITTLE_BIG_SWAP(imageTableOffset);
		}
	}
};

typedef struct madWorldTPLRecord_s
{
	uint32_t			imageOffset;
	uint32_t			paletteOffset;
} madWorldTPLRecord_t;

template <bool big>
struct madWorldTPLRecord : public madWorldTPLRecord_s {
	madWorldTPLRecord(madWorldTPLRecord_t *ptr) : madWorldTPLRecord_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(imageOffset);
			LITTLE_BIG_SWAP(paletteOffset);
		}
	}
};

typedef struct madWorldTPLImage_s
{
	uint16_t		height;
	uint16_t		width;
	uint32_t		format;
	uint32_t		offset;
	uint32_t		wrapS;
	uint32_t		wrapT;
	uint32_t		minFilter;
	uint32_t		magFilter;
	float			LODBias;
	uint8_t			edgeLODEnable;
	uint8_t			minLOD;
	uint8_t			maxLOD;
	uint8_t			unpacked;
} madWorldTPLImage_t;

template <bool big>
struct madWorldTPLImage : public madWorldTPLImage_s {
	madWorldTPLImage(madWorldTPLImage_t * ptr) : madWorldTPLImage_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(height);
			LITTLE_BIG_SWAP(width);
			LITTLE_BIG_SWAP(format);
			LITTLE_BIG_SWAP(offset);
			LITTLE_BIG_SWAP(wrapS);
			LITTLE_BIG_SWAP(wrapT);
			LITTLE_BIG_SWAP(minFilter);
			LITTLE_BIG_SWAP(magFilter);
			LITTLE_BIG_SWAP(LODBias);
		}
	}
};

typedef struct madWorldTPLPalette_s {
	uint16_t	numEntries;
	uint8_t		unpacked;
	uint8_t		padding;
	uint32_t	format;
	uint32_t	offset;
} madWorldTPLPalette_t;

template <bool big>
struct madWorldTPLPalette : public madWorldTPLPalette_s {
	madWorldTPLPalette(madWorldTPLPalette_t * ptr) : madWorldTPLPalette_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(numEntries);
			LITTLE_BIG_SWAP(format);
			LITTLE_BIG_SWAP(offset);
		}
	}
};

template <>
static void Model_Bayo_LoadTextures<true, MADWORLD>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi) {
	const bool big = true;
	uint32_t dataSize = texFiles[0]->dataSize;
	BYTE * data = texFiles[0]->data;
	char texName[MAX_NOESIS_PATH];

	if (dataSize < sizeof(madWorldTPLHdr_t))
	{
		return;
	}

	madWorldTPLHdr<big> hdr((madWorldTPLHdr_t *)data);
	if (memcmp(hdr.id, "\x30\xAF\x20\x00", 4))
	{ //not a valid texture bundle
		return;
	}

	rapi->Noesis_GetExtensionlessName(texName, texFiles[0]->name);

	if (hdr.numImages < 0 || hdr.imageTableOffset > dataSize || dataSize < hdr.imageTableOffset + hdr.numImages * sizeof(madWorldTPLRecord_t))
	{ //not a valid texture bundle
		return;
	}

	for (uint32_t i = 0; i < hdr.numImages; i++) {
		madWorldTPLRecord<big> record((madWorldTPLRecord_t*)(data + hdr.imageTableOffset + i * sizeof(madWorldTPLRecord_t)));
		if (!record.imageOffset || record.imageOffset < dataSize)
			return;
		madWorldTPLImage<big> image((madWorldTPLImage_t *)(data + record.imageOffset));
		uint32_t height = image.height;
		uint32_t width = image.width;

		char fname[8192];
		rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());

		char nameStr[MAX_NOESIS_PATH];
		sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%s%s%03i", rapi->Noesis_GetOption("texpre"), texName, i);
		strcat_s(fname, MAX_NOESIS_PATH, nameStr);
		DBGLOG("%s: %d, format: %x, width: %d, height: %d\n", fname, i, image.format, image.width, image.height);

		BYTE *pix = (BYTE *)rapi->Noesis_PooledAlloc((width*height) * 4);

		if (record.paletteOffset) {
			madWorldTPLPalette<big> palette((madWorldTPLPalette_t *)(data + record.paletteOffset));
			tplDecodeImage(pix, data + image.offset, image.width, image.height, (tplFormats)image.format, (tplPaletteFormats)palette.format, data + palette.offset);
		}
		else {
			tplDecodeImage(pix, data + image.offset, image.width, image.height, (tplFormats)image.format);
		}
		noesisTex_t *nt = rapi->Noesis_TextureAlloc(fname, width, height, pix, NOESISTEX_RGBA32);
		nt->shouldFreeData = false;

		nt->globalIdx = -1;
		textures.Append(nt);
	}

	char fname[MAX_NOESIS_PATH];
	rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());
	char nameStr[MAX_NOESIS_PATH];
	sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%sbayoflatnormal", rapi->Noesis_GetOption("texpre"));
	strcat_s(fname, MAX_NOESIS_PATH, nameStr);
	noesisTex_t *nt = rapi->Noesis_AllocPlaceholderTex(fname, 32, 32, true);
	textures.Append(nt);
}