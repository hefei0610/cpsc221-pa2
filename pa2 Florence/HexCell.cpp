#include "HexCell.h"

#include <cmath>

HexCell::HexCell(int Q, int R) {
    /**
     * @todo Your code here!
     */
    q = Q;
    r = R;
    path_dist_from_start = 0;
    for (int i = 0; i < 6; i++) {
        neighbours[i] = nullptr;
        links[i] = nullptr;
    }
}

/**
     * Link with a neighbouring cell.
     * @param cell A HexCell to link. If cell is nullptr or is not a neighbour of this cell, do nothing.
     * @note remember to link both directions!
     */
void HexCell::link(HexCell* cell) {
    /**
     * @todo Your code here!
     */
    if (cell == nullptr) {return;}

    int side = get_neighbour_side(cell);
    if (is_linked(cell)) {return;}
    if (side >= 0) {
        this->links[side] = cell;
        cell->link(this);
    }

}

int HexCell::get_neighbour_side(const HexCell* cell) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (cell == nullptr) {
        return -1;
    }

    int dq = cell->q - q;
    int dr = cell->r - r;
    if (dq == 0 && dr == -1) {
        return N;
    }

    if (dq == 1 && dr == -1) {
        return NE;
    }

    if (dq == 1 && dr == 0) {
        return SE;
    }

    if (dq == 0 && dr == 1) {
        return S;
    }

    if (dq == -1 && dr == 1) {
        return SW;
    }

    if (dq == -1 && dr == 0) {
        return NW;
    }

    return -1;
}

bool HexCell::is_linked(const HexCell* cell) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (cell == nullptr) {
        return false;
    }

    int side = get_neighbour_side(cell);
    return side >= 0 && side < 6 && links[side] == cell;
}

int HexCell::distance(const HexCell* cell) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (cell == nullptr) {
        return -1;
    }

    int distq = cell->q - q;
    int distr = cell->r - r;
    return (abs(distq) + abs(distq + distr) + abs(distr)) / 2;
}

bool HexCell::is_edge() const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    for (int i = 0; i <= 5; i++) {
        if (neighbours[i] == nullptr) {
            return true;
        }
    }
    return false;
}