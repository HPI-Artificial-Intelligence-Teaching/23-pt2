#include <iostream>
#include <vector>
#include <algorithm>

int min_coins(int amount)
{
    int coins[] = {25, 10, 5, 1};
    int num_coins = 0;
    int remaining = amount;

    for (int coin : coins)
    {
        while (remaining >= coin)
        {
            remaining -= coin;
            num_coins += 1;
        }
    }

    return num_coins;
}

int main()
{
    int amount = 42;
    std::cout << min_coins(amount) << std::endl; // Output: 5
    return 0;
}