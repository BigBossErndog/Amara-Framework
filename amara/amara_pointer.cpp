#pragma once
#ifndef AMARA_POINTER
#define AMARA_POINTER

#include "amara.h"

namespace Amara {
    class Pointer {
        public:
            int x = 0;
            int y = 0;
            bool isDown = false;
            bool justDown = false;

            bool isActivated = false;

            virtual void manage() {
                isActivated = false;
            }
    };
}

#endif