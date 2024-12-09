#include <iostream>

template <typename T>
class dynamic_arr {
    T* arr;
    size_t size;
    size_t m_capacity;

public:
    dynamic_arr() : arr(nullptr), size(0), m_capacity(0) {}

    dynamic_arr(size_t _size, T default_value = T()) : size(_size), m_capacity(_size) {
        arr = new T[m_capacity];
        for (size_t i = 0; i < size; i++) {
            arr[i] = default_value;
        }
    }

    void push(size_t pos, T val);
    void del_el(size_t pos);
    T get_pos(size_t pos);
    void push_back(T val);
    T& operator[](int index);
    size_t get_size() { return size; }

private:
    void capacity(size_t);
};

template <typename T>
T dynamic_arr<T>::get_pos(size_t pos) {
    return arr[pos];
}

template <typename T>
T& dynamic_arr<T>::operator[](int index) {
    return arr[index];
}

template <typename T>
void dynamic_arr<T>::capacity(size_t new_size) {
    if (new_size > m_capacity) {
        size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        T* new_arr = new T[new_capacity];
        for (size_t i = 0; i < size; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
        m_capacity = new_capacity;
    }
}

template <typename T>
void dynamic_arr<T>::push_back(T val) {
    if (size == m_capacity) {
        capacity(size + 1);
    }

    arr[size] = val;
    size++;
}

template <typename T>
void dynamic_arr<T>::push(size_t pos, T val) {
    if (pos > size) {
        std::cout << "Error: position out of range.";
        return;
    }

    if (size == m_capacity) {
        capacity(size + 1);
    }

    for (size_t i = size; i > pos; i--) {
        arr[i] = arr[i - 1];
    }

    arr[pos] = val;
    size++;
}

template <typename T>
void dynamic_arr<T>::del_el(size_t pos) {
    if (pos >= size) {
        std::cout << "Error: invalid position." << std::endl;
        return;
    }

    for (size_t i = pos; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
}
