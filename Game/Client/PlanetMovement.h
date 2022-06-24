#pragma once
#include "MonoBehaviour.h"
class PlanetMovement : public MonoBehaviour
{
public:
	PlanetMovement();
	virtual ~PlanetMovement();
	
	void SetPlanetOrbit(float planetOrbit);

	virtual void Update() override;

private:
	shared_ptr<Transform> _movementTransform;

	float _planetOrbit = 0.f; //°øÀü
	float _currentOrbit = 0.f;
};
