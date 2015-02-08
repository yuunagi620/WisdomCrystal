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


//#include <wincodec.h>
//template <>
//struct Deleter<IWICImagingFactory> {
//    void operator()(IWICImagingFactory *ptr) {
//        if (ptr != nullptr) {
//            ptr->Release();
//            ptr = nullptr;
//        }
//    }
//};
