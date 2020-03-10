#include <bits/stdc++.h>

class Node
{
public:
	Node(const int L, const int R) : lo(L),
									 hi(R),
									 value(0),
									 lazy_add(0),
									 lazy_set(0),
									 l(nullptr),
									 r(nullptr)
	{
		if (L != R)
		{
			const int mid = this->lo + ((this->hi - this->lo) >> 1);
			this->l = std::make_unique<Node>(L, mid);
			this->r = std::make_unique<Node>(mid + 1, R);
		}
	}

	void update(const int L, const int R, const int x, const int operation)
	{
		this->propagate();

		if (this->lo > R or this->hi < L)
		{
			return;
		}

		if (this->lo >= L and this->hi <= R)
		{
			if (operation == 2)
			{
				this->lazy_add = 0;
				this->lazy_set = x;
			}
			else
			{
				this->lazy_add += x;
			}

			this->propagate();
			return;
		}

		this->l->update(L, R, x, operation);
		this->r->update(L, R, x, operation);

		this->value = this->l->value + this->r->value;
	}

	long long int query(const int L, const int R)
	{
		this->propagate();

		if (this->lo > R or this->hi < L)
		{
			return 0LL;
		}

		if (this->lo >= L and this->hi <= R)
		{
			return this->value;
		}

		return this->l->query(L, R) + this->r->query(L, R);
	}

private:
	void propagate()
	{
		if (this->lazy_set)
		{
			this->value = (1LL * (this->hi - this->lo + 1) * this->lazy_set);

			if (this->lo != this->hi)
			{
				this->l->lazy_set = this->lazy_set;
				this->l->lazy_add = 0;

				this->r->lazy_set = this->lazy_set;
				this->r->lazy_add = 0;
			}

			this->lazy_set = 0;
		}

		if (this->lazy_add)
		{
			this->value += (1LL * (this->hi - this->lo + 1) * this->lazy_add);

			if (this->lo != this->hi)
			{
				this->l->lazy_add += this->lazy_add;
				this->r->lazy_add += this->lazy_add;
			}

			this->lazy_add = 0;
		}
	}

	int lo;
	int hi;
	long long int value;
	long long int lazy_add;
	long long int lazy_set;
	std::unique_ptr<Node> l;
	std::unique_ptr<Node> r;
};

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	int N, Q;
	std::cin >> N >> Q;

	std::unique_ptr<Node> segtree{new Node(0, N - 1)};

	for (int i = 0; i < N; i += 1)
	{
		int value;
		std::cin >> value;

		segtree->update(i, i, value, 2);
	}

	for (int i = 0; i < Q; i += 1)
	{
		int operation;
		std::cin >> operation;

		if (operation != 3)
		{
			int a, b, x;
			std::cin >> a >> b >> x;
			segtree->update(a - 1, b - 1, x, operation);
		}
		else
		{
			int a, b;
			std::cin >> a >> b;
			std::cout << segtree->query(a - 1, b - 1) << std::endl;
		}
	}

	return 0;
}
