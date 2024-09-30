bool is_multiplication_overflow(long long a, long long b, long long limit)
{
    return a == 0 ? false : (limit / a) < b;
}