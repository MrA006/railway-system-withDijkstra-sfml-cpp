#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;


struct TrieNode {
    TrieNode* children[26];
    bool endOfWord;

    TrieNode() {
        for (int i = 0; i < 26; i++)
            children[i] = NULL;
        endOfWord = false;
    }

};


void insert(TrieNode* root, string key) {

    TrieNode* cur = root;

    for (int i = 0; i < key.length(); i++) {
        char temp = key[i];
        if (cur->children[temp - 'a'] == NULL) {
            cur->children[temp - 'a'] = new TrieNode();

        }
        cur = cur->children[temp - 'a'];
    }
    
    cur->endOfWord = true;
}


void printAll(TrieNode* root, string a) {

    if (root->endOfWord) cout << a << endl;

    for (int i = 0; i < 26; i++) {

        if (root->children[i] != NULL) {
            char te = i + 'a';
            printAll(root->children[i], a + te);
        }
    }

}

bool isEmpty(TrieNode* node) {
    for (int i = 0; i < 26; ++i) {
        if (node->children[i] != NULL) {
            return false;
        }
    }
    return true;
}


TrieNode* deleteString(TrieNode* root, const string& key, int depth = 0) {
    if (root == nullptr) {
        return nullptr;
    }

    if (depth == key.length()) {
        root->endOfWord = false;

        if (isEmpty(root)) {
            delete root;
            root = nullptr;
        }
        return root;
    }

    int index = key[depth] - 'a';
    root->children[index] = deleteString(root->children[index], key, depth + 1);

    if (isEmpty(root) && root->endOfWord == false) {
        delete root;
        root = nullptr;
    }

    return root;
}
