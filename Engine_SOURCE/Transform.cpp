#include "Transform.h"
#include "Renderer.h"
#include "Camera.h"

namespace mh
{
	Transform::Transform()
		: IComponent(eComponentType::Transform)
		, mFoward(Vector3::Forward)
		, mRight(Vector3::Right)
		, mUp(Vector3::Up)
		, mScale(Vector3::One)
		, mRotation(Vector3::Zero)
		, mPosition(Vector3::One)
		, mParent(nullptr)
	{
		
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
		//cos(180);
	}

	void Transform::Update()
	{
		//���� ������ ĳ�����̵� ó��
	}

	void Transform::FixedUpdate()
	{
		//�������� ���� ��ġ������ ������Ʈ

		// ���� ��� ����
		
		// ũ�� ��ȯ ���
		Matrix scale = Matrix::CreateScale(mScale);

		// ȸ�� ��ȯ ���
		Matrix rotation;

		Vector3 radian(mRotation.x * (XM_PI / 180)
			, mRotation.y * (XM_PI / 180)
			, mRotation.z * (XM_PI / 180));

		rotation = Matrix::CreateRotationX(radian.x);
		rotation *= Matrix::CreateRotationY(radian.y);
		rotation *= Matrix::CreateRotationZ(radian.z);

		// �̵� ��ȯ ���
		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		
		// ī�޶� ������Ʈ���� �������ش�
		// ����� ����
		// �������� ��� ����

		if (mParent)
		{
			mWorld *= mParent->mWorld;
		}
	}

	void Transform::Render()
	{
	}

	void Transform::SetConstantBuffer()
	{
		renderer::TransformCB trCb = {};
		trCb.world = mWorld;
		trCb.view = Camera::GetGpuViewMatrix();
		trCb.projection = Camera::GetGpuProjectionMatrix();

		graphics::ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Transform];
		cb->SetData(&trCb);
		cb->Bind(graphics::eShaderStage::VS);
		cb->Bind(graphics::eShaderStage::HS);
		cb->Bind(graphics::eShaderStage::DS);
		cb->Bind(graphics::eShaderStage::GS);
		cb->Bind(graphics::eShaderStage::PS);
		cb->Bind(graphics::eShaderStage::CS);
	}
}
