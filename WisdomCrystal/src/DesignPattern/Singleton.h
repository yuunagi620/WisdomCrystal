// Singleton.h

#pragma once

#include <memory>

template <class T>
class Singleton {

public:
    static T* GetInstance() {
        static T instance;
        return &instance;
    }

protected:
    Singleton() {}
    virtual ~Singleton() {}

private:
    Singleton(const Singleton& rhs);
    Singleton& operator=(const Singleton& rhs) {};

};

