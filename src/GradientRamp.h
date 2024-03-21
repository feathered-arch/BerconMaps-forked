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

/*
	Gradient class

	Note that IGradient does NOT directly edit this class
	It reports UI actions to BerconGradient which then updates
	this to represent the changes done.
*/

#pragma once

#include "GradientMap.h"
#include "BerconCommon.h"


class GradientRamp {
private:
	static const int PADDING = 6;
	static const int ARROWS = 6;
	static const COLORREF ARROWDESEL = RGB(0,0,0);
	static const COLORREF ARROWSEL = RGB(255,255,255);

	HWND m_hWnd;
	GradientMap* parent;


	int width;
	int height;

	// Key information, always sorted by postion. From left to right (0..1)
	Texmap** subtex;
	float* position;
	AColor* color;
	int* number;

	int keys;
	int key = -1;
	
	bool keyMoved;

public:

	int selected; // Key number, not index		
	int interpolation; // 0 linear 1 smooth 2 solid near 3 solid left 4 solid right

	GradientRamp(GradientMap* p) {		
		m_hWnd = NULL;
		parent = p;
		selected = 0;
		interpolation = 0;
		keys = 0;
		subtex = NULL;
		position = NULL;
		color = NULL;
		number = NULL;
		reset();
	}

	~GradientRamp() {
		delete[] subtex;
		delete[] position;
		delete[] color;
		delete[] number;	// represents the index value in the parameter array for a given key
	}

	Animatable* anim;

	void setHWND(HWND hWnd);

	// Paint
	void paint(HDC hDC);	
	void paintArrow(int px, int py, bool up, HDC hDC, COLORREF colR);		
	void invalidate();

	// Mouse methods
	int hit(int x, int y, bool broad = false);
	float toPos(int x);
	
	void leftDown(int x, int y, bool ctrl, bool shift, bool alt);
	void leftUp(int x, int y, bool ctrl, bool shift, bool alt);
	void dragging(int x, int y, bool ctrl, bool shift, bool alt);

	void popup(int x, int y, int sel);
	void MouseStart();
	void MouseEnd();

	// Key methods
	int toIndex(int n);		//retrieve local key index value for a key based on its index value in Max's parameter array
	int indexUtil(float n);	// retrieve key index value for a key based on its position
	void selectKey(int n);	// directs user interface to set focus to a key on the gradient ramp
	//void moveKey(int n, float pos);
	void addKey(int n, float pos, AColor col, Texmap* sub = NULL);
	void reset();
//	void grad_sort();	//limited to however Max has sorted the parameter array
//	void swapkeys(int a, int b);
	Texmap* getSubtex(int n = -1);
	void setSubtex(int n, Texmap* sub);
	void setSubtex(Texmap* sub);
	int numKeys() { return keys; }

	// Shading methods
	int findHighKey(float x);	
	float interpolate(float x, float low, float high);
	AColor getColor(float x); // Required for preview
	AColor getColor(float x, ShadeContext& sc);	 // ShadeContext required for maps
	Point3 getBump(float x, Point3 normal, ShadeContext& sc); // ShadeContext required for maps
};