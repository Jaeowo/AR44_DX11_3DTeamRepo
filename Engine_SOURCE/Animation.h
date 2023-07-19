#pragma once
#include "Entity.h"
#include "Texture.h"

namespace mh
{
	class Animation : public Entity
	{
	public:
		struct tSprite
		{
			math::Vector2 LeftTop;	// ���� ��� ��ǥ
			math::Vector2 Size;		// ������ܺ��� �߶� ���� ������ �ȼ� ����
			math::Vector2 Offset;		// ������ ��ġ �����ϱ����� ��ǥ
			math::Vector2 AtlasSize;  // �ؽ�ó �̹����� ũ��
			float Duration;		// �����Ӱ��� �ð� ����

			tSprite()
				: LeftTop(0.0f, 0.0f)
				, Size(0.0f, 0.0f)
				, Offset(0.0f, 0.0f)
				, AtlasSize(0.0f)
				, Duration(0.1f)
			{

			}
		};

		Animation();
		~Animation();

		UINT Update();
		void FixedUpdate();
		void Render();

		void Create(const std::wstring& _name, std::shared_ptr<graphics::Texture> _atlas
			, math::Vector2 _leftTop, math::Vector2 _size, math::Vector2 _offset
			, UINT _spriteLegth, float _duration);

		void BindShader();
		void Reset();
		void Clear();

		bool IsComplete() const { return mbComplete; }
		const std::wstring& GetAnimationName() const { return mAnimationName; }

	private:
		class Animator* mAnimator;
		std::wstring mAnimationName;
		std::shared_ptr<graphics::Texture> mAtlas;
		std::vector<tSprite> mSpriteSheet;
		int mIndex;
		float mTime;
		bool mbComplete;
	};
}
