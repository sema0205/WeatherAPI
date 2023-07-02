# Weather Forecast

Консольное приложение, отображающие прогноз погоды для выбранного списка городов, используя сторонние библиотеки.

## Источник данных

- [Open-Meteo](https://open-meteo.com/en/docs#latitude=59.94&longitude=30.31&hourly=temperature_2m&forecast_days=16) для прогноза
- [Api-Ninjas](https://api-ninjas.com/api/city) для определения координат по названию города

## Функциональные требования

 - Отображение прогноз погоды на несколько дней вперед (значение по умолчанию задается конфигом)
 - Обновление с некоторой частотой (задается конфигом)
 - Переключение между городами с помощью клавиш "n", "p"
 - Конец работы программы по Esc
 - Увеличение\уменьшение количества дней прогноза по нажатию клавиш "+", "-"

Список городов, частота обновления, количество дней прогноза определяются в конфиге.

## Отображение

Образец визуализации:

![image](interface.png) Скриншот взят с  https://wttr.in

## Реализация

В качестве библиотеки для запросов использована [C++ Requests](https://github.com/libcpr/cpr)
