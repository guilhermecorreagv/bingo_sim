#include "bingo.h"

MyRNG get_gen()
{
    std::random_device rd;
    MyRNG gen(rd());
    return gen;
}

std::vector<int> sample_5(MyRNG &gen, int offset = 0)
{
    std::vector<int> vec;
    for (int i = 1; i < 16; i++)
        vec.push_back(i + 15 * offset);

    std::shuffle(vec.begin(), vec.end(), gen);
    std::vector<int> ret(vec.begin(), vec.begin() + 5); // we sample 5 elements
    std::sort(ret.begin(), ret.end());
    return ret;
}

BingoCard::BingoCard(MyRNG &gen)
{
    std::fill(row_sums.begin(), row_sums.end(), 5); // all numbers filled
    std::fill(col_sums.begin(), col_sums.end(), 5); // all numbers filled

    // get random values
    for (int i = 0; i < 5; i++)
    {
        std::vector<int> samples = sample_5(gen, i);
        if (i == 2)
            samples.erase(samples.begin() + 2); // middle element
        numbers.push_back(samples);

        for (auto v : samples)
            numbers_set.insert(v);
    }

    // remove the middle value
    row_sums[2]--;
    col_sums[2]--;
}

void BingoCard::update(int number)
{
    if (numbers_set.find(number) != numbers_set.end())
    {
        int row_idx = 0, col_idx = (number - 1) / 15;

        col_sums[col_idx]--;
        for (int i = 0; i < 5; i++)
        {
            if (numbers[col_idx][i] == number)
            {
                row_idx = i;
                numbers[col_idx][row_idx] = 0; // mark as done
                break;
            }
        }

        numbers_set.erase(number);

        if (row_sums[row_idx] == 0 || col_sums[row_idx] == 0)
            won = true;
    }
}

std::ostream &operator<<(std::ostream &os, const BingoCard &card)
{
    // Fixed width for each number
    const int width = 3;

    // Print the header with proper alignment
    os << std::setw(width) << "B" << " "
       << std::setw(width) << "I" << " "
       << std::setw(width) << "N" << " "
       << std::setw(width) << "G" << " "
       << std::setw(width) << "O" << "\n";

    // Print the bingo numbers
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            os << std::setw(width) << card.numbers[j][i] << " ";
        }
        os << '\n';
    }
    return os;
}

int BingoGame::Run()
{
    for (int i = 0; i < 75; i++)
    {
        int current_number = numbers[i];

#ifdef DEBUG
        std::cout << "Got the number " << current_number << std::endl;
        std::cout << "Situation of the cards:\n";
#endif

        for (int i = 0; i < (int)cards.size(); i++)
        {
            cards[i].update(current_number);

#ifdef DEBUG
            std::cout << "Card " << i << std::endl
                      << cards[i];
#endif
            if (cards[i].won)
                return i;
        }
    }
    return -1; // not allowed
}