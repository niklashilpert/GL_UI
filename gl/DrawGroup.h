//
// Created by niklas on 13.07.25.
//

#ifndef DRAWGROUP_H
#define DRAWGROUP_H
#include "DrawCall.h"

namespace gl {
    class DrawGroup {
    public:
        DrawGroup(std::vector<DrawCall*>);
        ~DrawGroup();
        void draw();
        void setPosition(float x, float y);
    private:
        std::vector<DrawCall*> drawCalls;
    };
}

#endif //DRAWGROUP_H
