#ifndef LIST
#define LIST

#include <cstddef>

template <typename T>
class List {
public:
	List() = default;
	virtual T& at(const size_t index) = 0;
	virtual size_t find(const T &n) const = 0;
    virtual size_t size() const = 0;
    void resize(const size_t n);
	virtual bool empty() const = 0;
	T& operator[](const size_t index);

	virtual bool push_back(const T &n) = 0;
	virtual T pop_back() = 0;
	virtual bool insert(const size_t index, const T &n) = 0;
	virtual bool erase(const size_t index, const size_t length) = 0;
	virtual bool clear() = 0;
	virtual ~List() = default;
};

template <typename T>
void List<T>::resize(const size_t n) {
    if(n < size()) {
        while(size() > n) {
            pop_back();
        }
    } else {
        while(size() < n) {
            push_back(T());
        }
    }
}

template <typename T>
T& List<T>::operator[](const size_t index) {
    return at(index);
}

#endif