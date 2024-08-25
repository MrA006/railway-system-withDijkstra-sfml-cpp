#pragma once
#include "stations.h"

void drawLine(sf::RenderWindow& window, const sf::Vector2f& from, const sf::Vector2f& to) {
	sf::Vector2f direction = to - from;

	float angle = atan2(direction.y, direction.x);

	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

	sf::RectangleShape road(sf::Vector2f(length, 2));
	road.setFillColor(sf::Color::Blue);
	road.setPosition(from);
	road.setRotation(angle * (180 / 3.14159265f)); 

	window.draw(road);

}

void drawArrow(sf::RenderWindow& window, const sf::Vector2f& from, const sf::Vector2f& to) {
	sf::Vector2f direction = to - from;

	float angle = atan2(direction.y, direction.x);

	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

	sf::RectangleShape line(sf::Vector2f(length, 5));
	line.setFillColor(sf::Color::Red);
	line.setPosition(from);
	line.setRotation(angle * (180.0f / static_cast<float>(3.14159265f)));

	window.draw(line);

	sf::ConvexShape arrowhead(3);
	arrowhead.setPoint(0, sf::Vector2f(-3, -3 * 3));
	arrowhead.setPoint(1, sf::Vector2f(0.0f, 0.0f));
	arrowhead.setPoint(2, sf::Vector2f(3, -3 * 3));
	arrowhead.setFillColor(sf::Color::Red);

	arrowhead.setPosition(to);
	arrowhead.setRotation(angle * (180.0f / static_cast<float>(3.14159265f)));

	window.draw(arrowhead);
}



string generateKey(int length) {
	static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	const int charsetSize = sizeof(charset) - 1;

	string key;
	for (int i = 0; i < length; ++i) {
		key += charset[rand() % charsetSize];
	}

	return key;
}

class DATA {
public:
	map<string, stationDATA> stations;

	DATA() {}

	void add(stationDATA s, string a) {
		stations.insert(make_pair(a,s));
	}

	stationDATA getstation(string a) {
		return stations[a];
	}

	void removelinks(vector<stationDATA*>& vec, stationDATA& value) {
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i]->name == value.name) {
				swap(vec[i], vec[vec.size() - 1]);
				vec.pop_back();
				return;
			}
		}
	}

	void deletestation(const string& a) {
		if (stations.count(a) < 1) {
			return;
		}

		stationDATA& s = stations.at(a);

		//stations.applyOperationExcept(s);

		for (auto& station : stations) {
			if (&station.second != &s) {
				removelinks(station.second.links, s);
			}
		}

		stations.erase(a);
	}

	

	void drawstationicons(const sf::Vector2f& map_pos, sf::RenderWindow& window, sf::Font& font) {

		sf::RectangleShape icon(sf::Vector2f(20, 20));
		icon.setFillColor(sf::Color::Green);

		for (const auto& a : stations) {
			icon.setPosition(a.second.relative_position + map_pos);

			for (const auto& b : a.second.links) {
				drawLine(window, a.second.relative_position + map_pos, b->relative_position + map_pos);
			}

			window.draw(icon);

			sf::Text text(a.second.name, font, 12);
			text.setFillColor(sf::Color::Black);
			text.setPosition(a.second.relative_position + map_pos + sf::Vector2f(5, 5));

			window.draw(text);
		}
	}
};


template <typename K, typename V>
struct TreeNode {
	K key;
	V value;
	TreeNode* left;
	TreeNode* right;

