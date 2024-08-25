#pragma once
#include "TreeNode.h"
#include "map.h"


class Suggestions {
public:

    sf::Text text;
    int pos_y;
    sf::Font font;
    vector<string> words;
    
    vector<sf::RectangleShape> rec;


    Suggestions():pos_y(0) {

        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Red);
        text.setFont(font);

        if (!font.loadFromFile("ModernWarfare-OV7KP.ttf")) {
            cout << "Failed to load font" << endl;
        }
    }

    void printAll(TrieNode* root, string a, sf::RenderWindow& window) {

        if (root->endOfWord) {
            words.push_back(a);
        }

        for (int i = 0; i < 26; i++) {

            if (root->children[i] != NULL) {
                char te = i + 'a';
                printAll(root->children[i], a + te, window);
            }
        }

    }

    void clear() {
        words.clear();
    }

    void Search_using_partial_string(TrieNode* root, string a, sf::RenderWindow& window) {

        words.clear();
        for (int i = 0; i < a.length(); i++) {

            if (root->children[a[i] - 'a'] != NULL && a[i] - 'a' <= 26) {
                root = root->children[a[i] - 'a'];
            }
            else {
                //cout << "WORD DOES NOT EXIST";
                return;
            }
        }

        printAll(root, a, window);
        
    }

    void checkclickedrec(sf::Vector2f& p) {
        for (size_t i = 0; i < rec.size(); ++i) {
            sf::FloatRect rectBounds = rec[i].getGlobalBounds();
            if (rectBounds.contains(p)) {
                if (rec[i].getFillColor() == sf::Color::Black) {
                    rec[i].setFillColor(sf::Color::Green);
                }
                else {
                    rec[i].setFillColor(sf::Color::Black);
                }
                    return ; 
            }
        }
        return ; 
    }

    string checkclickedstring(sf::Vector2f& p) {
        for (size_t i = 0; i < words.size(); ++i) {
            sf::FloatRect rectBounds = rec[i].getGlobalBounds();
            if (rectBounds.contains(p)) {
                if (rec[i].getFillColor() == sf::Color::Black) {
                    rec[i].setFillColor(sf::Color::Green);
                }
                else {
                    rec[i].setFillColor(sf::Color::Black);
                }
                return words[i]; 
            }
        }
        return ""; 
    }


    vector<stationDATA*> getpressedrec(DATA& d) {
        vector<stationDATA*> t;

        for (size_t i = 0; i < rec.size(); ++i) {
            if (rec[i].getFillColor() == sf::Color::Green) {
                stationDATA* temp = new stationDATA(d.getstation(words[i]));
                t.push_back(temp);
            }
        
        }
        return t;
    }

    void drawRectangles(int pos_x, int pos_y, int width, int height, int num) {

        for (int i = 0; i < num; i++) {
            rec.push_back(sf::RectangleShape(sf::Vector2f(width,height)));
            rec[i].setPosition(sf::Vector2f(pos_x, pos_y));
            rec[i].setFillColor(sf::Color::Black);
            rec[i].setOutlineColor(sf::Color::Red);
            rec[i].setOutlineThickness(1);
            pos_y += 20;
        }

    }


    void setRectangles(int pos_x, int pos_y, int width, int height, int num) {
        for (int i = 0; i < num; i++) {
            rec.push_back(sf::RectangleShape(sf::Vector2f(width, height)));
            rec[i].setPosition(sf::Vector2f(pos_x, pos_y));
            rec[i].setFillColor(sf::Color::Black);
            rec[i].setOutlineColor(sf::Color::Red);
            rec[i].setOutlineThickness(1);
            pos_y += 20;
        }
    }

    void drawSuggestion(sf::RenderWindow& window, int pos_x, int pos_y = 70) {
        //drawRectangles(pos_x, pos_y, 500, 20, words.size());
        for (int i = 0; i < words.size(); i++) {
            text.setString(words[i]);
            text.setPosition(sf::Vector2f(pos_x, pos_y));
            window.draw(rec[i]);
            window.draw(text);
            pos_y += 20;
        }

    }

};






class Bar {
public:
    sf::Text text;
    sf::Font font;
    sf::RectangleShape rec;

    Bar(sf::Vector2f a) {

        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Blue);
        text.setPosition(a);
        text.setFont(font);



        rec.setSize(sf::Vector2f(800, 35));
        rec.setOutlineThickness(5);
        rec.setOutlineColor(sf::Color::Red);
        rec.setPosition(sf::Vector2f(a.x,a.y + 15));

        if (!font.loadFromFile("Winter Night.ttf")) {
            cout << "Failed to load font" << endl;
        }
    }


    void DrawBar(sf::RenderWindow& window) {

        window.draw(rec);
        window.draw(text);

    }

    sf::Vector2f getBarPosition() {
        return rec.getPosition();
    }

};
