cmake_minimum_required(VERSION 3.10)
project(wizards_war_client)

set(CMAKE_CXX_STANDARD 17)

add_executable(client_exec client.cpp)

add_executable(game serverSide/gameCode/game.cpp
                    serverSide/gameCode/support/card.cpp
                    serverSide/gameCode/support/deck.cpp
                    serverSide/gameCode/support/player.cpp
                    serverSide/gameCode/support/wizardsWar.cpp)