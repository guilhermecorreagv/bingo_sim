#include "bingo.h"

int main(int argc, char **argv)
{
    // if (argc != 4)
    // {
    //     std::cerr << "Usage should be: MODE [Full/Line] NUM_PLAYERS NUM_ITERS"
    // }
    // int num_players = stoi(argv[2]), num_iters = stoi(argv[3]);
    // GameModes mode;

    // switch (toupper(argv[1]))
    // {
    // case "FULL":
    //     mode = GameModes::FullHouse;
    //     break;
    // case "LINE":
    //     mode = GameModes::Line;
    //     break;
    // default:
    //     std::cerr << "Invalid Mode, should be [FULL/LINE]";
    //     return 1;
    // }

    int num_players = 2;
    // stats
    std::vector<int> num_turns;

    MyRNG gen = get_gen(); // already seeded
    BingoGame b(num_players, gen);
    num_turns.push_back(b.Run());

    return 0;
}