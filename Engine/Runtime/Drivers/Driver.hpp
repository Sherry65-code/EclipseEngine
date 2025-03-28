#pragma once

#include <memory>

class Driver {
public:
    virtual ~Driver() = default;
    virtual void Initialize(void*) = 0;
    virtual void UpdateFrame() = 0;
};
