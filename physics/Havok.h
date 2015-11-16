#ifndef HAVOK_H
#define HAVOK_H

/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Math and base include
#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Config/hkConfigVersion.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <Common/Base/Container/String/hkStringBuf.h>

// Dynamics includes
#include <Physics2012/Collide/hkpCollide.h>
#include <Physics2012/Collide/Agent/ConvexAgent/SphereBox/hkpSphereBoxAgent.h>
#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics2012/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics2012/Collide/Dispatch/hkpAgentRegisterUtil.h>


#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>

// Visual Debugger includes
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>


#include <stdio.h>
#include <stdlib.h>

//#if defined( HK_PLATFORM_TIZEN )
//#include <osp/FBase.h>
//#endif
//
//#ifdef HK_PLATFORM_CTR
//#define PRINTF nndbgDetailPrintf
//#elif defined(HK_PLATFORM_ANDROID)
//#include <android/log.h>
//#define PRINTF(...) __android_log_print(ANDROID_LOG_INFO, "Havok", __VA_ARGS__)
//#elif defined(HK_PLATFORM_TIZEN)
//#define PRINTF(...) AppLogTag("Havok", __VA_ARGS__)
//#else
//#define PRINTF printf
//#endif
//
//#ifdef HK_ANDROID_PLATFROM_8
//#    include <jni.h>
//#endif
//
//void PlatformInit();
//void PlatformFileSystemInit();

/*
static void HK_CALL errorReport(const char* msg, void*)
{
	PRINTF("%s", msg);
#ifdef HK_PLATFORM_WIN32
	#ifndef HK_PLATFORM_WINRT
		OutputDebugStringA(msg);
	#else
		// Unicode only 
		int sLen = hkString::strLen(msg) + 1;
		wchar_t* wideStr = hkAllocateStack<wchar_t>( sLen );
		mbstowcs_s(HK_NULL, wideStr, sLen, msg, sLen - 1); 
		OutputDebugString(wideStr);
		hkDeallocateStack<wchar_t>( wideStr, sLen);
	#endif
#endif
}*/
//void PlatformInit();
//void PlatformFileSystemInit();

static void HK_CALL errorReport(const char* msg, void* userContext)
{
	using namespace std;
	printf("%s", msg);
}

/*
 * Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20140907)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2014
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available at www.havok.com/tryhavok.
 * 
 */

#endif