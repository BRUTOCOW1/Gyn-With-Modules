
import std;
export module Card;

export class Card
{
	public:
		enum suit { Hearts = 0, Spades, Diamonds, Clubs };
		Card(suit a, int b);
		Card();
		const char* getSuit() const;
		const int getVal() const;
		void printCard();
		bool operator<(const Card& other) const {
			return val < other.getVal();
		}
		const suit getsuitCode() const;

		bool operator==(Card& b) {
			return (s == b.getsuitCode() && val == b.getVal());
		}

	private:
		suit s;
		int val;
};

Card::Card()
	:s{}, val{} {}

Card::Card(suit a, int b)
	:s{ a }, val{ b } {}

const char* Card::getSuit() const {
	switch (s) {
	case Hearts: return "Hearts";
	case Spades: return "Spades";
	case Diamonds: return "Diamonds";
	case Clubs: return "Clubs";
	}
	return "naur";
}

const int Card::getVal() const {
	return val;
}

const Card::suit Card::getsuitCode() const {
	return s;
}

void Card::printCard() {
	if (val == 1 || val > 10) {
		switch (val) {
		case 1: std::cout << "Ace"; break;
		case 11: std::cout << "Jack";  break;
		case 12: std::cout << "Queen"; break;
		case 13: std::cout << "King"; break;
		}
	}
	else {
		std::cout << val;
	}
	std::cout << " of " << getSuit() << std::endl;
}