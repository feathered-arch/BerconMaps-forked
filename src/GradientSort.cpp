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
	Interface that has to be filled so gradient control can report users actions
*/

#pragma once
#include "GradientSort.h"


/*
pblock->SetValue(pb_submaps, t, NULL, 0);
pblock->SetValue(pb_colors, t, AColor(0.f,0.f,0.f,1.f), 0);
pblock->SetValue(pb_colors, t, AColor(1.f,1.f,1.f,1.f), 1);
pblock->SetValue(pb_positions, t, 0.f, 0);
pblock->SetValue(pb_positions, t, 1.f, 1);
*/


void GradientSort::foobar(int i, float pos, AColor col, Texmap *map)
{
	ramp->sort();
}

