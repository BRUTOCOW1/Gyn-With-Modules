
export module Hand;
import Deck;
import Card;
import std;


bool suitSort(const Card& lhs, const Card& rhs) {
	if (lhs.getSuit() != rhs.getSuit()) {
		return lhs.getSuit() < rhs.getSuit();
	}
	else {
		return lhs < rhs;
	}
}

std::vector<Card> makeHand(Deck& d, int dealer) {
	int number = dealer ? 10 : 11;
	std::vector<Card> ret;
	for (int i = 0; i < number; i++) {
		ret.push_back(d.seeCards().back());
		d.popBack();
		
	}
	std::sort(ret.begin(), ret.end(), &suitSort);

	return ret;
}


export struct Hand {
	public:
		Hand(Deck& d, int dealer);
		std::vector<Card> seeCards();
		void kill(Card& card);
		void birth(Card& card);
		void printHand();
		void getRuns(const std::unordered_map<const char*, std::vector<int>>& runs);
		void getBlocks(std::vector<Card>& cardos);
		bool victory();

	private:
		std::vector<Card> cards;
	
};

Hand::Hand(Deck& d, int dealer)
	: cards{ makeHand(d,dealer) } {}

std::vector<Card> Hand::seeCards() {
	return cards;
}

/***
	Here, we want to go through cards, and determine which runs exist.
	Runs are defined as three or more cards of a suit that run consecutively
	ie. 2 of Hearts, 3 of Hearts, 4 of Hearts.
	We will loop through Cards and keep the current suit Suit!
	if suit!= Suit, index goes to the first of the next index.

***/
bool Hand::victory() {
	return false;
}

void Hand::getRuns(const std::unordered_map<const char*, std::vector<int>>& runs) {
	std::unordered_map<const char*, std::vector<std::vector<int>>> jogs;
	bool full = false;
	for (const auto& entry : runs) {
		const char* key = entry.first;
		const std::vector<int>& values = entry.second;
		std::vector<int> tempy;
		for (int value : values) {
			if (tempy.size() == 0) {
				tempy.push_back(value);
			}else {
				if (value == tempy.back() + 1) {
					tempy.push_back(value);
				}
				else {
					if (tempy.size() > 2) {
						jogs[key].push_back(tempy);
						full = true;
					}
					
					tempy.clear();
					tempy.push_back(value);
				}
			}
		}
		if (tempy.size() > 2) {
			jogs[key].push_back(tempy);
			full = true;

		}
	}
	if (!full) return;
	std::cout << "RUNS" << std::endl;
	for (const auto& i : jogs) {
		std::cout << i.first << " : ";
		for (const auto& o : i.second){
			for (const auto& p : o) {
				std::cout << p << " ";
			}
		}

	}
	std::cout << std::endl;
	
	
	
}

void Hand::getBlocks(std::vector<Card>& cardos) {
	int val;
	std::unordered_map<int, int> track;
	for (auto& e : cards) {
		val = e.getVal();
		if (track.find(val) == track.end()) {
			track[val] = 0;
		}
		track[val]++;

	}
	bool print = false;
	for (auto& p : track) {
		if (p.second > 2) {
			print = true;
			std::cout << "BLOCKS" << std::endl;
			break;
		}
	}
	for (auto& p : track) {
		if (p.second > 2) {
			std::cout << p.first << "s: " <<  p.second << "  ";

		}
	}

	if (print) std::cout << std::endl;
	
}

void Hand::printHand() {
	//for (auto& e : cards) {
	//	e.printCard();
	//}
	
	std::unordered_map<const char*, std::vector<int>> runs;
	int index = 0, tempIndex, sz = cards.size();
	while (index < sz) {
		Card last = cards[index];
		const char* suitt = last.getSuit();
		tempIndex = index + 1;

		while (tempIndex < sz && cards[tempIndex].getSuit() == suitt) {
			tempIndex++;
		}

		std::vector<int>& values = runs[suitt];  // Get or create vector of values
		for (int i = index; i < tempIndex; i++) {
			values.push_back(cards[i].getVal());  // Push values into the vector
		}

		index = tempIndex;
	}
	for (const auto& entry : runs) {
		const char* key = entry.first;
		const std::vector<int>& values = entry.second;

		std::cout << key << ": ";
		for (int value : values) {
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	getBlocks(cards);
	getRuns(runs);
}

void Hand::kill( Card& card) {
	for (auto it = cards.begin(); it != cards.end(); ++it) {
		if (*it == card) {
			cards.erase(it);
			break;

		}
	}
}

void Hand::birth(Card& card) {
	int i = 0;
	card.printCard();
	cards.push_back(card);
	std::sort(cards.begin(), cards.end(), &suitSort);

}