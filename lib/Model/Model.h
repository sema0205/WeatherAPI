#pragma once

#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

class Model {
public:

    Model(const std::vector<std::string>& cities, int for_days, const std::string& key, const std::string& city, const std::string& meteo);

    void UpdateCurrentPosition(int direction);
    const std::string& ChangeCurrentCity(int city_pos, int days_amount);

    const std::string& ReturnCurrentCity() const;
    const nlohmann::json& GetCurrentCityInfo() const;
    const std::vector<std::string>& GetCitiesNames() const;

    int GetForecastDays() const;
    int GetCurrentCityPosition() const;

    const std::string& GetApiKey() const;
    const std::string& GetCityApiUrl() const;
    const std::string& GetMeteoApi() const;

    const std::vector<std::string>& GetCodesDayParts() const;
    const std::vector<std::string>& GetOutputDayParts() const;

    void SetNewJson(const nlohmann::json& new_data);

private:
    nlohmann::json current_city_info;
    std::vector<std::string> cities_names;

    int current_city = 0;
    int forecast_days = 0;
    std::vector<std::string> codes_day_parts = {"morning", "noon", "evening", "night"};
    std::vector<std::string> output_day_parts = {"Утро", "День", "Вечер", "Ночь"};

    std::string api_key;
    std::string api_city_url;
    std::string api_meteo_url;
};

