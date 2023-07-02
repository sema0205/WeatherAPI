#pragma once

#include "../Model/Model.h"

class Controller {
public:

    Controller() = default;
    Model* GetModel() const;

    void ControllerInitiliaze(const std::vector<std::string>& cities, int for_days, const std::string& key, const std::string& city, const std::string& meteo);

    void ChangeModel(int city_pos, int days_amount);
    nlohmann::json SendRequest(const std::string& name);
    nlohmann::json PrettifierJsonModel(const nlohmann::json& origin_data);

private:
    Model* model;
};
