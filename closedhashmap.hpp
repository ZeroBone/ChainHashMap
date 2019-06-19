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

#ifndef CLOSEDHASHMAP_CLOSEDHASHMAP_HPP
#define CLOSEDHASHMAP_CLOSEDHASHMAP_HPP

template <class K, class V, size_t (*H)(const K& value, size_t capacity)>
class ClosedHashMap {

    private:

    class ClosedListNode {

        public:

        K key;
        V value;

        ClosedListNode* next;

    };

    size_t capacity;
    ClosedListNode** table;

    public:

    explicit ClosedHashMap(size_t capacity) : capacity(capacity) {

        table = new ClosedListNode*[capacity];

        for (size_t i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }

    }

    ~ClosedHashMap();

    /**
     * Method for adding unique elements to the hashmap.
     * @param key the key.
     * @param value the value.
     */
    void add(const K& key, const V& value);

    /**
     * Method for allocating the memory for new unique elements.
     * @param key the key.
     * @param value the value.
     */
    V& addAllocate(const K& key);

    /**
     * Method for adding non-unique elements to the hashmap.
     * @param key
     * @param value
     */
    void set(const K& key, const V& value);

    /**
     * Method for allocating the memory for new non-unique elements.
     * @param key
     * @param value
     */
    V& setAllocate(const K& key);

    V* get(const K& key);

};

template<class K, class V, size_t (*H)(const K&, size_t)>
void ClosedHashMap<K, V, H>::add(const K& key, const V& value) {

    addAllocate(key) = value;

}

template<class K, class V, size_t (*H)(const K&, size_t)>
V& ClosedHashMap<K, V, H>::addAllocate(const K& key) {

    ClosedListNode* node = new ClosedListNode();

    node->key = key;

    ClosedListNode** listStart = &table[H(key, capacity)];

    node->next = *listStart == nullptr ? nullptr : (*listStart)->next;

    *listStart = node;

    return node->value;

}

template<class K, class V, size_t (*H)(const K&, size_t)>
void ClosedHashMap<K, V, H>::set(const K& key, const V& value) {

    setAllocate(key) = value;

}

template<class K, class V, size_t (*H)(const K&, size_t)>
V& ClosedHashMap<K, V, H>::setAllocate(const K& key) {

    ClosedListNode** pointerToNodePointer = &table[H(key, capacity)];

    ClosedListNode* currentNode = *pointerToNodePointer;

    if (currentNode == nullptr) {

        currentNode = new ClosedListNode();

        currentNode->next = nullptr;
        currentNode->key = key;

        *pointerToNodePointer = currentNode;

        return currentNode->value;

    }

    for (;;) {

        if (currentNode->key == key) {

            return currentNode->value;

        }

        if (currentNode->next == nullptr) {

            currentNode->next = new ClosedListNode();

            currentNode->next->next = nullptr;
            currentNode->next->key = key;

            return currentNode->next->value;

        }

        currentNode = currentNode->next;

    }

}

template<class K, class V, size_t (*H)(const K&, size_t)>
ClosedHashMap<K, V, H>::~ClosedHashMap() {

    ClosedListNode** pointerToNodePointer = table;
    ClosedListNode** end = table + capacity;

    for (; pointerToNodePointer < end; pointerToNodePointer++) {

        ClosedListNode* currentNode = *pointerToNodePointer;

        if (currentNode == nullptr) {
            continue;
        }

        /*while (currentNode->next != nullptr) {

            ClosedListNode* next = currentNode->next;
            delete currentNode;
            currentNode = next;

        }*/
        for (;;) {

            ClosedListNode* next = currentNode->next;

            delete currentNode;

            if (next == nullptr) {
                break;
            }

            currentNode = next;

        }

    }

    delete[] table;

}

template<class K, class V, size_t (*H)(const K&, size_t)>
V* ClosedHashMap<K, V, H>::get(const K& key) {

    ClosedListNode** pointerToNodePointer = &table[H(key, capacity)];

    ClosedListNode* currentNode = *pointerToNodePointer;

    if (currentNode == nullptr) {

        return nullptr;

    }

    /*while (currentNode->next != nullptr) {

        if (currentNode->key == key) {

            return &currentNode->value;

        }

        currentNode = currentNode->next;

    }*/

    for (;;) {

        if (currentNode->key == key) {

            return &currentNode->value;

        }

        if (currentNode->next == nullptr) {

            return nullptr;

        }

        currentNode = currentNode->next;

    }

}

#endif