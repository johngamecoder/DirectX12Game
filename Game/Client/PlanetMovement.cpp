#include "pch.h"
#include "PlanetMovement.h"
#include "Transform.h"
#include "Timer.h"

PlanetMovement::PlanetMovement()
{

}

PlanetMovement::~PlanetMovement()
{

}

void PlanetMovement::SetPlanetRotationAndOrbit(float planetRotation, float planetOrbit)
{
	_planetRotation = planetRotation;
	_planetOrbit = planetOrbit;

	_orbitalTransform = make_shared<Transform>();
	GetTransform()->SetParent(_orbitalTransform);
}

void PlanetMovement::Update()
{
	if (_planetRotation > 0.f)
	{
		Vec3 localRot = GetTransform()->GetLocalRotation();
		localRot.y -= _planetRotation * DELTA_TIME;
		GetTransform()->SetLocalRotation(localRot);
	}

	if (_planetOrbit > 0.f)
	{
		_currentOrbit -= _planetOrbit * DELTA_TIME;
		_orbitalTransform->SetMatWorld(Matrix::CreateRotationY(_currentOrbit));
	}
}
