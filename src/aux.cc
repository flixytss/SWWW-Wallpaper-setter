#include <aux.hpp>
#include <cstdlib>
#include <print>

void Finish(int s) {
    std::println("Exited {}", s); // COMPLETE
    exit(s);
}