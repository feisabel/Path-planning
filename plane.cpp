/*
 * plane.cpp
 *
 *  Created on: Jul 5, 2016
 *      Author: feisabel
 */

#include <vector>
#include "plane.h"

void Plane::addObstacle(vector<Point*> points) {
	vector<Point*>::iterator it;
	Point* p1;
	Point* p2;
	for (it = points.begin() ; it != points.end() - 1; ++it) {
		p1 = *it;
		p2 = *(it + 1);
		Segment* seg;
		if (p1->getX() < p2->getX() || (p1->getX() == p2->getX() && p1->getY() > p2->getY()))
			seg = new Segment(p1, p2);
		else
			seg = new Segment(p2, p1);
		p1->setSeg2(seg);
		p2->setSeg1(seg);
		segments.push_back(seg);
	    endpoints.push_back(*it);
	}
	p1 = *it;
	p2 = *(points.begin());
	Segment* seg;
	if (p1->getX() < p2->getX() || (p1->getX() == p2->getX() && p1->getY() > p2->getY()))
		seg = new Segment(p1, p2);
	else
		seg = new Segment(p2, p1);
	p1->setSeg2(seg);
	p2->setSeg1(seg);
	segments.push_back(seg);
	endpoints.push_back(*it);
}

void Plane::split(vector<Point*> A, int iStart, int iEnd, vector<Point*> B) {
	if (iEnd - iStart < 2)
		return;
	int iMiddle = (iEnd + iStart)/2;
	Plane::split(A, iStart, iMiddle, B);
	Plane::split(A, iMiddle, iEnd, B);
	Plane::merge(A, iStart, iMiddle, iEnd, B);
	for (int k = iStart; k < iEnd; k++)
		A[k] = B[k];
}

void Plane::merge(vector<Point*> A, int iStart, int iMiddle, int iEnd, vector<Point*> B) {
	int i = iStart, j = iEnd;
	for (int k = iStart; k < iEnd; k++) {
		if (i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
			B[k] = A[i];
			i++;
		}
		else {
			B[k] = A[j];
			j++;
		}
	}
}
