#define _USE_MATH_DEFINES
#include <iostream>
#include <algorithm>
#include <climits>
#include <cmath>  
#include <random>

int clampWeightRange(int intValue) 
{
    return std::clamp(intValue, 1, INT_MAX);
}

bool guardLowerIntMaxSqrt(int intValue)
{
    return INT_MAX / intValue >= intValue; 
}

class BodyData
 {
    public:
        BodyData(int inputWeight, int inputHeight) 
        {
            weight = inputWeight;
            height = inputHeight;
        }
        double minWeight()
        {
            if(!guardLowerIntMaxSqrt(height)) { return INT_MAX; }
            double d = (double)height * (double)height * 7.2 / 10000.0;
            return clampWeightRange((int)d);
        }
        double maxWeight()
        {
            // TODO: 相対的な筋力・耐久値の高さに対して変動する
            if(!guardLowerIntMaxSqrt(height)) { return INT_MAX; }
            double d = (double)height * (double)height * 24.0 / 10000.0;
            return clampWeightRange((int)d);
        }
        double meanWeight() 
        {
            // TODO: 相対的な筋力・耐久値の高さに対して変動する
            double d = (0.5 * minWeight() + 0.5 * maxWeight() ) ;
            return clampWeightRange(d);
        }
        double prob()
        {
            double coeff = (weight - meanWeight()) / (maxWeight() - meanWeight());
            double cosValue = cos(coeff * M_PI) * -1;
            return std::clamp(cosValue, 0.0, 1.0);
        }
        int adjustDelta(int delta)
        {
            // (1- prob)の確率で補正なしでreturn
            std::random_device seed_gen;
            std::mt19937 engine(seed_gen());
            std::bernoulli_distribution dist(prob());
            if(!dist(engine)) { return delta; }

            // 与えられたdeltaに対して 痩せ&減量 || 肥満&増量ならdeltaは0
            // 逆の関係ならdeltaが二倍になる 
            if(std::signbit((double)delta) && std::signbit(weight - meanWeight())) {
                return 0;
            } else {
                return delta * 2;
            }
        }
        int adjustWeight(int delta) {
            // 本家仕様では“元の体重 * (100 + delta) / (100 + (増量 ? (+1) : (-1)))」”
            double diff = (100.0 + adjustDelta(delta)) / 100.0;
            double adjusted = weight * diff;

            // TODO: 例えば身長48cm,体重1kgだと身長を伸ばさない限り体重が増えないので対策する必要がある
            return clampWeightRange((int)adjusted);
        }
        
        
    private:
        int weight;
        int height;
};

int main() {
    std::cout << "weightdiff" << std::endl;
    BodyData bdata(1, 46);
    std::cout << "Min " << bdata.minWeight() << std::endl;
    std::cout << "Max " << bdata.maxWeight() << std::endl;
    std::cout << "Mean " << bdata.meanWeight() << std::endl;
    std::cout << "prob " << bdata.prob() << std::endl;
    std::cout << "adjust " << bdata.adjustDelta(10) << std::endl;
    std::cout << "adjust " << bdata.adjustWeight(10) << std::endl;

    return 0;
}