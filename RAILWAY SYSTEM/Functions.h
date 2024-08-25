#pragma once

#include "map.h"


void setlabel(sf::Text& text, sf::Vector2f a,string info , sf::Font& font, int charsize = 25) {

    text.setCharacterSize(charsize);
    text.setFillColor(sf::Color::White);
    text.setPosition(a);
    text.setFont(font);
    text.setString(info);
}

sf::Vector2f dragNdrop(sf::RenderWindow& w, sf::Sprite& s) {
    sf::RectangleShape rec(sf::Vector2f(20, 30));
    rec.setFillColor(sf::Color::White);

    while (w.isOpen()) {
        sf::Event e;

        while (w.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                w.close();
            }

            if (e.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(w);
                rec.setPosition(static_cast<sf::Vector2f>(mousePos));
            }

            if (e.type == sf::Event::MouseButtonPressed) {
                if (e.mouseButton.button == sf::Mouse::Left) {
                    return rec.getPosition();
                }
                if (e.mouseButton.button == sf::Mouse::Right) {
                    return sf::Vector2f(0, 0);
                }
            }
        }

        w.clear();
        w.draw(s);
        w.draw(rec);
        w.display();
    }

    return sf::Vector2f(0, 0);
}


string Inputfunc(sf::RenderWindow& window, TrieNode* r = NULL, string a = "") {
	Bar bar(sf::Vector2f(100,100));
    string data;
    sf::Text enter;
    sf::Text back;
    sf::Text head;
    Suggestions s;
    sf::Vector2f bar_pos = bar.getBarPosition();

    sf::Font font;

    if (!font.loadFromFile("ModernWarfare-OV7KP.ttf")) {
        cout << "Failed to load font" << endl;
    }

    setlabel(enter, sf::Vector2f(100,250),"Enter", font);
    setlabel(back, sf::Vector2f(600, 250), "Back", font);
    if(!a.empty())
        setlabel(head, sf::Vector2f(250, 50),a, font);

	while (window.isOpen()) {
		sf::Event event;
        
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !data.empty()) {
                    // Handle backspace
                    data.pop_back();
                }
                else if (event.text.unicode >= 97 && event.text.unicode <= 122) {
                    // Handle regular input
                    data += static_cast<char>(event.text.unicode);
                }
                bar.text.setString(data);
                window.clear();
                if (r != NULL && data.size() != 0) {
                    s.Search_using_partial_string(r, data, window);
                    s.setRectangles(bar_pos.x, bar_pos.y + 40, 500, 20, s.words.size());
                }
                
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (enter.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    enter.setFillColor(sf::Color::Red);
                }
                else
                {
                    enter.setFillColor(sf::Color::White);

                }
                if (back.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    back.setFillColor(sf::Color::Red);
                }
                else
                {
                    back.setFillColor(sf::Color::White);

                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (enter.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    return data;
                }

                if (back.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    return "";
                }


                if (r != NULL && data.size() != 0) {
                    sf::Vector2i t = sf::Mouse::getPosition(window);
                    sf::Vector2f sa;sa.x = t.x; sa.y = t.y;
                    string a = s.checkclickedstring(sa);
                    if (!a.empty()) {
                        data = a;
                    }
                }


            }
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        return data;
                    }
                }

		}

            
        window.clear();
        window.draw(head);
        window.draw(enter);
        window.draw(back);
        bar.DrawBar(window);
        if (r != NULL && data.size() != 0) {
            s.drawSuggestion(window, bar_pos.x ,bar_pos.y + 40);
        }
        window.display();
	}

}



