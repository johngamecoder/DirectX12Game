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

void PlanetMovement::SetPlanetOrbit(float planetOrbit)
{
	_planetOrbit = planetOrbit;

	_movementTransform = make_shared<Transform>();
	GetTransform()->SetAdditionalTransform(_movementTransform);
}

void PlanetMovement::Update()
{
	//if (_planetRotation > 0.f)
	//{
	//	Vec3 localRot = GetTransform()->GetLocalRotation();
	//	localRot.y -= _planetRotation;
	//	GetTransform()->SetLocalRotation(localRot);
	//}

	if (_planetOrbit > 0.f)
	{
		_currentOrbit -= _planetOrbit;
		_movementTransform->SetMatWorld(Matrix::CreateRotationY(_currentOrbit));
	}
}
