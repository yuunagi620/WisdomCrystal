// COMPtr.h

#pragma once

#include <boost/noncopyable.hpp>

#include "SafeRelease.h"


template<class T>
class COMPtr {

public:
    COMPtr() : mPtr(nullptr), counter(0) {}
    COMPtr(T* ptr) : mPtr(nullptr), counter(0) { Set(ptr); }
    COMPtr(const COMPtr<T>& ptr) : mPtr(nullptr), counter(0) { Set(ptr); }

    ~COMPtr() { Release(); }

    operator T*() const { return mPtr; }
    T** operator&() { return &mPtr; }
    T* operator->() const { return mPtr; }

    const COMPtr<T>& operator=(T* ptr) { Set(ptr); return *this; }
    const COMPtr<T>& operator=(const COMPtr<T>& ptr) { Set(ptr); return *this; }

    void Set(T* ptr){
        Release();
        mPtr = ptr;
        AddRef();
    }

    void Set(const COMPtr<T>& ptr) {
        Release();
        mPtr = ptr.mPtr;
        AddRef();
    }

    T* Get() const { return mPtr; }

    void AddRef() {
        if (mPtr != nullptr) {
            counter = mPtr->AddRef();
        }
    }

    void Release() {
        if (mPtr != nullptr) {
            counter = SafeRelease(&mPtr);
        }
    }

private:
    T *mPtr;
    unsigned long counter;
};


// MasteringVoice —p‚Ì“ÁŽê‰»
template<>
class COMPtr<IXAudio2MasteringVoice> : private boost::noncopyable {

public:
    COMPtr() : mPtr(nullptr) {}
    COMPtr(IXAudio2MasteringVoice* ptr) : mPtr(nullptr) { Set(ptr); }
    COMPtr(const COMPtr<IXAudio2MasteringVoice>& ptr) : mPtr(nullptr) { Set(ptr); }

    ~COMPtr() { Release(); }

    operator IXAudio2MasteringVoice*() const { return mPtr; }
    IXAudio2MasteringVoice** operator&() { return &mPtr; }
    IXAudio2MasteringVoice* operator->() const { return mPtr; }

    void Set(IXAudio2MasteringVoice* ptr){
        Release();
        mPtr = ptr;
    }

    void Set(const COMPtr<IXAudio2MasteringVoice>& ptr) {
        Release();
        mPtr = ptr.mPtr;
    }

    IXAudio2MasteringVoice* Get() const { return mPtr; }

    void Release() {
        if (mPtr != nullptr) {
            mPtr->DestroyVoice();
        }
    }

private:
    IXAudio2MasteringVoice *mPtr;
};
