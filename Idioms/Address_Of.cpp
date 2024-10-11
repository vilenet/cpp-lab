// ADDRESS-OF IDIOM

//#include <memory>

template <class T>
T * addressof(T & v)
{
  return reinterpret_cast<T *>(& const_cast<char&>(reinterpret_cast<const volatile char &>(v)));
}

class nonaddressable 
{
public:
    typedef double useless_type;
private:
    useless_type operator&() const;
};

int main()
{
  nonaddressable na;

  //nonaddressable * naptr = &na;                // Ex1: Error: operator & of type nonadressable is private.

  nonaddressable * naptr = addressof(na);        // Ex2: C++98 using address off casts

  //nonaddressable * naptr = std::addressof(na); // Ex3: C++11 using std::addressof() from <memory>

}
