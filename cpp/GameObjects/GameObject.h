#pragma once

// GameObject:
// This is the class representing a generic object in the 3D world of the game.  There are
// specific sub-classes that have specific geometric shapes.  This class contains all the
// properties of objects that are common.
//
// During the game physics calculations the IsTouching method will be called to determine
// the object's proximity to a point.  It is expected the sub-classes will replace this method.
// The Render method will be called during rendering to include the object in the generation of
// the scene.

#include "Resources/MeshObject.h"
#include "Audio/SoundEffect.h"
#include "GameObjects/Animate.h"
#include "Rendering/Material.h"
#include <unordered_map>
#include "GameObjects/AxesEnum.h"
#include "GameObjects/GameObjectTypeEnum.h"

ref class GameObject
{
internal:
	GameObject();

	size_t hashCode;

	// Expect the IsTouching method to be overloaded by subclasses.
	virtual bool IsTouching(
		DirectX::XMFLOAT3 /* point */,
		float /* radius */,
		_Out_ DirectX::XMFLOAT3 *contact,
		_Out_ DirectX::XMFLOAT3 *normal
	)
	{
		*contact = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		*normal = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
		return false;
	};

	void Render(
		_In_ ID3D11DeviceContext *context,
		_In_ ID3D11Buffer *primitiveConstantBuffer
	);

	void Active(bool active);
	bool Active();
	void Target(bool target);
	bool Target();
	void Hit(bool hit);
	bool Hit();
	void OnGround(bool ground);
	bool OnGround();
	void TargetId(int targetId);
	int  TargetId();
	void HitTime(float t);
	float HitTime();

	void     AnimatePosition(_In_opt_ Animate^ animate);
	Animate^ AnimatePosition();

	void         HitSound(_In_ SoundEffect^ hitSound);
	SoundEffect^ HitSound();

	void PlaySound(float impactSpeed, DirectX::XMFLOAT3 eyePoint);

	void Mesh(_In_ MeshObject^ mesh);

	void NormalMaterial(_In_ Material^ material);
	Material^ NormalMaterial();
	void HitMaterial(_In_ Material^ material);
	Material^ HitMaterial();

	void Position(DirectX::XMFLOAT3 position);
	void Position(DirectX::XMVECTOR position);
	void Velocity(DirectX::XMFLOAT3 velocity);
	void Velocity(DirectX::XMVECTOR velocity);
	DirectX::XMMATRIX ModelMatrix();
	DirectX::XMFLOAT3 Position();
	DirectX::XMVECTOR VectorPosition();
	DirectX::XMVECTOR VectorVelocity();
	DirectX::XMFLOAT3 Velocity();

	bool operator < (const GameObject^ gO);
	bool UpdateOverlapFlags(Axes axis, int oOHashID);
	void ClearOverlapFlags();

	virtual GameObjectType Type();

	float XMin();
	float XMax();
	float YMin();
	float YMax();
	float ZMin();
	float ZMax();
	

protected private:
	virtual void UpdatePosition() {};
	// Object Data
	bool                m_active;
	bool                m_target;
	int                 m_targetId;
	bool                m_hit;
	bool                m_ground;

	DirectX::XMFLOAT3   m_position;
	DirectX::XMFLOAT3   m_velocity;
	DirectX::XMFLOAT4X4 m_modelMatrix;

	Material^           m_normalMaterial;
	Material^           m_hitMaterial;

	DirectX::XMFLOAT3   m_defaultXAxis;
	DirectX::XMFLOAT3   m_defaultYAxis;
	DirectX::XMFLOAT3   m_defaultZAxis;

	float               m_hitTime;

	Animate^            m_animatePosition;
	MeshObject^         m_mesh;

	SoundEffect^        m_hitSound;

	// Tools for Collision Detection

	// Basically just a wrapper for a bool in order
	// to smoothly use the unordered_map below.
	struct IsYOverlap {
		bool isYOverlap = false;
	};

	// These values describe the object's bounding box
	float xMin, xMax, yMin, yMax, zMin, zMax;

	// This map tracks XYZ overlaps for each potentially
	// colliding other object. The 'int' portion is the
	// GetHashCode() return value of the other object.
	// The usage logic is as follows:
	// 1.) The addition of a new key signifies an X Overlap.
	// 2.) When discovering Y Overlaps, we only care about
	// keys already present in the map. Set the bool to
	// true for these values.
	// 3.) When discovering Z Overlaps, we only care about
	// keys already present in the map which also have
	// a bool member set to true. The matched key signifies
	// the X Overlap and the true bool signifies the Y Overlap. 
	std::unordered_map<int, IsYOverlap> potentialCollisionsMap;
};

