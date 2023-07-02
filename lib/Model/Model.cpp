
#include "Model.h"

Model::Model(const std::vector<std::string>& cities, int for_days, const std::string& key, const std::string& city, const std::string& meteo) {
    cities_names = cities;
    forecast_days = for_days;
    api_key = key;
    api_city_url = city;
    api_meteo_url = meteo;
}

void Model::UpdateCurrentPosition(int direction) {
    if (direction == 1) {
        current_city = (current_city + 1) % cities_names.size();
    } else {
        if (current_city - 1 < 0) {
            current_city = cities_names.size() - 1;
        } else {
            --current_city;
        }
    }
}

const std::string& Model::ChangeCurrentCity(int city_pos, int days_amount) {
    switch (days_amount) {
        case -1:
            forecast_days = (forecast_days - 1 < 0) ? 0 : --forecast_days;
            break;
        case 1:
            ++forecast_days;
            break;
        default:
            break;
    }

    switch (city_pos) {
        case 0:
            return ReturnCurrentCity();
        case 1:
            UpdateCurrentPosition(1);
            return ReturnCurrentCity();
        case -1:
            UpdateCurrentPosition(-1);
            return ReturnCurrentCity();
    }
}

const std::string& Model::ReturnCurrentCity() const {
    return cities_names[current_city];
}

const nlohmann::json& Model::GetCurrentCityInfo() const {
    return current_city_info;
}

const std::vector<std::string>& Model::GetCitiesNames() const {
    return cities_names;
}

const std::string& Model::GetMeteoApi() const {
    return api_meteo_url;
}

const std::string &Model::GetCityApiUrl() const {
    return api_city_url;
}

const std::string &Model::GetApiKey() const {
    return api_key;
}

int Model::GetCurrentCityPosition() const {
    return current_city;
}

int Model::GetForecastDays() const {
    return forecast_days;
}

void Model::SetNewJson(const nlohmann::json& new_data) {
    current_city_info = new_data;
}

const std::vector<std::string> &Model::GetCodesDayParts() const {
    return codes_day_parts;
}

const std::vector<std::string> &Model::GetOutputDayParts() const {
    return output_day_parts;
}
