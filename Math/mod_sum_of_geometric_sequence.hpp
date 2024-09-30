template <class mint>
mint sum_of_geometric_sequence(mint a, mint r, long long n)
{
    assert(0 < n);

    if (n == 1)
    {
        return a;
    }

    mint x = sum_of_geometric_sequence(a, r, n / 2);

    mint ret = x + r.pow(n / 2) * x;
    if (n & 1)
    {
        ret = (a + r * ret);
    }

    return ret;
};