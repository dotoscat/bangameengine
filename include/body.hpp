//Copyright (c) 2011 Oscar (.teri) Triano <teritriano@gmail.com>

//This software is provided 'as-is', without any express or implied
//warranty. In no event will the authors be held liable for any damages
//arising from the use of this software.

//Permission is granted to anyone to use this software for any purpose,
//including commercial applications, and to alter it and redistribute it
//freely, subject to the following restrictions:

   //1. The origin of this software must not be misrepresented; you must not
   //claim that you wrote the original software. If you use this software
   //in a product, an acknowledgment in the product documentation would be
   //appreciated but is not required.

   //2. Altered source versions must be plainly marked as such, and must not be
   //misrepresented as being the original software.

   //3. This notice may not be removed or altered from any source
   //distribution.

#ifndef _bange_body_
#define _bange_body_

#include <vector>
#include <chipmunk/chipmunk.h>
//#include "colshape.hpp"

namespace bange{
    
    class body{
        private:
            cpSpace *space;
        public:
            //mutable std::vector<bange::colshape *> shapes;
            mutable cpBody *thebody;
            mutable bool inspace;
        public:
            body(cpSpace *, void *, cpFloat, cpFloat);
            ~body();
            
            cpVect GetPos(){
                return cpBodyGetPos(thebody);
            };
            
            void AddToSpace(){
                if (inspace){
                    return;}
                cpSpaceAddBody(space, thebody);
                inspace = true;
            };
            
            void RemoveFromSpace(){
                if (!inspace){
                    return;}
                cpSpaceRemoveBody(space, thebody);
                inspace = false;
            };
            
            cpVect GetVel(){
                return cpBodyGetVel(thebody);
            }
            
            void SetVel(cpVect vel){
                cpBodySetVel(thebody, vel);
            }
            
            /*
            void SetMass(cpFloat);
            cpFloat GetMass();
            void SetVel(cpVect);
            cpVect GetVel();
            cpVect GetPos();
            void SetPos(cpVect);
            void SetPos(float, float);
            void SetAngleDegrees(cpFloat);
            void SetAngleRadians(cpFloat);
            cpFloat GetAngleDegrees();
            cpFloat GetAngleRadians();
            void SetAngVelDegrees(cpFloat);
            void SetAngVelRadians(cpFloat);
            cpFloat GetAngVelDegrees();
            cpFloat GetAngVelRadians();
            bange::colshape &AddPolyShape(int, cpVect *, cpVect);
            bange::colshape &AddCircleShape(cpFloat, cpVect);
            bange::colshape &AddSegmentShape(cpVect, cpVect, cpFloat);
            void SetSpace(cpSpace *);
            void RemoveFromSpace();
            void SafelyRemoveFromSpace();
            void AddToSpace();
            void AddPostStepCallback(cpPostStepFunc, void *data=NULL);
            //const cpShape *operator[](size_t);
            void AddShapesToSpace();
            void RemoveShapesFromSpace();
        
            static void PostStepCallbackRemoveFromSpace(cpSpace *, void *, void *);
            */
            
            //static void RegisterVM(lua_State *);
            
    };
    
    //static int MomentForBox(lua_State *);//number mass, number width, number height
    //static int body_AddToSpace(lua_State *);
    //static int body_RemoveFromSpace(lua_State *);
    
}

#endif