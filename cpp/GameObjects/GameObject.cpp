#include "pch.h"
#include "GameObjects/GameObject.h"
#include "Rendering/ConstantBuffers.h"
#include "GameObjects/GameConstants.h"
#include "GameObject.h"

using namespace DirectX;

//--------------------------------------------------------------------------------

GameObject::GameObject() :
    m_normalMaterial(nullptr),
    m_hitMaterial(nullptr)
{
    m_active          = false;
    m_target          = false;
    m_targetId        = 0;
    m_hit             = false;
    m_ground          = true;

    m_position        = XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_velocity        = XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_defaultXAxis    = XMFLOAT3(1.0f, 0.0f, 0.0f);
    m_defaultYAxis    = XMFLOAT3(0.0f, 1.0f, 0.0f);
    m_defaultZAxis    = XMFLOAT3(0.0f, 0.0f, 1.0f);
    XMStoreFloat4x4(&m_modelMatrix, XMMatrixIdentity());

    m_hitTime         = 0.0f;

    m_animatePosition = nullptr;

	// Added Code
	xMin = 0;
	xMax = 0;
	yMin = 0;
	yMax = 0;
	zMin = 0;
	zMax = 0;
}

//----------------------------------------------------------------------

void GameObject::Render(
    _In_ ID3D11DeviceContext *context,
    _In_ ID3D11Buffer *primitiveConstantBuffer
    )
{
    if (!m_active || (m_mesh == nullptr) || (m_normalMaterial == nullptr))
    {
        return;
    }

    ConstantBufferChangesEveryPrim constantBuffer;

	// Put the model matrix info into a constant buffer, in world matrix.
    XMStoreFloat4x4(
        &constantBuffer.worldMatrix,
        XMMatrixTranspose(ModelMatrix())
        );

	// Check to see which material to use on the object.
	// If a collision (a hit) is detected, GameObject::Render checks the current context, which 
	// indicates whether the target has been hit by an ammo sphere. If the target has been hit, 
	// this method applies a hit material, which reverses the colors of the rings of the target to 
	// indicate a successful hit to the player. Otherwise, it applies the default material 
	// with the same method. In both cases, it sets the material by calling Material::RenderSetup, 
	// which sets the appropriate constants into the constant buffer. Then, it calls 
	// ID3D11DeviceContext::PSSetShaderResources to set the corresponding texture resource for the 
	// pixel shader, and ID3D11DeviceContext::VSSetShader and ID3D11DeviceContext::PSSetShader 
	// to set the vertex shader and pixel shader objects themselves, respectively.

    if (m_hit && m_hitMaterial != nullptr)
    {
        m_hitMaterial->RenderSetup(context, &constantBuffer);
    }
    else
    {
        m_normalMaterial->RenderSetup(context, &constantBuffer);
    }

	// Update the primitive constant buffer with the object model's info.
    context->UpdateSubresource(primitiveConstantBuffer, 0, nullptr, &constantBuffer, 0, 0);

	// Render the mesh.
	m_mesh->Render(context);
}

//----------------------------------------------------------------------

void GameObject::PlaySound(float impactSpeed, XMFLOAT3 eyePoint)
{
    if (m_hitSound != nullptr)
    {
        // Determine the sound volume adjustment based on velocity.
        float adjustment;
        if (impactSpeed < GameConstants::Sound::MinVelocity)
        {
            adjustment = 0.0f;  // Too soft.  Don't play sound.
        }
        else
        {
            adjustment = min(1.0f, impactSpeed / GameConstants::Sound::MaxVelocity);
            adjustment = GameConstants::Sound::MinAdjustment + adjustment * (1.0f - GameConstants::Sound::MinAdjustment);
        }

        // Compute Distance to eyePoint to adjust the volume based on that distance.
        XMVECTOR cameraToPosition = XMLoadFloat3(&eyePoint) - VectorPosition();
        float distToPositionSquared = XMVectorGetX(XMVector3LengthSq(cameraToPosition));

        float volume = min(distToPositionSquared, 1.0f);
        // Scale
        // Sound is proportional to how hard the ball is hitting.
        volume = adjustment * volume;

        m_hitSound->PlaySound(volume);
    }
}

//----------------------------------------------------------------------

bool GameObject::operator < (const GameObject^ gO)
{
	return false; // Comparison between Game Objects is senseless, so just return a dummy value.
}

bool GameObject::UpdateOverlapFlags(Axes axis, int oOHashID)
{
	switch (axis)
	{
	case Axes::X_Axis:
		// This is the first axis checked, so the corresponding YZOverlapBool structure will not be here yet.
		potentialCollisionsMap.emplace(oOHashID, IsYOverlap()); // We construct it as we add it into the map
		break;
	case Axes::Y_Axis:
		// Any objects that qualify for collision testing satisfy the overlap test on all three axes.
		// Therefore, the otherObject must already be in the map in order to bother setting its flag.
		if (potentialCollisionsMap.find(oOHashID) != potentialCollisionsMap.end()) {
			// We found the otherObject in the list.
			potentialCollisionsMap[oOHashID].isYOverlap = true;
		}
		break;
	default: // Defaults to Z axis
		// As above.
		if (potentialCollisionsMap.find(oOHashID) != potentialCollisionsMap.end()) {
			// Now we only care about otherObject if it is both already in the map
			// and has its isYOverlap flag set.
			if (potentialCollisionsMap[oOHashID].isYOverlap) {
				// Since we know that X and Y overlaps occurred
				// We know that these two objects qualify for further
				// collision detection testing.
				return true;
			}
		}
		break;
	}
	return false; // Signifies that we have yet to prove that these objects require further testing.
}

void GameObject::ClearOverlapFlags()
{
	potentialCollisionsMap.clear();
}