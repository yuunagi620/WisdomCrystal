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
