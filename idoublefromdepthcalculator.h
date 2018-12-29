#ifndef IDOUBLEFROMDEPTHCALCULATOR_H
#define IDOUBLEFROMDEPTHCALCULATOR_H


class IDoubleFromDepthCalculator
{
public:
    IDoubleFromDepthCalculator() = default;
    virtual ~IDoubleFromDepthCalculator() = default;

    virtual double Calculate(int depth) = 0;
};

#endif // IDOUBLEFROMDEPTHCALCULATOR_H
