#pragma once
typedef struct bayo2EXPHdr_s
{
	BYTE				id[4];
	int					version;
	unsigned int		offsetRecords;
	int					numRecords;
	unsigned int		offsetInterpolationData;
	int					numtInterpolationData;
} bayo2EXPHdr_t;
template <bool big>
struct bayo2EXPHdr : public bayo2EXPHdr_s
{
	bayo2EXPHdr(bayo2EXPHdr_t *ptr) : bayo2EXPHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(version);
			LITTLE_BIG_SWAP(offsetRecords);
			LITTLE_BIG_SWAP(numRecords);
			LITTLE_BIG_SWAP(offsetInterpolationData);
			LITTLE_BIG_SWAP(numtInterpolationData);
		}
	}
};

typedef struct bayo2EXPRecord_s
{
	short int			boneIndex;
	char				animationTrack;
	char				unknownA;
	short int			valueCount;
	short int			unknwonB;
	unsigned int		offset;
} bayo2EXPRecord_t;
template <bool big>
struct bayo2EXPRecord : public bayo2EXPRecord_s
{
	bayo2EXPRecord(bayo2EXPRecord_t *ptr) : bayo2EXPRecord_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(boneIndex);
			LITTLE_BIG_SWAP(valueCount);
			LITTLE_BIG_SWAP(unknwonB);
			LITTLE_BIG_SWAP(offset);
		}
	}
};

typedef struct bayo2EXPValue_s
{
	char			type;
	char			animationTrack;
	short int		boneIndex;
	float			value;
} bayo2EXPValue_t;
template <bool big>
struct bayo2EXPValue : public bayo2EXPValue_s
{
	bayo2EXPValue(bayo2EXPValue_t * ptr) : bayo2EXPValue_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(boneIndex);
			LITTLE_BIG_SWAP(value);
		}
	}
};
typedef struct bayo2EXPInterpolationData_s
{
	short int		numPoints;
	short int		unknownA;
	unsigned int	offset;
} bayo2EXPInterpolationData_t;
template <bool big>
struct bayo2EXPInterpolationData : public bayo2EXPInterpolationData_s
{
	bayo2EXPInterpolationData(bayo2EXPInterpolationData_t * ptr) : bayo2EXPInterpolationData_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(numPoints);
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(offset);
		}
	}
};
typedef struct bayo2EXPInterpolationPoint_s
{
	float v;
	float p;
	float m0;
	float m1;
} bayo2EXPInterpolationPoint_t;
template <bool big>
struct bayo2EXPInterpolationPoint : public bayo2EXPInterpolationPoint_s
{
	bayo2EXPInterpolationPoint(bayo2EXPInterpolationPoint_t *ptr) : bayo2EXPInterpolationPoint_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(v);
			LITTLE_BIG_SWAP(p);
			LITTLE_BIG_SWAP(m0);
			LITTLE_BIG_SWAP(m1);
		}
	}
};

typedef struct bayo2MOTHdr_s
{
	BYTE				id[4];
	int					hash;
	short int			unknownA;
	short int			frameCount;
	int					ofsMotion;
	int					numEntries;
} bayo2MOTHdr_t;
template <bool big>
struct bayo2MOTHdr : public bayo2MOTHdr_s {
	bayo2MOTHdr(bayo2MOTHdr_t *ptr) : bayo2MOTHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(hash);
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(frameCount);
			LITTLE_BIG_SWAP(ofsMotion);
			LITTLE_BIG_SWAP(numEntries);
		}
	}
};

typedef struct bayo2InterpolKeyframe4_s {
	unsigned short int index;
	unsigned short int dummy;
	float p;
	float m0;
	float m1;
} bayo2InterpolKeyframe4_t;
template <bool big>
struct bayo2InterpolKeyframe4 : public bayo2InterpolKeyframe4_s {
	bayo2InterpolKeyframe4(bayo2InterpolKeyframe4_t *ptr) : bayo2InterpolKeyframe4_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(index);
			LITTLE_BIG_SWAP(dummy);
			LITTLE_BIG_SWAP(p);
			LITTLE_BIG_SWAP(m0);
			LITTLE_BIG_SWAP(m1);
		}
	}
};

