# WeatherForecast

Console application that displays weather forecasts for a selected list of cities using third-party libraries.

## Data source

- [Open-Meteo](https://open-meteo.com/en/docs#latitude=59.94&longitude=30.31&hourly=temperature_2m&forecast_days=16) for forecast
- [Api-Ninjas](https://api-ninjas.com/api/city) to determine coordinates by city name

## Functional requirements

  - Display the weather forecast for several days ahead (the default value is set by the config)
  - Update with some frequency (set by config)
  - Switch between cities using the keys "n", "p"
  - End of program operation using Esc
  - Increase/decrease the number of forecast days by pressing the "+", "-" keys

The list of cities, update frequency, number of forecast days are determined in the config.

## Display

Sample visualization:

![image](interface.png) Screenshot taken from https://wttr.in

## Implementation

[C++ Requests](https://github.com/libcpr/cpr) was used as a library for requests.
