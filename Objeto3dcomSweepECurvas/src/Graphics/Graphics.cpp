/*
  Algoritmos baseados nos tutoriais ddo canal do Youtube do ChiliTomatoNoodle
*/

#include "../Modules/gl_canvas2d.h"
#include "../Utils/Utils.hpp"
#include "../Utils/Point.hpp"
#include "../Utils/Vector3.hpp"
#include "../Graphics/Graphics.hpp"

#include <vector>
#include <cmath>
#include <iostream>
#include "../Utils/Vector3.hpp"

using namespace std;

Graphics::Graphics()
{
}

void Graphics::DrawFlatTopTriangle(const Vec3f& v0, const Vec3f& v1, const Vec3f& v2)
{
	// calulcate slopes in screen space
	float m0 = (v2.x - v0.x) / (v2.y - v0.y);
	float m1 = (v2.x - v1.x) / (v2.y - v1.y);

	// calculate start and end scanlines
	const int yStart = (int)ceil(v0.y - 0.5f);
	const int yEnd = (int)ceil(v2.y - 0.5f); // the scanline AFTER the last line drawn

	for (int y = yStart; y < yEnd; y++)
	{
		// caluclate start and end points (x-coords)
		// add 0.5 to y value because we're calculating based on pixel CENTERS
		const float px0 = m0 * (float(y) + 0.5f - v0.y) + v0.x;
		const float px1 = m1 * (float(y) + 0.5f - v1.y) + v1.x;

		// calculate start and end pixels
		const int xStart = (int)ceil(px0 - 0.5f);
		const int xEnd = (int)ceil(px1 - 0.5f); // the pixel AFTER the last pixel drawn

		for (int x = xStart; x < xEnd; x++)
		{
			CV::color(0,1,0);
		    CV::point(x, y);
		}
	}
}

void Graphics::DrawFlatBottomTriangle(const Vec3f& v0, const Vec3f& v1, const Vec3f& v2)
{
	// calulcate slopes in screen space
	float m0 = (v1.x - v0.x) / (v1.y - v0.y);
	float m1 = (v2.x - v0.x) / (v2.y - v0.y);

	// calculate start and end scanlines
	const int yStart = (int)ceil(v0.y - 0.5f);
	const int yEnd = (int)ceil(v2.y - 0.5f); // the scanline AFTER the last line drawn

	for (int y = yStart; y < yEnd; y++)
	{
		// caluclate start and end points
		// add 0.5 to y value because we're calculating based on pixel CENTERS
		const float px0 = m0 * (float(y) + 0.5f - v0.y) + v0.x;
		const float px1 = m1 * (float(y) + 0.5f - v0.y) + v0.x;

		// calculate start and end pixels
		const int xStart = (int)ceil(px0 - 0.5f);
		const int xEnd = (int)ceil(px1 - 0.5f); // the pixel AFTER the last pixel drawn

		for (int x = xStart; x < xEnd; x++)
		{
		    CV::color(0,1,0);
		    CV::point(x, y);
		}
	}
}

void Graphics::DrawTriangle(const Vec3f& v0, const Vec3f& v1, const Vec3f& v2)
{
	// using pointers so we can swap (for sorting purposes)
	const Vec3f* pv0 = &v0;
	const Vec3f* pv1 = &v1;
	const Vec3f* pv2 = &v2;

	// sorting vertices by y
	if (pv1->y < pv0->y) std::swap(pv0, pv1);
	if (pv2->y < pv1->y) std::swap(pv1, pv2);
	if (pv1->y < pv0->y) std::swap(pv0, pv1);

	if (pv0->y == pv1->y) // natural flat top
	{
		// sorting top vertices by x
		if (pv1->x < pv0->x) std::swap(pv0, pv1);
		DrawFlatTopTriangle(*pv0, *pv1, *pv2);
	}
	else if (pv1->y == pv2->y) // natural flat bottom
	{
		// sorting bottom vertices by x
		if (pv2->x < pv1->x) std::swap(pv1, pv2);
		DrawFlatBottomTriangle(*pv0, *pv1, *pv2);
	}
	else // general triangle
	{
		// find splitting vertex
		const float alphaSplit =
			(pv1->y - pv0->y) /
			(pv2->y - pv0->y);
		const Vec3f vi = *pv0 + (*pv2 - *pv0) * alphaSplit;

		if (pv1->x < vi.x) // major right
		{
			DrawFlatBottomTriangle(*pv0, *pv1, vi);
			DrawFlatTopTriangle(*pv1, vi, *pv2);
		}
		else // major left
		{
			DrawFlatBottomTriangle(*pv0, vi, *pv1);
			DrawFlatTopTriangle(vi, *pv1, *pv2);
		}
	}
}

Graphics::~Graphics()
{
}
