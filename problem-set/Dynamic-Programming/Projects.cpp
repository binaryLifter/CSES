#include <bits/stdc++.h>

template <typename T>
class FenwickTree
{
public:
	FenwickTree(const int size)
	{
		this->v = std::vector<T>(size, 0);
	}

	void update(const int index, const T value)
	{
		for (int i = index; i < int(this->v.size()); i += i & -i)
		{
			this->v[i] = std::max(this->v[i], value);
		}
	}

	T query(const int index)
	{
		T ans = 0;
		for (int i = index; i > 0; i -= i & -i)
		{
			ans = std::max(ans, this->v[i]);
		}
		return ans;
	}

private:
	std::vector<T> v;
};

class Project
{
public:
	Project(const int s, const int f, const int r) : start(s), finish(f), reward(r)
	{
	}

	int start, finish, reward;

	bool operator<(const Project &other) const
	{
		return this->start < other.start;
	}
};

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(0);
	std::cout.tie(0);

	int N;
	std::cin >> N;

	std::set<int> set;

	std::vector<Project> v;
	for (int i = 0; i < N; i += 1)
	{
		int start, finish, reward;
		std::cin >> start >> finish >> reward;

		set.insert(start);
		set.insert(finish);

		v.push_back(Project(start, finish, reward));
	}

	int size = 0;
	std::map<int, int> hash;
	for (const int i : set)
	{
		size += 1;
		hash[i] = size;
	}

	std::sort(v.begin(), v.end());

	std::unique_ptr<FenwickTree<long long int>> bit(new FenwickTree<long long int>(size + 1));

	for (const auto &i : v)
	{
		const int start = hash[i.start];
		const int finish = hash[i.finish];
		bit->update(finish, bit->query(start - 1) + i.reward);
	}

	std::cout << bit->query(size) << std::endl;

	return 0;
}