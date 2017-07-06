#include "ao/render/brep/ms.hpp"

namespace Kernel {

/*
 *      Edges are recorded on the following square
 *      c ----- d
 *      |       |   ^ Y
 *      |       |   |
 *      a-------b   ---> X
 */
SquareMarcher::Edge SquareMarcher::cases[16][2][2] = {
    {{NONE, NONE}, {NONE, NONE}},    // 0000
    {{UPPER, RIGHT}, {NONE, NONE}},  // 000d
    {{LEFT, UPPER}, {NONE, NONE}},   // 00c0
    {{LEFT, RIGHT}, {NONE, NONE}},   // 00cd
    {{RIGHT, LOWER}, {NONE, NONE}},  // 0b00
    {{UPPER, LOWER}, {NONE, NONE}},  // 0b0d
    {{RIGHT, LOWER}, {LEFT, UPPER}}, // 0bc0
    {{LEFT, LOWER}, {NONE, NONE}},   // 0bcd

    {{NONE, NONE}, {NONE, NONE}},    // a000
    {{RIGHT, UPPER}, {NONE, NONE}},  // a00d
    {{UPPER, LEFT}, {NONE, NONE}},   // a0c0
    {{RIGHT, LEFT}, {NONE, NONE}},   // a0cd
    {{LOWER, RIGHT}, {NONE, NONE}},  // ab00
    {{LOWER, UPPER}, {NONE, NONE}},  // ab0d
    {{LOWER, RIGHT}, {UPPER, LEFT}}, // abc0
    {{LOWER, LEFT}, {NONE, NONE}},   // abcd
};

uint8_t SquareMarcher::edges[4][2][2] = {
    {{0, 0}, {0, 1}}, // LEFT
    {{1, 0}, {1, 1}}, // RIGHT
    {{0, 1}, {1, 1}}, // UPPER
    {{0, 0}, {1, 0}}, // LOWER
};

void SquareMarcher::operator()(const std::array<XTree<2>*, 4>& ts)
{
    unsigned i=0;
    for (auto t : ts)
    {
        eval->set(t->vert3(), i++);
    }
    auto vs = eval->values(4);

    // Build up the bitmask for marching squares
    uint8_t mask = 0;
    for (unsigned i=0; i < 4; ++i)
    {
        mask |= (vs[i] < 0) << i;
    }
}

}   // namespace Kernel