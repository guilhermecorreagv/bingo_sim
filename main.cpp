#include "bingo.h"
#include <iostream>
#include <numeric>
#include <string>
#include <cstring>

int parse_args(int argc, char **argv, GameMode &mode, int &num_players, int &num_iters)
{
    if (argc != 4)
    {
        std::cerr << "Usage should be: MODE [Full/Line] NUM_PLAYERS NUM_ITERS";
        return 1;
    }
    num_players = atoi(argv[2]);
    num_iters = atoi(argv[3]);

    std::string mode_str = argv[1];
    for (auto &c : mode_str)
        c = toupper(c);

    if (mode_str == "FULL")
        mode = GameMode::FullHouse;
    else if (mode_str == "LINE")
        mode = GameMode::Line;
    else
        return 1;

    return 0;
}

double calculate_mean(std::vector<double> &vec)
{
    if (vec.empty())
    {
        return 0.0; // Or handle this case as needed
    }
    return std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
}

double calculate_std(std::vector<double> &data)
{
    const size_t size = data.size();

    const double mean = calculate_mean(data);

    auto variance_func = [&mean, &size](double accumulator, const double &val)
    {
        return accumulator + ((val - mean) * (val - mean)) / (size - 1);
    };

    double variance = std::accumulate(data.begin(), data.end(), 0.0, variance_func);
    return std::sqrt(variance);
}

int main(int argc, char **argv)
{
    GameMode mode;
    int num_players, num_iters;

    if (parse_args(argc, argv, mode, num_players, num_iters))
    {
        std::cout << "Error while parsing args...\n";
        return 1;
    }
    std::cout << "Running simulation for:\n\t" << num_players << " players\n\t" << num_iters << " iterations\n";

    // stats
    std::vector<double> run_turns(num_iters, 0.0);

#pragma omp parallel for
    for (int i = 0; i < num_iters; i++)
    {
        BingoGame b(num_players, mode);
        b.Run();
        run_turns[i] = static_cast<double>(b.result);
    }

    std::cout << "Avg number of turns: " << calculate_mean(run_turns) << std::endl;
    std::cout << "Standard Deviation number of turns: " << calculate_std(run_turns) << std::endl;
    return 0;
}