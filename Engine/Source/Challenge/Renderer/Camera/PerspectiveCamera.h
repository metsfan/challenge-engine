//
//  PerspectiveCamera.h
//  vectormap2
//
//  Created by Lion User on 10/03/2013.
//  Copyright (c) 2013 Lion User. All rights reserved.
//

#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Camera/Camera.h>
//#include <Challenge/Renderer/Camera/Frustum.h>

namespace challenge
{
    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(real aspect, real fovy, real nearZ, real farZ, Size screenSize);
        virtual ~PerspectiveCamera() {};
        
        virtual void Update();
        
        //const Frustum& GetFrustum() const { return mFrustum; }
        
    protected:
        const real GetAspect() { return mAspect; }
        const real GetFovY() { return mFovY; }
        const real GetNearZ() { return mNearZ; }
        const real GetFarZ() { return mFarZ; }
        
    private:
        real mAspect;
        real mFovY;
        real mNearZ;
        real mFarZ;
        //Frustum mFrustum;
    };
};
