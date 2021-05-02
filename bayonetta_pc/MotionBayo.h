#pragma once
typedef struct bayoEXPHdr_s
{
	BYTE				id[4];
	int					unknownA;
	unsigned int		offsetRecords;
	unsigned int		numRecords;
} bayoEXPHdr_t;
template <bool big>
struct bayoEXPHdr : public bayoEXPHdr_s
{
	bayoEXPHdr(bayoEXPHdr_t *ptr) : bayoEXPHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(offsetRecords);
			LITTLE_BIG_SWAP(numRecords);
		}
	}
};

typedef struct bayoEXPRecord_s
{
	short int			flags;
	short int			boneIndex;
	char				animationTrack;
	char				entryCount;
	char				interpolationEntryCount;
	char				interpolationType;
	short int			numPoints;
	short int			unknownC;
	unsigned int		offset;
	unsigned int		offsetInterpolation;
} bayoEXPRecord_t;
template <bool big>
struct bayoEXPRecord : public bayoEXPRecord_s
{
	bayoEXPRecord(bayoEXPRecord_t * ptr) : bayoEXPRecord_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(flags);
			LITTLE_BIG_SWAP(boneIndex);
			LITTLE_BIG_SWAP(numPoints);
			LITTLE_BIG_SWAP(unknownC);
			LITTLE_BIG_SWAP(offset);
			LITTLE_BIG_SWAP(offsetInterpolation);
		}
	}
};

typedef struct bayoEXPInterpolationPoint2_s {
	float value;
	float p;
	float m0;
	float m1;
}bayoEXPInterpolationPoint2_t;
template <bool big>
struct bayoEXPInterpolationPoint2 : public bayoEXPInterpolationPoint2_s
{
	bayoEXPInterpolationPoint2(bayoEXPInterpolationPoint2_t * ptr) : bayoEXPInterpolationPoint2_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(value);
			LITTLE_BIG_SWAP(p);
			LITTLE_BIG_SWAP(m0);
			LITTLE_BIG_SWAP(m1);
		}
	}
};
typedef struct bayoEXPInterpolationData4_s
{
	float p;
	float dp;
	float m0;
	float dm0;
	float m1;
	float dm1;
} bayoEXPInterpolationData4_t;
template <bool big>
struct bayoEXPInterpolationData4 : public bayoEXPInterpolationData4_s
{
	bayoEXPInterpolationData4(bayoEXPInterpolationData4_t * ptr) : bayoEXPInterpolationData4_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(p);
			LITTLE_BIG_SWAP(dp);
			LITTLE_BIG_SWAP(m0);
			LITTLE_BIG_SWAP(dm0);
			LITTLE_BIG_SWAP(m1);
			LITTLE_BIG_SWAP(dm1);
		}
	}
};
typedef struct bayoEXPInterpolationPoint4_s {
	float			v;
	unsigned short	dummy;
	unsigned short	cp;
	unsigned short	cm0;
	unsigned short	cm1;
} bayoEXPInterpolationPoint4_t;
template <bool big>
struct bayoEXPInterpolationPoint4 : public bayoEXPInterpolationPoint4_s
{
	bayoEXPInterpolationPoint4(bayoEXPInterpolationPoint4_t * ptr) : bayoEXPInterpolationPoint4_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(v);
			LITTLE_BIG_SWAP(dummy);
			LITTLE_BIG_SWAP(cp);
			LITTLE_BIG_SWAP(cm0);
			LITTLE_BIG_SWAP(cm1);
		}
	}
};
typedef short unsigned int pghalf;
typedef struct bayoEXPInterpolationData6_s
{
	pghalf p;
	pghalf dp;
	pghalf m0;
	pghalf dm0;
	pghalf m1;
	pghalf dm1;
} bayoEXPInterpolationData6_t;
template <bool big>
struct bayoEXPInterpolationData6 : public bayoEXPInterpolationData6_s
{
	bayoEXPInterpolationData6(bayoEXPInterpolationData6_t * ptr) : bayoEXPInterpolationData6_s(*ptr) {
	}
};
typedef struct bayoEXPInterpolationPoint6_s {
	unsigned char	v;
	unsigned char	cp;
	unsigned char	cm0;
	unsigned char	cm1;
} bayoEXPInterpolationPoint6_t;
template <bool big>
struct bayoEXPInterpolationPoint6 : public bayoEXPInterpolationPoint6_s
{
	bayoEXPInterpolationPoint6(bayoEXPInterpolationPoint6_t * ptr) : bayoEXPInterpolationPoint6_s(*ptr) {
	}
};

typedef struct bayoExpEntryBoneTrackInfo_s {
	short int			boneIndex;
	char				animationTrack;
	char				padding;
} bayoExpEntryBoneTrackInfo_t;
typedef union bayoExpEntryUnion_u {
	float value;
	bayoExpEntryBoneTrackInfo_t boneTrackInfo;
} bayoExpEntryUnion_t;
typedef struct bayoEXPEntry_s
{
	unsigned int		flags;
	bayoExpEntryUnion_t entryUnion;
} bayoEXPEntry_t;
template <bool big>
struct bayoEXPEntry : public bayoEXPEntry_s
{
	bayoEXPEntry(bayoEXPEntry_t*ptr) : bayoEXPEntry_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(flags);
			if (flags & 0x80000000) {
				LITTLE_BIG_SWAP(entryUnion.boneTrackInfo.boneIndex);
			}
			else {
				LITTLE_BIG_SWAP(entryUnion.value);
			}
		}
	}
};
typedef struct bayoMOTHdr_s
{
	BYTE				id[4];
	short int			unknownA;
	short int			frameCount;
	int					ofsMotion;
	int					numEntries;
} bayoMOTHdr_t;
template <bool big>
struct bayoMOTHdr : public bayoMOTHdr_s {
	bayoMOTHdr(bayoMOTHdr_t *ptr) : bayoMOTHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(frameCount);
			LITTLE_BIG_SWAP(ofsMotion);
			LITTLE_BIG_SWAP(numEntries);
		}
	}
};

typedef union bayoMotField_u
{
	float flt;
	int offset;
} bayoMotField_t;
typedef struct bayoMotItem_s
{
	short int			boneIndex;
	char				index;
	BYTE				flag;
	short int			elem_number;
	short int			unknown;
	bayoMotField_t		value;
} bayoMotItem_t;
template <bool big>
struct bayoMotItem : public bayoMotItem_s {
	bayoMotItem(bayoMotItem_t *ptr) : bayoMotItem_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(boneIndex);
			LITTLE_BIG_SWAP(index);
			LITTLE_BIG_SWAP(flag);
			LITTLE_BIG_SWAP(elem_number);
			LITTLE_BIG_SWAP(unknown);
			LITTLE_BIG_SWAP(value);
		}
	}
};

