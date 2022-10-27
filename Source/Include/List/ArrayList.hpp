#ifndef ARRAY_LIST
#define ARRAY_LIST

#include <cstddef>
#include "List.hpp"
#define INITIAL_CAPACITY 4

template <typename T>
class ArrayList: public List<T> {
public:
	ArrayList();
    ArrayList(const ArrayList<T> &list);
    ArrayList<T> &operator=(const ArrayList<T> &list);
    ArrayList(const ArrayList<T> &&list);
    ArrayList<T> &operator=(const ArrayList<T> &&list);
	virtual T& at(const size_t index) override;
	virtual size_t find(const T &n) const override;
    virtual size_t size() const override;
	virtual bool empty() const override;
	T& operator[](const size_t index);

	virtual bool push_back(const T &n) override;
	virtual T pop_back() override;
	virtual bool insert(const size_t index, const T &n) override;
	virtual bool erase(const size_t index, const size_t length=1) override;
	virtual bool clear() override;

	virtual ~ArrayList();
private:
    void grow();
    T *_data;
    size_t _size;
    size_t _capacity;
};

template <typename T>
ArrayList<T>::ArrayList(): _data(new T[INITIAL_CAPACITY]), _size(0), _capacity(INITIAL_CAPACITY) { }

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T> &list) {
    for(size_t i = 0 ; i < list._size ; ++i) {
        push_back(list[i]);
    }
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T> &list) {
    clear();
    for(size_t i = 0 ; i < list._size ; ++i) {
        push_back(list[i]);
    }
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T> &&list) {
    _data = list._data;
    _size = list._size;
    _capacity = list._capacity;
    list._data = nullptr;
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T> &&list) {
    if(this == &list) return *this;
    _data = list._data;
    _size = list._size;
    _capacity = list._capacity;
    list._data = nullptr;
}


template <typename T>
T& ArrayList<T>::at(const size_t index) {
    return _data[index];
}

template <typename T>
size_t ArrayList<T>::find(const T &n) const {
    for (size_t i = 0 ; i < _size ; ++i) {
        if (_data[i] == n) {
            return i;
        }
    }
    return _size;
}

template <typename T>
size_t ArrayList<T>::size() const {
    return _size;
}

template <typename T>
bool ArrayList<T>::empty() const {
    return _size == 0;
}

template <typename T>
T& ArrayList<T>::operator[](const size_t index) {
    return at(index);
}

template <typename T>
bool ArrayList<T>::push_back(const T &n) {
    if(_size == _capacity) grow();
    _data[_size++] = n;
    return true;
}

template <typename T>
T ArrayList<T>::pop_back() {
    T t = _data[--_size];
    return t;
}

template <typename T>
bool ArrayList<T>::insert(const size_t index, const T &n) {
    if(index > _size) return false;
    if(_size == _capacity) grow();
    for(size_t i = _size; i > index; --i) {
        _data[i] = _data[i - 1];
    }
    _data[index] = n;
    ++_size;
    return true;
}

template <typename T>
bool ArrayList<T>::erase(const size_t index, const size_t length) {
    if(index + length > _size) return false;
    for(size_t i = index ; i + length < _size ; ++i) {
        _data[i] = _data[i + length];
    }
    _size -= length;
    return true;
}

template <typename T>
bool ArrayList<T>::clear() {
    _size = 0;
    return true;
}

template <typename T>
void ArrayList<T>::grow() {
    size_t new_capacity = _capacity * 2;
    T *new_data = new T[new_capacity];
    for(size_t i = 0 ; i < _size ; ++i) {
        new_data[i] = _data[i];
    }
    delete [] _data;
    _data = new_data;
    _capacity = new_capacity;
}

template <typename T>
ArrayList<T>::~ArrayList() {
    if(_data != nullptr) delete [] _data;
}


#endif