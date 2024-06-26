#pragma warning(disable : 4996 )

#include "imgui.h"
#include "imgui-SFML.h"
#include "../includes/gui.h"

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

std::string newEntry(std::string& filename, std::string& title, std::string& description)
{
    std::string formatedOutput;

    formatedOutput = "<a href=\"" + filename + "\">\n				\
						\t<li class = \"bgHover\"><u>" + title + "</u>\n";
    if (!description.empty())
        formatedOutput += "\t<br><span><em>" + description + "</em></span>\n";
    formatedOutput += "</li>\n</a>";
    //</a>";
    return formatedOutput;
}

int main()
{
    Gui app;  
    time_t now;
 
    sf::Color background = {0,0,8};
    sf::Color text_color = { 231,236,239,100 }; 

    sf::RenderWindow window(sf::VideoMode(800, 800), "Oblivion");
    ImGui::SFML::Init(window);

    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("./bin/graphic/chihiro-studio-ghibli.jpg"))
    {
        std::cerr << "Failed to load image";
    }
    else { 
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setPosition(0,120);
    }

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
        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 100.f);
        ImGui::Separator();
        app.DisplayActions();
        
        ImGui::End();
    
        window.clear(background);
        window.draw(date_text);
        window.draw(stats_text);
        window.draw(backgroundSprite);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();

    return 0;
}