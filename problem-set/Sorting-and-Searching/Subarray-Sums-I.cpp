#include <bits/stdc++.h>

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	int N, X;
	std::cin >> N >> X;

	std::vector<int> v(N);
	for (int &i : v)
	{
		std::cin >> i;
	}
	
	long long int sum = 0;
	std::map<long long int, int> dp;
	for (int i = 0; i < N; i += 1) 
	{
		sum += v[i];
		dp[sum] += 1;
	}

	sum = 0;
	long long int ans = 0;
	for (int i = 0; i < N; i += 1)
	{
		ans += dp[sum + X];
		
		sum += v[i];
		dp[sum] -= 1;
	}

	std::cout << ans << std::endl;

	return 0;
}