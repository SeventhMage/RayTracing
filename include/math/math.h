#ifndef _SE_MATH_H_
#define _SE_MATH_H_

#include <math.h>
#include "base/def.h"

namespace se
{
	static bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
	{
		float discr = b * b - 4 * a * c;
		if (discr < 0) return false;
		else if (discr == 0) {
			x0 = x1 = -0.5 * b / a;
		}
		else {
			float q = (b > 0) ?
				-0.5 * (b + sqrt(discr)) :
				-0.5 * (b - sqrt(discr));
			x0 = q / a;
			x1 = c / q;
		}

		return true;
	}

	static math::CVector3 reflect(const math::CVector3 &I, const math::CVector3 &N)
	{
		return I - 2 * I.dotProduct(N) * N;
	}

	static math::CVector3 refract(const math::CVector3 &I, const math::CVector3 &N, const float &ior)
	{
		float cosi = CLAMP(-1, 1, I.dotProduct(N));
		float etai = 1, etat = ior;
		math::CVector3 n = N;
		if (cosi < 0) { cosi = -cosi; }
		else { std::swap(etai, etat); n = -N; }
		float eta = etai / etat;
		float k = 1 - eta * eta * (1 - cosi * cosi);
		return k < 0 ? math::CVector3() : eta * I + (eta * cosi - sqrtf(k)) * n;
	}

	static void fresnel(const math::CVector3 &I, const math::CVector3 &N, const float &ior, float &kr)
	{
		float cosi = CLAMP(-1, 1, I.dotProduct(N));
		float etai = 1, etat = ior;
		if (cosi > 0) { std::swap(etai, etat); }
		// Compute sini using Snell's law
		float sint = etai / etat * sqrtf(MAX(0.f, 1 - cosi * cosi));
		// Total internal reflection
		if (sint >= 1) {
			kr = 1;
		}
		else {
			float cost = sqrtf(MAX(0.f, 1 - sint * sint));
			cosi = fabsf(cosi);
			float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
			float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
			kr = (Rs * Rs + Rp * Rp) / 2;
		}
		// As a consequence of the conservation of energy, transmittance is given by:
		// kt = 1 - kr;
	}
}

#endif