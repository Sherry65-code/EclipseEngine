#include "WindowManager.hpp"

#ifdef _WIN64
#include "_window_manager_windows.hpp"
#endif

#ifdef __linux__
#include "_window_manager_linux.hpp"
#endif