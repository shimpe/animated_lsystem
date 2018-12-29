#ifndef IDOUBLEFROMDEPTHCALCULATOR_H
#define IDOUBLEFROMDEPTHCALCULATOR_H


class IDoubleFromDepthCalculator
{
public:
    IDoubleFromDepthCalculator(bool ScaleWithZoom=true);
    virtual ~IDoubleFromDepthCalculator() = default;

    virtual double Calculate(int depth) = 0;

    bool ScaleWithZoom() const;
    void setScaleWithZoom(bool ScaleWithZoom);

private:
    bool m_ScaleWithZoom;
};

#endif // IDOUBLEFROMDEPTHCALCULATOR_H
