#pragma once

// Sphere:
// This class is a specialization of GameObject that represents a sphere primitive.
// The sphere is defined by a 'position' and radius.

#include "GameObjects/GameObject.h"

ref class Sphere: public GameObject
{
internal:
    Sphere();
    Sphere(DirectX::XMFLOAT3 pos, float radius);

    void Position(DirectX::XMFLOAT3 position);
    void Position(DirectX::XMVECTOR position);
    void Radius(float radius);
    float Radius();

    virtual bool IsTouching(
        DirectX::XMFLOAT3 point,
        float radius,
        _Out_ DirectX::XMFLOAT3 *contact,
        _Out_ DirectX::XMFLOAT3 *normal
        ) override;

	//virtual bool IsColliding(GameObject^ otherObject) override;

protected:
	virtual void UpdatePosition() override;

private:
    void Update();
	
    float m_radius;
};


__forceinline void Sphere::Position(DirectX::XMFLOAT3 position)
{
    m_position = position;
	UpdatePosition();
	Update();
}

__forceinline void Sphere::Position(DirectX::XMVECTOR position)
{
    DirectX::XMStoreFloat3(&m_position, position);
	UpdatePosition();
	Update();
}

__forceinline void Sphere::Radius(float radius)
{
    m_radius = radius;
    Update();
}

__forceinline float Sphere::Radius()
{
    return m_radius;
}