import std;
import Card;
export module Deck;

void shuffleDeck(std::vector<Card>& deck) {
	int s = deck.size();
	std::srand(std::time(0));
	for (int i = 0; i < s; i++)
	{
		int r = i + std::rand() % (52 - i);

		std::swap(deck[i], deck[r]);
	}
}

std::vector<Card> popDeck() {
	std::vector<Card> ret;
	const std::vector<Card::suit> a = { Card::Hearts, Card::Spades, Card::Diamonds, Card::Clubs };
	for (const auto& bae : a) {
		for (int i = 1; i < 14; i++)
		{
			ret.push_back(Card(bae, i));
		}
	}
	for (int j = 0; j < 5; j++) shuffleDeck(ret);

	return ret;

}

export class Deck {
	public:
		Deck();
		std::vector<Card> seeCards();
		void popBack();
		Card Back();
private:
	std::vector<Card> cards;
};

Deck::Deck()
	:cards{ popDeck() } {}

std::vector<Card> Deck::seeCards() {
	return cards;
}

void Deck::popBack() {
	cards.pop_back();
}
Card Deck::Back() {
	return cards.back();
}

