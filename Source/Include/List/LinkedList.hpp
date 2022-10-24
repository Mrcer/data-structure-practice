#ifndef LINKED_LIST
#define LINKED_LIST

struct _LLNode {
	_LLNode(_LLNode * next = nullptr, _LLNode * prev = nullptr, int n = 0) : next(next), prev(prev), data(n) { }
	
	_LLNode * next;
	_LLNode * prev;
	int data;
};

class LinkedList {
public:
	LinkedList(int _size = 0);
	int at(int index);
	int find(int n);
	bool empty();
	
	bool push_back(int n);
	int pop_back();
	bool insert(int index, int n);
	bool erase(int index);
	bool clear();

	~LinkedList();
private:
	_LLNode * head;
	_LLNode * tail;
	int size;
};

LinkedList::LinkedList(int _size) : head(nullptr), tail(nullptr), size(0) {
	for(int i = 0 ; i < _size ; i++)
		push_back(0);
}

int LinkedList::at(int index) {
	if(index < 0 or index >= size)
		return -1;
	_LLNode * p = head;
	for(int i = 0 ; i < index ; i++)
		p = p->next;
	return p->data;
}

int LinkedList::find(int n) {
	_LLNode * p = head;
	for(int i = 0 ; i < size ; i++) {
		if(p->data == n) {
			return i;
		}
	}
	return -1;
}

inline bool LinkedList::empty() {
	return size == 0;
}

bool LinkedList::push_back(int n) {
	if(size == 0) {
		head = tail = new _LLNode(nullptr, nullptr, n);
		size = 1;
	} else {
		tail->next = new _LLNode(nullptr, tail, n);
		tail = tail->next;
		size++;
	}
	return true;
}

int LinkedList::pop_back() {
	if(size == 0) {
		return -1;
	} else if(size == 1){
		size = 0;
		int res = tail->data;
		delete tail;
		head = tail = nullptr;
		return res;
	} else {
		size--;
		int res = tail->data;
		_LLNode * prev_node = tail->prev;
		delete tail;
		tail = prev_node;
		tail->next = nullptr;
		return res;
	}
}

bool LinkedList::insert(int index, int n) {
	if(index < 0 or index > size)
		return false;
	// Draw a table, columns with empty and non-empty
	// raws with zreo index and non-zero index and tail index.
	if(index == 0) {
		_LLNode * new_node = new _LLNode(head, nullptr, n);
		head->prev = new_node;
		head = new_node;
		size++;
	} else if(index == size) {
		push_back(n);
	} else {
		_LLNode * old_node = head;
		for(int i = 0 ; i < index ; i++) {
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
		size++;
	}
	return true;
}


bool LinkedList::erase(int index) {
	if(index < 0 or index >= size) return false;
	if(index == 0) {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
	} else if(index == size - 1) {
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
	} else {
		_LLNode * cur_node = head;
		_LLNode * prev_node;
		_LLNode * next_node;
		for(int i = 0 ; i < index ; i++) {
			cur_node = cur_node->next;
		}
		prev_node = cur_node->prev;
		next_node = cur_node->next;
		prev_node->next = next_node;
		next_node->prev = prev_node;
		delete cur_node;
	}
	size--;
	return true;
}

bool LinkedList::clear() {
	_LLNode * cur_node = head;
	_LLNode * old;	
	while(cur_node != nullptr) {
		old = cur_node;
		cur_node = cur_node->next;
		delete old;
	}
	return true;
}


LinkedList::~LinkedList() {
	clear();
}

#endif