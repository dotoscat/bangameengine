//body.hpp
//Copyright (C) 2010-2011 Oscar (.teri) Triano

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

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