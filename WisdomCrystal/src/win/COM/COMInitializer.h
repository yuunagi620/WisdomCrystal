// COMInitializer.h

#pragma once

#include <boost/noncopyable.hpp>


class COMInitializer : private boost::noncopyable {

public:
    COMInitializer();
    virtual ~COMInitializer();

    bool Init();
};
