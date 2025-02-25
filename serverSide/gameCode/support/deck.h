//
// Created by Nico Cevallos on 2/24/25.
//

#ifndef DECK_H
#define DECK_H
#include <vector>
#include "card.h"

class deck {
public:
    deck();
  	deck *getDeckPointer();

private:
	std::vector<std::shared_ptr<card>> cards;

};
#endif //DECK_H
