#pragma once

#include "../Driver.hpp"

class GL : public Driver {
    public:
    void Initialize(void* winptr_vp) override;
    void UpdateFrame() override;
    ~GL() override;
};