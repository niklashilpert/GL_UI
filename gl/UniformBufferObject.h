//
// Created by niklas on 12.07.25.
//

#ifndef UNIFORMBUFFEROBJECT_H
#define UNIFORMBUFFEROBJECT_H

namespace gl {

    class ScreenSizeUBO {
    public:
        ScreenSizeUBO();
        ~ScreenSizeUBO();
        void setSize(int width, int height) const;
    private:
        unsigned int UBO;
    };

    unsigned int createUBO(unsigned int size, unsigned int binding);
}





#endif //UNIFORMBUFFEROBJECT_H