typedef struct bayoInterpolHeader4_s {
	float values[6];
} bayoInterpolHeader4_t;
typedef struct bayoInterpolKeyframe4_s {
	unsigned short int index;
	unsigned short int coeffs[3];
} bayoInterpolKeyframe4_t;
template <bool big>
struct bayoInterpolKeyframe4 : public bayoInterpolKeyframe4_s {
	bayoInterpolKeyframe4(bayoInterpolKeyframe4_t *ptr) : bayoInterpolKeyframe4_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(index);
			for (int i = 0; i < 3; i++) LITTLE_BIG_SWAP(coeffs[i]);
		}
	}
};
typedef struct bayoInterpolHeader6_s {
	pghalf values[6];
} bayoInterpolHeader6_t;
typedef struct bayoInterpolKeyframe6_s {
	BYTE index;
	BYTE coeffs[3];
} bayoInterpolKeyframe6_t;
template <bool big>
struct bayoInterpolKeyframe6 : public bayoInterpolKeyframe6_s {
	bayoInterpolKeyframe6(bayoInterpolKeyframe6_t *ptr) : bayoInterpolKeyframe6_s(*ptr) {
	}
};
typedef struct bayoInterpolHeader7_s {
	pghalf values[6];
} bayoInterpolHeader7_t;
typedef struct bayoInterpolKeyframe7_s {
	unsigned short int index;
	BYTE dummy;
	BYTE coeffs[3];
} bayoInterpolKeyframe7_t;
template <bool big>
struct bayoInterpolKeyframe7 : public bayoInterpolKeyframe7_s {
	bayoInterpolKeyframe7(bayoInterpolKeyframe7_t *ptr) : bayoInterpolKeyframe7_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(index);
		}
	}
};
typedef struct bayoInterpolHeader8_s {
	pghalf values[6];
} bayoInterpolHeader8_t;
typedef struct bayoInterpolKeyframe8_s {
	unsigned short int index;
	BYTE coeffs[3];
} bayoInterpolKeyframe8_t;
template <bool big>
struct bayoInterpolKeyframe8 : public bayoInterpolKeyframe8_s {
	bayoInterpolKeyframe8(bayoInterpolKeyframe8_t *ptr) : bayoInterpolKeyframe8_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(index);
		}
		else {
			LITTLE_BIG_SWAP(index);
		}
	}
};

//decode motion index (simpler thanks to Alquazar(zenhax))
template <bool big, game_t game>
static inline short int Model_Bayo_DecodeMotionIndex(const short int *table, const short int boneIndex);
template <bool big, game_t game>
static inline short int Model_Bayo_DecodeMotionIndex(const short int *table, const short int boneIndex) {
	short int index = table[(boneIndex >> 8) & 0xf];
	if (big) LITTLE_BIG_SWAP(index);
	if (index != -1) {
		index = table[((boneIndex >> 4) & 0xf) + index];
		if (big) LITTLE_BIG_SWAP(index);
		if (index != -1) {
			index = table[(boneIndex & 0xf) + index];
			if (big) LITTLE_BIG_SWAP(index);
			return index;
		}
	}
	return 0x0fff;
}

template <>
static inline short int Model_Bayo_DecodeMotionIndex<true, MADWORLD>(const short int *table, const short int boneIndex) {
	const bool big = true;
	if (boneIndex > 0xff)
		return 0x0fff;
	short int index = table[boneIndex & 0xff];
	if (index == -1)
		return 0x0fff;
	return index;
}

