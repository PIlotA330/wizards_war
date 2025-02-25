//
// Created by Nico Cevallos on 2/24/25.
//

#ifndef CARD_H
#define CARD_H

class card {
public:
	card();
	int getNumber();
	int getSuit();

private:
	int number;
	int suit;
};

#endif //CARD_H
