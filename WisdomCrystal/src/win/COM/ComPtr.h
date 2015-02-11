// COMPtr.h

#pragma once


template<class INTERFACE, const IID *piid = nullptr>
class COMPtr {

public:
    COMPtr() {
        mInterface = nullptr;
    }

    COMPtr(INTERFACE *ptr) {
        mInterface = nullptr;
        if (ptr != nullptr) {
            mInterface = ptr;
            mInterface->AddRef();
        }
    }

    COMPtr(const COMPtr<INTERFACE, piid>& RefCOMPtr) {
        mInterface = nullptr;
        mInterface = reinterpret_cast<INTERFACE*>(RefCOMPtr);
        if (mInterface) {
            mInterface->AddRef();
        }
    }

    COMPtr(IUnknown* pIUnknown, IID iid) {
        mInterface = nullptr;
        if (pIUnknown != nullptr) {
            pIUnknown->QueryInterface(iid, reinterpret_cast<void**>(&mInterface));
        }
    }

    virtual ~COMPtr() {
        if (mInterface) {
            mInterface->Release();
            mInterface = nullptr;
        }
    }

    operator INTERFACE*() const {
        return mInterface;
    }

    INTERFACE& operator*() const {
        return *mInterface;
    }

    INTERFACE** operator&() {
        return &mInterface;
    }

    INTERFACE* operator->() const {
        return mInterface;
    }

    INTERFACE* operator=(INTERFACE *ptr) {
        if (IsEqualObject(ptr)) {
            return mInterface;
        }
        mInterface->Release();
        ptr->AddRef();
        mInterface = ptr;
        return mInterface;
    }

    INTERFACE* operator=(IUnknown* unknown) {
        assert(unknown != nullptr);
        assert(piid != nullptr);
        unknown->QueryInterface(*piid, (void**)&mInterface);
        assert(mInterface != nullptr);
        return mInterface;
    }

    INTERFACE* operator=(const COMPtr<INTERFACE, piid>& RefCOMPtr) {
        assert(&RefCOMPtr != nullptr);
        mInterface = reinterpret_cast<INTERFACE*>RefCOMPtr;
        if (mInterface) {
            mInterface->AddRef();
        }
        return mInterface;
    }

    void Attach(INTERFACE *ptr) {
        if (mInterface) {
            mInterface->Release();
        }
        mInterface = ptr;
    }

    INTERFACE* Detach() {
        INTERFACE *ptr = mInterface;
        mInterface = nullptr;
        return ptr;
    }

    void Release() {
        if (mInterface) {
            mInterface->Release();
            mInterface = nullptr;
        }
    }

    bool Equals(IUnknown *other) {
        if (other == nullptr) {
            return false;
        }
        IUnknown *unknown = nullptr;
        mInterface->QueryInterface(IID_IUnknown, reinterpret_cast<void**>(&unknown));
        const bool ret = ((other == unknown) ? true : false);
        pUnknown->Release();
        return ret;
    }

private:
    INTERFACE *mInterface;
};