template <bool big>
static float Model_Bayo2_InterpolateEXP_Value(short int interpolFunction, float value, BYTE *interpol) {
	BYTE *data = interpol + interpolFunction * sizeof(bayo2EXPInterpolationData_t);
	bayo2EXPInterpolationData<big> interpolData((bayo2EXPInterpolationData_t *)data);
	short int numPoints = interpolData.numPoints;
	float outValue = 0.0;
	data += interpolData.offset;
	for (int i = 0; i < numPoints - 1; i++) {
		bayo2EXPInterpolationPoint<big> leftPoint((bayo2EXPInterpolationPoint_t *)(data + i * sizeof(bayo2EXPInterpolationPoint_t)));
		bayo2EXPInterpolationPoint<big> rightPoint((bayo2EXPInterpolationPoint_t *)(data + (i + 1) * sizeof(bayo2EXPInterpolationPoint_t)));
		if (leftPoint.v <= value && rightPoint.v >= value) {
			float p0, p1, m0, m1;
			float t;
			p0 = leftPoint.p;
			p1 = rightPoint.p;
			m0 = leftPoint.m1;
			m1 = rightPoint.m0;
			t = (value - leftPoint.v) / (rightPoint.v - leftPoint.v);
			outValue = (2 * t*t*t - 3 * t*t + 1)*p0 + (t*t*t - 2 * t*t + t)*m0 + (-2 * t*t*t + 3 * t*t)*p1 + (t*t*t - t * t)*m1;
			DBGLOG("{t = %f}", t);
		}
	}
	return outValue;
}
template <bool big>
static float Model_Bayo2_DecodeEXP_Value(float * tmpValues, const int bone_number, const short int frameCount, short int * animBoneTT, BYTE *interpol, BYTE *&values, int &valueCount, int frame) {
	//DBGLOG("\t\tDecoding, remaining: %d\n\t\t\t", valueCount);
	static int maxCoeffs = 16;
	std::stack<float> s;
	char o = -1;
	while (valueCount > 0) {
		if (o != -1 && s.size() >= 2) {
			float v2 = s.top();
			s.pop();
			float v1 = s.top();
			s.pop();
			if (o == '+') {
				v1 += v2;
			}
			else if (o == '*') {
				v1 *= v2;
			}
			s.push(v1);
			o = -1;
		}
		bayo2EXPValue<big> v((bayo2EXPValue_t *)values);
		values += sizeof(bayo2EXPValue_t);
		valueCount -= 1;
		switch (v.type) {
		case 0: //terminator
			DBGLOG(" = ");
			return s.top();
			break;
		case 1: //Parenthesis
			DBGLOG("( ");
			s.push(Model_Bayo2_DecodeEXP_Value<big>(tmpValues, bone_number, frameCount, animBoneTT, interpol, values, valueCount, frame));
			break;
		case 2: //Closing Parenthesis
			DBGLOG(") ");
			return s.top();
			break;
		case 3: //Animation track
			s.push(tmpValues[frame + v.animationTrack * frameCount + Model_Bayo_DecodeMotionIndex<big>(animBoneTT, v.boneIndex) * frameCount * maxCoeffs]);
			DBGLOG("[%d:%d](%f)", Model_Bayo_DecodeMotionIndex<big>(animBoneTT, v.boneIndex), v.animationTrack, s.top());
			break;
		case 4: //Immediate
			DBGLOG("%f ", v.value);
			s.push(v.value);
			break;
		case 5: // Arithmetic
			if (v.boneIndex == 0) {
				o = '+';
			}
			else if (v.boneIndex == 2) {
				o = '*';
			}
			DBGLOG("%c ", o);
			break;
		case 6: // Function call
			DBGLOG("abs( ");
			s.push(abs(Model_Bayo2_DecodeEXP_Value<big>(tmpValues, bone_number, frameCount, animBoneTT, interpol, values, valueCount, frame)));
			break;
		case 7: // End function call
			DBGLOG(") ");
			return s.top();
			break;
		case 8: // interpolate
			DBGLOG("Interpolate%d( ", v.boneIndex);
			s.push(Model_Bayo2_InterpolateEXP_Value<big>(v.boneIndex,
				Model_Bayo2_DecodeEXP_Value<big>(tmpValues, bone_number, frameCount, animBoneTT, interpol, values, valueCount, frame),
				interpol)
			);
			break;
		}

	}
	return s.top();
}
template <bool big>
static void Model_Bayo2_ApplyEXP(CArrayList<bayoDatFile_t *> & expfile, float * tmpValues, const int bone_number, const short int frameCount, short int * animBoneTT) {
	static int maxCoeffs = 16;
	if (expfile.Num() > 0) {
		DBGLOG("\tapplying: %s\n", expfile[0]->name);
		BYTE *data = expfile[0]->data;
		size_t dataSize = expfile[0]->dataSize;
		if (dataSize < sizeof(bayo2EXPHdr_t))
		{
			return;
		}
		bayo2EXPHdr<big> hdr((bayo2EXPHdr_t *)data);
		BYTE *interpol = data + hdr.offsetInterpolationData;
		for (int i = 0; i < hdr.numRecords; i++) {
			bayo2EXPRecord<big> record((bayo2EXPRecord_t *)(data + hdr.offsetRecords + i * sizeof(bayo2EXPRecord_t)));
			short int targetBone = Model_Bayo_DecodeMotionIndex<big>(animBoneTT, record.boneIndex);
			char targetTrack = record.animationTrack;
			DBGLOG("\t\tfound bone: %d, track: %d, numValues: %d\n", targetBone, targetTrack, record.valueCount);
			for (int fi = 0; fi < frameCount; fi++) {
				BYTE *vals = data + hdr.offsetRecords + i * sizeof(bayo2EXPRecord_t) + record.offset;
				int count = record.valueCount;
				float value = Model_Bayo2_DecodeEXP_Value<big>(
					tmpValues,
					bone_number,
					frameCount,
					animBoneTT,
					interpol,
					vals,
					count,
					fi);
				DBGLOG("%f\n", value);
				tmpValues[fi + targetTrack * frameCount + targetBone * frameCount * maxCoeffs] = value;
			}
		}
	}
}