#pragma once

#include <ftxui/dom/elements.hpp>

#include "../Controller/Controller.h"

class View {
public:

    void RunProgramm();
    void ShowScreen();
    void ReadConfig();
    ftxui::Element GetVboxDayPart(const std::string& day_name, const std::string& day_code, int pos);

private:
    Controller* controller;
    int update_frequency;
};
