// Example: Minimal custom allocator (C++98/03)
// Note: commented code is desirable, but not required for a minimal implementation.
#include <iostream>
#include <vector>

template <typename T>
class MinimalAllocator {
public:
    typedef T              value_type;
    typedef T*             pointer;
    typedef const T*       const_pointer;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    template <typename U>
    struct rebind { typedef MinimalAllocator<U> other; };

    MinimalAllocator() {}

    template <typename U>
    MinimalAllocator(const MinimalAllocator<U>&) {}

    pointer allocate(size_type n, const void* = 0) {
        return static_cast<pointer>(::operator new(n * sizeof(T)));
    }

    void deallocate(pointer p, size_type) { ::operator delete(p); }
    void construct(pointer p, const_reference val) { new(static_cast<void*>(p)) T(val); }
    void destroy(pointer p) { p->~T(); }
};

// template <typename T, typename U>
// bool operator==(const MinimalAllocator<T>&, const MinimalAllocator<U>&) {
//     return true;
// }

// template <typename T, typename U>
// bool operator!=(const MinimalAllocator<T>&, const MinimalAllocator<U>&) {
//     return false;
// }

int main() 
{
    std::vector<int, MinimalAllocator<int> > vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    for (std::size_t i = 0; i < vec.size(); ++i) {
        std::cout << "Value: " << vec[i] << std::endl;
    }

    return 0;
}
