
#include "../lib/View/View.h"


int main() {

    View user_interface;
    user_interface.RunProgramm();

    return 0;
}


/* TODO config:
 * 1) Отображать прогноз погоды на несколько дней вперед (значение по умолчанию задается конфигом)
 * 2) Обновлять с некоторой частотой (задается конфигом)
 * 3) Список городов
 * 4) частота обновления
 * 5) количество дней прогноза
 * должны быть определены в конфиге (например в формате OMFL)
 */

/* TODO interface buttons:
 * 1) Переключаться между городами с помощью клавиш "n", "p"
 * 2) Увеличивать\уменьшать количество дней прогноза по нажатие клавиш "+", "-"
 * 3) Заканчивать работу программы по Esc
 */