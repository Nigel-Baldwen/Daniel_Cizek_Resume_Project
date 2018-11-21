#pragma once

// RectangularPrism:
// This class is a specialization of GameObject that represents
// a right-rectangular prism primitive.
// The prism is defined by an upper leftmost (closest to 0, 0 ,0)
// corner 'position', width, height, depth,
// and a set of rotation values for each axis.
// These elements are represented by three, three-component vectors.

#include "GameObjects/GameObject.h"

ref class RectangularPrism : public GameObject
{
internal:
	RectangularPrism();
	RectangularPrism(	DirectX::XMFLOAT3 xyzPosition,
						DirectX::XMFLOAT3 whdSize,
						DirectX::XMFLOAT3 xyzRotation);

	void Position(DirectX::XMFLOAT3 xyzPosition);
	void Position(DirectX::XMVECTOR xyzPosition);

	void Size(DirectX::XMFLOAT3 whdSize);
	void Size(DirectX::XMVECTOR whdSize);

	void Rotation(DirectX::XMFLOAT3 xyzRotation);
	void Rotation(DirectX::XMVECTOR xyzRotation);

	DirectX::XMFLOAT3 Size();
	DirectX::XMFLOAT3 Rotation();
	
	virtual bool IsTouching(
		DirectX::XMFLOAT3 point,
		float radius,
		_Out_ DirectX::XMFLOAT3 *contact,
		_Out_ DirectX::XMFLOAT3 *normal
	) override;

private:
	void Update();

	DirectX::XMFLOAT3 m_size, m_rotation;
};


__forceinline void RectangularPrism::Position(DirectX::XMFLOAT3 xyzPosition)
{
	m_position = xyzPosition;
	Update();
}

__forceinline void RectangularPrism::Position(DirectX::XMVECTOR position)
{
	DirectX::XMStoreFloat3(&m_position, position);
	Update();
}

__forceinline void RectangularPrism::Size(DirectX::XMFLOAT3 whdSize) {
	m_size = whdSize;
	Update();
}

__forceinline void RectangularPrism::Size(DirectX::XMVECTOR whdSize) {
	DirectX::XMStoreFloat3(&m_size, whdSize);
	Update();
}

__forceinline void RectangularPrism::Rotation(DirectX::XMFLOAT3 xyzRotation)
{
	m_rotation = xyzRotation;
	Update();
}

__forceinline void RectangularPrism::Rotation(DirectX::XMVECTOR xyzRotation)
{
	DirectX::XMStoreFloat3(&m_rotation, xyzRotation);
	Update();
}

__forceinline DirectX::XMFLOAT3 RectangularPrism::Size()
{
	return m_size;
}

__forceinline DirectX::XMFLOAT3 RectangularPrism::Rotation()
{
	return m_rotation;
}