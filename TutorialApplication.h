/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <iostream>
#include <vector>
using namespace std;

#include "Lua_loader.h"
#include "BaseApplication.h"
#include "buttonGUI.h"
#include "Physics.h"
#include "Sounds.h"
using namespace buttonGUI;
#include <irrKlang.h>//sound
#include <conio.h>
#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;

lua_State* LS;
std::vector <Object_info> obj_info;
int lua_loader(lua_State* L){//루아스크립트 정보 로드함수
	Object_info OI;
	//int n = lua_gettop(L);//스크립트 마지막까지 가기 위함

	//set_obj("Head", "ogrehead.mesh", "HeadNode", 5, 10, 0, 0.02, 0.02, 0.02)
	OI.set_obj(lua_tonumber(L, 4), (float)lua_tonumber(L, 5), (float)lua_tonumber(L, 6), (float)lua_tonumber(L, 7), 
		(float)lua_tonumber(L, 8), (float)lua_tonumber(L, 9), lua_tostring(L, 1), lua_tostring(L, 2), lua_tostring(L, 3));
	
	obj_info.push_back(OI);

	return 0;
}
class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

	////싱글톤
	//static TutorialApplication* GetInstance(){
	//	if (instance == NULL) {
	//		instance = new TutorialApplication();
	//	}
	//	return instance;
	//}

	//루아 로더 함수 부르기위해 루아객체 만듬
	
	void callLua(const char* func_name, lua_CFunction func, const char* lua_file_name);//루아스크립트 실행부분
	//Ogre::Entity* OgreObj[10];
	
	
protected:
    virtual void createScene(void);
	virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent&);
	 
	Physics physics;
	Ogre::SceneNode* cubeNode;
	Ogre::SceneNode* ninjaNode;

private:
	////싱글톤
	//TutorialApplication(const TutorialApplication& other);
	//static TutorialApplication *instance;

	
	//유아이
	buttonGUI::buttonManager* buttonMgr;
	void set_button();
	void handleButtonEvent(buttonEvent * e);
	//갱신부분
	bool processUnbufferedInput(const Ogre::FrameEvent& fe);
	//사운드
	Sound sound;
	
};
#endif // #ifndef __TutorialApplication_h_