string addstopfunc(sf::RenderWindow& window, TrieNode* r, string a) {
    Bar bar(sf::Vector2f(100, 100));
    string data;
    sf::Text enter;
    sf::Text back;
    sf::Text head;
    Suggestions s;



    sf::Font font;

    if (!font.loadFromFile("ModernWarfare-OV7KP.ttf")) {
        cout << "Failed to load font" << endl;
    }

    setlabel(enter, sf::Vector2f(100, 250), "Enter", font);
    setlabel(back, sf::Vector2f(600, 250), "Back", font);
    setlabel(head, sf::Vector2f(200, 150), a, font);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !data.empty()) {
                    data.pop_back();
                }
                else if (event.text.unicode < 128) {
                    data += static_cast<char>(event.text.unicode);
                }
                bar.text.setString(data);
                window.clear();
                if (r != NULL && data.size() != 0) {
                    s.Search_using_partial_string(r, data, window);
                }

            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (enter.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    enter.setFillColor(sf::Color::Red);
                }
                else
                {
                    enter.setFillColor(sf::Color::White);

                }
                if (back.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    back.setFillColor(sf::Color::Red);
                }
                else
                {
                    back.setFillColor(sf::Color::White);

                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (enter.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    return data;
                }

                if (back.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    return data;
                }
            }

        }

        window.clear();
        window.draw(enter);
        window.draw(back);
        bar.DrawBar(window);
        if (data.size() != 0) {
            s.drawSuggestion(window, 150);
        }
        window.display();
    }

}



vector<stationDATA*> findlinks(sf::RenderWindow& w, sf::Sprite& s, Suggestions& sugg,DATA& d) {

    vector<stationDATA*> linkname;
    sugg.setRectangles(20, 70, 500, 20, sugg.words.size());

    while (w.isOpen()) {
        sf::Event e;

        while (w.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                w.close();
            }

            if (e.type == sf::Event::MouseButtonPressed) {
                if (e.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(w));
                    sugg.checkclickedrec(mouse_pos);
                }
            }

            if (e.type == sf::Event::KeyPressed) {
                if(e.key.code == sf::Keyboard::Enter){
                linkname = sugg.getpressedrec(d);
                return linkname;
                }
            }
        }

        w.clear();
        w.draw(s);
        sugg.drawSuggestion(w, 20);
        w.display();
    }

    return vector<stationDATA*>();
}


