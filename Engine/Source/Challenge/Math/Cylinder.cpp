#include <Challenge/Challenge.h>
#include "Cylinder.h"
using namespace challenge;

Cylinder::Cylinder(std::vector<glm::vec3> points, glm::vec3 principalAxis, glm::vec3 secondaryAxis)
{
	std::vector<glm::vec3> projPoints;
	std::vector<glm::vec3>::iterator it = points.begin();

	while(it != points.end()) {
		glm::vec3 point = (*it);

		glm::vec3 projPoint = point - (glm::dot(point, principalAxis) * principalAxis);
		projPoints.push_back(projPoint);
		++it;
	}

	float least = kInfinity, greatest = -kInfinity;
	glm::vec3 leastPoint, greatestPoint;

	it = projPoints.begin();

	while(it != projPoints.end()) {
		glm::vec3 point = (*it);

		float dot = glm::dot(point, secondaryAxis);

		if(dot > greatest) {
			greatest = dot;
			greatestPoint = point;
		} else {
			least = dot;
			leastPoint = point;
		}

		++it;
	}

	glm::vec3 center = (leastPoint + greatestPoint) / 2.0f;

	float radius = glm::length(leastPoint - center);
	float radius2 = r * r;

	it = projPoints.begin();

	while(it != projPoints.end()) {
		glm::vec3 point = (*it);

		glm::vec3 pointMinusCenter = point - center;
		float length = glm::length(pointMinusCenter);
		float test = length * length;

		if(test > radius2) {
			glm::vec3 dif = center - (r * (pointMinusCenter / length));
			center = (dif + point) / 2.0f;
			radius = length;
			radius2 = r * r;
		}

		++it;
	}

	it = points.begin();

	least = kInfinity;
	greatest = -kInfinity;

	while(it != points.end()) {
		glm::vec3 point = (*it);

		float dot = glm::dot(point, principalAxis);

		if(dot > greatest) {
			greatest = dot;
			greatestPoint = point;
		} else {
			least = dot;
			leastPoint = point;
		}

		++it;
	}

	top = center + (greatest * principalAxis);
	bottom = center + (least * principalAxis);
	r = radius;
	s = radius;
	m = 1;
	height = glm::distance(top, bottom);
}

bool Cylinder::Intersects(Ray ray, glm::vec3 &intersectionPoint)
{
	/*float vx = ray.direction.x;
	float vx2 = vx * vx;
	float vy = ray.direction.z;
	float vy2 = vy * vy;
	float sx = ray.origin.x;
	float sx2 = sx * sx;
	float sy = ray.origin.z;
	float sy2 = sy * sy;
	float m2 = m * m;
	float r2 = r * r;

	float a = (vx2 + (m2 * vy2));
	float b = 2 * ((sx * vx) + (m2 * sy * vy));
	float c = sx2 + (m2 * sy2) - r2;

	float D = (b * b) - (4 * a * c);
	
	if(D > 0) {
		float twoA = 2 * a;
		float sqrtD = sqrt(D);
		float t1 = (-b + sqrtD) / twoA;
		float t2 = (-b - sqrtD) / twoA;

		glm::vec3 intp1 = ray.ValueAt(t1);
		glm::vec3 intp2 = ray.ValueAt(t2);
		float y1 = ray.origin.y + (t1 * ray.direction.y);
		float y2 = ray.origin.y + (t2 * ray.direction.y);
		/*if(intp1.y >= 0 && intp1.y <= height) {
			return true;
		} else {
			intersectionPoint = ray.ValueAt(t2);
			if(intp2.y >= 0 && intp2.y <= height) {
				return true;
			}
		}
		if(intp2.y >= 0 && intp2.y <= height) {
			return true;
		}
	}

	intersectionPoint = glm::vec3(0.0f);*/
	return false;
}