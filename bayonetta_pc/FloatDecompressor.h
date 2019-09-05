#pragma once
//thanks Phernost (stackoverflow)
class FloatDecompressor
{
	union Bits
	{
		float f;
		int si;
		unsigned int ui;
	};

	static int const significandFBits = 23;
	static int const exponentFBits = 8;
	static int const biasF = 127;
	static int const exponentF = 0x7F800000;
	static int const significandF = 0x007fffff;
	static int const signF = 0x80000000;

	int const significandHBits;
	int const exponentHBits;
	int const biasH;
	int exponentH;
	int significandH;
	static int const signH = 0x8000;

	int shiftSign;
	int shiftBits;

public:

	FloatDecompressor(int eHBits, int sHBits, int bH) : exponentHBits(eHBits), significandHBits(sHBits), biasH(bH) {
		int tmp = 0;
		for (int i = 0; i < eHBits; i++) {
			tmp <<= 1;
			tmp += 1;
		}
		tmp <<= sHBits;
		exponentH = tmp;

		tmp = 0;
		for (int i = 0; i < sHBits; i++) {
			tmp <<= 1;
			tmp += 1;
		}
		significandH = tmp;
		shiftSign = significandFBits + exponentFBits - significandHBits - exponentHBits;
		shiftBits = significandFBits - significandHBits;
	}

	float decompress(short unsigned int value)
	{
		Bits v;
		v.ui = value;
		int sign = v.si & signH;
		v.si ^= sign;

		sign <<= shiftSign;
		int exponent = v.si & exponentH;
		int significand = v.si ^ exponent;
		significand <<= shiftBits;

		v.si = sign | significand;
		if (exponent == exponentH) {
			v.si |= exponentF;
		}
		else if (exponent != 0) {
			exponent >>= significandHBits;
			exponent += biasF - biasH;
			exponent <<= significandFBits;
			v.si |= exponent;
		}
		else if (significand) { //denorm
			Bits magic;
			magic.ui = (biasF - biasH + biasF) << significandFBits;
			v.f *= magic.f;
		}
		return v.f;
	}
	float decompress(short unsigned int value, bool big) {
		short unsigned int v2 = value;
		if (big) LITTLE_BIG_SWAP(v2);
		return decompress(v2);
	}

};