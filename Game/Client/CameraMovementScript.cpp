#include "pch.h"
#include "Engine.h"
#include "CameraMovementScript.h"
#include "Input.h"
#include "Component.h"
#include "Transform.h"
#include "Timer.h"
#include "SceneManager.h"

CameraMovementScript::CameraMovementScript()
{

}

CameraMovementScript::~CameraMovementScript()
{

}

void CameraMovementScript::LateUpdate()
{
	Vec3 pos = GetTransform()->GetLocalPosition();

	if (INPUT->GetButton(KEY_TYPE::W))
		pos += GetTransform()->GetLook() * _speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::S))
		pos -= GetTransform()->GetLook() * _speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::A))
		pos -= GetTransform()->GetRight() * _speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::D))
		pos += GetTransform()->GetRight() * _speed * DELTA_TIME;
	
	if (INPUT->GetButton(KEY_TYPE::Q))
		pos -= GetTransform()->GetUp() * _speed * DELTA_TIME;
	
	if (INPUT->GetButton(KEY_TYPE::E))
		pos += GetTransform()->GetUp() * _speed * DELTA_TIME;

	GetTransform()->SetLocalPosition(pos);

	if (INPUT->GetButton(KEY_TYPE::G))
	{
		Vec3 rotation = GetTransform()->GetLocalRotation();
		rotation.x += DELTA_TIME * 0.5f;
		GetTransform()->SetLocalRotation(rotation);
	}

	if (INPUT->GetButton(KEY_TYPE::T))
	{
		Vec3 rotation = GetTransform()->GetLocalRotation();
		rotation.x -= DELTA_TIME * 0.5f;
		GetTransform()->SetLocalRotation(rotation);
	}

	if (INPUT->GetButton(KEY_TYPE::H))
	{
		Vec3 rotation = GetTransform()->GetLocalRotation();
		rotation.y += DELTA_TIME * 0.5f;
		GetTransform()->SetLocalRotation(rotation);
	}

	if (INPUT->GetButton(KEY_TYPE::F))
	{
		Vec3 rotation = GetTransform()->GetLocalRotation();
		rotation.y -= DELTA_TIME * 0.5f;
		GetTransform()->SetLocalRotation(rotation);
	}

	if (INPUT->GetButtonDown(KEY_TYPE::LBUTTON))
	{
		const POINT& pos = INPUT->GetMousePos();
		GET_SINGLE(SceneManager)->Pick(pos.x, pos.y);
	}

	if (INPUT->GetButtonDown(KEY_TYPE::ESC))
	{
		GEngine->Exit();
	}
}
