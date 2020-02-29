#include <bits/stdc++.h>

template <typename T>
class FenwickTree
{
public:
	FenwickTree(const int size)
	{
		this->v = std::vector<T>(size, 0);
	}

	void update(const int idx, const T value)
	{
		for (int i = idx; i < int(this->v.size()); i += i & -i)
		{
			this->v[i] += value;
		}
	}

	T query(const int idx) const
	{
		T sum = 0;
		for (int i = idx; i > 0; i -= i & -i)
		{
			sum += this->v[i];
		}
		return sum;
	}

private:
	std::vector<T> v;
};

int solve(const int L, const int R, const auto &bit, const int goal)
{
	int lo = L;
	int hi = R;

	while (lo <= hi)
	{
		const int mid = lo + ((hi - lo) >> 1);

		const int current = bit->query(mid);

		if (current < goal)
		{
			lo = mid + 1;
		}
		else
		{
			hi = mid - 1;
		}
	}

	return hi + 1;
}

long long int other_solve(auto &hash, auto &unhash, const int size, const auto &bit_frequency, const auto &bit_sum, const int value)
{
	long long int ans = 0;

	const int qty_before = bit_frequency->query(value - 1);
	const long long int sum_before = bit_sum->query(value - 1);

	ans += 1LL * qty_before * unhash[value] - sum_before;

	const int qty_after = bit_frequency->query(size) - bit_frequency->query(value);
	const long long int sum_after = bit_sum->query(size) - bit_sum->query(value);

	ans += sum_after - 1LL * qty_after * unhash[value];

	return ans;
}

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(0);
	std::cout.tie(0);

	int N, K;
	std::cin >> N >> K;

	std::vector<int> v(N);
	for (int &i : v)
	{
		std::cin >> i;
	}

	std::set<int> unique_numbers;
	for (const int i : v)
	{
		unique_numbers.insert(i);
	}

	int size = 0;
	std::map<int, int> hash;
	std::map<int, int> unhash;
	for (const int i : unique_numbers)
	{
		size += 1;
		hash[i] = size;
		unhash[size] = i;
	}

	FenwickTree<int> *bit_frequency = new FenwickTree<int>(size + 1);
	FenwickTree<long long int> *bit_sum = new FenwickTree<long long int>(size + 1);

	v.insert(v.begin(), v[0]);
	for (int i = 0; i < K; i += 1)
	{
		bit_frequency->update(hash[v[i]], +1);
		bit_sum->update(hash[v[i]], +v[i]);
	}

	for (int i = K; i <= N; i += 1)
	{
		bit_frequency->update(hash[v[i - K]], -1);
		bit_frequency->update(hash[v[i]], +1);

		bit_sum->update(hash[v[i - K]], -v[i - K]);
		bit_sum->update(hash[v[i]], +v[i]);

		const int value = solve(1, size, bit_frequency, (K + 1) >> 1);

		std::cout << other_solve(hash, unhash, size, bit_frequency, bit_sum, value) << ' ';
	}
	std::cout << std::endl;

	return 0;
}