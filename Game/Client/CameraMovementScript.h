#pragma once
#include "MonoBehaviour.h"

class CameraMovementScript : public MonoBehaviour
{
public:
	CameraMovementScript();
	virtual ~CameraMovementScript();

	virtual void LateUpdate() override;

private:
	float		_speed = 100.f;
	float		_mouseSpeed = 0.01f;
	DWORD		_dwMouseX = 0;
	DWORD		_dwMouseY = 0;
};