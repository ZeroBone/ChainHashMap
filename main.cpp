/**
MIT License

Copyright (c) 2019 Alexander Mayorov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#include <iostream>
#include "closedhashmap.hpp"

size_t intHasher(const int& value, size_t capacity) {
    return value % capacity;
}

int main() {

    // also works:
    // constexpr auto intHasher = [](const int& value, size_t capacity) -> size_t {
    //    return *value % capacity;
    // };

    auto hashMap = new ClosedHashMap<int, int, intHasher>(50);

    hashMap->add(1, 1);
    hashMap->add(4, 1);
    hashMap->add(5, 1);
    hashMap->add(6, 1);
    hashMap->add(7, 1);
    hashMap->add(50, 4);
    hashMap->add(51, 125);
    hashMap->set(51, 140);
    hashMap->set(51, 141);
    hashMap->set(51, 20);

    std::cout << *hashMap->get(51) << std::endl;

    delete hashMap;

    return 0;

}