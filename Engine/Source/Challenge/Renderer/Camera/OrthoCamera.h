//
//  OrthoCamera.h
//  vectormap2
//
//  Created by Lion User on 10/03/2013.
//  Copyright (c) 2013 Lion User. All rights reserved.
//

#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Camera/Camera.h>

namespace challenge
{
    class OrthoCamera : public Camera
    {
    public:
        OrthoCamera(float left, float right, float bottom, float top, float nearZ, float farZ, Size screenSize);
        ~OrthoCamera() {};
        
    private:
        float mLeft;
        float mRight;
        float mBottom;
        float mTop;
        float mNearZ;
        float mFarZ;
    };
};
