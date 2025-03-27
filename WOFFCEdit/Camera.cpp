#include "Camera.h"

Camera::Camera(): 
    m_position(11.5f, 6.19f, -7.61f),
      m_orientation(-18.0f, -32.0f, 0.0f),
      m_moveSpeed(0.30f),
      m_rotRate(3.0f)
{
    m_lookDirection = Vector3::Zero;
    m_right = Vector3::Zero;
}

void Camera::Update(InputCommands input, const DX::StepTimer& timer)
{
    // camera rotation

	if (input.rotRight)
		m_orientation.y -= m_rotRate;
	if (input.rotLeft)
		m_orientation.y += m_rotRate;
	if (input.rotUP)
	{
		m_orientation.x += m_rotRate;
		// prevent flipping
		if (m_orientation.x > 89.0f)
			m_orientation.x = 89.0f;
	}
	if (input.rotDown)
	{
		m_orientation.x -= m_rotRate;
		// prevent flipping
		if (m_orientation.x < -89.0f)
			m_orientation.x = -89.0f;
	}

	//ProcessMouseMovement(timer);

	float yaw = m_orientation.y * 3.1415f / 180.0f;
	float pitch = m_orientation.x * 3.1415f / 180.0f;

	m_lookDirection.x = cos(pitch) * sin(yaw);
	m_lookDirection.y = sin(pitch);
	m_lookDirection.z = cos(pitch) * cos(yaw);
	m_lookDirection.Normalize();

	//create right vector from look Direction
	m_right = m_lookDirection.Cross(Vector3::UnitY);
	m_right.Normalize();

	if (input.forward)
		m_position += m_lookDirection * m_moveSpeed;
	if (input.back)
		m_position -= m_lookDirection * m_moveSpeed;
	if (input.right)
		m_position += m_right * m_moveSpeed;
	if (input.left)
		m_position -= m_right * m_moveSpeed;
	if (input.up)
		m_position.y += m_moveSpeed;
	if (input.down)
		m_position.y -= m_moveSpeed;

	//update lookat point
	m_lookAt = m_position + m_lookDirection;
}

DirectX::SimpleMath::Matrix Camera::GetViewMatrix() const
{
	//apply camera vectors
    return Matrix::CreateLookAt(
		m_position, m_lookAt, 
		Vector3::UnitY);
}

DirectX::SimpleMath::Vector3 Camera::GetPosition() const
{
	return m_position;
}

DirectX::SimpleMath::Vector3 Camera::GetOrientation() const
{
	return m_orientation;
}

void Camera::ProcessMouseMovement(const Mouse::State& mouseState, 
	float deltaTime, bool& firstRelativeFrame)
{
	//Mouse::State mouseState = m_mouse->GetState();
	//float deltaTime = 1.0f;
	const float maxDeltaThreshold = 50.0f;
	float sensitivity = 10.0f;

	//if (timer.GetFramesPerSecond() != 0)
	//	deltaTime = 1.0f / timer.GetFramesPerSecond();

	if (mouseState.rightButton)
	{
		//m_mouse->SetMode(Mouse::MODE_RELATIVE);

		if (firstRelativeFrame)
		{
			firstRelativeFrame = false;
			return;
		}


		float offsetX = mouseState.x * sensitivity * deltaTime;
		float offsetY = mouseState.y * sensitivity * deltaTime;

		// Ignore offsets that are excessively large.
		if (fabs(offsetX) > maxDeltaThreshold || 
			fabs(offsetY) > maxDeltaThreshold)
		{
			offsetX = 0.0f;
			offsetY = 0.0f;
		}

		m_orientation.y -= offsetX;
		m_orientation.x -= offsetY;

		// Preventing flipping
		if (m_orientation.x > 89.0f)
			m_orientation.x = 89.0f;
		if (m_orientation.x < -89.0f)
			m_orientation.x = -89.0f;

		float yaw = DirectX::XMConvertToRadians(m_orientation.y);
		float pitch = DirectX::XMConvertToRadians(m_orientation.x);

		m_lookDirection.x = cosf(pitch) * sinf(yaw);
		m_lookDirection.y = sinf(pitch);
		m_lookDirection.z = cosf(pitch) * cosf(yaw);
		m_lookDirection.Normalize();

		m_right = m_lookDirection.Cross(Vector3::UnitY);
		m_right.Normalize();

	}
	//else
	//{
	//	m_mouse->SetMode(Mouse::MODE_ABSOLUTE);
	//	firstMouse = true;
	//	firstRelativeFrame = true;
	//}
}