//initialize motion matrix
template <bool big, game_t game>
static void Model_Bayo_InitMotions(modelMatrix_t * &matrixes, float * &tmpValues, float * &tmpCumulScale, modelBone_t *bones, const int boneNumber, const short int frameCount, noeRAPI_t *rapi, void * extraBoneInfo) {
	const int maxCoeffs = 16;
	matrixes = (modelMatrix_t *)rapi->Noesis_UnpooledAlloc(sizeof(modelMatrix_t) * (boneNumber + 1) * frameCount);
	tmpValues = (float *)rapi->Noesis_UnpooledAlloc(sizeof(float) * (boneNumber + 1) * frameCount * maxCoeffs);
	tmpCumulScale = (float *)rapi->Noesis_UnpooledAlloc(sizeof(float) * (boneNumber + 1) * frameCount * 3);
	memset(tmpValues, 0, sizeof(float) * (boneNumber + 1) * frameCount * maxCoeffs);

	for (int i = 0; i < boneNumber; i++) {
		float translate[3] = { 0.0, 0.0, 0.0 };
		float rotate[3] = { 0.0, 0.0, 0.0 };
		float scale[3] = { 1.0, 1.0, 1.0 };
		if (game == NIER_AUTOMATA || game == ASTRAL_CHAIN) {
			nierBone<big> nBone((nierBone_t *)((BYTE*)extraBoneInfo + i * sizeof(nierBone_t)));
			translate[0] = nBone.localPosition.x;
			translate[1] = nBone.localPosition.y;
			translate[2] = nBone.localPosition.z;
			rotate[0] = nBone.localRotation.x;
			rotate[1] = nBone.localRotation.y;
			rotate[2] = nBone.localRotation.z;
			scale[0] = nBone.localScale.x;
			scale[1] = nBone.localScale.y;
			scale[2] = nBone.localScale.z;
			if (big) {
				for (int k = 0; k < 3; k++) {
					LITTLE_BIG_SWAP(translate[k]);
					LITTLE_BIG_SWAP(rotate[k]);
					LITTLE_BIG_SWAP(scale[k]);
				}
			}
		}
		else if (game == MGRR || game == TD) {
			MGRRBone<big> mBone((MGRRBone_t *)((BYTE*)extraBoneInfo + i * sizeof(MGRRBone_t)));
			translate[0] = mBone.relativePosition[0];
			translate[1] = mBone.relativePosition[1];
			translate[2] = mBone.relativePosition[2];
			if (big) {
				for (int k = 0; k < 3; k++) {
					LITTLE_BIG_SWAP(translate[k]);
				}
			}
		}
		else {
			float *relativePos = (float *)extraBoneInfo;
			for (int k = 0; k < 3; k++) {
				translate[k] = relativePos[k + i * 3];
				if (big) {
					LITTLE_BIG_SWAP(translate[k]);
				}
			}
		}
		for (int j = 0; j < frameCount; j++) {
			matrixes[i + j * (boneNumber + 1)] = g_identityMatrix;
			for (int k = 0; k < 3; k++) {
				tmpValues[j + k * frameCount + i * frameCount * maxCoeffs] = translate[k];
			}
			for (int k = 3, l = 0; k < 6; k++, l++) {
				tmpValues[j + k * frameCount + i * frameCount * maxCoeffs] = rotate[l];
			}
			for (int k = 7, l = 0; k < 10; k++, l++) {
				tmpValues[j + k * frameCount + i * frameCount * maxCoeffs] = scale[l];
			}
			for (int k = 0; k < 3; k++) {
				tmpCumulScale[j + k * frameCount + i * frameCount * 3] = 1.0f;
			}
			//g_mfn->Math_TranslateMatrix(&matrixes[i + j*bone_number], bones[i].mat.o);
			//float zero[3] = {0.0f, 0.0f, 0.0f};
			//g_mfn->Math_RotationMatrix(0.0, 0, &matrixes[i + j*bone_number]);
		}
	}
	// bone -1
	for (int j = 0; j < frameCount; j++) {
		matrixes[boneNumber + j * (boneNumber + 1)] = g_identityMatrix;
		for (int k = 0; k < 3; k++) {
			tmpCumulScale[j + k * frameCount + boneNumber * frameCount * 3] = 1.0f;
		}
		for (int k = 7, l = 0; k < 10; k++, l++) {
			tmpValues[j + k * frameCount + boneNumber * frameCount * maxCoeffs] = 1.0f;
		}
	}
}
template <bool big>
static float Model_Bayo_Interpolate2EXP_Value(float value, BYTE *interpol, short int numPoints) {
	BYTE *data = interpol;
	float outValue = 0.0;
	if (numPoints == 1) {
		bayoEXPInterpolationPoint2<big> point((bayoEXPInterpolationPoint2_t *)(data));
		outValue = point.value;
		return outValue;
	}
	for (int i = 0; i < numPoints - 1; i++) {
		bayoEXPInterpolationPoint2<big> leftPoint((bayoEXPInterpolationPoint2_t *)(data + i * sizeof(bayoEXPInterpolationPoint2_t)));
		bayoEXPInterpolationPoint2<big> rightPoint((bayoEXPInterpolationPoint2_t *)(data + (i + 1) * sizeof(bayoEXPInterpolationPoint2_t)));
		if (value <= leftPoint.value) {
			outValue = leftPoint.value;
			return outValue;
		}
		if (leftPoint.value < value && rightPoint.value > value) {
			float p0, p1, m0, m1;
			float t;
			p0 = leftPoint.p;
			p1 = rightPoint.p;
			m0 = leftPoint.m1;
			m1 = rightPoint.m0;
			t = (value - leftPoint.value) / (rightPoint.value - leftPoint.value);
			outValue = (2 * t*t*t - 3 * t*t + 1)*p0 + (t*t*t - 2 * t*t + t)*m0 + (-2 * t*t*t + 3 * t*t)*p1 + (t*t*t - t * t)*m1;
			return outValue;
		}
		if (value >= rightPoint.value) {
			outValue = rightPoint.value;
		}
	}
	return outValue;
}
template <bool big>
static float Model_Bayo_Interpolate4EXP_Value(float value, BYTE *interpol, short int numPoints) {
	BYTE *data = interpol;
	bayoEXPInterpolationData4<big> interpolData((bayoEXPInterpolationData4_t *)data);
	float outValue = 0.0;
	data += sizeof(bayoEXPInterpolationData4_t);
	if (numPoints == 1) {
		bayoEXPInterpolationPoint4<big> point((bayoEXPInterpolationPoint4_t *)(data));
		outValue = interpolData.p + point.cp * interpolData.dp;
		return outValue;
	}
	for (int i = 0; i < numPoints - 1; i++) {
		bayoEXPInterpolationPoint4<big> leftPoint((bayoEXPInterpolationPoint4_t *)(data + i * sizeof(bayoEXPInterpolationPoint4_t)));
		bayoEXPInterpolationPoint4<big> rightPoint((bayoEXPInterpolationPoint4_t *)(data + (i + 1) * sizeof(bayoEXPInterpolationPoint4_t)));
		if (value <= leftPoint.v) {
			outValue = interpolData.p + leftPoint.cp * interpolData.dp;
			return outValue;
		}
		if (leftPoint.v < value && rightPoint.v > value) {
			float p0, p1, m0, m1;
			float t;
			p0 = interpolData.p + leftPoint.cp * interpolData.dp;
			p1 = interpolData.p + rightPoint.cp * interpolData.dp;
			m0 = interpolData.m1 + leftPoint.cm1 * interpolData.dm1;
			m1 = interpolData.m0 + rightPoint.cm0 * interpolData.dm0;
			t = (value - leftPoint.v) / (rightPoint.v - leftPoint.v);
			outValue = (2 * t*t*t - 3 * t*t + 1)*p0 + (t*t*t - 2 * t*t + t)*m0 + (-2 * t*t*t + 3 * t*t)*p1 + (t*t*t - t * t)*m1;
			return outValue;
		}
		if (value >= rightPoint.v) {
			outValue = interpolData.p + rightPoint.cp * interpolData.dp;
		}
	}
	return outValue;
}
template <bool big>
static float Model_Bayo_Interpolate6EXP_Value(float value, BYTE *interpol, short int numPoints) {
	BYTE *data = interpol;
	bayoEXPInterpolationData6<big> interpolData((bayoEXPInterpolationData6_t *)data);
	float p = C.decompress(interpolData.p, big);
	float dp = C.decompress(interpolData.dp, big);
	float m_1 = C.decompress(interpolData.m1, big);
	float dm_1 = C.decompress(interpolData.dm1, big);
	float m_0 = C.decompress(interpolData.m0, big);
	float dm_0 = C.decompress(interpolData.dm0, big);
	float outValue = 0.0;
	float pointValue = 0.0;
	data += sizeof(bayoEXPInterpolationData6_t);
	if (numPoints == 1) {
		bayoEXPInterpolationPoint6<big> point((bayoEXPInterpolationPoint6_t *)(data));
		outValue = p + point.cp * dp;
		return outValue;
	}
	for (int i = 0; i < numPoints - 1; i++) {
		bayoEXPInterpolationPoint6<big> leftPoint((bayoEXPInterpolationPoint6_t *)(data + i * sizeof(bayoEXPInterpolationPoint6_t)));
		bayoEXPInterpolationPoint6<big> rightPoint((bayoEXPInterpolationPoint6_t *)(data + (i + 1) * sizeof(bayoEXPInterpolationPoint6_t)));
		pointValue = pointValue + leftPoint.v;
		if (value <= pointValue) {
			outValue = p + leftPoint.cp * dp;
			return outValue;
		}
		if (pointValue < value && (pointValue + rightPoint.v) > value) {
			float p0, p1, m0, m1;
			float t;
			p0 = p + leftPoint.cp * dp;
			p1 = p + rightPoint.cp * dp;
			m0 = m_1 + leftPoint.cm1 * dm_1;
			m1 = m_0 + rightPoint.cm0 * dm_0;
			t = (value - pointValue) / (rightPoint.v);
			outValue = (2 * t*t*t - 3 * t*t + 1)*p0 + (t*t*t - 2 * t*t + t)*m0 + (-2 * t*t*t + 3 * t*t)*p1 + (t*t*t - t * t)*m1;
			return outValue;
		}
		if (value >= (pointValue + rightPoint.v)) {
			outValue = p + rightPoint.cp * dp;
		}
	}
	return outValue;
}

struct expState_s {
	unsigned int flags;
	float fArray[4];
	int iArray[4];
	char fCount;
	char iCount;
	short unknown;
};

static void init_expState(struct expState_s &expState) {
	expState.flags = 0;
	expState.fCount = 0;
	expState.iCount = 0;
	expState.unknown = 0;
	for (int i = 0; i < 4; i++) {
		expState.fArray[i] = 0.0;
		expState.iArray[i] = 0;
	}
}

template <bool big>
static float getExpEntryValue(bayoEXPEntry<big> &entry, int fi, float * tmpValues, const short int frameCount, short int * animBoneTT) {
	static int maxCoeffs = 16;
	if (entry.flags & 0x80000000) {
		short int sourceBone;
		char sourceTrack;
		sourceBone = Model_Bayo_DecodeMotionIndex<big, BAYONETTA>(animBoneTT, entry.entryUnion.boneTrackInfo.boneIndex);
		sourceTrack = entry.entryUnion.boneTrackInfo.animationTrack;
		if (fi == 0) {
			DBGLOG("\t\t\t\t\tsrcBone: %d\n", sourceBone);
			DBGLOG("\t\t\t\t\tsrcTrack: %d\n", sourceTrack);
		}
		return  tmpValues[fi + sourceTrack * frameCount + sourceBone * frameCount * maxCoeffs];
	}
	else {
		return entry.entryUnion.value;
	}
}

template <bool big>
static float modifyExpEntryValue(struct expState_s &expState, float value, int fi) {
	expState.iCount--;
	int flags = expState.iArray[expState.iCount] & 0xFF00;
	if (fi == 0)
		DBGLOG("\t\t\t\t\tflags: %x\n", flags);
	if (flags) {
		if (flags & 0x100) {
			value = fabsf(value);
		}
		else if (flags & 0x200) {
			value = ceilf(value);
		}
		else if (flags & 0x400) {
			value = floorf(value);
		}
		else if (flags & 0x800) {
			value = roundf(value);
		}
	}
	expState.fArray[expState.fCount] = value;
	int fCount = expState.fCount;
	int iCount = expState.iCount;

	expState.fCount = expState.iCount;

	value = expState.fArray[iCount];
	if (fCount > iCount) {
		do {
			flags = expState.iArray[iCount];
			float tmp = expState.fArray[iCount + 1];
			if (flags & 1) {
				value += tmp;
			}
			else if (flags & 2) {
				value -= tmp;
			}
			else if (flags & 4) {
				value *= tmp;
			}
			else if ((flags & 8) && tmp != 0.0f) {
				value /= tmp;
			}
			iCount++;
		} while (fCount > iCount);
	}
	return value;
}

