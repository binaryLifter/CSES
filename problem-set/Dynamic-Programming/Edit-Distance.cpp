#include <bits/stdc++.h>

const int MAX_SIZE = 5000 + 1;

std::string A, B;
int dp[MAX_SIZE][MAX_SIZE];

int solve(const int i, const int j)
{
	if (dp[i][j] != -1)
	{
		return dp[i][j];
	}

	if (i == int(A.size()) and j == int(B.size()))
	{
		return dp[i][j] = 0;
	}

	int ans = INT_MAX;

	if (i < int(A.size()))
	{
		ans = std::min(ans, solve(i + 1, j) + 1);
	}

	if (j < int(B.size()))
	{
		ans = std::min(ans, solve(i, j + 1) + 1);
	}

	if (i < int(A.size()) and j < int(B.size()))
	{
		ans = std::min(ans, solve(i + 1, j + 1) + (A[i] != B[j]));
	}

	return dp[i][j] = ans;
}

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> A >> B;

	std::memset(dp, -1, sizeof dp);
	std::cout << solve(0, 0) << std::endl;

	return 0;
}