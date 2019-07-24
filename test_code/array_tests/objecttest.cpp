#include "testobject.h"
#include <iostream>
#include <sstream>
#include <stdio.h>

#define HEADER "abc:"
#define INT " %d"
#define COMMA " ,"

int main() {
    TestObject o1;
    TestObject o2;

    std::cout << "object1 before: " << o1.getI() << std::endl;
    std::cout << "object2 before: " << o2.getI() << std::endl;

    o1.setI(2);

    std::cout << "object1 after: " << o1.getI() << std::endl;
    std::cout << "object2 after: " << o2.getI() << std::endl;


    std::stringstream x;
    x << "abc:  ASD " << 5 << "," << "6,7,8";
    std::string s = x.str();
    std::cout << s << std::endl;

    int y, z;
    char mt[5];
    int r = sscanf(s.c_str(), HEADER " %4s" INT COMMA INT, mt, &y, &z);
    std::cout << r << std::endl;
    std::cout << mt << std::endl;
    //if (r >= 2) {
        std::cout << y << " " << z << std::endl;
    //}

}
