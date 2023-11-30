/// @brief a * bの結果がmaxを超えるかどうかの判定をする(オーバーフローの判定)
/// @param a
/// @param b
/// @return
bool is_multiplication_overflow(long long a, long long b, long long limit)
{
    return (limit / a) < b;
}