#include <bits/stdc++.h>

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(0);
	std::cout.tie(0);

	int N, K;
	std::cin >> N >> K;

	std::vector<std::pair<int, int>> movies(N);
	for (auto &i : movies)
	{
		std::cin >> i.second >> i.first;
	}

	std::multiset<int> members;
	for (int i = 0; i < K; i += 1)
	{
		members.insert(0);
	}

	int ans = 0;
	std::sort(movies.begin(), movies.end());

	for (const auto &i : movies)
	{
		const int start = i.second;
		const int finish = i.first;

		auto it = members.upper_bound(start);

		if (it == members.begin())
		{
			continue;
		}

		--it;
		members.erase(it);
		members.insert(finish);
		ans += 1;
	}

	std::cout << ans << std::endl;

	return 0;
}