template <bool big>
static float applyExpEntry(struct expState_s &expState, bayoEXPEntry<big> &entry, int fi, float value, float * tmpValues, const short int frameCount, short int * animBoneTT) {
	if (fi == 0)
		DBGLOG("\t\t\tentry flags: %x\n", entry.flags);
	if (entry.flags & 0x1FF00) {
		if (fi == 0)
			DBGLOG("\t\t\t\tspecial:\n");
		unsigned int flags = entry.flags;
		unsigned int iValue = 0;
		if ((flags & 0x40000) && (flags & 0x8000))
		{
			iValue = flags & 0xFF00;
			flags = flags & ~iValue;
		}
		expState.fArray[expState.fCount++] = value;
		expState.iArray[expState.iCount++] = flags;
		value = getExpEntryValue<big>(entry, fi, tmpValues, frameCount, animBoneTT);
		if (fi == 0)
			DBGLOG("\t\t\t\t\tvalue: %f\n", value);
		if (entry.flags & 0x40000) {
			expState.fArray[expState.fCount++] = 0.0;
			expState.iArray[expState.iCount++] = iValue | 1;
		}
	}
	else {
		if (fi == 0)
			DBGLOG("\t\t\t\tnormal:\n");
		float tmp = getExpEntryValue<big>(entry, fi, tmpValues, frameCount, animBoneTT);
		if (fi == 0)
			DBGLOG("\t\t\t\t\tvalue: %f\n", value);
		if (entry.flags & 1) {
			value += tmp;
		}
		else if (entry.flags & 2) {
			value -= tmp;
		}
		else if (entry.flags & 4) {
			value *= tmp;
		}
		else if ((entry.flags & 8) && tmp != 0.0f) {
			value /= tmp;
		}
	}
	if (entry.flags & 0x20000) {
		if (fi == 0)
			DBGLOG("\t\t\t\tmodifying:\n");
		value = modifyExpEntryValue<big>(expState, value, fi);
		if (entry.flags & 0x80000) {
			value = modifyExpEntryValue<big>(expState, value, fi);
		}
	}
	return value;
}

/* em0600 exp entries 15 and 20 seem to lead to buffer underrun
   in the state struct, flag is used instead of a value from fArray.
   Similarly the last value of fArray is used instead of a value from iArray...*/
template <bool big>
static void Model_Bayo1_ApplyEXP(CArrayList<bayoDatFile_t *> & expfile, float * tmpValues, const int bone_number, const short int frameCount, short int * animBoneTT) {
	static int maxCoeffs = 16;
	if (expfile.Num() > 0) {
		DBGLOG("\tapplying: %s\n", expfile[0]->name);
		BYTE *data = expfile[0]->data;
		size_t dataSize = expfile[0]->dataSize;
		if (dataSize < sizeof(bayoEXPHdr_t))
		{
			return;
		}
		bayoEXPHdr<big> hdr((bayoEXPHdr_t *)data);
		for (unsigned int i = 0; i < hdr.numRecords - 1; i++) {
			DBGLOG("\t\trecord: %d\n", i);
			bayoEXPRecord<big> record((bayoEXPRecord_t *)(data + hdr.offsetRecords + i * sizeof(bayoEXPRecord_t)));
			short int targetBone = Model_Bayo_DecodeMotionIndex<big, BAYONETTA>(animBoneTT, record.boneIndex);
			char targetTrack = record.animationTrack;
			DBGLOG("\t\t\tbone: %d, track: %d\n", (int)targetBone, (int)targetTrack);
			for (int fi = 0; fi < frameCount; fi++) {
				struct expState_s expState;
				init_expState(expState);
				float res = 0.0f;
				for (int j = 0; j < record.entryCount; j++) {
					if (fi == 0)
						DBGLOG("\t\t\t: entry: %d\n", j);
					bayoEXPEntry<big> entry((bayoEXPEntry_t *)(data + record.offset + j * sizeof(bayoEXPEntry_t)));
					res = applyExpEntry<big>(expState, entry, fi, res, tmpValues, frameCount, animBoneTT);
					if (fi == 0)
						DBGLOG("\t\t\tres: %f\n", res);
				}
				if (record.flags & 1) {
					if (fi == 0)
						DBGLOG("\t\t\t: interpolating %d\n", record.interpolationType);
					if (record.interpolationType == 2) {
						res = Model_Bayo_Interpolate2EXP_Value<big>(res, data + record.offsetInterpolation, record.numPoints);
					}
					else if (record.interpolationType == 4) {
						res = Model_Bayo_Interpolate4EXP_Value<big>(res, data + record.offsetInterpolation, record.numPoints);
					}
					else if (record.interpolationType == 6) {
						res = Model_Bayo_Interpolate6EXP_Value<big>(res, data + record.offsetInterpolation, record.numPoints);
					}
					if (fi == 0)
						DBGLOG("\t\t\tres: %f\n", res);
					if (record.flags & 2) {
						for (int j = 0; j < record.interpolationEntryCount; j++) {
							if (fi == 0)
								DBGLOG("\t\t\t: interpolation entry: %d\n", j);
							bayoEXPEntry<big> entry((bayoEXPEntry_t *)(data + record.offset + (record.entryCount + j) * sizeof(bayoEXPEntry_t)));
							res = applyExpEntry<big>(expState, entry, fi, res, tmpValues, frameCount, animBoneTT);
							if (fi == 0)
								DBGLOG("\t\t\tres: %f\n", res);
						}
					}
				}
				if (fi == 0)
					DBGLOG("\t\t\tvalue: %f\n", res);
				tmpValues[fi + targetTrack * frameCount + targetBone * frameCount * maxCoeffs] = res;
			}
		}
	}
}

template <bool big>
static void Model_Bayo2_ApplyEXP(CArrayList<bayoDatFile_t *> & expfile, float * tmpValues, const int bone_number, const short int frameCount, short int * animBoneTT);

