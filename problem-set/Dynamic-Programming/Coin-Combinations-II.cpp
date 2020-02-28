#include <bits/stdc++.h>

const int MOD = 1000000000 + 7;

int N, X;
int dp[100 + 5][1000000 + 5];
std::vector<std::pair<int, int>> coins;

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N >> X;

	std::map<int, int> aux_coins;
	for (int i = 0; i < N; i += 1)
	{
		int coin;
		std::cin >> coin;
		aux_coins[coin] += 1;
	}

	for (const auto &i : aux_coins)
	{
		coins.push_back(i);
	}

	for (int i = 0; i < N; i += 1)
	{
		if (!i)
		{
			dp[i][0] = 1;
		}
		else
		{
			for (int j = 0; j <= X; j += 1)
			{
				dp[i][j] += dp[i - 1][j];
				if (dp[i][j] >= MOD)
				{
					dp[i][j] -= MOD;
				}
			}
		}

		for (int j = 0; j + coins[i].first <= X; j += 1)
		{
			const int k = j + coins[i].first;

			dp[i][k] = (1LL * coins[i].second * dp[i][j] + dp[i][k]) % MOD;
		}
	}

	std::cout << dp[N - 1][X] << std::endl;

	return 0;
}