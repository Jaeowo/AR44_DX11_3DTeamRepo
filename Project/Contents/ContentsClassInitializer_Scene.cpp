

//=========================================================
//This Code is Automatically generated by CodeGenerator.exe
//=========================================================


#include "PCH_Contents.h"

#include "ContentsClassInitializer.h"
#include <Engine/SceneMgr.h>
#include "strKey_Scene.h"


#include "Scene_Play.h"
#include "Scene_TestBehaviourTree.h"
#include "Scene_Title.h"

#define CONSTRUCTOR_T(T) SceneMgr::AddSceneConstructor<T>(strKey::Scene::##T)

namespace mh
{
	using namespace mh::define;
	void ContentsClassInitializer::InitScene()
	{
		CONSTRUCTOR_T(Scene_Play);
		CONSTRUCTOR_T(Scene_TestBehaviourTree);
		CONSTRUCTOR_T(Scene_Title);
	}
}