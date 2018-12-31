#include "pch.h"
#include "GameObjects/CollisionDetectionTools/PrecisionCollision.h"

using namespace DirectX;

namespace PrecisionCollision {
	namespace { // Anonymous namespace 
		bool SphereSphere(Sphere^ ibb, Sphere^ obb) {

			auto ibbPos = ibb->Position(),
				obbPos = obb->Position();

			XMVECTOR ibbToObb = XMLoadFloat3(&ibbPos) - XMLoadFloat3(&obbPos);
			float distance = XMVectorGetX(XMVector3Length(ibbToObb));

			ibbToObb = XMVector3Normalize(ibbToObb);

			// Ensure we are using the magnitude of the distance value
			if (distance < 0.0f) {
				distance *= -1.0f;
			}

			if (distance < (ibb->Radius() + obb->Radius())) {
				OutputDebugStringW(L"REEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n");
				return true;
			}
			else {
				OutputDebugStringW(L"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
				return false;
			}
		}
		
		// TODO :: Implement actual detection
		bool SphereCylinder(Sphere^ ibb, Cylinder^ obb) {
			return true; // Dummy Return
		}
	
		// TODO :: Implement actual detection
		bool SphereFace(Sphere^ ibb, Face^ obb) {
			return true; // Dummy Return
		}

		// TODO :: Implement actual detection
		bool SphereRectangularPrism(Sphere^ ibb, RectangularPrism^ obb) {
			return true; // Dummy Return
		}

		// TODO :: Implement actual detection
		bool CylinderCylinder(Cylinder^ ibb, Cylinder^ obb) {
			return true; // Dummy Return
		}

		// TODO :: Implement actual detection
		bool CylinderFace(Cylinder^ ibb, Face^ obb) {
			return true; // Dummy Return
		}

		// TODO :: Implement actual detection
		bool CylinderRectangularPrism(Cylinder^ ibb, RectangularPrism^ obb) {
			return true; // Dummy Return
		}

		// TODO :: Implement actual detection
		bool FaceFace(Face^ ibb, Face^ obb) {
			return true; // Dummy Return
		}

		// TODO :: Implement actual detection
		bool FaceRectangularPrism(Face^ ibb, RectangularPrism^ obb) {
			return true; // Dummy Return
		}

		// TODO :: Implement actual detection
		bool RectangularPrismRectangularPrism(RectangularPrism^ ibb, RectangularPrism^ obb) {
			return true; // Dummy Return
		}

	};

	bool PrecisionCollision::IsColliding(GameObject^ ibb, GameObject^ obb) {
		// Right now there are few enough item types that I can reasonably use
		// a nested switch statement. However, this is a graceless solution that
		// would ideally be replaced either by some sort of static const function
		// mapping or replaced by essentially adding enum values together according
		// to something like ibb.Type() + obb.Type() * #ofObjectTypes.
		// Either solution is currently more trouble than it's worth, but they are
		// worth thinking about in advance to know that it is a requirement when
		// scaling the object system up.
		switch (ibb->Type())
		{
		case GameObjectType::Sphere:
			switch (obb->Type())
			{
			case GameObjectType::Sphere:
				return SphereSphere(dynamic_cast<Sphere^> (ibb), dynamic_cast<Sphere^>(obb));
				break;
			case GameObjectType::Cylinder:
				return SphereCylinder(dynamic_cast<Sphere^> (ibb), dynamic_cast<Cylinder^>(obb));
				break;
			case GameObjectType::Face:
				return SphereFace(dynamic_cast<Sphere^> (ibb), dynamic_cast<Face^>(obb));
				break;
			case GameObjectType::RectangularPrism:
				return SphereRectangularPrism(dynamic_cast<Sphere^> (ibb), dynamic_cast<RectangularPrism^>(obb));
				break;
			default: // obb->Type()== UNKNOWN -> No sensible return, so just say true since the bounding box test passed
				return true;
			}
		case GameObjectType::Cylinder:
			switch (obb->Type())
			{
			case GameObjectType::Sphere:
				return SphereCylinder(dynamic_cast<Sphere^> (obb), dynamic_cast<Cylinder^>(ibb));
				break;
			case GameObjectType::Cylinder:
				return CylinderCylinder(dynamic_cast<Cylinder^> (ibb), dynamic_cast<Cylinder^>(obb));
				break;
			case GameObjectType::Face:
				return CylinderFace(dynamic_cast<Cylinder^> (ibb), dynamic_cast<Face^>(obb));
				break;
			case GameObjectType::RectangularPrism:
				return CylinderRectangularPrism(dynamic_cast<Cylinder^> (ibb), dynamic_cast<RectangularPrism ^>(obb));
				break;
			default: // obb->Type()== UNKNOWN -> No sensible return, so just say true since the bounding box test passed
				return true;
			}
		case GameObjectType::Face:
			switch (obb->Type())
			{
			case GameObjectType::Sphere:
				return SphereFace(dynamic_cast<Sphere^> (obb), dynamic_cast<Face^>(ibb));
				break;
			case GameObjectType::Cylinder:
				return CylinderFace(dynamic_cast<Cylinder^> (obb), dynamic_cast<Face^>(ibb));
				break;
			case GameObjectType::Face:
				return FaceFace(dynamic_cast<Face^> (ibb), dynamic_cast<Face^>(obb));
				break;
			case GameObjectType::RectangularPrism:
				return FaceRectangularPrism(dynamic_cast<Face^> (ibb), dynamic_cast<RectangularPrism^>(obb));
				break;
			default: // obb->Type()== UNKNOWN -> No sensible return, so just say true since the bounding box test passed
				return true;
			}
		case GameObjectType::RectangularPrism:
			switch (obb->Type())
			{
			case GameObjectType::Sphere:
				return SphereRectangularPrism(dynamic_cast<Sphere^> (obb), dynamic_cast<RectangularPrism^>(ibb));
				break;
			case GameObjectType::Cylinder:
				return CylinderRectangularPrism(dynamic_cast<Cylinder^> (obb), dynamic_cast<RectangularPrism^>(ibb));
				break;
			case GameObjectType::Face:
				return FaceRectangularPrism(dynamic_cast<Face^> (obb), dynamic_cast<RectangularPrism^>(ibb));
				break;
			case GameObjectType::RectangularPrism:
				return RectangularPrismRectangularPrism(dynamic_cast<RectangularPrism^> (ibb), dynamic_cast<RectangularPrism^>(obb));
				break;
			default: // obb->Type()== UNKNOWN -> No sensible return, so just say true since the bounding box test passed
				return true;
			}
		default: // ibb->Type()== UNKNOWN -> No sensible return, so just say true since the bounding box test passed
			return true;
		}
	}
};