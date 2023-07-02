
#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "Controller.h"
#include "../Model/Model.h"


void Controller::ControllerInitiliaze(const std::vector <std::string>& cities, int for_days, const std::string& key,
                                      const std::string& city, const std::string& meteo) {
    model = new Model(cities, for_days, key, city, meteo);
}

nlohmann::json Controller::SendRequest(const std::string& name) {

    cpr::Response city_info_response = cpr::Get(cpr::Url{model->GetCityApiUrl()},
                      cpr::Header{{"X-Api-Key", model->GetApiKey()}},
                      cpr::Parameters{{"name", name}});

    nlohmann::json city_info = nlohmann::json::parse(city_info_response.text.substr(1, city_info_response.text.size() - 2));
    cpr::Response get_info = cpr::Get(cpr::Url{model->GetMeteoApi()},
                                      cpr::Parameters{{"latitude", std::to_string(city_info["latitude"].get<float>())},
                                                      {"longitude", std::to_string(city_info["longitude"].get<float>())},
                                                      {"hourly", "temperature_2m"},
                                                      {"hourly", "windspeed_10m"},
                                                      {"hourly", "winddirection_10m"},
                                                      {"hourly", "visibility"},
                                                      {"hourly", "rain"},
                                                      {"hourly", "precipitation_probability"},
                                                      {"hourly", "weathercode"},
                                                      {"forecast_days", std::to_string(model->GetForecastDays())}});

    return nlohmann::json::parse(get_info.text);
}

void Controller::ChangeModel(int city_pos, int days_amount) {
    model->SetNewJson(PrettifierJsonModel(SendRequest(model->ChangeCurrentCity(city_pos, days_amount))));
}

nlohmann::json Controller::PrettifierJsonModel(const nlohmann::json& origin_data) {
    nlohmann::json city_data;
    city_data["city"] = model->ReturnCurrentCity();
    auto day_parts = model->GetCodesDayParts();

    int date_pos = 0;
    int info_pos = 0;

    for (int i = 0; i < model->GetForecastDays(); i++) {

        city_data["days"][i]["date"] = origin_data["hourly"]["time"][date_pos].get<std::string>().substr(0, 10);
        city_data["days"][i]["hours"];
        int start_day = 0;

        while (start_day < 4) {

            float average_temp = 0;
            float min_temp = INT_MAX;

            int weather_code = 0;
            float wind_speed = 0;
            float min_wind_speed = INT_MAX;
            int wind_direction = 0;
            int visibility = 0;
            float rain_length = 0;
            int rain_chance = 0;

            int start_day_part = 0;
            while (start_day_part < 6) {
                min_temp = min_temp < origin_data["hourly"]["temperature_2m"][info_pos].get<float>() ? min_temp :
                        origin_data["hourly"]["temperature_2m"][info_pos].get<float>();
                average_temp += origin_data["hourly"]["temperature_2m"][info_pos].get<float>();
                weather_code += origin_data["hourly"]["weathercode"][info_pos].get<int>();
                wind_speed += origin_data["hourly"]["windspeed_10m"][info_pos].get<float>();
                min_wind_speed = min_wind_speed < origin_data["hourly"]["windspeed_10m"][info_pos].get<float>() ? min_wind_speed :
                        origin_data["hourly"]["windspeed_10m"][info_pos].get<float>();
                wind_direction += origin_data["hourly"]["winddirection_10m"][info_pos].get<int>();
                visibility += origin_data["hourly"]["visibility"][info_pos].get<int>();
                rain_length += origin_data["hourly"]["rain"][info_pos].get<float>();
                rain_chance += origin_data["hourly"]["precipitation_probability"][info_pos].get<int>();
                start_day_part++;
                info_pos++;
            }

            std::string average_temp_str;
            std::string min_temp_str;

            if (average_temp / 6 < 0) {
                average_temp_str = "-" + std::to_string(int(average_temp / 6));
            } else {
                average_temp_str = "+" + std::to_string(int(average_temp / 6));
            }

            if (min_temp / 6 < 0) {
                min_temp_str = "-" + std::to_string(int(min_temp));
            } else {
                min_temp_str = std::to_string(int(min_temp));
            }

            nlohmann::json hour = {
                {"weather_code", weather_code / 6},
                {"average_temp", average_temp_str},
                {"min_temp", min_temp_str},
                {"min_wind_speed", std::to_string(int(min_wind_speed))},
                {"wind_speed", std::to_string(int(wind_speed / 6)) + " " + origin_data["hourly_units"]["windspeed_10m"].get<std::string>()},
                {"wind_direction", std::to_string(wind_direction / 6) + origin_data["hourly_units"]["winddirection_10m"].get<std::string>()},
                {"visibility", std::to_string(visibility / 6000) + " km"},
                {"rain_length", std::to_string(rain_length / 6).substr(0, 3) + " " + origin_data["hourly_units"]["rain"].get<std::string>()},
                {"rain_chance", std::to_string(rain_chance / 6) + " " + origin_data["hourly_units"]["precipitation_probability"].get<std::string>()}
            };

            city_data["days"][i]["hours"][day_parts[start_day]] = hour;
            start_day++;
        }
        date_pos += 24;
    }

    return city_data;
}

Model* Controller::GetModel() const {
    return model;
}


