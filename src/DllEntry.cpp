/*
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements. The ASF licenses this
file to you under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.   
*/

#include <tchar.h>
#include <iparamb2.h>
#include "resource.h"

extern ClassDesc2* GetBerconNoiseDesc();
extern ClassDesc2* GetBerconWoodDesc();
extern ClassDesc2* GetBerconTileDesc();
extern ClassDesc2* GetBerconDistortionDesc();
extern ClassDesc2* GetBerconGradientDesc();
extern void InitGradientControls();

HINSTANCE hInstance;
int controlsInit = FALSE;

BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID /*lpvReserved*/) {
	if( fdwReason == DLL_PROCESS_ATTACH ) {
		//MaxSDK::Util::UseLanguagePackLocale();   /*we don't provide a language pack for our plugin
		// Hang on to this DLL's instance handle.
		hInstance = hinstDLL;
		DisableThreadLibraryCalls(hInstance);
		// DO NOT do any initialization here. Use LibInitialize() instead
	}      
	return(TRUE);
}

__declspec( dllexport ) int LibNumberClasses() {
	return 5;
}

__declspec( dllexport ) ClassDesc* LibClassDesc(int i) {
	switch(i) {
		case 0: return GetBerconNoiseDesc();
		case 1: return GetBerconWoodDesc();
		case 2: return GetBerconTileDesc();
		case 3: return GetBerconDistortionDesc();
		case 4: return GetBerconGradientDesc();
		default: return 0;
	}
}

/*	See https://cg-source.com/MultiTexture
#include "MultiMap.h"

extern ClassDesc2* GetMultiMapDesc();
HINSTANCE hInstance;
int controlsInit = FALSE;
BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID \*lpvReserved*\) {
	if( fdwReason == DLL_PROCESS_ATTACH ) {
		hInstance = hinstDLL;
		DisableThreadLibraryCalls(hInstance);
	}      
	return(TRUE);
}

__declspec( dllexport ) int LibNumberClasses() {
	return 1;
}

__declspec( dllexport ) ClassDesc* LibClassDesc(int i) {
	switch(i) {
		case 0: return GetMultiMapDesc();
		default: return 0;
	}
}
*/



TCHAR* GetString(int id)
{
	static TCHAR buf[256];

	if (hInstance)
	{
		return LoadString(hInstance, id, buf, _countof(buf)) ? buf : NULL;
	}

	return NULL;
}


__declspec( dllexport ) const TCHAR* LibDescription()
{
	return GetString(IDS_LIBDESCRIPTION);
}

__declspec( dllexport ) ULONG LibVersion()
{
	return VERSION_3DSMAX;
}

__declspec( dllexport ) int LibInitialize() {

	if (!controlsInit) {
		controlsInit = TRUE;
		//InitCustomControls(hInstance);     // Initialize MAX's custom controls
		InitCommonControls();               // Initialize Windows controls
		InitGradientControls();            // Initialize my GradientRamp control
	}
	return TRUE;
}

__declspec( dllexport ) int LibShutdown() {
	return TRUE;	
}
