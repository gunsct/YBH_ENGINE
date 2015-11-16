/*
-----------------------------------------------------------------------------
Filename:    Application_main.h
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
#ifndef __Application_main_h_
#define __Application_main_h_

//stl 벡터용
#include <iostream>
#include <vector>
using namespace std;

//기타 엔진 라이브러리들
#include "../lua/Lua_loader.h"
extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "../ui_sound/buttonGUI.h"

#include "../physics/Physics.h"

#include "../ui_sound/Sounds.h"
using namespace buttonGUI;
#include <irrKlang.h>//sound
#include <conio.h>
#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;

#include "BaseApplication.h"
#include "../resource.h"//define용도

lua_State* LS;
std::vector <Object_info> obj_info;
int lua_loader(lua_State* L){//루아스크립트 정보 로드함수
	Object_info OI;

	//정보 객체 만들어서 거기에 루아스크립트에 있는 값 다 넣는다.
	OI.set_obj(lua_tonumber(L, 4), (float)lua_tonumber(L, 5), (float)lua_tonumber(L, 6), (float)lua_tonumber(L, 7), 
		(float)lua_tonumber(L, 8), (float)lua_tonumber(L, 9), lua_tostring(L, 1), lua_tostring(L, 2), lua_tostring(L, 3));
	
	obj_info.push_back(OI);//그다음 벡터에 넣어줌

	return 0;
}

class Application_main : public BaseApplication
{
public:
	Application_main(void);
	virtual ~Application_main(void);

	////싱글톤
	//static Application_main* GetInstance(){
	//	if (instance == NULL) {
	//		instance = new Application_main();
	//	}
	//	return instance;
	//}

protected:
    virtual void createScene(void);
	virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent&);

private:
	////싱글톤
	//Application_main(const Application_main& other);
	//static Application_main *instance;

	//오브젝트
	Ogre::SceneNode* ObjNode[OBJ_NUM];
	int obj_num_cnt;//오브젝트 카운터 우선은 뺴둠
	void set_obj();
	//루아 로더 함수 부르기위해 루아객체 만듬
	void callLua(const char* func_name, lua_CFunction func, const char* lua_file_name);//루아스크립트 실행부분

	//물리
	Physics physics;
	hkVector4 p[OBJ_NUM];//오브젝트 수만큼 콜리더 위치받을것도 만들어줌
	Ogre::Vector3 pos[OBJ_NUM];//같은 이유

	//유아이
	buttonGUI::buttonManager* buttonMgr;
	void set_button();
	void handleButtonEvent(buttonEvent * e);
	
	//사운드
	Sound sound;
	
	//갱신부분
	bool processUnbufferedInput(const Ogre::FrameEvent& fe);
};
#endif // #ifndef __Application_main_h_
