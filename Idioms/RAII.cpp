// RAII (Resource Acquisition Is Initialization) 

// The idea is to manage resources such as memory, file handles, or locks by tying their 
// lifecycle to the lifetime of objects. In RAII, resources are acquired during 
// object construction and automatically released in the destructor. This ensures 
// that resources are properly freed when objects go out of scope, even if an 
// exception occurs, making the code safer and less prone to resource leaks.

#include <iostream>
#include <fstream>
#include <string>

class FileHandler {
public:
    FileHandler(const std::string& filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file");
        }
    }

    void write(const std::string& data) {
        if (file.is_open()) {
            file << data << std::endl;
        }
    }

    ~FileHandler() {
        if (file.is_open()) {
            file.close();
        }
    }

private:
    std::ofstream file;
};

int main() {
    try {
        FileHandler fh("example.txt");
        fh.write("Hello, RAII!");
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
