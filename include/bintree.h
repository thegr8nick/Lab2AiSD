#pragma once
#include <iostream>
#include <set>

using namespace std;

int tabs = 0;

template <typename T>
struct Node {
	T data;
	Node* left;
	Node* right;
	Node(T value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinTree {
private:
	Node<T>* _root;
public:
	BinTree() {
		_root = nullptr;
	}

	BinTree(T value) {
		_root = new Node<T>(value);
	}

	BinTree(const BinTree& other) {
		_root(copyTree(other._root));
	}

	~BinTree() {
		deleteTree(_root);
	}

	BinTree& operator=(const BinTree& other) {
		if (this != &other) {
			deleteTree(_root);
			_root = copyTree(other._root);
		}
		return *this;
	}

	void print()
	{
		printTree(_root);
	}

	void insert(T value) {
		if (!_root) {
			_root = new Node<T>(value);
		}
		else {
			Node<T>* current = _root;
			while ((current) && (current->data != value)) {
				if ((current->data > value) && (current->left == nullptr)) {
					current->left = new Node<T>(value);
					return;
				}
				if ((current->data < value) && (current->right == nullptr)) {
					current->right = new Node<T>(value);
					return;
				}
				if (current->data > value) {
					current = current->left;
				}
				else {
					current = current->right;
				}
			}
		}
	}

	bool contains(T value) {
		Node<T>* current = _root;
		while (current && current->data != value)
		{
			if (current->data > value) {
				current = current->left;
			}
			else {
				current = current->right;
			}
		}
		return current != nullptr;
	}

	void erase(T value) {
		_root = eraseNode(_root, value);
	}

	void deleteTree(Node<T>* current) {
		if (current) {
			deleteTree(current->left);
			deleteTree(current->right);
			delete current;
		}
	}

	void printTree(Node<T>* current)
	{
		if (current)
		{
			tabs += 5;
			printTree(current->right);
			for (int i = 0; i < tabs; i++) {
				cout << " ";
			}
			cout << current->data << endl;
			printTree(current->left);
			tabs -= 5;
			return;
		}
	}

	Node<T>* copyTree(Node<T>* other) {
		if (other) {
			Node<T>* current = new Node<T>(other->data);
			current->left = copyTree(other->left);
			current->right = copyTree(other->right);
		}
		else {
			return nullptr;
		}
	}

	Node<T>* eraseNode(Node<T>* current, T key) {
		if (current == nullptr) {
			return current;
		}
		if (key < current->data) {
			current->left = eraseNode(current->left, key);
		}
		else if (key > current->data) {
			current->right = eraseNode(current->right, key);
		}
		else {
			if (current->left == nullptr) {
				Node<T>* temp = current->right;
				delete current;
				return temp;
			}
			else if (current->right == nullptr) {
				Node<T>* temp = current->left;
				delete current;
				return temp;
			}
			Node<T>* temp = findMin(current->right);
			current->data = temp->data;
			current->right = eraseNode(current->right, temp->data);
		}
		return current;
	}

	Node<T>* findMin(Node<T>* current) {
		while (current->left != nullptr) {
			current = current->left;
		}
		return current;
	}

	Node<T>* getRoot() const {
		return _root;
	}
};

template <typename T>
set<T> intersection(Node<T>* current, BinTree<T>& other, set<T>& elements) {
	if (current) {
		if (other.contains(current->data)) {
			elements.insert(current->data);
		}
		intersection(current->left, other, elements);
		intersection(current->right, other, elements);
	}
	return elements;
}

template <typename T>
set<T> difference(Node<T>* current, BinTree<T>& other, set<T>& elements) {
	if (current) {
		if (!(other.contains(current->data))) {
			elements.insert(current->data);
		}
		difference(current->left, other, elements);
		difference(current->right, other, elements);
	}
	return elements;
}

template <typename T>
void intersectionTrees(BinTree<T>& first, BinTree<T>& second) {
	set<T> elements;
	intersection(first.getRoot(), second, elements);
	cout << "Intersection: ";
	for (int i : elements) {
		cout << i << " ";
	}
}

template <typename T>
void differenceTrees(BinTree<T>& first, BinTree<T>& second) {
	set<T> elements;
	difference(first.getRoot(), second, elements);
	cout << "Difference: ";
	for (int i : elements) {
		cout << i << " ";
	}
}