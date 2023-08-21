export module IO;
import Card;
import Hand;
import std;
#include <Windows.h>
#include <ioapiset.h>



export struct IO {
	public:
		Card handle_input();
        char getOC();
        void termSize();
};



void IO::termSize() {
    int rows, cols;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    if (GetConsoleScreenBufferInfo(hConsole, &bufferInfo)) {
        rows = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;
        cols = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
    }
    else {
        std::cout << "Unable to determine terminal dimensions." << std::endl;
    }
    std::vector<int> bop {rows, cols};



    for (int i{ 0 }; i < bop[0]-1; i++) {
        for (int j{ 0 }; j < bop[1]; j++) {
            if (i == (int)(rows / 2 -1) && j == (int)(cols / 2 - cols * .1)) {
                std::cout << " Lets Play Some Mf Gyn ";
                for (int b = (int)(cols / 2 - cols * .1) + 23; b < cols; b++) std::cout << 0;
                break;
            }
            std::cout << "0";
        }
        std::cout << std::endl;
    }
}

char IO::getOC() {
    char opCode;

    std::cout << "Take from Discards (a):  | Take From Deck(b) " << std::endl;

    std::cin >> opCode;
    return opCode;
}

Card IO::handle_input() {
    std::cout << " In LN -> LetterNumber notation, which card would you like to discard?" << std::endl;

    std::string input;
    std::cin >> input;
    int val = (int)input[1] - '0';
    if (val == 1) {
        if (input[2] != '\0') {
            val += 9 + (int)input[2] - '0';
        }
    }
    std::cout << val << std::endl;

    Card::suit suit;
    char suit2 = input[0];
    switch (suit2) {
    case 'h': suit = Card::Hearts; break;
    case 's': suit = Card::Spades; break;
    case 'd': suit = Card::Diamonds; break;
    case 'c': suit = Card::Clubs; break;
    }
    return Card{ suit, val };
}