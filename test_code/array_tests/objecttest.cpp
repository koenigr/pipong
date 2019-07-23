#include "testobject.h"
#include <iostream>

int main() {
    TestObject o1;
    TestObject o2;

    std::cout << "object1 before: " << o1.getI() << std::endl;
    std::cout << "object2 before: " << o2.getI() << std::endl;

    o1.setI(2);

    std::cout << "object1 after: " << o1.getI() << std::endl;
    std::cout << "object2 after: " << o2.getI() << std::endl;

}
