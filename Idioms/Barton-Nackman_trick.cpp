// Barton–Nackman trick - Restricted template expansion

#include <iostream>

template<typename T>
class equal_comparable {
    friend bool operator==(T const &a, T const &b) { return  a.equal_to(b); }
    friend bool operator!=(T const &a, T const &b) { return !a.equal_to(b); }
};

class value_type : private equal_comparable<value_type> {
public:
    value_type(int value) : value_(value) {}

    bool equal_to(value_type const& rhs) const {
        return value_ == rhs.value_;
    }

    int get_value() const {
        return value_;
    }

private:
    int value_;
};


int main() 
{
    value_type a(10);
    value_type b(10);
    value_type c(20);

    std::cout << "a == b: " << (a == b) << std::endl; // Output: 1 (true)
    std::cout << "a != b: " << (a != b) << std::endl; // Output: 0 (false)
    std::cout << "a == c: " << (a == c) << std::endl; // Output: 0 (false)
    std::cout << "a != c: " << (a != c) << std::endl; // Output: 1 (true)

    return 0;
}
