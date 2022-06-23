#pragma once
#include "MonoBehaviour.h"
class PlanetMovement : public MonoBehaviour
{
public:
	PlanetMovement();
	virtual ~PlanetMovement();
	
	void SetPlanetRotationAndOrbit(float planetRotation, float planetOrbit);

	virtual void Update() override;

private:
	shared_ptr<Transform> _orbitalTransform;

	float _planetRotation = 0.f; //자전
	float _planetOrbit = 0.f; //공전

	float _currentOrbit = 0.f;
};
