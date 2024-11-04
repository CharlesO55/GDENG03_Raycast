#include "RaycastComponent.h"

#include "Debugger.h"
#include "SceneObject.h"

#include <exception>

RaycastComponent::RaycastComponent(SceneObject* owner, INTERSECTION_TYPE type) : Component(ComponentID::RAYCAST, owner), m_IntersectionType(type)
{
}


unsigned int RaycastComponent::checkRaycastHits(const Vector3D& rayOrigin, const Vector3D& rayDir, const Vector3D& targetCenter, const Vector3D& targetNormal, float* t)
{
	switch (m_IntersectionType)
	{
	case RaycastComponent::INTERSECTION_TYPE::SPHERE_CAST:
		return sphereCheck(rayOrigin, rayDir, targetCenter, t);
	case RaycastComponent::INTERSECTION_TYPE::PLANE_CAST:
		return planeCheck(rayOrigin, rayDir, targetCenter, targetNormal, t);
	default:
		return 0;
	}
}

unsigned int RaycastComponent::planeCheck(const Vector3D& rayOrigin, const Vector3D& rayDir, const Vector3D& targetCenter, const Vector3D& targetNormal, float* t)
{
	/* REFERENCE:
	* https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html
	*/

	
	// NO COLLISION HAPPENS WHEN LINES ARE NEAR PARALLEL
	float parallelCheck = Vector3D::dot(rayDir, targetNormal);

	// SINCE PLANE, CHECK BOTH ABOVE AND BELOW
	if (abs(parallelCheck) > 0.1f)
	{
		Vector3D oc = targetCenter - rayOrigin;

		// CHECK AGAIN FOR ANOTHER INTERSECTION BUT BASED ON POSITION
		*t = Vector3D::dot(oc, targetNormal) / parallelCheck;
		if (*t >= 0) {
			return 1;
		}
	}
	return 0;
}

unsigned int RaycastComponent::sphereCheck(const Vector3D& rayOrigin, const Vector3D& rayDir, const Vector3D& targetCenter, float* t)
{
	/* REFERENCE:
	* Paul Bourke: https://paulbourke.net/geometry/circlesphere/index.html#linesphere
	* Cherno: https://youtu.be/4NshnkzOdI0?si=OZll5GEPCP3DhxL1
	*/


	float sphereRadius;
	try {
		Vector3D scale = m_Owner->getTransform()->getScale();
		//	AVERAGE OF SCALE DIMENSIONS
		sphereRadius = (scale.x + scale.y + scale.z) / 3;
	}
	catch (std::exception e) {
		Debugger::Error("Failed to get Raycast Sphere radius");
		sphereRadius = 1;
	}

	Vector3D oc = rayOrigin - targetCenter;

	//(direction^2)t^2 + 2(direction*origin) + (origin^2 - r^2)
	float a = Vector3D::dot(rayDir, rayDir);
	float b = Vector3D::dot(oc, rayDir) * 2.0f;
	float c = Vector3D::dot(oc, oc) - (sphereRadius * sphereRadius);

	//b^2 - 4ac
	float discriminant = b * b - (4 * a * c);

	//SINGLE HIT
	if (discriminant == 0.f) {
		float t0 = (sqrt(discriminant) - b) / (2 * a);
		//DO NOT REGISTER HITS BEHIND THE ORIGIN
		if (t0 >= 0.f) {
			*t = t0;
			return 1;
		}
	}
	//2 HITS
	else if (discriminant > 0.f)
	{
		float t0 = (sqrt(discriminant) - b) / (2 * a);
		float t1 = (-sqrt(discriminant) - b) / (2 * a);

		//DETERMINE THE HIT POSITIONS IF t ARE VALID AND CLOSER
		if (t0 >= 0.f && t0 <= t1) {
			*t = t0;
			return 1;
		}
		else if (t1 >= 0.f && t1 <= t0) {
			*t = t1;
			return 1;
		}
	}

	return 0;
}

void RaycastComponent::onHit()
{
	Debugger::Success("Hit");
}
