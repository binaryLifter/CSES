#include <bits/stdc++.h>

bool valid(const int block_amount_limit, const std::vector<int> &v, const long long int sum_amount_limit)
{
	int used = 1;
	long long int sum = 0;

	for (const int &i : v)
	{
		if (i > sum_amount_limit)
		{
			return false;
		}

		if (sum + i > sum_amount_limit)
		{
			used += 1;

			if (used > block_amount_limit)
			{
				return false;
			}

			sum = 0;
		}

		sum += i;
	}

	return true;
}

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	int N, K;
	std::cin >> N >> K;

	long long int sum = 0;
	std::vector<int> v(N);
	for (int &i : v)
	{
		std::cin >> i;
		sum += i;
	}

	long long int lo = 0;
	long long int hi = sum;
	
	while (lo <= hi)
	{
		const long long int mid = lo + ((hi - lo) >> 1);

		if (valid(K, v, mid))
		{
			hi = mid - 1;
		}
		else
		{
			lo = mid + 1;
		}
	}

	std::cout << hi + 1 << std::endl;

	return 0;
}