void DefaultSettings(TrieNode* r, DATA& d, graph& g) {
    //insert(r, "anas");
    //insert(r, "khan");
    //insert(r, "ali");
    //insert(r, "feroz");


    //stationDATA* temp1 = new stationDATA("anas", sf::Vector2f(70, 70));// links 3
    //stationDATA* temp2 = new stationDATA("khan", sf::Vector2f(140, 140));// links 2
    //stationDATA* temp3 = new stationDATA("ali", sf::Vector2f(70, 20));
    //stationDATA* temp4 = new stationDATA("feroz", sf::Vector2f(100,200));

    //temp1->addlink(temp2);
    //temp2->addlink(temp1);

    //temp1->addlink(temp3);
    //temp3->addlink(temp1);

    //temp4->addlink(temp1);
    //temp1->addlink(temp4);

    //temp4->addlink(temp2);
    //temp2->addlink(temp4);

    //d.add(*temp1, "anas");
    //d.add(*temp2, "khan");
    //d.add(*temp3, "ali");
    //d.add(*temp4, "feroz");
    //

    //g.defaultset(*temp1);
    //g.defaultset(*temp2);
    //g.defaultset(*temp3);
    //g.defaultset(*temp4);

    insert(r, "maplewood");
    insert(r, "riverside");
    insert(r, "westend");
    insert(r, "oceanfront");
    insert(r, "pinecrest");
    insert(r, "hillcrest");
    insert(r, "park");
    insert(r, "elm");
    insert(r, "cent");
    insert(r, "hbr");
    insert(r, "hlcrst");
    insert(r, "sntst");
    insert(r, "view");
    insert(r, "end");
    insert(r, "valley");
    insert(r, "profanas");
    insert(r, "profayan");
    insert(r, "profammar");


    stationDATA* maplewood = new stationDATA("maplewood", sf::Vector2f(70, 70));// links 3
    stationDATA* riverside = new stationDATA("riverside", sf::Vector2f(140, 140));// links 2
    stationDATA* westend = new stationDATA("westend", sf::Vector2f(70, 20));
    stationDATA* oceanfront = new stationDATA("oceanfront", sf::Vector2f(100, 200));
    stationDATA* pinecrest = new stationDATA("pinecrest", sf::Vector2f(300, 300));
    stationDATA* hillcrest = new stationDATA("hillcrest", sf::Vector2f(400, 330));
    stationDATA* park = new stationDATA("park", sf::Vector2f(350, 430));
    stationDATA* elm = new stationDATA("elm", sf::Vector2f(200, 400));
    stationDATA* cent = new stationDATA("cent", sf::Vector2f(350, 600));
    stationDATA* hlcrst = new stationDATA("hlcrst", sf::Vector2f(600, 550));
    stationDATA* sntst = new stationDATA("sntst", sf::Vector2f(500, 720));
    stationDATA* view = new stationDATA("view", sf::Vector2f(750, 850));
    stationDATA* end = new stationDATA("end", sf::Vector2f(400, 800));
    stationDATA* valley = new stationDATA("valley", sf::Vector2f(450, 850));
    stationDATA* hbr = new stationDATA("hbr", sf::Vector2f(1000, 350));
    stationDATA* profammar = new stationDATA("profammar", sf::Vector2f(950, 550));
    stationDATA* profayan = new stationDATA("profayan", sf::Vector2f(1150, 350));
    stationDATA* profanas = new stationDATA("profanas", sf::Vector2f(850, 300));

    maplewood->addlink(riverside);
    riverside->addlink(maplewood);

    maplewood->addlink(westend);
    westend->addlink(maplewood);

    oceanfront->addlink(maplewood);
    maplewood->addlink(oceanfront);

    oceanfront->addlink(riverside);
    riverside->addlink(oceanfront);

    pinecrest->addlink(riverside);
    riverside->addlink(pinecrest);

    hillcrest->addlink(pinecrest);
    pinecrest->addlink(hillcrest);

    park->addlink(hillcrest);
    hillcrest->addlink(park);

    park->addlink(elm);
    elm->addlink(park);

    pinecrest->addlink(elm);
    elm->addlink(pinecrest);

    cent->addlink(elm);
    elm->addlink(cent);

    cent->addlink(hlcrst);
    hlcrst->addlink(cent);

    hlcrst->addlink(hillcrest);
    hillcrest->addlink(hlcrst);

    hlcrst->addlink(park);
    park->addlink(hlcrst);

    sntst->addlink(cent);
    cent->addlink(sntst);

    sntst->addlink(end);
    end->addlink(sntst);

    sntst->addlink(view);
    view->addlink(sntst);

    end->addlink(valley);
    valley->addlink(end);
    
    profammar->addlink(hbr);
    hbr->addlink(profammar);

    profammar->addlink(view);
    view->addlink(profammar);

    profanas->addlink(hbr);
    hbr->addlink(profanas);

    profayan->addlink(hbr);
    hbr->addlink(profayan);

    d.add(*maplewood, "maplewood");
    d.add(*riverside, "riverside");
    d.add(*westend, "westend");
    d.add(*oceanfront, "oceanfront");
    d.add(*pinecrest, "pinecrest");
    d.add(*hillcrest, "hillcrest");
    d.add(*park, "park");
    d.add(*elm, "elm");
    d.add(*cent, "cent");
    d.add(*hbr, "hbr");
    d.add(*hlcrst, "hlcrst");
    d.add(*sntst, "sntst");
    d.add(*view, "view");
    d.add(*end, "end");
    d.add(*valley, "valley");
    d.add(*profammar, "profammar");
    d.add(*profayan, "profayan");
    d.add(*profanas, "profanas");


    g.defaultset(*maplewood);
    g.defaultset(*riverside);
    g.defaultset(*westend);
    g.defaultset(*oceanfront);
    g.defaultset(*pinecrest);
    g.defaultset(*hillcrest);
    g.defaultset(*park);
    g.defaultset(*elm);
    g.defaultset(*cent);
    g.defaultset(*hbr);
    g.defaultset(*hlcrst);
    g.defaultset(*sntst);
    g.defaultset(*view);
    g.defaultset(*end);
    g.defaultset(*valley);
    g.defaultset(*profammar);
    g.defaultset(*profayan);
    g.defaultset(*profanas);
}
