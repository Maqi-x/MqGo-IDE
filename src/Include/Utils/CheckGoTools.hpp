#include <Utils/Types.hpp>
#include <Utils/Utils.hpp>

void CheckGo() {
    try {
        GetPath("go")
    } catch std::runtime_error {
        // TODO
    }
}