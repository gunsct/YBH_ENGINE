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

//stl ���Ϳ�
#include <iostream>
#include <vector>
using namespace std;

//��Ÿ ���� ���̺귯����
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
#include "../resource.h"//define�뵵

lua_State* LS;
std::vector <Object_info> obj_info;
int lua_loader(lua_State* L){//��ƽ�ũ��Ʈ ���� �ε��Լ�
	Object_info OI;

	//���� ��ü ���� �ű⿡ ��ƽ�ũ��Ʈ�� �ִ� �� �� �ִ´�.
	OI.set_obj(lua_tonumber(L, 4), (float)lua_tonumber(L, 5), (float)lua_tonumber(L, 6), (float)lua_tonumber(L, 7), 
		(float)lua_tonumber(L, 8), (float)lua_tonumber(L, 9), lua_tostring(L, 1), lua_tostring(L, 2), lua_tostring(L, 3));
	
	obj_info.push_back(OI);//�״��� ���Ϳ� �־���

	return 0;
}

class Application_main : public BaseApplication
{
public:
	Application_main(void);
	virtual ~Application_main(void);

	////�̱���
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
	////�̱���
	//Application_main(const Application_main& other);
	//static Application_main *instance;

	//������Ʈ
	Ogre::SceneNode* ObjNode[OBJ_NUM];
	int obj_num_cnt;//������Ʈ ī���� �켱�� ����
	void set_obj();
	//��� �δ� �Լ� �θ������� ��ư�ü ����
	void callLua(const char* func_name, lua_CFunction func, const char* lua_file_name);//��ƽ�ũ��Ʈ ����κ�

	//����
	Physics physics;
	hkVector4 p[OBJ_NUM];//������Ʈ ����ŭ �ݸ��� ��ġ�����͵� �������
	Ogre::Vector3 pos[OBJ_NUM];//���� ����

	//������
	buttonGUI::buttonManager* buttonMgr;
	void set_button();
	void handleButtonEvent(buttonEvent * e);
	
	//����
	Sound sound;
	
	//���źκ�
	bool processUnbufferedInput(const Ogre::FrameEvent& fe);
};
#endif // #ifndef __Application_main_h_
