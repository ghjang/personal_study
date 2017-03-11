#include <iostream>

#include "dynamic_polymorphism.h"
#include "static_polymorphism.h"


int main() {
    using std::cout;
    using std::endl;

    cout << "[dynamic polymorphism test]" << endl;
    runDynamicPolymorphismTest();

    cout << '\n';

    cout << "[static polymorphism test]" << endl;
    runStaticPolymorphismTest();

    return 0;
}

