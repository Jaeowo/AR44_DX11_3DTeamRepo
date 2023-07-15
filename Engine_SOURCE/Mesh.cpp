#include "Mesh.h"
#include "Renderer.h"
#include "GraphicDevice_DX11.h"

namespace mh
{
	Mesh::Mesh()
		: Resource(eResourceType::Mesh)
		, mVBDesc{}
		, mIBDesc{}
		, mIndexCount(0)
	{

	}

	Mesh::~Mesh()
	{

	}

	HRESULT Mesh::Load(const std::wstring& _path)
	{
		return E_NOTIMPL;
	}

	bool Mesh::CreateVertexBuffer(void* _data, UINT _count)
	{
		// ���ؽ� ����
		mVBDesc.ByteWidth = sizeof(renderer::Vertex) * _count;
		mVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		mVBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mVBDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = _data;

		if (!GetDevice()->CreateBuffer(&mVBDesc, &subData, mVertexBuffer.GetAddressOf()))
			return false;

		return true;
	}

	bool Mesh::CreateIndexBuffer(void* _data, UINT _count)
	{
		mIndexCount = _count;
		mIBDesc.ByteWidth = sizeof(UINT) * _count;
		mIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		mIBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mIBDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = _data;

		if (!GetDevice()->CreateBuffer(&mIBDesc, &subData, mIndexBuffer.GetAddressOf()))
		{
			return false;
		}

		return true;
	}

	void Mesh::BindBuffer() const
	{
		// Input Assembeler �ܰ迡 ���ؽ����� ���� ����
		UINT stride = sizeof(renderer::Vertex);
		UINT offset = 0;

		GetDevice()->BindVertexBuffer(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
		GetDevice()->BindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	void Mesh::Render() const
	{
		GetDevice()->DrawIndexed(mIndexCount, 0, 0);
	}
	
	void Mesh::RenderInstanced(UINT _count) const
	{
		GetDevice()->DrawIndexedInstanced(mIndexCount, _count, 0, 0, 0);
	}
}
