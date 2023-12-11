#pragma once
#include <iostream>
#include <random>
#include <stdexcept>
#include <ctime>

using namespace std;

template<typename T>
struct Node {
	T _data;
	int _power;
	Node* _next;
	Node() : _data(0), _power(0), _next(nullptr) {};
	Node(T value, int power) {
		_data = value;
		_power = power;
		_next = nullptr;
	}
};

template<typename T>
class SingleLinkedList {
	int _size;
	Node<T>* _head;
public:
	SingleLinkedList() : _size(0), _head(nullptr) {};
	SingleLinkedList(const SingleLinkedList<T>& other) {
		_head = nullptr;
		_size = 0;
		if (other._head) {
			Node<T>* current = other._head;
			do {
				push_tail(current->_data, current->_power);
				current = current->_next;
			} while (current != other._head);
		}
	}

	SingleLinkedList(int size, const T min_value,const T max_value) : _head(nullptr) {
		if (size < 0) {
			throw out_of_range("Size can't be < 0.");
		}
		for (int i = 0; i < size; ++i) {
			T value = (T)(min_value + (double)(rand()) / RAND_MAX * (max_value - min_value + 1));
			if (value == 0) {
				value += (T)(1);
			}
			push_tail(value, i);
		}
		_size = size;
	}

	~SingleLinkedList() {
		while (_head) {
			pop_head();
		}
	}

	int get_size() const {
		return _size;
	}

	SingleLinkedList<T> operator=(const SingleLinkedList<T> other) {
		if (other._head) {
			Node<T>* othercurrent = other._head;
			do {
				push_tail(othercurrent->_cofficient);
				othercurrent = othercurrent->_next;
			} while (othercurrent != other._head);
		}
		return *this;
	}

	void push_tail(T value, int power) {
		if (value == 0) {
			return;
		}
		Node<T>* element = new Node<T>(value, power);
		if (_head == nullptr) {
			_head = element;
			_head->_next = _head;
		}
		else {
			Node<T>* current = _head;
			while (current->_next != _head) {
				if (current->_power == power) {
					current->_data += value;
					if (current->_data == 0) {
						delete_node(0);
					}
					return;
				}
				current = current->_next;
			}
			if (current->_power == power) {
				current->_data += value;
				if (current->_data == 0) {
					delete_node(0);
				}
				return;
			}
			current->_next = element;
			element->_next = _head;
		}
		_size++;
	}

	void push_tail(SingleLinkedList<T> other) {
		if (other._head == nullptr) {
			return;
		}
		else {
			Node<T>* current = other._head;
			do {
				push_tail(current->_data, current->_power);
				current = current->_next;
			} while (current != other._head);
		}
	}

	void push_head(T value, int power) {
		if (value == 0) {
			return;
		}
		Node<T>* element = new Node<T>(value, power);
		if (_head == nullptr) {
			_head = element;
			_head->_next = _head;
			_size++;
			return;
		}
		Node<T>* current = _head;
		while (current->_next != _head) {
			if (current->_power == power) {
				current->_data += value;
				if (current->_data == 0) {
					delete_node(0);
				}
				return;
			}
			current = current->_next;
		}
		if (current->_power == power) {
			current->_data += value;
			if (current->_data == 0) {
				delete_node(0);
			}
			return;
		}
		element->_next = _head;
		current->_next = element;
		_head = element;
		_size++;
	}

	void push_head(SingleLinkedList<T>& other) {
		SingleLinkedList<T>& temp(other);
		while (temp._head) {
			Node<T>* current = temp._head;
			while (current->_next != temp._head) {
				current = current->_next;
			}
			push_head(current->_data, current->_power);
			temp.pop_tail();
			current->_next;
			if (current == temp._head) {
				push_head(current->_data, current->_power);
				temp.pop_tail();
			}
		}
	}

	void pop_head() {
		if (_size == 0) {
			cout << "List is empty." << endl;
			return;
		}
		if (_head && _head->_next == _head) {
			delete _head;
			_head = nullptr;
		}
		else {
			Node<T>* temp = _head;
			Node<T>* current = _head;
			while (current->_next != _head) {
				current = current->_next;
			}
			_head = _head->_next;
			current->_next = _head;
			delete temp;
		}
		_size--;
	}

