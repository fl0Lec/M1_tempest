
#include "levels.hpp"

using namespace Engine;


const std::vector<Line2f> Level::basePlus{
    Line2f{Vect2f{ 0,    1},   Vect2f{ 0,  2}},
    Line2f{Vect2f{ 0.5,  1},   Vect2f{ 1,  2}},
    Line2f{Vect2f{ 0.5,  0.5}, Vect2f{ 1,  1}},
    Line2f{Vect2f{ 1,    0.5}, Vect2f{ 2,  1}},
    Line2f{Vect2f{ 1,    0},   Vect2f{ 2,  0}},
    Line2f{Vect2f{ 1,   -0.5}, Vect2f{ 2, -1}},
    Line2f{Vect2f{ 0.5, -0.5}, Vect2f{ 1, -1}},
    Line2f{Vect2f{ 0.5, -1},   Vect2f{ 1, -2}},
    Line2f{Vect2f{ 0,   -1},   Vect2f{ 0, -2}},
    Line2f{Vect2f{-0.5, -1},   Vect2f{-1, -2}},
    Line2f{Vect2f{-0.5, -0.5}, Vect2f{-1, -1}},
    Line2f{Vect2f{-1,   -0.5}, Vect2f{-2, -1}},
    Line2f{Vect2f{-1,    0},   Vect2f{-2,  0}},
    Line2f{Vect2f{-1,    0.5}, Vect2f{-2,  1}},
    Line2f{Vect2f{-0.5,  0.5}, Vect2f{-1,  1}},
    Line2f{Vect2f{-0.5,  1},   Vect2f{-1,  2}},
    Line2f{Vect2f{ 0,    1},   Vect2f{ 0,  2}}
};

const std::vector<Line2f> Level::baseSquare{
    Line2f{Vect2f{ 0,    1},    Vect2f{ 0,  2}},
    Line2f{Vect2f{ 0.25, 1},    Vect2f{ 1,  2}},
    Line2f{Vect2f{ 0.5,  1},    Vect2f{ 2,  2}},
    Line2f{Vect2f{ 0.5,  0.75}, Vect2f{ 2,  1}},
    Line2f{Vect2f{ 0.5,  0.5},  Vect2f{ 2,  0}},
    Line2f{Vect2f{ 0.5,  0.25}, Vect2f{ 2, -1}},
    Line2f{Vect2f{ 0.5,  0},    Vect2f{ 2, -2}},
    Line2f{Vect2f{ 0.25, 0},    Vect2f{ 1, -2}},
    Line2f{Vect2f{ 0,    0},    Vect2f{ 0, -2}},
    Line2f{Vect2f{-0.25, 0},    Vect2f{-1, -2}},
    Line2f{Vect2f{-0.5,  0},    Vect2f{-2, -2}},
    Line2f{Vect2f{-0.5,  0.25}, Vect2f{-2, -1}},
    Line2f{Vect2f{-0.5,  0.5},  Vect2f{-2,  0}},
    Line2f{Vect2f{-0.5,  0.75}, Vect2f{-2,  1}},
    Line2f{Vect2f{-0.5,  1},    Vect2f{-2,  2}},
    Line2f{Vect2f{-0.25, 1},    Vect2f{-1,  2}},
    Line2f{Vect2f{ 0,    1},    Vect2f{ 0,  2}}
};

const std::vector<Vect2f> Level::baseTriangle{
    Vect2f{-1.75, -2},
    Vect2f{-1.75, -1},
    Vect2f{-1.25, -1},
    Vect2f{-1.25,  0},
    Vect2f{-0.75,  0},
    Vect2f{-0.75,  1},
    Vect2f{-0.25,  1},
    Vect2f{-0.25,  2},
    Vect2f{ 0.25,  2},
    Vect2f{ 0.25,  1},
    Vect2f{ 0.75,  1},
    Vect2f{ 0.75,  0},
    Vect2f{ 1.25,  0},
    Vect2f{ 1.25,  -1},
    Vect2f{ 1.75,  -1},
    Vect2f{ 1.75,  -2}
};

const std::vector<Vect2f> Level::baseCircle{
    Vect2f{ 0,      -1},
    Vect2f{-0.4375, -0.9375},
    Vect2f{-0.75,   -0.75},
    Vect2f{-0.9375, -0.4375},
    Vect2f{-1,       0},
    Vect2f{-0.9375,  0.4375},
    Vect2f{-0.75,    0.75},
    Vect2f{-0.4375,  0.9375},
    Vect2f{ 0,       1},
    Vect2f{ 0.4375,  0.9375},
    Vect2f{ 0.75,    0.75},
    Vect2f{ 0.9375,  0.4375},
    Vect2f{ 1,       0},
    Vect2f{ 0.9375, -0.4375},
    Vect2f{ 0.75,   -0.75},
    Vect2f{ 0.4375, -0.9375},
    Vect2f{ 0,      -1}
};

const std::vector<float> Level::baseFlat{
    -1,
    -0.875,
    -0.75,
    -0.625,
    -0.5,
    -0.375,
    -0.25,
    -0.125,
     0,
     0.125,
     0.25,
     0.375,
     0.5,
     0.625,
     0.75,
     0.875,
     1
};

const std::vector<Vect2f> Level::baseStar{
    Vect2f{ 0,      -0.75},
    Vect2f{-0.375,  -1},
    Vect2f{-0.5625, -0.5625},
    Vect2f{-1,      -0.375},
    Vect2f{-0.75,    0},
    Vect2f{-1,       0.375},
    Vect2f{-0.5625,  0.5625},
    Vect2f{-0.375,   1},
    Vect2f{ 0,       0.75},
    Vect2f{ 0.375,   1},
    Vect2f{ 0.5625,  0.5625},
    Vect2f{ 1,       0.375},
    Vect2f{ 0.75,    0},
    Vect2f{ 1,      -0.375},
    Vect2f{ 0.5625, -0.5625},
    Vect2f{ 0.375,  -1},
    Vect2f{ 0,      -0.75}
};

std::vector<Line2f> Level::levelBasePoints(LevelType type)
{
    std::vector<Line2f> lines;

    switch(type)
    {
        case PLUS:
            lines = Level::basePlus;
            for(auto& line : lines)
            {
                line.first += Vect2f{0, 1.5};
                line.first *= 3.0f;
            }
            break;
        
        case SQUARE:
            lines = Level::baseSquare;
            for(auto& line : lines)
            {
                line.first += Vect2f{0, 1.5};
                line.first *= 4.0f;
            }
            break;

        case TRIANGLE:
            for(const auto& pt : Level::baseTriangle)
                lines.emplace_back(std::make_pair(
                    pt - Vect2f{0, 10.0f},
                    Vect2f{pt.x * 1.8f, pt.y}
                ));
            break;

        case CIRCLE:
            for(const auto& pt : Level::baseCircle)
                lines.emplace_back(std::make_pair(
                    pt + Vect2f{0, 8.0f},
                    Vect2f{pt.x * 1.6f, pt.y * 1.9f}
                ));
            break;

        case FLAT:
            for(const auto& val : Level::baseFlat)
                lines.emplace_back(std::make_pair(
                    Vect2f{val * 1.5f, -12.0f},
                    Vect2f{val * 2.5f, 1.7f}
                ));
            break;

        case STAR:
            for(const auto& pt : Level::baseStar)
                lines.emplace_back(std::make_pair(
                    (pt + Vect2f{0, 3.0f}) * 1.2f,
                    Vect2f{pt.x * 1.6f, pt.y * 1.9f}
                ));
            break;
    }

    return lines;
}
