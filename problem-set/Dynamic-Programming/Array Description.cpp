#include <bits/stdc++.h>

const int MOD = 1000000000 + 7;

int N, M;
std::vector<int> v;
int dp[100000 + 5][100 + 5];

int solve(const int i, const int j, const int direction)
{
	if (j < 1 or j > M)
	{
		return 0;
	}

	if (i == -1 or i == N)
	{
		return 1;
	}

	if (dp[i][j] != -1)
	{
		return dp[i][j];
	}

	int ans = 0;

	if (v[i] == 0)
	{
		for (int k = -1; k <= 1; k += 1)
		{
			ans += solve(i + direction, j + k, direction);
			if (ans >= MOD)
			{
				ans -= MOD;
			}
		}
	}
	else if (std::abs(v[i] - j) <= 1)
	{
		ans = solve(i + direction, v[i], direction);
	}

	return dp[i][j] = ans;
}

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N >> M;

	v.resize(N);
	for (int &i : v)
	{
		std::cin >> i;
	}

	int idx = -1;
	for (int i = 0; i < N; i += 1)
	{
		if (v[i] != 0)
		{
			idx = i;
		}
	}

	int ans = 0;

	std::memset(dp, -1, sizeof dp);

	if (idx == -1)
	{
		for (int i = 1; i <= M; i += 1)
		{
			ans += solve(1, i, +1);
			if (ans >= MOD)
			{
				ans -= MOD;
			}
		}
	}
	else
	{
		const int L = (idx - 1 >= 0) ? solve(idx - 1, v[idx], -1) : 1;
		const int R = (idx + 1 < N)  ? solve(idx + 1, v[idx], +1) : 1;

		ans = (1LL * L * R) % MOD;
	}

	std::cout << ans << std::endl;

	return 0;
}