template <bool big, game_t game>
inline static void Model_Bayo_ApplyEXP(CArrayList<bayoDatFile_t *> & expfile, float * tmpValues, const int bone_number, const short int frameCount, short int * animBoneTT) {
	if (game == BAYONETTA) {
		Model_Bayo1_ApplyEXP<big>(expfile, tmpValues, bone_number, frameCount, animBoneTT);
	}
	else if (game == BAYONETTA2) {
		Model_Bayo2_ApplyEXP<big>(expfile, tmpValues, bone_number, frameCount, animBoneTT);
	}
}
//apply rotate/translate to model matrix
static void Model_Bayo_ApplyMotions(modelMatrix_t * matrixes, float * tmpValues, float *tmpCumulScale, modelBone_t *bones, const int boneNumber, const short int frameCount) {
	const int maxCoeffs = 16;
	DBGALOG("-------------------------------\n");
	for (int bi = 0; bi < boneNumber + 1; bi++) {
		DBGALOG("bone %d (%d)", bi, bones[bi].index);
		DBGALOG(" parent %d\n", bones[bi].eData.parent ? bones[bi].eData.parent->index : -1);
		//DBGLOG("\ttranslate: %f, %f, %f\n", bones[bi].mat.o[0], bones[bi].mat.o[1], bones[bi].mat.o[2]);
		DBGALOG("\trelative: %f, %f, %f\n",
			bones[bi].mat.o[0] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[0] : 0.0),
			bones[bi].mat.o[1] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[1] : 0.0),
			bones[bi].mat.o[2] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[2] : 0.0));
	}
	DBGALOG("-------------------------------\n");
	for (int bi = 0; bi < boneNumber + 1; bi++) {
		DBGALOG("bone %d\n", bi);

		for (int fi = 0; fi < frameCount; fi++) {
			DBGALOG("\tframe %d\n", fi);
			float translate[3];
			float rotate[3];
			float scale[3];
			//int rotate_order[3] = {2,1,0};
			float rotate_coeff[3] = { -1.0, 1.0, -1.0 };
			float translate_coeff[3] = { 1.0, 1.0, 1.0 };
			float scale_coeff[3] = { 1.0, 1.0, 1.0 };

			for (int i = 0; i < 3; i++) {
				translate[i] = translate_coeff[i] * tmpValues[fi + i * frameCount + bi * frameCount * maxCoeffs];
			}
			for (int i = 3, j = 0; i < 6; i++, j++) {
				rotate[j] = rotate_coeff[j] * tmpValues[fi + i * frameCount + bi * frameCount * maxCoeffs];
			}
			for (int i = 7, j = 0; i < 10; i++, j++) {
				scale[j] = scale_coeff[j] * tmpValues[fi + i * frameCount + bi * frameCount * maxCoeffs];
			}
			DBGALOG("\t\ttranslate: %f, %f, %f\n", translate[0], translate[1], translate[2]);
			DBGALOG("\t\tref relative: %f, %f, %f\n",
				bones[bi].mat.o[0] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[0] : 0.0),
				bones[bi].mat.o[1] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[1] : 0.0),
				bones[bi].mat.o[2] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[2] : 0.0));

			g_mfn->Math_TranslateMatrix(&matrixes[bi + (boneNumber + 1) * fi], translate);

			if (bones[bi].eData.parent) {
				int pi = bones[bi].eData.parent->index;
				float parentCumulScale[3];
				for (int i = 0; i < 3; i++)
					parentCumulScale[i] = tmpCumulScale[fi + i * frameCount + pi * frameCount * 3];
				for (int i = 0; i < 3; i++)
					scale[i] *= parentCumulScale[i];
				for (int i = 0; i < 3; i++) {
					matrixes[bi + (boneNumber + 1) * fi].x1[i] /= parentCumulScale[i];
					matrixes[bi + (boneNumber + 1) * fi].x2[i] /= parentCumulScale[i];
					matrixes[bi + (boneNumber + 1) * fi].x3[i] /= parentCumulScale[i];
				}
			}
			for (int i = 0; i < 3; i++)
				tmpCumulScale[fi + i * frameCount + bi * frameCount * 3] = scale[i];
			DBGALOG("\t\trotate: %f, %f, %f (order %d)\n", rotate[0], rotate[1], rotate[2], bones[bi].userIndex);
			switch (bones[bi].userIndex) {
			case 0:
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[0], 1.0f, 0.0f, 0.0f);
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[1], 0.0f, 1.0f, 0.0f);
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[2], 0.0f, 0.0f, 1.0f);
				break;
			case 1:
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[0], 1.0f, 0.0f, 0.0f);
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[2], 0.0f, 0.0f, 1.0f);
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[1], 0.0f, 1.0f, 0.0f);
				break;
			case 2:
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[1], 0.0f, 1.0f, 0.0f);
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[0], 1.0f, 0.0f, 0.0f);
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[2], 0.0f, 0.0f, 1.0f);
				break;
			case 3:
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[1], 0.0f, 1.0f, 0.0f);
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[2], 0.0f, 0.0f, 1.0f);
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[0], 1.0f, 0.0f, 0.0f);
				break;
			case 4:
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[2], 0.0f, 0.0f, 1.0f);
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[0], 1.0f, 0.0f, 0.0f);
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[1], 0.0f, 1.0f, 0.0f);
				break;
			default:
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[2], 0.0f, 0.0f, 1.0f);
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[1], 0.0f, 1.0f, 0.0f);
				g_mfn->Math_RotateMatrix(&matrixes[bi + (boneNumber + 1) * fi], rotate[0], 1.0f, 0.0f, 0.0f);
			}

			DBGALOG("\t\tscale: %f, %f, %f\n", scale[0], scale[1], scale[2]);
			for (int i = 0; i < 3; i++) {
				matrixes[bi + (boneNumber + 1) * fi].x1[i] *= scale[i];
				matrixes[bi + (boneNumber + 1) * fi].x2[i] *= scale[i];
				matrixes[bi + (boneNumber + 1) * fi].x3[i] *= scale[i];
			}
		}
	}
}

