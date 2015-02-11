// ComPtr.h

#pragma once

#include "SafeRelease.h"


template<typename INTERFACE>
class ComPtr {

public:
    ComPtr();
    ComPtr(INTERFACE *ptr);
    ComPtr(const ComPtr<INTERFACE>& other);

    virtual ~ComPtr();

    INTERFACE* operator=(INTERFACE *ptr);
    INTERFACE* operator=(const ComPtr<INTERFACE>& RefComPtr);

    bool Equals(IUnknown *other);

    inline operator INTERFACE*() const {
        return mPtr;
    }

    inline INTERFACE& operator*() const {
        return *mPtr;
    }

    inline INTERFACE** operator&() {
        return &mPtr;
    }

    inline INTERFACE* operator->() const {
        return mPtr;
    }

    inline void Release() {
        SafeRelease(&mPtr);
    }

private:
    INTERFACE *mPtr;
};


template<typename INTERFACE>
ComPtr<INTERFACE>::ComPtr() {
    mPtr = nullptr;
}


template<typename INTERFACE>
ComPtr<INTERFACE>::ComPtr(INTERFACE *ptr) {
    mPtr = nullptr;
    if (ptr != nullptr) {
        mPtr = ptr;
        mPtr->AddRef();
    }
}


template<typename INTERFACE>
ComPtr<INTERFACE>::ComPtr(const ComPtr<INTERFACE>& other) {
    mPtr = nullptr;
    mPtr = reinterpret_cast<INTERFACE*>(RefComPtr);
    if (mPtr) {
        mPtr->AddRef();
    }
}

template<typename INTERFACE>
ComPtr<INTERFACE>::~ComPtr() {
    SafeRelease(&mPtr);
}


template<typename INTERFACE>
INTERFACE* ComPtr<INTERFACE>::operator=(INTERFACE *rhs) {
    if (Equals(rhs)) {
        return mPtr;
    }
    mPtr->Release();
    rhs->AddRef();
    mPtr = rhs;
    return mPtr;
}


template<typename INTERFACE>
INTERFACE* ComPtr<INTERFACE>::operator=(const ComPtr<INTERFACE>& rhs) {
    if (&rhs == nullptr) {
        mPtr = nullptr;
        return nullptr;
    }

    mPtr = reinterpret_cast<INTERFACE*>rhs;
    if (mPtr) {
        mPtr->AddRef();
    }
    return mPtr;
}


template<typename INTERFACE>
bool ComPtr<INTERFACE>::Equals(IUnknown *other) {
    if (other == nullptr) {
        return false;
    }
    IUnknown *unknown = nullptr;
    mPtr->QueryInterface(IID_IUnknown, reinterpret_cast<void**>(&unknown));
    const bool ret = ((other == unknown) ? true : false);
    unknown->Release();
    return ret;
}