#include "rulesystempreset.h"
#include <QColor>
#include "rule.h"
#include "idoublefromdepthcalculator.h"
#include "lineardepthvaluescaler.h"
#include "constantvalueprovider.h"
#include <QMap>
#include <QChar>
#include "charactervaluelookup.h"

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
            rs.setThicknessCalculator(std::unique_ptr<LinearDepthValueScaler>(new LinearDepthValueScaler(false, DEEPER_IS_LESS, 10, 0.5, 0)));
            rs.setSegmentLengthCalculator(std::unique_ptr<ConstantValueProvider>(new ConstantValueProvider(false, 10)));
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
            rs.addRule(Rule("X","C2X+[X-C0X]+C1X", 1.0));
            rs.addColor(QColor::fromRgb(140, 80, 60, static_cast<int>(0.5*255)));  // brown
            rs.addColor(QColor::fromRgb(24, 180, 24, static_cast<int>(0.75*255))); // green
            rs.addColor(QColor::fromRgb(255, 211, 0, static_cast<int>(0.75*255))); // yellow
            rs.addColor(QColor::fromRgb(64, 64, 255, static_cast<int>(0.5*255)));  // blue
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);
        }
        break;

        case FERN_CLAW:
        {
            rs.setAxiom("X+X-X");
            rs.addRule(Rule("X", "X+[X+X]-X", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);
            rs.setThicknessCalculator(std::unique_ptr<ConstantValueProvider>(new ConstantValueProvider(false, 3)));
        }
        break;

        case NECKLACE:
        {
            rs.setAxiom("X+Y-X");
            rs.addRule(Rule("X", "X+X+X-X", 0.9));
            rs.addRule(Rule("Y", "Y-Y-Y+Y", 0.7));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);
            rs.setAngleIncrementPerSecond(0.2);
            rs.setThicknessCalculator(std::unique_ptr<ConstantValueProvider>(new ConstantValueProvider(false, 3)));
        }
        break;

        case TWO_EYES_OF_SAURON:
        {
            rs.setAxiom("X+Y-X");
            rs.addRule(Rule("X", "X+X+[X]-X", 1.0));
            rs.addRule(Rule("Y", "Y-[Y]-Y+Y", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);
            rs.setAngleIncrementPerSecond(0.1);
            rs.setThicknessCalculator(std::unique_ptr<ConstantValueProvider>(new ConstantValueProvider(false, 2)));
        }
        break;

        case DANDELIONS:
        {
            rs.setAxiom("X+Y-X");
            rs.addRule(Rule("X", "X+C0X+[Y]-C1X", 1.0));
            rs.addRule(Rule("Y", "Y-[Y]-C2Y+C3X", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);
            rs.setAngleIncrementPerSecond(0.3);
            rs.setThicknessCalculator(std::unique_ptr<ConstantValueProvider>(new ConstantValueProvider(false, 2)));
            QMap<QChar, double> LengthForSymbol;
            LengthForSymbol['X'] = 10;
            LengthForSymbol['Y'] = -5;
            rs.setSegmentLengthCalculator(std::unique_ptr<CharacterValueLookup>(new CharacterValueLookup(LengthForSymbol, 10)));
            rs.addColor(QColor::fromRgb(140, 80, 60, static_cast<int>(0.5*255)));  // brown
            rs.addColor(QColor::fromRgb(24, 180, 24, static_cast<int>(0.75*255))); // green
            rs.addColor(QColor::fromRgb(255, 211, 0, static_cast<int>(0.75*255))); // yellow
            rs.addColor(QColor::fromRgb(64, 64, 255, static_cast<int>(0.5*255)));  // blue
        }
        break;

        case ABSTRACT_DANCE:
        {
            rs.setAxiom("X+Y-X");
            rs.addRule(Rule("X", "X+C0X+[Y]-C1X", 1.0));
            rs.addRule(Rule("Y", "Y-[Y]-C2Y+C3X", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);
            rs.setAngleIncrementPerSecond(0.4);
            QMap<QChar, double> ThicknessForSymbol;
            ThicknessForSymbol['X'] = 6;
            ThicknessForSymbol['Y'] = 0;
            rs.setThicknessCalculator(std::unique_ptr<CharacterValueLookup>(new CharacterValueLookup(ThicknessForSymbol, 0)));
            QMap<QChar, double> LengthForSymbol;
            LengthForSymbol['X'] = 1;
            LengthForSymbol['Y'] = -15;
            rs.setSegmentLengthCalculator(std::unique_ptr<CharacterValueLookup>(new CharacterValueLookup(LengthForSymbol, 10)));
            rs.addColor(QColor::fromRgb(140, 80, 60, static_cast<int>(0.5*255)));  // brown
            rs.addColor(QColor::fromRgb(24, 180, 24, static_cast<int>(0.75*255))); // green
            rs.addColor(QColor::fromRgb(255, 211, 0, static_cast<int>(0.75*255))); // yellow
            rs.addColor(QColor::fromRgb(64, 64, 255, static_cast<int>(0.5*255)));  // blue
        }
        break;

        case KOLAM_PATTERN:
        {
            rs.setAxiom("AAAA");
            rs.addRule(Rule("A","X+X+X+X+X+X+",1.0));
            rs.addRule(Rule("X","[F+F+F+F[---X-Y]+++++F++++++++F-F-F-F]",1.0));
            rs.addRule(Rule("Y","[F+F+F+F[---Y]+++++F++++++++F-F-F-F]",1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);
        }
        break;

        case KOCH_ISLAND:
        {
            rs.setAxiom("F-F-F-F");
            rs.addRule(Rule("F","F-f+FF-F-FF-Ff-FF+f-FF+F+FF+Ff+FFF",1.0));
            rs.addRule(Rule("f", "ffffff", 5.0));
            rs.setThicknessCalculator(std::unique_ptr<ConstantValueProvider>(new ConstantValueProvider(false, 0)));
            rs.setNoOfIterations(NoOfIterations == -1 ? 3 : NoOfIterations);
            rs.setAngleIncrementPerSecond(3.0);
        }
        break;

        case PENTAPLEXITY:
        {
            rs.setAxiom("F++F++F++F++F");
            rs.addRule(Rule("F", "F++F++F|F-F++F", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 3 : NoOfIterations);
            rs.setAngleIncrementPerSecond(0.01);
            rs.setInitialAnimationAngle(getRecommendedAngle(PENTAPLEXITY)-0.3);
        }
        break;
    }
    return rs;
}

double RuleSystemPreset::getRecommendedAngle(RSP type) const
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
        case FERN_CLAW:
            return 80;
        case NECKLACE:
            return 89;
        case TWO_EYES_OF_SAURON:
            return 35;
        case DANDELIONS:
            return 40;
        case ABSTRACT_DANCE:
            return 40;
        case KOLAM_PATTERN:
            return 15;
        case KOCH_ISLAND:
            return 90;
        case PENTAPLEXITY:
            return 36;
    }

    return 0.0;
}
