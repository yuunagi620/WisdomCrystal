// Deleter.h

#pragma once

//#include <wincodec.h>


template <typename T>
struct Deleter {
    void operator()(T *ptr) {
        if (ptr != nullptr) {
            ptr->Release();
            ptr = nullptr;
        }
    }
};


//template <>
//struct Deleter<IWICImagingFactory> {
//    void operator()(IWICImagingFactory *ptr) {
//        if (ptr != nullptr) {
//            ptr->Release();
//            ptr = nullptr;
//        }
//    }
//};
