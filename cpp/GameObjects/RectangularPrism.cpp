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

// TODO :: This will obviously be changed to be correct eventually.
// Currently, we will just do something dumb and return false.
bool RectangularPrism::IsTouching(
	XMFLOAT3 point,
	float radius,
	_Out_ XMFLOAT3 *contact,
	_Out_ XMFLOAT3 *normal
)
{
	auto dPoint = point;
	auto dRadius = radius;
	dRadius++;
	auto dID = XMVECTOR();
	XMStoreFloat3(contact, dID);
	XMStoreFloat3(normal, dID);

	return false;
}

GameObjectType RectangularPrism::Type()
{
	return GameObjectType::RectangularPrism;
}

//----------------------------------------------------------------------