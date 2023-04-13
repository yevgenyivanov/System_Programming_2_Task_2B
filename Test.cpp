
#include "doctest.h"
#include <iostream>
//objects' headers
#include "sources/game.hpp"
#include "sources/player.hpp"
#include "sources/card.hpp"
using namespace ariel;
//objects' implementations
// #include "./sources/game.cpp"
// #include "./sources/player.cpp"
// #include "./sources/card.cpp"

TEST_CASE("Player Initialization")
{
    std::cout<< "Testing player initialization..." << std::endl;
    Player player1("Alice");
    Player player2("Bob");
    // player stack is 0 upon player initialization as well as cards taken before game start
    CHECK(player1.stacksize() == 0);
    CHECK(player2.stacksize() == 0);
    CHECK(player1.cardesTaken() == 0);
    CHECK(player2.cardesTaken() == 0);
    CHECK(player1.getIsPlaying() == false);
    CHECK(player2.getIsPlaying() == false);
    
}

TEST_CASE("Game Test")
{
    // create players and game obj
    std::cout<< "Testing game initialization..." << std::endl;
    Player player1("Charlie");
    Player player2("David");
    Game testgame(player1, player2);
    // check that each player is dealt 26 cards
    CHECK(player1.stacksize() == 26);
    CHECK(player2.stacksize() == 26);
    // check that each player hasn't taken a card yet
    CHECK(player1.cardesTaken() == 0);
    CHECK(player2.cardesTaken() == 0);
    // check prints before any turn is played
    CHECK_NOTHROW(testgame.printLastTurn()); // check if the previous turn is not printed (because no turn was played)
    CHECK_NOTHROW(testgame.printLog());      // check that the game log is not printed (because no turn was played)

    // check if a turn is played correctly and check prints again
    CHECK_NOTHROW(testgame.playTurn());
    // check that each player played a card
    CHECK(player1.stacksize() == 25);
    CHECK(player2.stacksize() == 25);
    CHECK_NOTHROW(testgame.printLastTurn());
    CHECK_NOTHROW(testgame.printLog());


    // check that a game is played until the end correctly
    CHECK_NOTHROW(testgame.playAll());
    CHECK(player1.stacksize() == 0);
    CHECK(player2.stacksize() == 0);                            // both players played all of their cards
    CHECK(player1.cardesTaken() + player2.cardesTaken() == 52); // all 52 cards were played
    CHECK_NOTHROW(testgame.printWiner());                       // a winner exists
    // check prints are correct
    CHECK_NOTHROW(testgame.printLog());   // every game turn is printed
    CHECK_NOTHROW(testgame.printStats()); // check that each player has his stats printed correctly

    // stacks are empty and each player won 26 cards
    // SUBCASE("Draw")
    // {   
    //     bool draw_condition = player1.cardesTaken() == 26 && player1.stacksize() == 0 && player2.cardesTaken() == 26 && player2.stacksize() == 0;
    //     CHECK(draw_condition);
    // }
    // SUBCASE("Player 1 won")
    // {
    //     bool player1_win_condition = (player1.cardesTaken() > player2.cardesTaken()) && player1.stacksize() == 0 && player2.stacksize() == 0;
    //     CHECK(player1_win_condition == true);
    // }
    // SUBCASE("Player 2 won")
    // {
    //     bool player2_win_condition = (player2.cardesTaken() > player1.cardesTaken()) && player1.stacksize() == 0 && player2.stacksize() == 0;
    //     CHECK(player2_win_condition == true);
    // }
}

TEST_CASE("Solo Game")
{
    Player soloPlayer("Player");
    CHECK_NOTHROW(Game(soloPlayer, soloPlayer)); // game with one player
}

TEST_CASE("Playing another game"){
    Player player1("Alice");
    Player player2("Bob");
    Player player3("Charlie");

    Game game1(player1, player2);
    SUBCASE("One player in two games at the same time"){
        CHECK_NOTHROW(Game(player1, player3));
    }
    CHECK_NOTHROW(game1.playAll());
    CHECK_NOTHROW(game1.printWiner());
    CHECK(player1.getIsPlaying() == false);
    CHECK(player2.getIsPlaying() == false);
    std::cout<< std::endl;
    Game game2 = Game(game1);
    // game1.~Game();
    
    CHECK(player1.getIsPlaying() == false);
    CHECK(player2.getIsPlaying() == false);
}