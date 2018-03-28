#define _USE_MATH_DEFINES
#include <iostream>
#include <algorithm>
#include <climits>
#include <cmath>  

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
        int adjustWeight()
        {
            // TODO:
            // 与えられたdeltaに対して 痩せ&減量 || 肥満&増量ならdeltaが区間[0,delta]の一様分布で選びなおし
            // 逆の関係ならdeltaが二倍になる 

            // 元の体重 * (100 + delta) / (100 + (増量 ? (+1) : (-1)))

            // TODO: 0以下なら1を返す
            return 1; 
        }
        
        
    private:
        int weight;
        int height;
};

int main() {
    std::cout << "weightdiff" << std::endl;
    BodyData bdata(22, 181);
    std::cout << "Min " << bdata.minWeight() << std::endl;
    std::cout << "Max " << bdata.maxWeight() << std::endl;
    std::cout << "Mean " << bdata.meanWeight() << std::endl;
    std::cout << "prob " << bdata.prob() << std::endl;
    return 0;
}