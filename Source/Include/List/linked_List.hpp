#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>
#include "list.hpp"

template <typename T>
class LinkedList: public List<T> {
public:
	LinkedList(size_t _size = 0);
	virtual T& at(const size_t index) override;
	virtual size_t find(const T &n) const override;
    virtual size_t size() const override;
	virtual bool empty() const override;

	virtual bool push_back(const T &n) override;
	virtual T pop_back() override;
	virtual bool insert(const size_t index, const T &n) override;
	bool erase(const size_t index);
	virtual bool erase(const size_t index, const size_t length) override;
	virtual bool clear() override;
	virtual void print() override;
	virtual ~LinkedList();
private:
	struct _LLNode {
		_LLNode(_LLNode * next = nullptr, _LLNode * prev = nullptr, T n = T()) : next(next), prev(prev), data(n) { }
		
		_LLNode * next;
		_LLNode * prev;
		T data;
	};
	_LLNode * _head;
	_LLNode * _tail;
	size_t _size;
};

template <typename T>
LinkedList<T>::LinkedList(size_t _size) : _head(nullptr), _tail(nullptr), _size(0) {
	for(size_t i = 0 ; i < _size ; i++)
		push_back(T());
}

template <typename T>
T& LinkedList<T>::at(size_t index) {
	if(index < 0 or index >= _size)
		throw "Out of bound!";
	_LLNode * p = _head;
	for(size_t i = 0 ; i < index ; i++)
		p = p->next;
	return p->data;
}

template <typename T>
size_t LinkedList<T>::find(const T &n) const {
	_LLNode * p = _head;
	for(size_t i = 0 ; i < _size ; i++) {
		if(p->data == n) {
			return i;
		}
	}
	return _size;
}

template <typename T>
inline size_t LinkedList<T>::size() const {
	return _size;
}

template <typename T>
inline bool LinkedList<T>::empty() const {
	return _size == 0;
}

template <typename T>
bool LinkedList<T>::push_back(const T &n) {
	if(_size == 0) {
		_head = _tail = new _LLNode(nullptr, nullptr, n);
		_size = 1;
	} else {
		_tail->next = new _LLNode(nullptr, _tail, n);
		_tail = _tail->next;
		_size++;
	}
	return true;
}

template <typename T>
T LinkedList<T>::pop_back() {
	if(_size == 0) {
		throw "Out of bound!";
	} else if(_size == 1){
		_size = 0;
		T res = _tail->data;
		delete _tail;
		_head = _tail = nullptr;
		return res;
	} else {
		_size--;
		T res = _tail->data;
		_LLNode * prev_node = _tail->prev;
		delete _tail;
		_tail = prev_node;
		_tail->next = nullptr;
		return res;
	}
}

template <typename T>
bool LinkedList<T>::insert(size_t index, const T &n) {
	if(index < 0 or index > _size)
		return false;
	// Draw a table, columns with empty and non-empty
	// raws with zreo index and non-zero index and tail index.
	if(index == 0) {
		_LLNode * new_node = new _LLNode(_head, nullptr, n);
		_head->prev = new_node;
		_head = new_node;
		_size++;
	} else if(index == _size) {
		push_back(n);
	} else {
		_LLNode * old_node = _head;
		for(size_t i = 0 ; i < index ; i++) {
			old_node = old_node->next;
		}
		// better to store these nodes!
		_LLNode * old_prev = old_node->prev;
		_LLNode * new_node = new _LLNode();
		new_node->data = n;
		
		new_node->prev = old_prev;
		new_node->next = old_node;
		old_node->prev = new_node;
		old_prev->next = new_node;
		_size++;
	}
	return true;
}

template <typename T>
bool LinkedList<T>::erase(const size_t index) {
	if(index < 0 or index >= _size) return false;
	if(index == 0) {
		_head = _head->next;
		delete _head->prev;
		_head->prev = nullptr;
	} else if(index == _size - 1) {
		_tail = _tail->prev;
		delete _tail->next;
		_tail->next = nullptr;
	} else {
		_LLNode * cur_node = _head;
		_LLNode * prev_node;
		_LLNode * next_node;
		for(size_t i = 0 ; i < index ; i++) {
			cur_node = cur_node->next;
		}
		prev_node = cur_node->prev;
		next_node = cur_node->next;
		prev_node->next = next_node;
		next_node->prev = prev_node;
		delete cur_node;
	}
	_size--;
	return true;
}

template <typename T>
bool LinkedList<T>::erase(const size_t index, const size_t length) {
	if(index + length > _size) {
		return false;
	} else {
		for(size_t i = 0 ; i < length ; ++i) {
			erase(index);
		}
		return true;
	}
}

template <typename T>
bool LinkedList<T>::clear() {
	_LLNode * cur_node = _head;
	_LLNode * old;
	while(cur_node != nullptr) {
		old = cur_node;
		cur_node = cur_node->next;
		delete old;
	}
	return true;
}

template <typename T>
void LinkedList<T>::print() {
	_LLNode *cur = _head;
	int cnt = 0;
	while(cur != nullptr) {
		std::cout << cnt << ": " << cur->data << std::endl;
		cnt++;
		cur = cur->next;
	}
}

template <typename T>
LinkedList<T>::~LinkedList() {
	clear();
}

#endif