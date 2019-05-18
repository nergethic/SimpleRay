#pragma once

#include "hitable.h"

struct HitableList : IHitable {
	IHitable** list;
	int listSize;

	HitableList(IHitable **l, int n) {list = l; listSize = n; }
	virtual bool hit(Ray& r, float tMin, float tMax, HitRecord& rec) const;
};

bool HitableList::hit(Ray& r, float tMin, float tMax, HitRecord& rec) const {
	HitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = tMax;

	for (int i = 0; i < listSize; ++i) {
		if (list[i]->hit(r, tMin, closestSoFar, tempRec)) {
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}
	return hitAnything;
}