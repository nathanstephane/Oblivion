#pragma warning(disable : 4996 )

#include "imgui.h"
#include "imgui-SFML.h"
#include "Gui.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <ctime>

void timer(time_t &time_now, sf::Text &text_)
{
    time_now = time(0);
    char* date = ctime(&time_now);
    std::string strDate = date;

  
    text_.setString(strDate);
      
}

int main()
{

    Gui app;
    
    
    time_t now;
    //= time(0);
    //char* date = ctime(&now);
    sf::Color background = {0,0,8};
    sf::Color text_color = { 231,236,239,100 };
    //std::string strDate = date;
    std::cout << "Program started\n";

    sf::RenderWindow window(sf::VideoMode(800, 800), "Oblivion");
    ImGui::SFML::Init(window);

    

    sf::Font font;
    if (!font.loadFromFile("./bin/fonts/LINESeedJP_A_TTF_Rg.ttf"))
    {
        std::cout << "Font not loaded!";
    }
    
    sf::Text date_text;
    date_text.setFont(font);
    date_text.setFillColor(text_color);
    date_text.setCharacterSize(16);
    timer(now,date_text);

    app.metrics();
    std::string pages = std::to_string(app.get_overallcount());
    std::string project_pages = std::to_string(app.get_projectsCount());
    std::string thoughts_pages = std::to_string(app.get_thoughtsCount());
    std::string wikilog_pages = std::to_string(app.get_wikilogCount());
    //std::cout << app.get_overallcount() << "\n";


    sf::Text stats_text;
    stats_text.setFont(font);
    stats_text.setFillColor(text_color);
    stats_text.setCharacterSize(16);
    stats_text.setPosition(0,date_text.getLocalBounds().height);
    stats_text.setString("\tMetrics \nOverall pages: " + pages + "\t\tProjects: "+project_pages 
                        +"\nThoughts:   \t"+thoughts_pages+"\t\tWikilogs: "+wikilog_pages);
    




    sf::Clock deltaClock;
    while (window.isOpen())
    {
        timer(now, date_text);
       /* now = time(0);
        char* date = ctime(&now);
        std::string strDate = date;
        text.setString("Date: " + strDate);*/
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("engine window");

        app.DisplayMenu();
        ImGui::Separator();
        app.DisplayContent();
        
        ImGui::End();

        window.clear(background);
        window.draw(date_text);
        window.draw(stats_text);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}