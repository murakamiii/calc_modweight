#include <iostream>
#include <algorithm>
#include <climits>

int clampWeightRange(int intValue) 
{
    return std::clamp(intValue, 1, INT_MAX);
}

bool assertLowerIntMaxSqrt(int intValue)
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

        std::string weightValue() 
        {
            return std::to_string(weight);
        }
        std::string heightValue() 
        {
            return std::to_string(height);
        }
        int bmi() 
        {
            double d = (double)weight / ((double)height * (double)height) * 10000.0;
            return (int)d;
        }
        int minWeight()
        {
            if(!assertLowerIntMaxSqrt(height)) { return INT_MAX; }
            double d = (double)height * (double)height * 7.2 / 10000.0;
            return clampWeightRange((int)d);
        }
        int maxWeight()
        {
            if(!assertLowerIntMaxSqrt(height)) { return INT_MAX; }
            double d = (double)height * (double)height * 24.0 / 10000.0;
            return clampWeightRange((int)d);
        }
        int meanWeight() 
        {
            double d = (0.5 * minWeight() + 0.5 * maxWeight() ) ;
            return clampWeightRange(d);
        }
    private:
        int weight;
        int height;
};

int main() {
    std::cout << "weightdiff" << std::endl;
    BodyData bdata(72, 2147483647);
    std::cout << bdata.heightValue() << std::endl;
    std::cout << bdata.weightValue() << std::endl;
    std::cout << bdata.bmi() << std::endl;
    std::cout << "Min " << bdata.minWeight() << std::endl;
    std::cout << "Max " << bdata.maxWeight() << std::endl;
    std::cout << "Mean " << bdata.meanWeight() << std::endl;
    return 0;
}