#pragma once
#include <iostream>



template<typename T>
class Node {
public:
	T value;
	Node* next;
	Node* prev;

	Node() {
		next = nullptr;
		prev = nullptr;
	}

	Node(T x) {
		value = x;
		next = nullptr;
		prev = nullptr;
	}
};



template<typename T>
class Container {
private:
	int size;
	Node<T>* first;
	Node<T>* last;
public:
	Container() {
		size = 0;
		first = nullptr;
		last = nullptr;
	}

	class Iterator {
	private:
		Node<T>* pointer;
	public:
		Iterator(Node<T>* new_pointer): pointer(new_pointer) {}

		Iterator operator++(int) {
			pointer = pointer->next;
			return *this;
		}

		void next() {
			pointer = pointer->next;
		}

		bool operator !=(const Iterator& another) {
			return pointer != another.pointer;
		}

		bool operator ==(const Iterator& another) {
			return pointer == another.pointer;
		}

		T const & value() {
			return pointer->value;
		}
	};

	Iterator begin() { return Iterator(this->first->next); }
	Iterator end() { return Iterator(this->last); }



	int get_size() const {
		return size;
	}

	bool is_empty() const{
		return size == 0;
	}

	void push_front(T x) {
		Node<T>* p = new Node<T>(x);
		if (is_empty()) {
			delete first;
			delete last;
			first = new Node<T>(x);
			last = new Node<T>(x);
			first->next = p;
			last->prev = p;
			p->next = last;
			p->prev = first;
			size++;
		}
		else {
			first->next->prev = p;
			p->next = first->next;
			first->next = p;
			p->prev = first;
			size++;
		}
	}

	void push_back(T x) {
		Node<T>* p = new Node<T>(x);
		if (is_empty()) {
			delete first;
			delete last;
			first = new Node<T>(x);
			last = new Node<T>(x);
			first->next = p;
			last->prev = p;
			p->next = last;
			p->prev = first;
			size++;
		}
		else {
			last->prev->next = p;
			p->prev = last->prev;
			last->prev = p;
			p->next = last;
			size++;
		}
	}

	void pop_front() {
		if (is_empty()) {
			return;
		}
		Node<T>* p = first->next->next;
		p->prev = first;
		delete first->next;
		first->next = p;
		size--;
	}

	void pop_back() {
		if (is_empty()) {
			return;
		}
		Node<T>* p = last->prev->prev;
		p->next = last;
		delete last->prev;
		last->prev = p;
		size--;
	}

	T const & get_first() const {
		return first->next->value;
	}

	T const & get_last() const {
		return last->prev->value;
	}

	void clear() {
		Node<T>* buffer = nullptr;
		if (is_empty()) {
			return;
		}
		while (first->next != last) {
			buffer = first->next;
			delete first;
			first = buffer;
			size--;
		}
		last = nullptr;
	}

	void reverse() {
		if (is_empty()) {
			return;
		}
		Node<T>* p = first;
		Node<T>* buffer = nullptr;
		while (p != nullptr) {
			buffer = p->prev;
			p->prev = p->next;
			p->next = buffer;
			p = p->prev;
		}
		last = first;
		first = buffer->prev;
	}

	void swap_with(Container& second_container) {
		std::swap(this->first, second_container.first);
		std::swap(this->last, second_container.last);
		std::swap(this->size, second_container.size);
	}

	void print() const{
		if (is_empty()) {
			return;
		}
		Node<T>* p = first->next;
		while (p != last) {
			std::cout << p->value << " ";
			p = p->next;
		}
		std::cout << std::endl;
	}

};