#include "pch.h"
#include "GameObjects/RectangularPrism.h"

using namespace DirectX;

//----------------------------------------------------------------------

RectangularPrism::RectangularPrism()
{
	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	Update();
}

//----------------------------------------------------------------------

RectangularPrism::RectangularPrism(	DirectX::XMFLOAT3 xyzPosition,
									DirectX::XMFLOAT3 whdSize,
									DirectX::XMFLOAT3 xyzRotation)
{
	m_position = xyzPosition;
	m_size = whdSize;
	m_rotation = xyzRotation;
	Update();
}

//----------------------------------------------------------------------

void RectangularPrism::Update()
{
	//XMStoreFloat4x4(
	//	&m_modelMatrix,
	//	XMMatrixScaling(m_radius, m_radius, m_radius) *
	//	XMMatrixTranslation(m_position.x, m_position.y, m_position.z)
	//);
}

//----------------------------------------------------------------------

bool RectangularPrism::IsTouching(
	XMFLOAT3 point,
	float radius,
	_Out_ XMFLOAT3 *contact,
	_Out_ XMFLOAT3 *normal
)
{
	// Check collision between instances One and Two.
	// oneToTwo is the collision normal vector.
	XMVECTOR oneToTwo = XMLoadFloat3(&m_position) - XMLoadFloat3(&point);

	float distance = XMVectorGetX(XMVector3Length(oneToTwo));

	oneToTwo = XMVector3Normalize(oneToTwo);
	XMStoreFloat3(normal, oneToTwo);
	//XMStoreFloat3(contact, oneToTwo * m_radius);

	if (distance < 0.0f)
	{
		distance *= -1.0f;
	}

	//if (distance < (radius + m_radius))
	//{
	//	return true;
	//}
	//else
	//{
		return false;
	//}
}

GameObjectType RectangularPrism::Type()
{
	return GameObjectType::RectangularPrism;
}

//----------------------------------------------------------------------