#pragma once

#include <d3d11.h>
#include "InputCommands.h"
#include "StepTimer.h"
#include "DirectXMath.h"
#include <SimpleMath.h>
#include <Mouse.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;


class Camera
{
public:
	Camera();

	void Update(InputCommands input, const DX::StepTimer& timer);
	void ProcessMouseMovement(const DirectX::Mouse::State& mouseState, float deltaTime, bool& firstRelativeFrame);

	Matrix GetViewMatrix() const;
    Vector3 GetPosition() const;
    Vector3 GetOrientation() const;

private:
    Vector3 m_position;
    Vector3 m_orientation;
    Vector3 m_lookAt;
    Vector3 m_lookDirection;
    Vector3 m_right;

    float m_moveSpeed;
    float m_rotRate;
};

