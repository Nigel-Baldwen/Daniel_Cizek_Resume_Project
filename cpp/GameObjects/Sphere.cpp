#include "pch.h"
#include "GameObjects/Sphere.h"

using namespace DirectX;

//----------------------------------------------------------------------

Sphere::Sphere()
{
    m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_radius = 1.0f;
	
	// A sphere's bounding box never rotates and is always given by
	// Adding/Subtracting its radius to its position on the relevant
	// axis.
	//xMin = -1.0f;
	//xMax = 1.0f;
	//yMin = -1.0f;
	//yMax = 1.0f;
	//zMin = -1.0f;
	//zMax = 1.0f;
    
	Update();
}

//----------------------------------------------------------------------

Sphere::Sphere(
    DirectX::XMFLOAT3 position,
    float radius
    )
{
    m_position = position;
    m_radius = radius;
    
	// A sphere's bounding box never rotates and is always given by
	// Adding/Subtracting its radius to its position on the relevant
	// axis.
	//xMin = position.x - radius;
	//xMax = position.x + radius;
	//yMin = position.y - radius;
	//yMax = position.y + radius;
	//zMin = position.z - radius;
	//zMax = position.z + radius;

	Update();
}

//----------------------------------------------------------------------

void Sphere::Update()
{
    XMStoreFloat4x4(
        &m_modelMatrix,
        XMMatrixScaling(m_radius, m_radius, m_radius) *
        XMMatrixTranslation(m_position.x, m_position.y, m_position.z)
        );
}

//----------------------------------------------------------------------

void Sphere::UpdatePosition()
{
	// The only relevant change is that the bounding box needs
	// to be shifted in accordance with the new position.

	//xMin = m_position.x - m_radius;
	//xMax = m_position.x + m_radius;
	//yMin = m_position.y - m_radius;
	//yMax = m_position.y + m_radius;
	//zMin = m_position.z - m_radius;
	//zMax = m_position.z + m_radius;
}

bool Sphere::IsTouching(
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
    XMStoreFloat3(contact, oneToTwo * m_radius);

    if (distance < 0.0f)
    {
        distance *= -1.0f;
    }

    if (distance < (radius + m_radius))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//----------------------------------------------------------------------

/*
bool IsColliding(GameObject^ otherObject) {
	// First we narrow in on the type of the other object.
	// Then we do collision testing specifically for that type.
	switch (otherObject->Type())
	{
	case GameObject::GameObjectType::Sphere:
		return true; // return IsColliding(Sphere^ otherSphere);
	case GameObject::GameObjectType::Cylinder:
		return true; // return IsColliding(Cylinder^ theCylinder);
	case GameObject::GameObjectType::Face:
		return true; // return IsColliding(Face^ theFace);
	case GameObject::GameObjectType::RectangularPrism:
		return true; // return IsColliding(RectangularPrism^ theRectangularPrism);
	default:
		return false;
	}
}
*/