//
// Created by Nico Cevallos on 2/24/25.
//

#pragma once

#ifndef WIZARDSWAR_H
#define WIZARDSWAR_H

#include "player.h"
#include "deck.h"
#include <vector>


class wizardsWar {
public:
  explicit wizardsWar(int numberPlayers);
  int run();
  int addPlayer();
  int removePlayer();
  int addDeck();

private:
  int numPlayers;
  std::vector<std::shared_ptr<player>> players;
  deck* CurrentDeck = nullptr;
};

#endif //WIZARDSWAR_H
