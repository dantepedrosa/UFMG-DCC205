#include <iostream>
#include <limits>

int main() {
    std::cout << "Tamanho do long long: " << sizeof(unsigned int) << " bytes\n";
    std::cout << "Máximo valor: " << std::numeric_limits<unsigned int>::max() << "\n";
    std::cout << "Mínimo valor: " << std::numeric_limits<unsigned int>::min() << "\n";
    return 0;
}