template <bool big>
static inline void Model_Bayo_DecodeInterpolateHeader(float * fvals, bayoInterpolHeader4_t *h) {
	for (int j = 0; j < 6; j++) {
		fvals[j] = h->values[j];
		if (big) LITTLE_BIG_SWAP(fvals[j]);
	}
}
static FloatDecompressor C(6, 9, 47);
static FloatDecompressor H(5, 10, 15);
template <bool big>
static inline void Model_Bayo_DecodeInterpolateHeader(float * fvals, bayoInterpolHeader6_t *h) {
	for (int j = 0; j < 6; j++) {
		fvals[j] = C.decompress(h->values[j], big);
	}
}
template <bool big>
static inline void Model_Bayo_DecodeInterpolateHeader(float * fvals, bayoInterpolHeader7_t *h) {
	for (int j = 0; j < 6; j++) {
		fvals[j] = C.decompress(h->values[j], big);
	}
}
template <bool big>
static inline void Model_Bayo_DecodeInterpolateHeader(float * fvals, bayoInterpolHeader8_t *h) {
	for (int j = 0; j < 6; j++) {
		fvals[j] = C.decompress(h->values[j], big);
	}
}
template <bool big, game_e game>
static inline void Model_Bayo_DecodeFrameIndex(short int &firstFrame, short int &lastFrame, short int, bayoInterpolKeyframe4<big> &p_v, bayoInterpolKeyframe4<big> &v) {
	firstFrame = p_v.index;
	lastFrame = v.index;
}
template <bool big, game_e game>
static inline void Model_Bayo_DecodeFrameIndex(short int &firstFrame, short int &lastFrame, short int frameCount, bayoInterpolKeyframe6<big> &p_v, bayoInterpolKeyframe6<big> &v) {
	if (game == BAYONETTA2) {
		firstFrame = p_v.index;
		lastFrame = v.index;
	}
	else {
		firstFrame = frameCount - 1;
		lastFrame = frameCount - 1 + v.index;
	}
}
template <bool big, game_e game>
static inline void Model_Bayo_DecodeFrameIndex(short int &firstFrame, short int &lastFrame, short int, bayoInterpolKeyframe7<big> &p_v, bayoInterpolKeyframe7<big> &v) {
	firstFrame = p_v.index;
	lastFrame = v.index;
}
template <bool big, game_e game>
static inline void Model_Bayo_DecodeFrameIndex(short int &firstFrame, short int &lastFrame, short int, bayoInterpolKeyframe8<big> &p_v, bayoInterpolKeyframe8<big> &v) {
	firstFrame = p_v.index;
	lastFrame = v.index;
}
template <class T>
static void Model_Bayo_HermitInterpolate(float * tmpValues, float *fvals, const T &p_v, const T &v, short int &frameCount, const short int first_frame, const short int last_frame) {
	float p0, p1, m0, m1;
	p0 = fvals[0] + fvals[1] * p_v.coeffs[0];
	p1 = fvals[0] + fvals[1] * v.coeffs[0];
	m0 = fvals[4] + fvals[5] * p_v.coeffs[2];
	m1 = fvals[2] + fvals[3] * v.coeffs[1];

	for (; frameCount <= last_frame; frameCount++) {
		float t;
		t = (float)(frameCount - first_frame) / (last_frame - first_frame);
		tmpValues[frameCount] = (2 * t*t*t - 3 * t*t + 1)*p0 + (t*t*t - 2 * t*t + t)*m0 + (-2 * t*t*t + 3 * t*t)*p1 + (t*t*t - t * t)*m1;
		DBGALOG("%f, %d, %f\n\t", t, frameCount, tmpValues[frameCount]);
	}
	DBGALOG("%3d %5d %5d %5d (%+f %+f %+f)\n\t", v.index, v.coeffs[0], v.coeffs[1], v.coeffs[2],
		fvals[0] + fvals[1] * v.coeffs[0],
		fvals[2] + fvals[3] * v.coeffs[1],
		fvals[4] + fvals[5] * v.coeffs[2]);
}
//interpolate motion
template <bool big, game_e game, class T1, class T2, class T3>
static void Model_Bayo_Interpolate(float * tmpValues, BYTE * data, const short int elemNumber, short int length) {
	short int frameCount;
	T1 *h = (T1 *)(data);
	T2 *v_p = (T2 *)(h + 1);
	T2 *p_v_p;

	float fvals[6];
	Model_Bayo_DecodeInterpolateHeader<big>(fvals, h);
	DBGALOG("\t");
	for (int j = 0; j < 6; j++)
	{
		DBGALOG("%#g ", fvals[j]);
	}
	DBGALOG("\n\t(");
	for (int j = 0; j < sizeof(*h); j++)
	{
		DBGALOG("%02x ", ((BYTE *)h)[j]);
	}
	DBGALOG(")\n\t");

	T3 t_v(v_p);
	DBGALOG("%3d %5d %5d %5d (%+f %+f %+f)\n\t", t_v.index, t_v.coeffs[0], t_v.coeffs[1], t_v.coeffs[2],
		fvals[0] + fvals[1] * t_v.coeffs[0],
		fvals[2] + fvals[3] * t_v.coeffs[1],
		fvals[4] + fvals[5] * t_v.coeffs[2]);
	frameCount = t_v.index;
	float f = fvals[0] + fvals[1] * t_v.coeffs[0];
	for (int j = 0; j < frameCount; j++) {
		tmpValues[j] = f;
		DBGALOG("%d, %f\n\t", j, f);
	}
	tmpValues[frameCount] = f;
	DBGALOG("%f, %d, %f\n\t", 0.0, frameCount, f);

	p_v_p = v_p;
	v_p++;
	frameCount++;

	for (int j = 1; j < elemNumber; j++, p_v_p++, v_p++)
	{
		T3 p_v(p_v_p);
		T3 v(v_p);
		short int first_frame, last_frame;
		Model_Bayo_DecodeFrameIndex<big, game>(first_frame, last_frame, frameCount, p_v, v);
		Model_Bayo_HermitInterpolate(tmpValues, fvals, p_v, v, frameCount, first_frame, last_frame);
	}
	for (int j = frameCount; j < length; j++) {
		tmpValues[j] = tmpValues[frameCount - 1];
		DBGALOG("%d, %f\n\t", j, tmpValues[j]);
	}

	DBGALOG("\n");
}
template <bool big, game_t game>
static void Model_Bayo_CreateRestPoseAnim(CArrayList<noesisAnim_t *> &animList, modelBone_t *bones, int bone_number, noeRAPI_t *rapi, void * extraBoneInfo)
{
	const int frameCount = 1;
	const int maxCoeffs = 16;
	modelMatrix_t * matrixes;
	float * tmp_values;
	float * tmp_cumul_scale;
	Model_Bayo_InitMotions<big, game>(matrixes, tmp_values, tmp_cumul_scale, bones, bone_number, frameCount, rapi, extraBoneInfo);
	for (int bi = 0; bi < bone_number + 1; bi++) {
		for (int fi = 0; fi < frameCount; fi++) {
			// convert to degrees
			tmp_values[fi + 3 * frameCount + bi * frameCount * maxCoeffs] *= g_flRadToDeg;
			tmp_values[fi + 4 * frameCount + bi * frameCount * maxCoeffs] *= g_flRadToDeg;
			tmp_values[fi + 5 * frameCount + bi * frameCount * maxCoeffs] *= g_flRadToDeg;
		}
	}
	Model_Bayo_ApplyMotions(matrixes, tmp_values, tmp_cumul_scale, bones, bone_number, frameCount);
	noesisAnim_t *anim = rapi->rpgAnimFromBonesAndMatsFinish(bones, bone_number + 1, matrixes, frameCount, 60);

	anim->filename = rapi->Noesis_PooledString("restpose");
	anim->flags |= NANIMFLAG_FILENAMETOSEQ;
	anim->aseq = rapi->Noesis_AnimSequencesAlloc(1, frameCount);
	anim->aseq->s->startFrame = 0;
	anim->aseq->s->endFrame = frameCount - 1;
	anim->aseq->s->frameRate = 60;
	anim->aseq->s->name = rapi->Noesis_PooledString("restpose");
	if (anim)
	{
		animList.Append(anim);
	}
	rapi->Noesis_UnpooledFree(matrixes);
	rapi->Noesis_UnpooledFree(tmp_values);
	rapi->Noesis_UnpooledFree(tmp_cumul_scale);
}
//loat motion file
template <bool big, game_t game>
static void Model_Bayo_LoadMotions(CArrayList<noesisAnim_t *> &animList, CArrayList<bayoDatFile_t *> &motfiles, CArrayList<bayoDatFile_t *> &expfile, modelBone_t *bones, int bone_number, noeRAPI_t *rapi, short int * animBoneTT, void * extraBoneInfo)
{
	const int maxCoeffs = 16;
	if (motfiles.Num() > 0) {
		Model_Bayo_CreateRestPoseAnim<big, game>(animList, bones, bone_number, rapi, extraBoneInfo);
	}
	else {
		return;
	}
	for (int mi = 0; mi < motfiles.Num(); mi++)// motfiles.Num(); mi++)
	{
		DBGLOG("Loading %s\n", motfiles[mi]->name);

		BYTE * data = motfiles[mi]->data;
		size_t dataSize = motfiles[mi]->dataSize;
		int unknownA;
		int frameCount;
		int ofsMotion;
		int numEntries;
		if (game != BAYONETTA && game != MADWORLD) {
			if (dataSize < sizeof(bayo2MOTHdr_t))
			{
				continue;
			}
			bayo2MOTHdr<big> hdr((bayo2MOTHdr_t *)data);
			if (memcmp(hdr.id, "mot\0", 4))
			{ //not a valid motion file
				continue;
			}
			unknownA = hdr.unknownA;
			frameCount = hdr.frameCount;
			ofsMotion = hdr.ofsMotion;
			numEntries = hdr.numEntries;
		}
		else {
			if (dataSize < sizeof(bayoMOTHdr_t))
			{
				continue;
			}
			bayoMOTHdr<big> hdr((bayoMOTHdr_t *)data);
			if (memcmp(hdr.id, "mot\0", 4))
			{ //not a valid motion file
				continue;
			}
			unknownA = hdr.unknownA;
			frameCount = hdr.frameCount;
			ofsMotion = hdr.ofsMotion;
			numEntries = hdr.numEntries;
		}

		char fname[MAX_NOESIS_PATH];
		sprintf_s(fname, MAX_NOESIS_PATH, "%s", motfiles[mi]->name);

		modelMatrix_t * matrixes;
		float * tmp_values;
		float * tmp_cumul_scale;
		Model_Bayo_InitMotions<big, game>(matrixes, tmp_values, tmp_cumul_scale, bones, bone_number, frameCount, rapi, extraBoneInfo);

		bayoMotItem_t * items = (bayoMotItem_t*)(data + ofsMotion);
		DBGALOG("unknown flag: 0x%04x, frame count: %d, data offset: 0x%04x, record number: %d\n", unknownA, frameCount, ofsMotion, numEntries);
		for (int i = 0; i < numEntries; i++) {
			bayoMotItem<big> it(&items[i]);
			if (game != BAYONETTA && game != MADWORLD) data = (BYTE *)&items[i];
			if (it.boneIndex == 0x7fff) {
				DBGALOG("%5d %3d 0x%02x %3d %3d %+f (0x%08x)\n", it.boneIndex, it.index, it.flag, it.elem_number, it.unknown, it.value.flt, it.value.offset);
				continue;
			}
			else if (it.boneIndex >= 0xf60) {
				DBGALOG("%5d %3d 0x%02x %3d %3d %+f (0x%08x) special flag 0x2 index\n", it.boneIndex, it.index, it.flag, it.elem_number, it.unknown, it.value.flt, it.value.offset);
				continue;
			}

			short int boneIndex;
			if (it.boneIndex == -1) {
				boneIndex = bone_number;
			}
			else {
				boneIndex = Model_Bayo_DecodeMotionIndex<big, game>(animBoneTT, it.boneIndex);
			}
			if (boneIndex == 0x0fff) {
				DBGALOG("%5d %3d 0x%02x %3d %3d %+f (0x%08x) cannot translate bone\n", it.boneIndex, it.index, it.flag, it.elem_number, it.unknown, it.value.flt, it.value.offset);
				continue;
			}

			//float tmp_values[65536];
			DBGALOG("%5d (%5d) %3d 0x%02x %3d %3d", boneIndex, it.boneIndex, it.index, it.flag, it.elem_number, it.unknown);
			DBGALOG(" %+f (0x%08x)\n", it.value.flt, it.value.offset);
			if (boneIndex > bone_number) {
				DBGALOG(" out of bone bounds\n");
				continue;
			}
			if (it.flag == 1) {
				float *fdata = (float *)(data + it.value.offset);
				for (int frame_number = 0; frame_number < it.elem_number; frame_number++) {
					float f = fdata[frame_number];
					if (big) LITTLE_BIG_SWAP(f);
					tmp_values[frame_number + it.index * frameCount + boneIndex * frameCount * maxCoeffs] = f;
					DBGALOG("\t%3d %+f\n", frame_number, f);
				}
				float v = tmp_values[it.elem_number - 1 + it.index * frameCount + boneIndex * frameCount * maxCoeffs];
				for (int frame_number = it.elem_number; frame_number < frameCount; frame_number++) {
					tmp_values[frame_number + it.index * frameCount + boneIndex * frameCount * maxCoeffs] = v;
					DBGALOG("\t%d, %f\n", frame_number, v);
				}
			}
			else if (it.flag == 2) {
				float *fData = (float *)(data + it.value.offset);
				short unsigned int *suiData = (short unsigned int *)&fData[2];
				float fbase = fData[0];
				float fdelta = fData[1];
				if (big) LITTLE_BIG_SWAP(fbase);
				if (big) LITTLE_BIG_SWAP(fdelta);
				DBGALOG("\t%f %f\n", fbase, fdelta);
				for (int frame_count = 0; frame_count < it.elem_number; frame_count++) {
					short unsigned int val;
					float f;
					val = suiData[frame_count];
					if (big) LITTLE_BIG_SWAP(val);
					f = fbase + fdelta * val;
					DBGALOG("\t%d %d %f\n", frame_count, val, f);
					tmp_values[frame_count + it.index * frameCount + boneIndex * frameCount * maxCoeffs] = f;
				}
				float v = tmp_values[it.elem_number - 1 + it.index * frameCount + boneIndex * frameCount * maxCoeffs];
				for (int j = it.elem_number; j < frameCount; j++) {
					tmp_values[j + it.index * frameCount + boneIndex * frameCount * maxCoeffs] = v;
					DBGALOG("\t%d, %f\n", j, v);
				}
			}
			else if (it.flag == 3) {
				short unsigned int *suiData = (short unsigned int *)(data + it.value.offset);
				BYTE * bData = (BYTE *)&suiData[2];
				float fbase = C.decompress(suiData[0], big);
				float fdelta = C.decompress(suiData[1], big);
				DBGALOG("\t%f %f\n", fbase, fdelta);
				for (int frame_count = 0; frame_count < it.elem_number; frame_count++) {
					BYTE val = bData[frame_count];
					float f = fbase + fdelta * val;
					DBGALOG("\t%d %d %f\n", frame_count, val, f);
					tmp_values[frame_count + it.index * frameCount + boneIndex * frameCount * maxCoeffs] = f;
				}
				float v = tmp_values[it.elem_number - 1 + it.index * frameCount + boneIndex * frameCount * maxCoeffs];
				for (int j = it.elem_number; j < frameCount; j++) {
					tmp_values[j + it.index * frameCount + boneIndex * frameCount * maxCoeffs] = v;
					DBGALOG("\t%d, %f\n", j, v);
				}
			}
			else if ((game != BAYONETTA && game != MADWORLD) && it.flag == 4) {
				bayo2InterpolKeyframe4_t *v_p = (bayo2InterpolKeyframe4_t *)(data + it.value.offset);
				bayo2InterpolKeyframe4_t *p_v_p;
				bayo2InterpolKeyframe4<big> t_v(v_p);
				int frame_count = t_v.index;

				DBGALOG("\t%d %f (%f %f)\n", t_v.index, t_v.p, t_v.m0, t_v.m1);
				for (int j = 0; j < frame_count; j++) {
					tmp_values[j + it.index * frameCount + boneIndex * frameCount * maxCoeffs] = t_v.p;
					DBGALOG("\t%d, %f\n", j, t_v.p);
				}
				tmp_values[frame_count + it.index * frameCount + boneIndex * frameCount * maxCoeffs] = t_v.p;
				DBGALOG("\t%f, %d, %f\n", 0.0, frame_count, t_v.p);
				frame_count++;
				p_v_p = v_p;
				v_p++;
				for (int j = 1; j < it.elem_number; j++, p_v_p++, v_p++) {
					bayo2InterpolKeyframe4<big> v(v_p);
					bayo2InterpolKeyframe4<big> p_v(p_v_p);
					float p0, p1, m0, m1;
					p0 = p_v.p;
					m0 = p_v.m1;
					p1 = v.p;
					m1 = v.m0;
					for (; frame_count <= v.index; frame_count++) {
						float t;
						float f;
						t = (float)(frame_count - p_v.index) / (v.index - p_v.index);
						f = (2 * t*t*t - 3 * t*t + 1)*p0 + (t*t*t - 2 * t*t + t)*m0 + (-2 * t*t*t + 3 * t*t)*p1 + (t*t*t - t * t)*m1;
						tmp_values[frame_count + it.index * frameCount + boneIndex * frameCount * maxCoeffs] = f;
						DBGALOG("\t%f, %d, %f\n", 0.0, frame_count, f);
					}
					DBGALOG("\t%d %f (%f %f)\n", v.index, v.p, v.m0, v.m1);
				}
				float v = tmp_values[frame_count - 1 + it.index * frameCount + boneIndex * frameCount * maxCoeffs];
				for (int j = frame_count; j < frameCount; j++) {
					tmp_values[j + it.index * frameCount + boneIndex * frameCount * maxCoeffs] = v;
					DBGALOG("\t%d, %f\n", j, v);
				}
				DBGALOG("\n");
			}
			else if (it.flag == 4 || ((game != BAYONETTA && game != MADWORLD) && it.flag == 5)) {

				Model_Bayo_Interpolate<big, game, bayoInterpolHeader4_t, bayoInterpolKeyframe4_t, bayoInterpolKeyframe4<big>>(tmp_values + it.index * frameCount + boneIndex * frameCount * maxCoeffs,
					data + it.value.offset,
					it.elem_number, frameCount);
			}
			else if ((game != BAYONETTA && game != MADWORLD) && it.flag == 6) {

				Model_Bayo_Interpolate<big, BAYONETTA2, bayoInterpolHeader6_t, bayoInterpolKeyframe6_t, bayoInterpolKeyframe6<big>>(tmp_values + it.index * frameCount + boneIndex * frameCount * maxCoeffs,
					data + it.value.offset,
					it.elem_number, frameCount);

			}
			else if (it.flag == 6 || ((game != BAYONETTA && game != MADWORLD) && it.flag == 7)) {

				Model_Bayo_Interpolate<big, BAYONETTA, bayoInterpolHeader6_t, bayoInterpolKeyframe6_t, bayoInterpolKeyframe6<big>>(tmp_values + it.index * frameCount + boneIndex * frameCount * maxCoeffs,
					data + it.value.offset,
					it.elem_number, frameCount);

			}
			else if (it.flag == 7) { //diff from 6 because frame delta would be > 255

				Model_Bayo_Interpolate<big, game, bayoInterpolHeader7_t, bayoInterpolKeyframe7_t, bayoInterpolKeyframe7<big>>(tmp_values + it.index * frameCount + boneIndex * frameCount * maxCoeffs,
					data + it.value.offset,
					it.elem_number, frameCount);

			}
			else if (it.flag == 8) {

				Model_Bayo_Interpolate<big, game, bayoInterpolHeader8_t, bayoInterpolKeyframe8_t, bayoInterpolKeyframe8<big>>(tmp_values + it.index * frameCount + boneIndex * frameCount * maxCoeffs,
					data + it.value.offset,
					it.elem_number, frameCount);

			}
			else if (it.flag == 0xff) {
				continue;
			}
			else if (it.flag != 0) {
				DBGLOG("WARNING: Unknown motion flag %02x.\n", it.flag);
				assert(0);
				continue;
				rapi->LogOutput("WARNING: Unknown motion flag %02x.\n", it.flag);
			}
			else {
				for (int j = 0; j < frameCount; j++) {
					tmp_values[j + it.index * frameCount + boneIndex * frameCount * maxCoeffs] = it.value.flt;
				}
			}

		}

		for (int bi = 0; bi < bone_number + 1; bi++) {
			for (int fi = 0; fi < frameCount; fi++) {
				// convert to degrees
				tmp_values[fi + 3 * frameCount + bi * frameCount * maxCoeffs] *= g_flRadToDeg;
				tmp_values[fi + 4 * frameCount + bi * frameCount * maxCoeffs] *= g_flRadToDeg;
				tmp_values[fi + 5 * frameCount + bi * frameCount * maxCoeffs] *= g_flRadToDeg;
			}
		}

		if (game == BAYONETTA2) {
			for (int bi = 0; bi < bone_number + 1; bi++) {
				for (int fi = 0; fi < frameCount; fi++) {
					// convert to dm: ugly fix for animations, doubtfull to be legit...
					tmp_values[fi + 0 * frameCount + bi * frameCount * maxCoeffs] *= 10.0f;
					tmp_values[fi + 1 * frameCount + bi * frameCount * maxCoeffs] *= 10.0f;
					tmp_values[fi + 2 * frameCount + bi * frameCount * maxCoeffs] *= 10.0f;
				}
			}
		}

		Model_Bayo_ApplyEXP<big, game>(expfile, tmp_values, bone_number, frameCount, animBoneTT);

		if (game == BAYONETTA2) {
			for (int bi = 0; bi < bone_number + 1; bi++) {
				for (int fi = 0; fi < frameCount; fi++) {
					// convert back to m
					tmp_values[fi + 0 * frameCount + bi * frameCount * maxCoeffs] *= 0.1f;
					tmp_values[fi + 1 * frameCount + bi * frameCount * maxCoeffs] *= 0.1f;
					tmp_values[fi + 2 * frameCount + bi * frameCount * maxCoeffs] *= 0.1f;
				}
			}
		}

		Model_Bayo_ApplyMotions(matrixes, tmp_values, tmp_cumul_scale, bones, bone_number, frameCount);

		noesisAnim_t *anim = rapi->rpgAnimFromBonesAndMatsFinish(bones, bone_number + 1, matrixes, frameCount, 60);
		if (!anim) {
			DBGLOG("Could not create anim for %s (out of memory?)!\n", fname);
			rapi->Noesis_UnpooledFree(matrixes);
			rapi->Noesis_UnpooledFree(tmp_values);
			continue;
		}

		anim->filename = rapi->Noesis_PooledString(fname);
		anim->flags |= NANIMFLAG_FILENAMETOSEQ;
		anim->aseq = rapi->Noesis_AnimSequencesAlloc(1, frameCount);
		anim->aseq->s->startFrame = 0;
		anim->aseq->s->endFrame = frameCount - 1;
		anim->aseq->s->frameRate = 60;
		anim->aseq->s->name = rapi->Noesis_PooledString(fname);
		if (anim)
		{
			animList.Append(anim);
		}
		rapi->Noesis_UnpooledFree(matrixes);
		rapi->Noesis_UnpooledFree(tmp_values);
		rapi->Noesis_UnpooledFree(tmp_cumul_scale);
	}

}

