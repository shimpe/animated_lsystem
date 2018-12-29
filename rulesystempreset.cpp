#include "rulesystempreset.h"
#include <QColor>
#include "rule.h"
#include "idoublefromdepthcalculator.h"
#include "lineardepthvaluescaler.h"
#include "constantvalueprovider.h"

RuleSystemPreset::RuleSystemPreset()
{
}

RuleSystem RuleSystemPreset::CreateRuleSystem(RSP type, int NoOfIterations)
{
    RuleSystem rs;
    switch (type)
    {
        case HEIGHWAY_DRAGON:
        {
            rs.setAxiom("FX");
            rs.addRule(Rule("X","X+YF+", 1.0));
            rs.addRule(Rule("Y","-FX-Y", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 12 : NoOfIterations);
        }
        break;

        case RANDOMCIRCLE:
        {
            rs.setAxiom("FX");
            rs.addRule(Rule("X", "X+YF-YX", 1.0));
            rs.addRule(Rule("Y", "-FX-Y", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 6 : NoOfIterations);
        }
        break;

        case RANDOMCIRCLE_COLOR:
        {
            rs.setAxiom("FX");
            rs.addRule(Rule("X", "X+C0YF-YC1X", 1.0));
            rs.addRule(Rule("Y", "-FC2X-Y", 1.0));

            QColor red("red");
            red.setAlphaF(0.5);
            QColor green("green");
            red.setAlphaF(0.5);
            QColor blue("blue");
            red.setAlphaF(0.5);
            rs.addColor(red);
            rs.addColor(green);
            rs.addColor(blue);
            rs.setNoOfIterations(NoOfIterations == -1 ? 4 : NoOfIterations);
            rs.setThicknessCalculator(std::unique_ptr<LinearDepthValueScaler>(new LinearDepthValueScaler(DEEPER_IS_LESS, 10, 0.5, 0)));
            rs.setSegmentLengthCalculator(std::unique_ptr<ConstantValueProvider>(new ConstantValueProvider(10)));
        }
        break;

        case KOCHCURVE:
        {
            rs.setAxiom("-F");
            rs.addRule(Rule("F","F+F-F-F+F",1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 4 : NoOfIterations);
        }
        break;

        case SIERPINSKY_CURVED:
        {
            rs.setAxiom("A");
            rs.addRule(Rule("A","B-A-B",1.0));
            rs.addRule(Rule("B","A+B+A",1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 7 : NoOfIterations);
        }
        break;

        case SIERPINSKY_TRIANGLES:
        {
            rs.setAxiom("F-G-G");
            rs.addRule(Rule("F","F-G+F+G-F",1.0));
            rs.addRule(Rule("G","GG",1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 6 : NoOfIterations);
        }
        break;

        case DRAGON:
        {
            rs.setAxiom("FX");
            rs.addConstant('F');
            rs.addRule(Rule("X","X+YF",1.0));
            rs.addRule(Rule("Y","FX-Y",1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 10 : NoOfIterations);
        }
        break;

        case KEVS_TREE:
        {
            rs.setAxiom("F");
            rs.addRule(Rule("F", "C0FF-[C1-F+F+F]+[C2+F-F-F]", 1.0));
            rs.addColor(QColor::fromRgb(140, 80, 60, static_cast<int>(0.75*255)));
            rs.addColor(QColor::fromRgb(24, 180, 24, static_cast<int>(0.75*255)));
            rs.addColor(QColor::fromRgb(48, 220, 48, static_cast<int>(0.5*255)));
            rs.addColor(QColor::fromRgb(64, 255, 64, static_cast<int>(0.5*255)));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);
        }
        break;

        case KEVS_WISPY_TREE:
        {
            rs.setAxiom("FX");
            rs.addRule(Rule("F", "C0FF-[C1-F+F]+[C2+F-F]", 1.0));
            rs.addRule(Rule("X", "C0FF+[C1+F]+[C3-F]", 1.0));
            rs.addColor(QColor::fromRgb(140, 80, 60, static_cast<int>(0.75*255)));
            rs.addColor(QColor::fromRgb(24, 180, 24, static_cast<int>(0.75*255)));
            rs.addColor(QColor::fromRgb(48, 220, 48, static_cast<int>(0.5*255)));
            rs.addColor(QColor::fromRgb(64, 255, 64, static_cast<int>(0.5*255)));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);
        }
        break;

        case KOCH_SNOWFLAKE:
        {
            rs.setAxiom("F++F++F");
            rs.addConstant('X');
            rs.addRule(Rule("F", "F-F++F-F", 1.0));
            rs.addRule(Rule("X", "FF", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 4 : NoOfIterations);
        }
        break;

        case PENTAGON_LAKE:
        {
            rs.setAxiom("F-F-F-F-F");
            rs.addRule(Rule("F", "F-F++F+F-F-F", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 4 : NoOfIterations);
        }
        break;

        case SIERPINSKY_CARPET:
        {
            rs.setAxiom("F");
            rs.addRule(Rule("F", "F+F-F-F-G+F+F+F-F", 1.0));
            rs.addRule(Rule("G", "GGG", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 4 : NoOfIterations);
        }
        break;

        case PENROSE_TILING:
        {
            rs.setAxiom("[7]++[7]++[7]++[7]++[7]");
            rs.addConstant('6');
            rs.addConstant('7');
            rs.addConstant('8');
            rs.addConstant('9');
            rs.addRule(Rule("6", "81++91----71[-81----61]++", 1.0));
            rs.addRule(Rule("7", "+81--91[---61--71]+", 1.0));
            rs.addRule(Rule("8", "-61++71[+++81++91]-", 1.0));
            rs.addRule(Rule("9", "--81++++61[+91++++71]--71", 1.0));
            rs.addRule(Rule("1","",1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);
        }
        break;

        case PENROSE_TILING_COLOR:
        {
            rs.setAxiom("[C0B]++[C1B]++[C2B]++[C3B]++[C0B]");
            rs.addConstant('A');
            rs.addConstant('B');
            rs.addConstant('Z');
            rs.addConstant('D');
            rs.addColor(QColor::fromRgb(140, 80, 60, static_cast<int>(0.5*255)));  // brown
            rs.addColor(QColor::fromRgb(24, 180, 24, static_cast<int>(0.75*255))); // green
            rs.addColor(QColor::fromRgb(255, 211, 0, static_cast<int>(0.75*255))); // yellow
            rs.addColor(QColor::fromRgb(64, 64, 255, static_cast<int>(0.5*255)));  // blue
            rs.addRule(Rule("A", "ZE++DE----BE[-ZE----AE]++", 1.0));
            rs.addRule(Rule("B", "+ZE--DE[---AE--BE]+", 1.0));
            rs.addRule(Rule("Z", "-AE++BE[+++ZE++DE]-", 1.0));
            rs.addRule(Rule("D", "--ZE++++AE[+DE++++BE]--BE", 1.0));
            rs.addRule(Rule("E","",1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);
        }
        break;

        case EYE_OF_SAURON:
        {
            rs.setAxiom("X+X+X");
            rs.addRule(Rule("X","X+[X-X]+X", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);
        }
        break;

        default:
        {
            return rs;
        }
    }
    return rs;
}

double RuleSystemPreset::GetRecommendedAngle(RSP type) const
{
    switch(type)
    {
        case HEIGHWAY_DRAGON:
            return 90;
        case RANDOMCIRCLE:
            return 53;
        case KOCHCURVE:
            return 90;
        case SIERPINSKY_CURVED:
            return 60;
        case SIERPINSKY_TRIANGLES:
            return 120;
        case DRAGON:
            return 90;
        case KEVS_TREE:
            return 22;
        case KEVS_WISPY_TREE:
            return 25;
        case KOCH_SNOWFLAKE:
            return 60;
        case PENTAGON_LAKE:
            return 72;
        case SIERPINSKY_CARPET:
            return 90;
        case PENROSE_TILING:
            return 36;
        case PENROSE_TILING_COLOR:
            return 36;
        case RANDOMCIRCLE_COLOR:
            return 53;
        case EYE_OF_SAURON:
            return 30;
    }

    return 0.0;
}
