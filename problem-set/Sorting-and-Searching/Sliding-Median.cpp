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

	FenwickTree<int> *bit = new FenwickTree<int>(size + 1);

	for (int i = 0; i < K; i += 1)
	{
		bit->update(hash[v[i]], +1);
	}

	std::cout << unhash[solve(1, size, bit, (K + 1) >> 1)];
	for (int i = K; i < N; i += 1)
	{
		bit->update(hash[v[i - K]], -1);
		bit->update(hash[v[i]], +1);
		std::cout << ' ' << unhash[solve(1, size, bit, (K + 1) >> 1)];
	}
	std::cout << std::endl;

	return 0;
}