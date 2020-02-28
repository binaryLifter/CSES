#include <bits/stdc++.h>

const int MOD = 1000000000 + 7;

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int N, X;
    std::cin >> N >> X;

    std::vector<int> v(N);
    for (int &i : v)
    {
        std::cin >> i;
    }

    std::vector<int> dp(X + 1, 0);

    dp[0] = 1;
    for (int i = 1; i <= X; i += 1)
    {
        for (const int j : v)
        {
            if (i - j >= 0)
            {
                dp[i] += dp[i - j];
                if (dp[i] > MOD)
                {
                    dp[i] -= MOD;
                }
            }
        }
    }

    std::cout << dp[X] << std::endl;

    return 0;
}
