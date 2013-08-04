//
//  OrthoCamera.cpp
//  vectormap2
//
//  Created by Lion User on 10/03/2013.
//  Copyright (c) 2013 Lion User. All rights reserved.
//

#include <Engine/Challenge.h>
#include "OrthoCamera.h"

namespace challenge
{
	OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float nearZ, float farZ, Size screenSize) :
		Camera((glm::mat4)glm::ortho(left, right, bottom, top, nearZ, farZ), screenSize),
		mLeft(left),
		mRight(right),
		mBottom(bottom),
		mTop(top),
		mNearZ(nearZ),
		mFarZ(farZ)
	{
	}
};

