// Deleter.h

#pragma once


template <typename T>
struct Deleter {
    void operator()(T *ptr) {
        if (ptr != nullptr) {
            ptr->Release();
            ptr = nullptr;
        }
    }
};


//#include <d2d1.h>
//#include <Dwrite.h>
//template <>
//struct Deleter<ID2D1SolidColorBrush> {
//    void operator()(ID2D1SolidColorBrush *ptr) {
//        if (ptr != nullptr) {
//            ptr->Release();
//            ptr = nullptr;
//        }
//    }
//};
