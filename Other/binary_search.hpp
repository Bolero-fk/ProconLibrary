#include <bits/stdc++.h>
using namespace std;

template <typename T>
enable_if_t<is_integral_v<T>, T>
bin_search(T ok, T ng, function<bool(T)> check)
{
    while (max(ok, ng) - min(ok, ng) > 1)
    {
        T mid = midpoint(ok, ng);
        (check(mid) ? ok : ng) = mid;
    }
    return ok;
}

template <typename T>
enable_if_t<is_floating_point_v<T>, T>
bin_search(T ok, T ng, function<bool(T)> check)
{
    // midpointが成立するように浮動小数型を整数型にbit_castするクラス
    class OrderedBitcastFloat
    {
    public:
        using UInt = conditional_t<sizeof(T) == 4, uint32_t, conditional_t<sizeof(T) == 8, uint64_t, void>>;
        static_assert(!is_same_v<UInt, void>, "T must be float(4), double(8)");

        T real;       // 元の実数
        UInt int_key; // マッピング整数

        OrderedBitcastFloat(T x) : real(x), int_key(real_to_int_key(x)) {}
        OrderedBitcastFloat(UInt u) : real(int_key_to_real(u)), int_key(u) {}

    private:
        static constexpr UInt msb()
        {
            return UInt(1) << (8 * sizeof(UInt) - 1);
        }

        // 実数 → マッピング整数
        static UInt real_to_int_key(T x)
        {
            UInt bits = bit_cast<UInt>(x);
            if (bits & msb())
            {
                // 符号ビット＝1（負数領域）：反転
                return ~bits;
            }
            else
            {
                // 符号ビット＝0（正数領域）：MSB bit を足してオフセット
                return bits | msb();
            }
        }

        // マッピング整数 → 実数
        static T int_key_to_real(UInt u)
        {
            UInt bits;
            if (u & msb())
            {
                // MSB=1 → 正数領域：MSBを落とす
                bits = u & ~msb();
            }
            else
            {
                // MSB=0 → 負数領域：反転を戻す
                bits = ~u;
            }
            return bit_cast<T>(bits);
        }
    };

    OrderedBitcastFloat temp_ok(ok), temp_ng(ng);

    while (max(temp_ok.int_key, temp_ng.int_key) - min(temp_ok.int_key, temp_ng.int_key) > 1)
    {
        OrderedBitcastFloat mid(midpoint(temp_ok.int_key, temp_ng.int_key));
        (check(mid.real) ? temp_ok : temp_ng) = mid;
    }

    return temp_ok.real;
}
