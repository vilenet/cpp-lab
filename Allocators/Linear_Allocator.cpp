// Linear Allocator (Bump Allocator) (С++11)
#include <iostream>
#include <vector>
#include <cstring>

template <typename T>
class LinearAllocator {
public:
    using value_type = T;

    LinearAllocator() noexcept : m_buffer(nullptr), m_size(0), m_offset(0) {}

    LinearAllocator(std::size_t size) : m_size(size), m_offset(0) {
        m_buffer = static_cast<char*>(::operator new(m_size));
    }

    LinearAllocator(const LinearAllocator& other) noexcept {
        m_size = other.m_size;
        m_offset = other.m_offset;

        if (other.m_buffer) {
            m_buffer = static_cast<char*>(::operator new(m_size));  // Re-allocate memory
            std::memcpy(m_buffer, other.m_buffer, m_size);          // Copy the contents of memory
        } 
        else {
            m_buffer = nullptr;
        }
    }

    LinearAllocator(LinearAllocator&& other) noexcept {
        m_buffer = other.m_buffer;
        m_size = other.m_size;
        m_offset = other.m_offset;
        other.m_buffer = nullptr;
        other.m_size = 0;
        other.m_offset = 0;
    }

    ~LinearAllocator() { 
        ::operator delete(m_buffer); 
        m_buffer = nullptr;
    }

    LinearAllocator& operator=(const LinearAllocator& other) noexcept {
        if (this != &other) {
            if (m_buffer) { ::operator delete(m_buffer); }
            m_size = other.m_size;
            m_offset = other.m_offset;

            if (other.m_buffer) {
                m_buffer = static_cast<char*>(::operator new(m_size));  // Re-allocate memory
                std::memcpy(m_buffer, other.m_buffer, m_size);          // Copy the contents of memory
            } 
            else {
                m_buffer = nullptr;
            }
        }
        return *this;
    }

    LinearAllocator& operator=(LinearAllocator&& other) noexcept {
        if (this != &other) {
            ::operator delete(m_buffer);
            m_buffer = other.m_buffer;
            m_size = other.m_size;
            m_offset = other.m_offset;
            other.m_buffer = nullptr;
            other.m_size = 0;
            other.m_offset = 0;
        }
        return *this;
    }

    T* allocate(std::size_t n) {
        std::size_t bytes = n * sizeof(T);
        if (m_offset + bytes > m_size) { throw std::bad_alloc(); }
        T* ptr = reinterpret_cast<T*>(m_buffer + m_offset);
        m_offset += bytes;
        return ptr;
    }

    // Linear allocator does not support freeing individual blocks!
    void deallocate(T*, std::size_t) noexcept { /* Doesn't do anything! */}

    void reset() { m_offset = 0; }

    std::size_t max_size() const noexcept { return m_size / sizeof(T); }

    template <typename U>
    bool operator==(const LinearAllocator<U>& other) const noexcept {
        return m_buffer == other.m_buffer;
    }

    template <typename U>
    bool operator!=(const LinearAllocator<U>& other) const noexcept {
        return !(*this == other);
    }

private:
    char* m_buffer;          // Pointer to the beginning of the memory block
    std::size_t m_size;      // Total size of the allocated block
    std::size_t m_offset;    // Offset relative to the beginning of the block
};

int main() 
{
    const std::size_t allocatorSize = 1024;  // 1 KB
    LinearAllocator<int> allocator(allocatorSize);

    std::vector<int, LinearAllocator<int>> vec(allocator);

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    for (const auto& val : vec) {
        std::cout << "Value: " << val << std::endl;
    }

    allocator.reset();

    std::vector<int, LinearAllocator<int>> new_vec(allocator);

    new_vec.push_back(40);
    new_vec.push_back(50);
    new_vec.push_back(60);

    for (const auto& val : new_vec) {
        std::cout << "New value: " << val << std::endl;
    }

    return 0;
}
