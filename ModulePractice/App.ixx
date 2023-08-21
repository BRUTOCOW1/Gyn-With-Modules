export module App;
import Game;
import std;
import IO;
#include <stdlib.h>



export struct App {
    public: 
        void start_game();
        void open_app();
        App();
        IO io;

       

};

App::App() {
    open_app();
    start_game();


}


void App::open_app() {
    io.termSize();
    std::cout << "Press Enter to play...";
    std::cin.get();
    system("cls");

}


void App::start_game()
{
    Game a{ Game() };
    return;

}
