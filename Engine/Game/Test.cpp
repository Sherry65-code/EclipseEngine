#include <Runtime/Runtime.hpp>

int main(int argc, char* argv[]) {
    EclipseRuntime rt;
    rt.Init();
    rt.Shutdown();
}