#include "pch.h"
#include "Resources/MeshObject.h"
#include "Utilities/DirectXSample.h"
#include "Rendering/ConstantBuffers.h"

using namespace Microsoft::WRL;
using namespace DirectX;

MeshObject::MeshObject():
    m_vertexCount(0),
    m_indexCount(0)
{
}

//--------------------------------------------------------------------------------

void MeshObject::Render(_In_ ID3D11DeviceContext *context)
{
	// PNTVertex is a struct. stride provides us the size required for all the mesh data
	// struct PNTVertex
	//{
	//  DirectX::XMFLOAT3 position;
	//  DirectX::XMFLOAT3 normal;
	//  DirectX::XMFLOAT2 textureCoordinate;
	//};
    uint32 stride = sizeof(PNTVertex);
    uint32 offset = 0;

	// Similar to the main render loop.
	// Input-layout objects describe how vertex buffer data is streamed into the IA pipeline stage.
	context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
    
	// IASetIndexBuffer binds an index buffer to the input-assembler stage.
	// For more info, go to: https://msdn.microsoft.com/library/windows/desktop/ff476453.aspx
	context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    
	// Binds information about the primitive type, and data order that describes input data for the input assembler stage.
	// For more info, go to: https://msdn.microsoft.com/library/windows/desktop/ff476455.aspx
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    
	// Draw indexed, non-instanced primitives. A draw API submits work to the rendering pipeline.
	// For more info, go to: https://msdn.microsoft.com/library/windows/desktop/ff476409.aspx
	context->DrawIndexed(m_indexCount, 0, 0);
}

//--------------------------------------------------------------------------------
