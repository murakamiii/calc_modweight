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
            if(!guardLowerIntMaxSqrt(height)) { return INT_MAX; }
            double d = (double)height * (double)height * 24.0 / 10000.0;
            return clampWeightRange((int)d);
        }
        double meanWeight() 
        {
            double d = (0.5 * minWeight() + 0.5 * maxWeight() ) ;
            return clampWeightRange(d);
        }
        double prob()
        {
            double coeff = (weight - meanWeight()) / (maxWeight() - meanWeight());
            double cosValue = cos(coeff * M_PI) * -1;
            return std::clamp(cosValue, 0.0, 1.0);
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