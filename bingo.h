#pragma once

#include <omp.h>
#include <iostream>
#include <array>
#include <random>
#include <set>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>

typedef std::mt19937 MyRNG;

MyRNG get_gen();

std::vector<int> sample_5(MyRNG &gen, int offset);

enum GameModes
{
    FullHouse, // full card
    Line       // horizontal or vertical line
};

struct BingoCard
{
    // std::set<int> numbers;
    std::vector<std::vector<int>> numbers;
    std::set<int> numbers_set;
    std::array<int, 5> row_sums, col_sums;
    bool won = false;
    void update(int number);
    BingoCard(MyRNG &gen);
};

class BingoGame
{
private:
    int num_players;
    MyRNG gen;
    std::vector<int> numbers;
    std::vector<BingoCard> cards;

public:
    BingoGame(int num_players, MyRNG &gen) : num_players(num_players), gen(gen)
    {
        for (int i = 0; i < 75; i++)
            numbers.push_back(i + 1);
        std::shuffle(numbers.begin(), numbers.end(), gen);
        for (int i = 0; i < num_players; i++)
            cards.push_back(BingoCard(gen));
    }
    ~BingoGame()
    {
        cards.clear();
        numbers.clear();
    }
    int Run();
};