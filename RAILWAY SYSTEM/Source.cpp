#include <iostream>
#include <unordered_map>
#include <queue>
#include <SFML/Graphics.hpp>
#include "Suggestions.h"
#include "SideMenu.h"
#include "Functions.h"
#include "stations.h"
#include "map.h"
#include "Travel.h"

using namespace std;
 

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!");
    Bar bar(sf::Vector2f(150,10));
    string data;
    Suggestions suggestions;
    sf::Font font;
    sf::Texture map_texture;
    graph GRAPH;


    if (!map_texture.loadFromFile("map.jpg")) {
        cout << " MAP NOT LOADED " << endl;
    }

    if (!font.loadFromFile("ModernWarfare-OV7KP.ttf")) {
        cout << " FONT NOT LOADED " << endl;
    }
    Travel travel;
    sf::Sprite map;

    map.setPosition(0, 0);

    bool isDragging = false;
    sf::Vector2f lastMousePos;

    map.setTexture(map_texture);
    // Get window size
    sf::Vector2u windowSize = window.getSize();

    // Set the sprite's scale to cover the window
    map.setScale(static_cast<float>(windowSize.x * 2) / map.getLocalBounds().width,
        static_cast<float>(windowSize.y * 2) / map.getLocalBounds().height);

    sidemenu menu(font);

    DATA d;
    TrieNode* r = new TrieNode();
    DefaultSettings(r,d,GRAPH);

    int curr_menu = 1;
    

    while (window.isOpen())
    {
        

        bool flag = 0;
        sf::Event event; 
        while (window.pollEvent(event))
        {
            

            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;


            case sf::Event::MouseButtonPressed:{
                    int a = menu.Check_cursor_click(window, curr_menu);
                    
                    if (a == labels::addstation) {

                        string name = Inputfunc(window);

                        bool check_dup = GRAPH.doesExist(name);

                        if (!name.empty() && check_dup) {

                        sf::Vector2f pos = dragNdrop(window, map);

                        suggestions.clear();
                        //save all suggestions to words
                        suggestions.printAll(r, "", window); 

                        //display and connecting links
                        vector<stationDATA*> links = findlinks(window, map, suggestions, d);
                        struct stationDATA temp(name, pos, links);
                        insert(r, name);
                        d.add(temp, name);
                        GRAPH.addstation(temp);

                        }
                        else {
                            /*sf::Font font;
                            if (!font.loadFromFile("C:\Winter Night.ttf")) {
                                cout << "Failed to load font!" << endl;
                                return EXIT_FAILURE;
                            }*/
                            cout << "INVALID NAME. Station already exists or no string enter" << endl;
                            /*sf::Text errorMessage = createErrorMessage("INVALID NAME. Station already exists or no string entered", font);
                            window.draw(errorMessage);
                            cin.get();*/
                        }
                     

                    } else if (a == labels::removestation) {
                        string name = Inputfunc(window);

                        if (!name.empty()) {

                            GRAPH.removestation(name);
                            d.deletestation(name);
                        
                            deleteString(r, name);
                            //flag = 1; //FIX HERE
                            //break;
                        }
                    }
                    else if (a == labels::travel) {
                        curr_menu = 0;
                    }
                    else if (a == labels::addstop) {
                        if(travel.addstop(window, r, GRAPH))
                            travel.printroute(GRAPH, window, font, 350 ,false);
                    }
                    else if (a == labels::removestop) {
                        string a = Inputfunc(window, r, "Enter Name To Remove stop");
                        travel.removestop(a,GRAPH);
                    }
                    else if (a == labels::journey) {
                        travel.routeScreen(GRAPH, font, window);
                    }
                    else if (a == labels::back) {
                        if (curr_menu == 0) {
                            curr_menu = 1;
                            travel.clear();

                        }
                        else {
                            window.close();
                        }
                    }
                    else if (event.mouseButton.button == sf::Mouse::Left) {
                        // if mouse button is pressed drag is on 
                        isDragging = true;
                        lastMousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

                    }


                    break;
                }
                case sf::Event::MouseButtonReleased:
                    // is mouse button is released no longer drag 
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        isDragging = false;
                    }
                    break;
                case sf::Event::MouseMoved:

                    //drag if mouse is pressed and moving
                    if (isDragging) {
                        sf::Vector2f currentMousePos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                        sf::Vector2f delta = currentMousePos - lastMousePos;

                        map.move(delta);
                        lastMousePos = currentMousePos;
                    }
                    break;


            }



        }

        
        window.clear();

        window.draw(map);
        
        d.drawstationicons(map.getPosition(), window, font);

        //if (!flag) {
            if (!curr_menu && !travel.route.empty()) {
                vector<int> path = travel.route.back().second;
                for (int i = 0; i < path.size() - 1; i++) {
                    string start = travel.getKeyByValue(GRAPH.nameofindex, path[i]);
                    string end = travel.getKeyByValue(GRAPH.nameofindex, path[i + 1]);

                    stationDATA ts = d.getstation(start);
                    stationDATA te = d.getstation(end);

                    drawArrow(window, ts.relative_position + map.getPosition(),
                        te.relative_position + map.getPosition());

                }
            }

            menu.Check_cursor(window);
            menu.draw_Menu(window, curr_menu);
            if (curr_menu == 0) {
                travel.printroute(GRAPH, window, font, 350, false, true);
                travel.printroute(GRAPH, window, font);
            }
        //}

        window.display();
    }

    return 0;
}