	TreeNode(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

template <typename K, typename V>
class MyMap {
private:
	TreeNode<K, V>* root;

	TreeNode<K, V>* insert(TreeNode<K, V>* node, const K& key, const V& value) {
		if (node == nullptr) {
			return new TreeNode<K, V>(key, value);
		}

		if (key < node->key) {
			node->left = insert(node->left, key, value);
		}
		else if (key > node->key) {
			node->right = insert(node->right, key, value);
		}
		else {
			node->value = value;
		}

		return node;
	}

	TreeNode<K, V>* find(TreeNode<K, V>* node, const K& key) const {
		if (node == nullptr || node->key == key) {
			return node;
		}

		if (key < node->key) {
			return find(node->left, key);
		}
		else {
			return find(node->right, key);
		}
	}

	void inorder(TreeNode<K, V>* node) const {
		if (node != nullptr) {
			inorder(node->left);
			cout << node->key << ": " << node->value << endl;
			inorder(node->right);
		}
	}

	void clear(TreeNode<K, V>* node) {
		if (node != nullptr) {
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}

	

public:
	void applyOperationExcept(const V& s) {
		traverseAndApply(root, s);
	}


	size_t size() const {
		return size(root);
	}

	V& at(const K& key) const {
		TreeNode<K, V>* node = find(root, key);
		if (node != nullptr) {
			return node->value;
		}
		throw out_of_range("Key not found");
	}

	void erase(TreeNode<K, V>*& node, const K& key) {
		if (node == nullptr) {
			return;
		}

		if (key < node->key) {
			erase(node->left, key);
		}
		else if (key > node->key) {
			erase(node->right, key);
		}
		else {
			if (node->left == nullptr) {
				TreeNode<K, V>* temp = node->right;
				delete node;
				node = temp;
			}
			else if (node->right == nullptr) {
				TreeNode<K, V>* temp = node->left;
				delete node;
				node = temp;
			}
			else {
				TreeNode<K, V>* successor = findMin(node->right);
				node->key = successor->key;
				node->value = successor->value;
				erase(node->right, successor->key);
			}
		}
	}

	void erase(const K& key) {
		erase(root, key);
	}

	MyMap& operator=(const MyMap& other) {
		if (this != &other) {
			clear(root);
			root = copyTree(other.root);
		}
		return *this;
	}
	MyMap() : root(nullptr) {
		srand(static_cast<unsigned int>(time(nullptr)));
	}

	V& operator[](const K& key) {
		root = insert(root, key, V{});
		TreeNode<K, V>* node = find(root, key);
		return node->value;
	}


	void insert(const K& key, const V& value) {
		root = insert(root, key, value);
	}

	V& operator[](const K& key) const {
		TreeNode<K, V>* node = find(root, key);
		if (node != nullptr) {
			return node->value;
		}
		else {
			throw out_of_range("Key not found");
		}
	}

	bool get(const K& key, V& value) const {
		TreeNode<K, V>* node = find(root, key);
		if (node != nullptr) {
			value = node->value;
			return true;
		}
		return false;
	}

	void print() const {
		inorder(root);
	}

	bool searchByKey(const K& key) const {
		return find(root, key) != nullptr;
	}


	~MyMap() {
		clear(root);
	}
};

//
//class DATAT {
//public:
//
//	unordered_map<string, stationDATA> stations;
//	
//
//	DATAT() {
//
//	}
//
//	void add(stationDATA s, string a) {
//		stations[a] = s;
//
//	}
//
//	stationDATA getstation(string a) {
//		return stations[a];
//	}
//
//	void removelinks(vector<stationDATA*>& vec, stationDATA& value) {
//		for (int i = 0; i < vec.size(); i++) {
//			if (vec[i]->name == value.name) {
//				swap(vec[i], vec[vec.size() - 1]);
//				//cout << " hrere " << vec[vec.size() - 1]->name << endl;
//				vec.pop_back();
//				return;
//			}
//		}
//	}
//
//	void deletestation(const string& a) {
//
//		if (stations.count(a) < 1) {
//			return;
//		}
//
//		stationDATA& s = stations.at(a);
//
//		for (auto& station : stations) {
//			if (&station.second != &s) {
//				removelinks(station.second.links, s);
//			}
//		}
//		
//		stations.erase(a);
//	}
//
//	void print() {
//		for (const auto& a : stations) {
//			cout << a.first << endl;
//			
//		}
//		cout << "end " << endl;
//	}
//
//
//	void drawstationicons(const sf::Vector2f& map_pos, sf::RenderWindow& window, sf::Font& font) {
//
//		sf::RectangleShape icon(sf::Vector2f(20, 20));
//		icon.setFillColor(sf::Color::Green);
//
//		for (const auto& a : stations) {
//			icon.setPosition(a.second.relative_position + map_pos);
//
//			for (const auto& b : a.second.links) {
//				drawLine(window, a.second.relative_position + map_pos, b->relative_position + map_pos);
//			}
//
//			window.draw(icon);
//
//			sf::Text text(a.second.name, font, 12);
//			text.setFillColor(sf::Color::Black);
//			text.setPosition(a.second.relative_position + map_pos + sf::Vector2f(5, 5)); 
//
//			window.draw(text);
//		}
//	}
//
//
//};