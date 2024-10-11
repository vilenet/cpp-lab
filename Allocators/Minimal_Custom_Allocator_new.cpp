// Example: Minimal custom allocator (C++11)
// Note: commented code is desirable, but not required for a minimal implementation.
#include <iostream>
#include <vector>

template <typename T>
class MinimalAllocator {
public:
    using value_type = T;

    // MinimalAllocator() = default; // Or MinimalAllocator() noexcept {}
    // template <typename U> 
    // MinimalAllocator(const MinimalAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t) noexcept { ::operator delete(p); }
};

// template <typename T, typename U>
// bool operator==(const MinimalAllocator<T>&, const MinimalAllocator<U>&) noexcept {
//     return true;
// }

// template <typename T, typename U>
// bool operator!=(const MinimalAllocator<T>&, const MinimalAllocator<U>&) noexcept {
//     return false;
// }

int main() 
{
    std::vector<int, MinimalAllocator<int>> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    for (const auto& val : vec) {
        std::cout << "Value: " << val << std::endl;
    }

    return 0;
}


