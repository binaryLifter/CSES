#include <bits/stdc++.h>

const int MAX_SIZE = 60;

std::vector<int> v;
long long int dp[MAX_SIZE][2];
long long int qty[MAX_SIZE][2];

long long int solve(const int i, const int j)
{
    if (qty[i][j] != -1)
    {
        return qty[i][j];
    }

    if (i == int(v.size()))
    {
        return qty[i][j] = 1;
    }

    long long int ans = 0;
    const int limit = j ? 1 : v[i];

    for (int k = 0; k <= limit; k += 1)
    {
        const int x = i + 1;
        const int y = j | (k < v[i]);

        ans += solve(x, y);

        if (k == 1)
        {
            dp[i][j] += solve(x, y);
        }

        dp[i][j] += dp[x][y];
    }

    return qty[i][j] = ans;
}

int main()
{
    long long int N;
    std::cin >> N;

    for (int i = MAX_SIZE - 2; i >= 0; i -= 1)
    {
        v.push_back((N & (1LL << i)) ? 1 : 0);
    }

    std::memset(dp, 0, sizeof dp);
    std::memset(qty, -1, sizeof qty);
    solve(0, 0);

    std::cout << dp[0][0] << std::endl;

    return 0;
}