__forceinline float GameObject::XMin() {
	return xMin;
}

__forceinline float GameObject::XMax() {
	return xMax;
}

__forceinline float GameObject::YMin() {
	return yMin;
}

__forceinline float GameObject::YMax() {
	return yMax;
}

__forceinline float GameObject::ZMin() {
	return zMin;
}

__forceinline float GameObject::ZMax() {
	return zMax;
}

__forceinline void GameObject::Active(bool active)
{
	m_active = active;
}

__forceinline bool GameObject::Active()
{
	return m_active;
}

__forceinline void GameObject::Target(bool target)
{
	m_target = target;
}

__forceinline bool GameObject::Target()
{
	return m_target;
}

__forceinline void GameObject::Hit(bool hit)
{
	m_hit = hit;
}

__forceinline bool GameObject::Hit()
{
	return m_hit;
}

__forceinline void GameObject::OnGround(bool ground)
{
	m_ground = ground;
}

__forceinline bool GameObject::OnGround()
{
	return m_ground;
}

__forceinline void GameObject::TargetId(int targetId)
{
	m_targetId = targetId;
}

__forceinline int GameObject::TargetId()
{
	return m_targetId;
}

__forceinline void GameObject::HitTime(float t)
{
	m_hitTime = t;
}

__forceinline float GameObject::HitTime()
{
	return m_hitTime;
}

__forceinline void GameObject::Position(DirectX::XMFLOAT3 position)
{
	m_position = position;
	// Update any internal states that are dependent on the position.
	// UpdatePosition is a virtual function that is specific to the derived class.
	UpdatePosition();
}

__forceinline void GameObject::Position(DirectX::XMVECTOR position)
{
	XMStoreFloat3(&m_position, position);
	// Update any internal states that are dependent on the position.
	// UpdatePosition is a virtual function that is specific to the derived class.
	UpdatePosition();
}

__forceinline DirectX::XMFLOAT3 GameObject::Position()
{
	return m_position;
}

__forceinline DirectX::XMVECTOR GameObject::VectorPosition()
{
	return DirectX::XMLoadFloat3(&m_position);
}

__forceinline void GameObject::Velocity(DirectX::XMFLOAT3 velocity)
{
	m_velocity = velocity;
}

__forceinline void GameObject::Velocity(DirectX::XMVECTOR velocity)
{
	XMStoreFloat3(&m_velocity, velocity);
}

__forceinline DirectX::XMFLOAT3 GameObject::Velocity()
{
	return m_velocity;
}

__forceinline DirectX::XMVECTOR GameObject::VectorVelocity()
{
	return DirectX::XMLoadFloat3(&m_velocity);
}

__forceinline void GameObject::AnimatePosition(_In_opt_ Animate^ animate)
{
	m_animatePosition = animate;
}

__forceinline Animate^ GameObject::AnimatePosition()
{
	return m_animatePosition;
}

__forceinline void GameObject::NormalMaterial(_In_ Material^ material)
{
	m_normalMaterial = material;
}

__forceinline Material^ GameObject::NormalMaterial()
{
	return m_normalMaterial;
}

__forceinline void GameObject::HitMaterial(_In_ Material^ material)
{
	m_hitMaterial = material;
}

__forceinline Material^ GameObject::HitMaterial()
{
	return m_hitMaterial;
}

__forceinline void GameObject::Mesh(_In_ MeshObject^ mesh)
{
	m_mesh = mesh;
}

__forceinline void GameObject::HitSound(_In_ SoundEffect^ hitSound)
{
	m_hitSound = hitSound;
}

__forceinline SoundEffect^ GameObject::HitSound()
{
	return m_hitSound;
}

__forceinline DirectX::XMMATRIX GameObject::ModelMatrix()
{
	return DirectX::XMLoadFloat4x4(&m_modelMatrix);
}