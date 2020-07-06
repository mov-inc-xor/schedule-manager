#pragma once

#include <map>
#include <iostream>

template <class T>
class Collection {
protected:
    int nextId;
    std::map<int, T> items;
public:
    Collection() : nextId(0) {}

    virtual int add(const T& item);
    void remove(int id);
    bool has(int id);
    T find(int id);
    size_t size();
    bool empty();
    void print(std::ostream & out);

    const std::map<int, T> & getItems() const;
};

template <class T>
int Collection<T>::add(const T& item) {
    items[nextId] = item;
    return nextId++;
}

template <class T>
void Collection<T>::remove(int id) {
    if (has(id)) {
        items.erase(items.find(id));
    }
}

template<class T>
bool Collection<T>::has(int id) {
    return items.find(id) != items.end();
}

template<class T>
T Collection<T>::find(int id) {
    if (has(id)) {
        return items[id];
    }
    return T();
}

template<class T>
size_t Collection<T>::size() {
    return items.size();
}

template<class T>
bool Collection<T>::empty() {
    return items.empty();
}

template<class T>
void Collection<T>::print(std::ostream &out) {
    for (auto it = items.begin(); it != items.end(); it++) {
        out << '<' << (*it).first << '>' << ' ' << (*it).second << std::endl;
    }
}

template<class T>
const std::map<int, T> &Collection<T>::getItems() const {
    return items;
}
