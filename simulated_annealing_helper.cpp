#include "modules/template.cpp"

/**
 * 焼きなまし法の温度計算などをまとめたヘルパークラス
 */
template <typename T, bool MAXIMIZE>
class SimulatedAnnealingHelper
{
    const Timer *timer;
    double get_temperature()
    {
        double elapsed = timer->get_process_time();
        double fraction = clamp(elapsed / timer->get_limit_time(), 0.0, 1.0);
        return T_initial * pow(T_final / T_initial, fraction);
    }

public:
    SimulatedAnnealingHelper(const Timer *timer) : timer(timer)
    {
        assert(0 < timer->get_limit_time());
    };

    double T_initial = 300.0;
    double T_final = 0.1;

    // SA の確率的受け入れを行う
    inline bool accept_prob(T current_score, T next_score)
    {
        T diff_score;

        if constexpr (MAXIMIZE)
        {
            diff_score = next_score - current_score;
        }
        else
        {
            diff_score = current_score - next_score;
        }

        if (0 < diff_score)
        {
            return true;
        }

        double prob = exp(diff_score / get_temperature());

        bool result = rand_engine.random_real(0, 1) < prob;

        /*
        if (diff_score < 0 && result)
        {
            cerr << timer->get_process_time() << "[ms] acceptProb" << endl;
        }*/

        return result;
    };
};