#include "main_menu.h"

// Обработка главного меню
game_mode main_menu()
{
    short choosen_index = 0;

    while (true)
    {
        print_menu();
        choosen_index = get_move_input(0, 3);
        switch (choosen_index)
        {
        case invalid_input:
            std::cout << "Неверный ввод, попробуйте ещё раз!" << std::endl;
            break;
        case invalid_index:
            std::cout << "Неверный индекс, попробуйте ещё раз!" << std::endl;
            break;
        case 1:
            return with_bot;
            break;
        case 2:
            return with_other_player;
            break;
        case 3:
            print_rules();
            break;
        case 0:
            exit(0);
            break;
        }
    }
}