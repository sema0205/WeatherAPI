
#include <iostream>
#include <fstream>
#include <conio.h>
#include <chrono>
#include <unordered_map>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"

#include "View.h"

using namespace ftxui;

void View::RunProgramm() {

    system("cls");
    ReadConfig();
    controller->ChangeModel(0, 0);
    ShowScreen();

    while (true) {

        auto start = std::chrono::steady_clock::now();

        while (!_kbhit()) {

            // wait till button clicked and while doing it updates info with frequency
            if (int(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count()) == update_frequency) {
                system("cls");
                controller->ChangeModel(0, 0);
                ShowScreen();
            }

        }

        char button_clicked = _getch();

        switch (button_clicked) {
            case 'n':
                controller->ChangeModel(-1, 0);
                system("cls");
                ShowScreen();
                break;
            case 'p':
                controller->ChangeModel(1, 0);
                system("cls");
                ShowScreen();
                break;
            case '+':
                controller->ChangeModel(0, 1);
                system("cls");
                ShowScreen();
                break;
            case '-':
                controller->ChangeModel(0, -1);
                system("cls");
                ShowScreen();
                break;
            case 27:
                system("cls");
                return;
        }
    }
}

std::unordered_map<int, std::vector<std::string>> console_weather_images = {
        {0, {"Солнечно             ", "    \\   /   ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {1, {"В основном ясно      ", "             ",
                                "     .--.    ",
                                "  .-(    ).  ",
                                " (___.__)__) ",
                                "             "}},
        {2, {"Переменная облачность", "   \\  /     ",
                                " _ /\"\".-.    ",
                                "   \\_(   ).   ",
                                "   /(___(__)   ",
                                "            "}},
        {3, {"Пасмурная погода     ", "             ",
                                "     .--.      ",
                                "  .-(    ).    ",
                                " (___.__)__)   ",
                                "               "}},
        {45, {"Туман               ", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {48, {"Изморозь            ", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {51, {"Легкая морось", "     .-.     ",
                                "    (   ).   ",
                                "   (___(__)  ",
                                "    ‘ ‘ ‘ ‘  ",
                                "   ‘ ‘ ‘ ‘   "}},
        {53, {"Умеренная морось", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {55, {"Ливень", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {56, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {57, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {61, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {63, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {65, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {66, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {67, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {71, {"Слабый снегопад", " _`/\"\".-.    ",
                                "  ,\\_(   ).  ",
                                "   /(___(__)  ",
                                "     *  *  *  ",
                                "    *  *  *   "}},
        {73, {"Умеренный снегопад", " _`/\"\".-.    ",
                                "  ,\\_(   ).  ",
                                "   /(___(__)  ",
                                "    * * * *   ",
                                "   * * * *    "}},
        {75, {"Сильный снегопад", "     .-.     ",
                                "    (   ).   ",
                                "   (___(__)  ",
                                "   * * * *   ",
                                "  * * * *    "}},
        {77, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {80, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {81, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {82, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {85, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’     ",
                                "    /   \\    "}},
        {86, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {95, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {96, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {99, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
        {28, {"Солнечно", "    \\   /    ",
                                "     .-.      ",
                                "  ― (   ) ―  ",
                                "     `-’      ",
                                "    /   \\    "}},
};

std::vector<std::string> GetWeatherImage(int weather_code) {
    return console_weather_images[weather_code];
}

ftxui::Element View::GetVboxDayPart(const std::string& day_name, const std::string& day_code, int pos) {

    auto info = controller->GetModel()->GetCurrentCityInfo();

    auto vbox_element = vbox({
        text(day_name) | center,
        separator(),
        hbox({
          vbox({
              text(GetWeatherImage(info["days"][pos]["hours"][day_code]["weather_code"].get<int>())[1]),
              text(GetWeatherImage(info["days"][pos]["hours"][day_code]["weather_code"].get<int>())[2]),
              text(GetWeatherImage(info["days"][pos]["hours"][day_code]["weather_code"].get<int>())[3]),
              text(GetWeatherImage(info["days"][pos]["hours"][day_code]["weather_code"].get<int>())[4]),
              text(GetWeatherImage(info["days"][pos]["hours"][day_code]["weather_code"].get<int>())[5]),
          }),
          vbox({
              text(GetWeatherImage(info["days"][pos]["hours"][day_code]["weather_code"].get<int>())[0]),
              text(info["days"][pos]["hours"][day_code]["average_temp"].get<std::string>() + "(" + info["days"][pos]["hours"][day_code]["min_temp"].get<std::string>() + ") °C"),
              text(info["days"][pos]["hours"][day_code]["wind_direction"].get<std::string>() + " "
                      + info["days"][pos]["hours"][day_code]["min_wind_speed"].get<std::string>() + "-" +
                              info["days"][pos]["hours"][day_code]["wind_speed"].get<std::string>()),
              text(info["days"][pos]["hours"][day_code]["visibility"].get<std::string>()),
              text(info["days"][pos]["hours"][day_code]["rain_length"].get<std::string>() + " | " + info["days"][pos]["hours"][day_code]["rain_chance"].get<std::string>()),
          })
        }) | center,
    }) | flex;


    return vbox_element;
}

void View::ShowScreen() {

    auto info = controller->GetModel()->GetCurrentCityInfo();
    auto codes_name = controller->GetModel()->GetCodesDayParts();
    auto days_name = controller->GetModel()->GetOutputDayParts();

    std::cout << "Прогноз погоды: " << info["city"].get<std::string>() << "\n";
    ftxui::Element document;

    for (int i = 0; i < info["days"].size(); i++) {

        document = window(text(info["days"][i]["date"].get<std::string>()) | bold | hcenter,
            hbox({
              GetVboxDayPart(days_name[0], codes_name[0], i),
              separator(),
              GetVboxDayPart(days_name[1], codes_name[1], i),
              separator(),
              GetVboxDayPart(days_name[2], codes_name[2], i),
              separator(),
              GetVboxDayPart(days_name[3], codes_name[3], i),
        }));

        auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
        Render(screen, document);
        screen.Print();
        std::cout << "\n";
    }

}

void View::ReadConfig() {
    std::ifstream config_file(R"(C:\secondSemLab\labwork10\config.json)");
    nlohmann::json config_json = nlohmann::json::parse(config_file);
    update_frequency = config_json["update_freq"].get<int>();
    controller = new Controller;
    controller->ControllerInitiliaze(config_json["cities"].get<std::vector<std::string>>(), config_json["for_days"].get<int>(),
                      config_json["api-key"].get<std::string>(), config_json["city_api"].get<std::string>(),
                              config_json["meteo_api"].get<std::string>());
}
