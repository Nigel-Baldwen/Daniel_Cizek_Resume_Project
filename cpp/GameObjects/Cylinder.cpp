#include "pch.h"
#include "GameObjects/Cylinder.h"

using namespace DirectX;

//----------------------------------------------------------------------

Cylinder::Cylinder()
{
    Initialize(XMFLOAT3(0.0f, 0.0f, 0.0f), 1.0f, XMFLOAT3(0.0f, 0.0f, 1.0f));
		
	// This cylinder is axis aligned with Z. It has an x extent of 
	// O - R to O + R where O is the origin and R is the radius.
	// similarly for the y extent.
	// It's z extent however is just O to P where P is the point [0,0,1]
	
	xMin = -1; 
	xMax =  1;
	yMin = -1;
	yMax =  1;
	zMin =  0;
	zMax =  1;
}

//----------------------------------------------------------------------

Cylinder::Cylinder(
    XMFLOAT3 position,
    float radius,
    XMFLOAT3 direction
    )
{
    Initialize(position, radius, direction);

	// [ 1 - direction unit normal component ] * radius this is the
	// magnitude of the direction vector along the face. The endpoints
	// on the face lie at P +/- this value.
	
	float rExtent;

	// m_axis, set in Initialize, gives the normalized direction vector
	// for this cylinder. Therefore, we can simply use its components.
	
	// X Components
	rExtent = (1 - m_axis.x) * m_radius; // rExtent along the x direction vector
	float one = m_position.x + rExtent, two = m_position.x - rExtent, // 'Origin' X values
		tre = direction.x + rExtent, fur = direction.x - rExtent; // 'Terminal Point' X values

	xMin = min(min(one, two), min(tre, fur));
	xMax = max(max(one, two), max(tre, fur));
	
	// Y components
	rExtent = (1 - m_axis.y) * m_radius; // rExtent along the x direction vector
	one = m_position.y + rExtent, two = m_position.y - rExtent, // 'Origin' Y values
		tre = direction.y + rExtent, fur = direction.y - rExtent; // 'Terminal Point' Y values

	yMin = min(min(one, two), min(tre, fur));
	yMax = max(max(one, two), max(tre, fur));

	// Z components
	rExtent = (1 - m_axis.z) * m_radius; // rExtent along the x direction vector
	one = m_position.z + rExtent, two = m_position.z - rExtent, // 'Origin' Z values
		tre = direction.z + rExtent, fur = direction.z - rExtent; // 'Terminal Point' Z values

	zMin = min(min(one, two), min(tre, fur));
	zMax = max(max(one, two), max(tre, fur));

}

//----------------------------------------------------------------------

void Cylinder::Initialize(
    XMFLOAT3 position,
    float radius,
    XMFLOAT3 direction
    )
{
    m_position = position;
    m_radius = radius;
    m_length = XMVectorGetX(XMVector3Length(XMLoadFloat3(&direction)));
    XMStoreFloat3(&m_axis, XMVector3Normalize(XMLoadFloat3(&direction)));

    XMVECTOR up = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
    float angle1 = XMVectorGetX(
        XMVector3AngleBetweenVectors(up, XMLoadFloat3(&m_axis))
        );

    XMMATRIX mat1 = XMMatrixIdentity();

    if ((angle1 * angle1) > 0.025)
    {
        XMVECTOR axis1 = XMVector3Cross(up, XMLoadFloat3(&m_axis));

        mat1 = XMMatrixRotationAxis(axis1, angle1);
    }
    XMStoreFloat4x4(&m_rotationMatrix, mat1);

    XMStoreFloat4x4(
        &m_modelMatrix,
        XMMatrixScaling(m_radius, m_radius, m_length) *
        mat1 *
        XMMatrixTranslation(m_position.x, m_position.y, m_position.z)
        );
}

//--------------------------------------------------------------------------------

void Cylinder::UpdatePosition()
{
    XMStoreFloat4x4(
        &m_modelMatrix,
        XMMatrixScaling(m_radius, m_radius, m_length) *
        XMLoadFloat4x4(&m_rotationMatrix) *
        XMMatrixTranslation(m_position.x, m_position.y, m_position.z)
        );

	// [ 1 - direction unit normal component ] * radius this is the
	// magnitude of the direction vector along the face. The endpoints
	// on the face lie at P +/- this value.
	
	float rExtent;

	// m_axis, set in Initialize, gives the normalized direction vector
	// for this cylinder. Therefore, we can simply use its components.
	
	// Caluclate the point at the center of the end of the cylinder.
	XMFLOAT3 direction;
	XMStoreFloat3(&direction, XMLoadFloat3(&m_position) + XMVectorScale(XMLoadFloat3(&m_axis), m_length));

	// X Components
	rExtent = (1 - m_axis.x) * m_radius; // rExtent along the x direction vector
	float one = m_position.x + rExtent, two = m_position.x - rExtent, // 'Origin' X values
		tre = direction.x + rExtent, fur = direction.x - rExtent; // 'Terminal Point' X values

	xMin = min(min(one, two), min(tre, fur));
	xMax = max(max(one, two), max(tre, fur));
	
	// Y components
	rExtent = (1 - m_axis.y) * m_radius; // rExtent along the x direction vector
	one = m_position.y + rExtent, two = m_position.y - rExtent, // 'Origin' Y values
		tre = direction.y + rExtent, fur = direction.y - rExtent; // 'Terminal Point' Y values

	yMin = min(min(one, two), min(tre, fur));
	yMax = max(max(one, two), max(tre, fur));

	// Z components
	rExtent = (1 - m_axis.z) * m_radius; // rExtent along the x direction vector
	one = m_position.z + rExtent, two = m_position.z - rExtent, // 'Origin' Z values
		tre = direction.z + rExtent, fur = direction.z - rExtent; // 'Terminal Point' Z values

	zMin = min(min(one, two), min(tre, fur));
	zMax = max(max(one, two), max(tre, fur));
}

//--------------------------------------------------------------------------------

bool Cylinder::IsTouching(
    XMFLOAT3 point,
    float radius,
    _Out_ XMFLOAT3 *contact,
    _Out_ XMFLOAT3 *normal
    )
{
    XMVECTOR p0;
    XMVECTOR axis;
    XMVECTOR p1;
    XMVECTOR px;

    // Determine if a point is within radius distance of the cylinder and
    // return the point of contact (projection of the point onto the cylinder).

    p0 = XMLoadFloat3(&m_position);
    axis = XMLoadFloat3(&m_axis);
    p1 = p0 + axis * m_length;
    px = XMLoadFloat3(&point);

    float dist = XMVectorGetX(
        XMVector3LinePointDistance(p0, p1, px)
        );

    // Projection of the point onto the Vector.
    float dist2 = XMVectorGetX(
        XMVector3Dot(px - p0, axis)
        );

    XMVECTOR ptOnVector =  p0 + dist2 * axis;

    XMVECTOR normalVector = XMVector3Normalize(px - ptOnVector);

    XMStoreFloat3(normal, normalVector);
    XMStoreFloat3(contact, ptOnVector + normalVector * m_radius);

    if (dist < 0.0f)
    {
        dist *= -1.0f;
    }

    if (dist < (radius + m_radius))
    {
        if (dist2 >= 0.0f && dist2 <= m_length)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

GameObjectType Cylinder::Type()
{
	return GameObjectType::Cylinder;
}


//--------------------------------------------------------------------------------
