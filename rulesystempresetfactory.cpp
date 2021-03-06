#include "rulesystempreset.h"
#include <QColor>
#include "rule.h"
#include "idoublefromdepthcalculator.h"
#include "lineardepthvaluescaler.h"
#include "constantvalueprovider.h"
#include <QMap>
#include <QChar>
#include "charactervaluelookup.h"
#include "renderhints.h"


RuleSystemPresetFactory::RuleSystemPresetFactory()
{
}

LSystemPreset RuleSystemPresetFactory::CreateRuleSystemPreset(RSP type, int NoOfIterations)
{
    RuleSystem rs;
    RenderHints rh;
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
            rs.setNoOfIterations(NoOfIterations == -1 ? 4 : NoOfIterations);

            QColor red("red");
            red.setAlphaF(0.5);
            QColor green("green");
            red.setAlphaF(0.5);
            QColor blue("blue");
            red.setAlphaF(0.5);
            rh.addColor(red);
            rh.addColor(green);
            rh.addColor(blue);
            rh.setThicknessCalculator(std::make_shared<LinearDepthValueScaler>(false, DEEPER_IS_LESS, 10, 0.5, 0));
            rh.setSegmentLengthCalculator(std::make_shared<ConstantValueProvider>(false, 10));
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
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);

            rh.addColor(QColor::fromRgb(140, 80, 60, static_cast<int>(0.75*255)));
            rh.addColor(QColor::fromRgb(24, 180, 24, static_cast<int>(0.75*255)));
            rh.addColor(QColor::fromRgb(48, 220, 48, static_cast<int>(0.5*255)));
            rh.addColor(QColor::fromRgb(64, 255, 64, static_cast<int>(0.5*255)));
        }
        break;

        case KEVS_WISPY_TREE:
        {
            rs.setAxiom("FX");
            rs.addRule(Rule("F", "C0FF-[C1-F+F]+[C2+F-F]", 1.0));
            rs.addRule(Rule("X", "C0FF+[C1+F]+[C3-F]", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);

            rh.addColor(QColor::fromRgb(140, 80, 60, static_cast<int>(0.75*255)));
            rh.addColor(QColor::fromRgb(24, 180, 24, static_cast<int>(0.75*255)));
            rh.addColor(QColor::fromRgb(48, 220, 48, static_cast<int>(0.5*255)));
            rh.addColor(QColor::fromRgb(64, 255, 64, static_cast<int>(0.5*255)));

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
            rs.addRule(Rule("A", "ZE++DE----BE[-ZE----AE]++", 1.0));
            rs.addRule(Rule("B", "+ZE--DE[---AE--BE]+", 1.0));
            rs.addRule(Rule("Z", "-AE++BE[+++ZE++DE]-", 1.0));
            rs.addRule(Rule("D", "--ZE++++AE[+DE++++BE]--BE", 1.0));
            rs.addRule(Rule("E","",1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);

            rh.addColor(QColor::fromRgb(140, 80, 60, static_cast<int>(0.5*255)));  // brown
            rh.addColor(QColor::fromRgb(24, 180, 24, static_cast<int>(0.75*255))); // green
            rh.addColor(QColor::fromRgb(255, 211, 0, static_cast<int>(0.75*255))); // yellow
            rh.addColor(QColor::fromRgb(64, 64, 255, static_cast<int>(0.5*255)));  // blue
        }
        break;

        case EYE_OF_SAURON:
        {
            rs.setAxiom("X+X+X");
            rs.addRule(Rule("X","C2X+[X-C0X]+C1X", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);

            rh.addColor(QColor::fromRgb(140, 80, 60, static_cast<int>(0.5*255)));  // brown
            rh.addColor(QColor::fromRgb(24, 180, 24, static_cast<int>(0.75*255))); // green
            rh.addColor(QColor::fromRgb(255, 211, 0, static_cast<int>(0.75*255))); // yellow
            rh.addColor(QColor::fromRgb(64, 64, 255, static_cast<int>(0.5*255)));  // blue
        }
        break;

        case FERN_CLAW:
        {
            rs.setAxiom("X+X-X");
            rs.addRule(Rule("X", "X+[X+X]-X", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);

            rh.setThicknessCalculator(std::make_shared<ConstantValueProvider>(false, 3));
        }
        break;

        case NECKLACE:
        {
            rs.setAxiom("X+Y-X");
            rs.addRule(Rule("X", "X+X+X-X", 0.9));
            rs.addRule(Rule("Y", "Y-Y-Y+Y", 0.7));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);

            rh.setAngleIncrementPerSecond(0.2);
            rh.setThicknessCalculator(std::make_shared<ConstantValueProvider>(false, 3));
        }
        break;

        case TWO_EYES_OF_SAURON:
        {
            rs.setAxiom("X+Y-X");
            rs.addRule(Rule("X", "X+X+[X]-X", 1.0));
            rs.addRule(Rule("Y", "Y-[Y]-Y+Y", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);

            rh.setAngleIncrementPerSecond(0.1);
            rh.setThicknessCalculator(std::make_shared<ConstantValueProvider>(false, 2));
        }
        break;

        case DANDELIONS:
        {
            rs.setAxiom("X+Y-X");
            rs.addRule(Rule("X", "X+C0X+[Y]-C1X", 1.0));
            rs.addRule(Rule("Y", "Y-[Y]-C2Y+C3X", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);

            rh.setAngleIncrementPerSecond(0.1);
            rh.setThicknessCalculator(std::make_shared<ConstantValueProvider>(false, 2));
            QMap<QChar, double> LengthForSymbol;
            LengthForSymbol['X'] = 10;
            LengthForSymbol['Y'] = -5;
            rh.setSegmentLengthCalculator(std::make_shared<CharacterValueLookup>(LengthForSymbol, 10));
            rh.addColor(QColor::fromRgb(140, 80, 60, static_cast<int>(0.5*255)));  // brown
            rh.addColor(QColor::fromRgb(24, 180, 24, static_cast<int>(0.75*255))); // green
            rh.addColor(QColor::fromRgb(255, 211, 0, static_cast<int>(0.75*255))); // yellow
            rh.addColor(QColor::fromRgb(64, 64, 255, static_cast<int>(0.5*255)));  // blue
        }
        break;

        case ABSTRACT_DANCE:
        {
            rs.setAxiom("X+Y-X");
            rs.addRule(Rule("X", "X+C0X+[Y]-C1X", 1.0));
            rs.addRule(Rule("Y", "Y-[Y]-C2Y+C3X", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);

            rh.setAngleIncrementPerSecond(0.1);
            QMap<QChar, double> ThicknessForSymbol;
            ThicknessForSymbol['X'] = 6;
            ThicknessForSymbol['Y'] = 0;
            rh.setThicknessCalculator(std::make_shared<CharacterValueLookup>(ThicknessForSymbol, 0));
            QMap<QChar, double> LengthForSymbol;
            LengthForSymbol['X'] = 1;
            LengthForSymbol['Y'] = -15;
            rh.setSegmentLengthCalculator(std::make_shared<CharacterValueLookup>(LengthForSymbol, 10));
            rh.addColor(QColor::fromRgb(140, 80, 60, static_cast<int>(0.5*255)));  // brown
            rh.addColor(QColor::fromRgb(24, 180, 24, static_cast<int>(0.75*255))); // green
            rh.addColor(QColor::fromRgb(255, 211, 0, static_cast<int>(0.75*255))); // yellow
            rh.addColor(QColor::fromRgb(64, 64, 255, static_cast<int>(0.5*255)));  // blue
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
            rs.setNoOfIterations(NoOfIterations == -1 ? 3 : NoOfIterations);

            rh.setThicknessCalculator(std::make_shared<ConstantValueProvider>(false, 0));
            rh.setAngleIncrementPerSecond(3.0);
        }
        break;

        case PENTAPLEXITY:
        {
            rs.setAxiom("F++F++F++F++F");
            rs.addRule(Rule("F", "F++F++F|F-F++F", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 3 : NoOfIterations);

            rh.setAngleIncrementPerSecond(0.01);
            rh.setInitialAnimationAngle(getRecommendedAngle(PENTAPLEXITY)-0.3);
        }
        break;

        case STARRY_NECKLACE:
        {
            rs.setAxiom("C0X+C0X+C1X+C2X+C3X+C4X+C4X+C5X+C6X+C7X+C8X+C9X");
            rs.addRule(Rule("X", "Y-Z", 1.0));
            rs.addRule(Rule("Y", "--Z+X-Y", 1.0));
            rs.addRule(Rule("Z", "X-Y|-X", 1.0));
            rs.setNoOfIterations(NoOfIterations == -1 ? 5 : NoOfIterations);

            rh.setInitialAnimationAngle(0);
            rh.setAngleIncrementPerSecond(0.1);

            rh.addColor(QColor::fromRgb(94,79,162, 127));
            rh.addColor(QColor::fromRgb(108,85,155, 127));
            rh.addColor(QColor::fromRgb(122,92,149, 127));
            rh.addColor(QColor::fromRgb(136,98,142, 127));
            rh.addColor(QColor::fromRgb(150,104,135, 127));
            rh.addColor(QColor::fromRgb(164,110,129, 127));
            rh.addColor(QColor::fromRgb(177,117,122, 127));
            rh.addColor(QColor::fromRgb(191,123,116, 127));
            rh.addColor(QColor::fromRgb(205,129,109, 127));
            rh.addColor(QColor::fromRgb(219,135,102, 127));
            rh.addColor(QColor::fromRgb(233,142,96, 127));
            rh.addColor(QColor::fromRgb(247,148,89, 127));

            rh.setThicknessCalculator(std::make_shared<ConstantValueProvider>(false, 10));

        }
        break;
    }
    return LSystemPreset(rs, rh);
}

double RuleSystemPresetFactory::getRecommendedAngle(RSP type) const
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
        case STARRY_NECKLACE:
            return 0;
    }

    return 0.0;
}
