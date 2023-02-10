//
// Created by Denisa on 06.04.2022.
//

#include "DynamicArray.h"

void test_dynamic_vector() {
    TemplateVector<int> intregi;
    assert(intregi.size() == 0);
    for (int i = 0; i < 20; i++) {
        intregi.add(i);
    }
    assert(intregi.size() == 20);
    assert(intregi.get(3) == 3);

}