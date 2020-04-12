#include <iostream>
#include <memory>

template <typename T>
class Value
{
public:
    Value() :
        prefix(0),
        suffix(0),
        total(0),
        best(0)
    {}

    Value(const T _prefix, const T _suffix, const T _total, const T _best) :
        prefix(_prefix),
        suffix(_suffix),
        total(_total),
        best(_best)
    {}

    static Value<T> merge(const Value<T> &a, const Value<T> &b)
    {
        const T prefix
            = std::max(a.prefix, std::max(a.total, a.total + b.prefix));

        const T suffix
            = std::max(b.suffix, std::max(b.total, b.total + a.suffix));

        const T total = a.total + b.total;

        const T between = a.suffix + b.prefix;

        T best = std::max(a.best, b.best);
        best = std::max(best, prefix);
        best = std::max(best, suffix);
        best = std::max(best, total);
        best = std::max(best, between);

        return Value<T>(prefix, suffix, total, best);
    }

    const T prefix;
    const T suffix;
    const T total;
    const T best;
};

template <typename T>
class Node
{
public:
    Node<T>(const int _lo, const int _hi) :
        lo(_lo),
        hi(_hi),
        l(nullptr),
        r(nullptr),
        value(new Value<T>())
    {
        if (this->lo != this->hi)
        {
            const int mid = lo + ((this->hi - this->lo) >> 1);

            this->l = std::make_unique<Node<T>>(this->lo, mid);
            this->r = std::make_unique<Node<T>>(mid + 1, this->hi);
        }
    }

    void update(const int index, const T new_value)
    {
        if (this->lo > index or this->hi < index)
        {
            return;
        }

        if (this->lo == index and this->hi == index)
        {

            this->value = std::make_unique<Value<T>>(new_value, new_value, new_value, new_value);
            return;
        }

        this->l->update(index, new_value);
        this->r->update(index, new_value);

        this->value = std::make_unique<Value<T>>(Value<T>::merge(*(this->l->value), *(this->r->value)));
    }

    Value<T> query(const int _lo, const int _hi)
    {
        if (this->lo > _hi or this->hi < _lo)
        {
            return Value<T>();
        }

        if (this->lo >= _lo and this->hi <= _hi)
        {
            return *(this->value);
        }

        const Value<T> &value_l = this->l->query(_lo, _hi);
        const Value<T> &value_r = this->r->query(_lo, _hi);

        return Value<T>::merge(value_l, value_r);
    }

private:
    const int lo;
    const int hi;
    std::unique_ptr<Node<T>> l;
    std::unique_ptr<Node<T>> r;
    std::unique_ptr<Value<T>> value;
};

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int N, M;
    std::cin >> N >> M;

    std::unique_ptr<Node<long long int>> segtree(new Node<long long int>(0, N - 1));

    for (int i = 0; i < N; i += 1)
    {
        int value;
        std::cin >> value;
        segtree->update(i, value);
    }

    while (M-- > 0)
    {
        int index, new_value;
        std::cin >> index >> new_value;
        segtree->update(index - 1, new_value);
        std::cout << segtree->query(0, N -1).best << std::endl;
    }

    return 0;
}