template <bool big, game_t game>
static void Model_Bayo_LoadExternalMotions(CArrayList<noesisAnim_t *> &animList, bayoDatFile_t &df, CArrayList<bayoDatFile_t *> &expfile, modelBone_t *bones, int bone_number, noeRAPI_t *rapi, short int * animBoneTT, void* extraBoneInfo) {
	//if(game==VANQUISH || game == ANARCHY_REIGNS) return;
	// TW101 is Vanquish but uses mot
	if (!gpPGOptions->bAnimPrompt) return;
	if (game == ANARCHY_REIGNS) return;
	noeUserPromptParam_t promptParams;
	char wmbName[MAX_NOESIS_PATH];
	char motionPrompt[MAX_NOESIS_PATH];
	char defaultValue[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(wmbName, df.name);
	sprintf_s(motionPrompt, MAX_NOESIS_PATH, "Load motions for %s in other files? (specify prefix if different)", wmbName);
	sprintf_s(defaultValue, MAX_NOESIS_PATH, "%s", wmbName);
	promptParams.titleStr = "Load motions?";
	promptParams.promptStr = motionPrompt;
	promptParams.defaultValue = defaultValue;
	promptParams.valType = NOEUSERVAL_STRING;
	promptParams.valHandler = NULL;
	wchar_t noepath[MAX_NOESIS_PATH];
	GetCurrentDirectory(MAX_NOESIS_PATH, noepath);

	while (g_nfn->NPAPI_UserPrompt(&promptParams)) {
		int dataLength;
		BYTE* data = rapi->Noesis_LoadPairedFile("Bayonetta PC Model", ".dat", dataLength, NULL);
		if (data) {
			CArrayList<bayoDatFile_t> datfiles;
			Model_Bayo_GetDATEntries<big>(datfiles, data, dataLength);
			if (datfiles.Num() > 0) {
				CArrayList<bayoDatFile_t *> motfiles;
				Model_Bayo_GetMotionFiles(datfiles, df, rapi, motfiles, (char *)promptParams.valBuf);
				if (motfiles.Num() > 0) {
					Model_Bayo_LoadMotions<big, game>(animList, motfiles, expfile, bones, bone_number, rapi, animBoneTT, extraBoneInfo);
				}
				motfiles.Clear();
			}
			datfiles.Clear();
			rapi->Noesis_UnpooledFree(data);
		}
	}
	SetCurrentDirectory(noepath);
}