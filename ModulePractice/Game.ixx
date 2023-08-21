export module Game;
import std;
import Card;
import Deck;
import Hand;
import IO;
#include <stdlib.h>

export struct Game {
public:
    Game();
    bool start_game();
    void take_turn();
    void discard();
    void printDiscard();
    void take_card();
    void incrTurn();
    void initDiscard();
    void clearAndPrint();
    IO io;

private:
	Deck d;
	Hand a;
	Hand b;
    int curHand;
    Hand* hand;
    std::stack<Card> played;
};

void Game::clearAndPrint() {
    system("cls");
    (*hand).printHand();
}
void Game::discard() {
    Card enteredCard = io.handle_input();
    played.push(enteredCard);
    (*hand).kill(enteredCard);
    clearAndPrint();

}

void Game::printDiscard() {
    std::cout << "Top Discard: ";
    played.top().printCard();
}


void Game::initDiscard() {
    b.printHand();
    Card a = io.handle_input();
    played.push(a);
    b.kill(a);
}

void Game::take_card() {
    printDiscard();
    char opCode = io.getOC();
    Card toAdd;
    switch (opCode) {
        case 'b': { 
            toAdd = d.Back();
            d.popBack();
            break; 
        }
        case 'a': {
            toAdd = played.top();
            played.pop();
            break;
        }
    };
    (*hand).birth(toAdd);
    clearAndPrint();

}

void Game::incrTurn() {
    curHand++;
}

Game::Game()
    : d{ Deck() }, a{ Hand(d,1) }, b{ Hand(d,0) }, curHand{ 0 }, hand{&a} {
        start_game();
    }

bool Game::start_game() {
    initDiscard();
    for (int i = 0; i < 30; i++) {
        hand = curHand % 2 == 0 ? &a : &b;
        clearAndPrint();

        take_turn();
    }
    return true;
}

void Game::take_turn() {
    
    take_card();
    discard();
    incrTurn();

}

