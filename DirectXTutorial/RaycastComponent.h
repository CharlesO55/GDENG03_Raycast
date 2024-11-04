#pragma once
#include "Component.h"

#include "Vector3D.h"


class RaycastComponent : public Component
{
public:
	enum class INTERSECTION_TYPE
	{
		SPHERE_CAST,
		PLANE_CAST
	};
	
	
	RaycastComponent(SceneObject* owner, INTERSECTION_TYPE type);
	

	void update() override {};
	
	virtual void onHit();

	unsigned int checkRaycastHits(const Vector3D& rayOrigin, const Vector3D& rayDir, const Vector3D& targetCenter, const Vector3D& targetNormal, float* t);
	unsigned int planeCheck(const Vector3D& rayOrigin, const Vector3D& rayDir, const Vector3D& targetCenter, const Vector3D& targetNormal, float* t);
	unsigned int sphereCheck(const Vector3D& rayOrigin, const Vector3D& rayDir, const Vector3D& targetCenter, float* t);

private:
	INTERSECTION_TYPE m_IntersectionType;
};