	void pop_tail() {
		if (_size == 0) {
			cout << "List is empty." << endl;
			return;
		}
		Node<T>* current = _head;
		Node<T>* penultimate = nullptr;
		while (current->_next != _head) {
			penultimate = current;
			current = current->_next;
		}
		if (penultimate) {
			penultimate->_next = _head;
		}
		else {
			_head = nullptr;
		}
		delete current;
		_size--;

	}

	void delete_node(T val) {
		if (get_size() == 0) {
			return;
		}
		if (_head != nullptr) {
			Node<T>* current = _head;
			while (current->_next != _head) {
				if (val == current->_next->_data) {
					Node<T>* temp = current->_next;
					current->_next = current->_next->_next;
					delete temp;
					_size--;
				}
				else current = current->_next;
			}
		}
		if (_head && _head->_data == val) {
			pop_head();
		}
	}

	void delete_node(const Node<T>& node) {
		if (get_size() == 0) {
			return;
		}
		if (_head != nullptr) {
			Node<T>* current = _head;
			while (current->_next != _head) {
				if (node._data == current->_next->_data) {
					Node<T>* temp = current->_next;
					current->_next = current->_next->_next;
					delete temp;
					_size--;
				}
				else current = current->_next;
			}
		}
		if (_head && _head->_data == node._data) {
			pop_head();
		}
	}

	T operator[](const int index) const {
		if (index < 0 || index >= get_size()) {
			throw out_of_range("[operator[]]: Index out of range.");
		}
		if (get_size() == 0) {
			throw runtime_error("[operator[]]: List is empty.");
		}
		int counter = 0;
		Node<T>* current = _head;
		while (current) {
			if (counter == index) {
				return current->_data;
			}
			current = current->_next;
			counter++;
		}
	}


	T& operator[](const int index) {
		if (index < 0 || index >= get_size()) {
			throw runtime_error("[operator[]]: Index out of range.");
		}
		if (get_size() == 0) {
			throw runtime_error("[operator[]]: List is empty.");
		}
		int counter = 0;
		Node<T>* current = _head;
		while (current) {
			if (counter == index) {
				return current->_data;
			}
			current = current->_next;
			counter++;
		}
	}

	int get_power(int index) {
		if (index < 0 || index >= get_size()) {
			throw runtime_error("[operator[]]: Index out of range.");
		}
		if (get_size() == 0) {
			throw runtime_error("[operator[]]: List is empty.");
		}
		int counter = 0;
		Node<T>* current = _head;
		while (current) {
			if (counter == index) {
				return current->_power;
			}
			current = current->_next;
			counter++;
		}
	}

	void print() {
		if (_head == nullptr) {
			std::cout << "List is empty." << endl;
			return;
		}
		Node<T>* current = _head;
		if (current->_next == _head) {
			std::cout << current->_data << endl;
			return;
		}
		while (current->_next != _head) {
			std::cout << current->_data << ", ";
			current = current->_next;
		}
		std::cout << current->_data << endl;
	}


	friend std::ostream& operator<<(std::ostream& stream, SingleLinkedList<T>& lhs) {
		SingleLinkedList<T> temp(lhs);
		if (temp.get_size() == 0) {
			stream << "List is empty." << endl;
			return stream;
		}
		stream << "Polynomial: ";
		int size = temp.get_size() - 1;
		for (int i = size; i >= 0; --i) {
			if (i < size) {
				if (temp[i] >= T(0)) stream << " +";
				if (temp[i] < T(0)) stream << " ";
			}
			if (i > 0) stream << temp[i] << "*x^" << temp.get_power(i);
			else stream << temp[i] << "*x^" << temp.get_power(i);
		}
		return stream;
	}
};

template<typename T>
T calculate_value(SingleLinkedList<T>& list, const T x) {
	T value = 0;
	if (list.get_size() == 0) {
		return value;
	}
	for (int i = 0; i < list.get_size(); ++i) {
		value += list[i] * pow(x, list.get_power(i));
	}
	return value;
}