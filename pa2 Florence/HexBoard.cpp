#include "HexBoard.h"

#include <iostream>

#include "queue.h"
#include "stack.h"

/**
     * Constructor. Creates a board with given radius, creating new HexCells and inserting them into this->cells by calling createBoard()
     * and setting cells to have the appropriate neighbours by calling configure_cells(). The default start_coord is (0, 0).
     * @note There is no maze yet! The board is just a beehive for now.
     * @param radius The radius of the board
     */
HexBoard::HexBoard(int radius): longest_path_dist(0), radius(radius), start_coord({0, 0}), end_coord({0, 0}) {
    /**
     * @todo Your code here!
     */
    create_board();
    configure_cells();
}

/**
     * Creates all neccessary HexCells up to the given radius and insert them into this->cells.
     */
void HexBoard::create_board() {
    /**
     * @todo Your code here!
     */
     int newR = radius - 1;
     for (int r = -newR; r <= newR; r++) {

          if (r <= 0) {
               for (int q = -(newR + r); q <= newR; q++) {
                    HexCell* cell = new HexCell(q, r);
                    cells[{q, r}] = cell;
               } 
          } else {
               for (int q = -newR; q <= newR - r; q++) {
                    HexCell* cell = new HexCell(q, r);
                    cells[{q, r}] = cell;
               }
          }
    }
    
}


/**
     * Set all cells in this->cells to have the appropriate neighbours.
     */
void HexBoard::configure_cells() {
    /**
     * @todo Your code here!
     */
     for(auto kv: cells ) {
          HexCell * cell = kv.second;
          vector<pair<int, int>> neigh_coords = get_neigh_coords({cell->q, cell->r});

          for (int i = 0; i < 6; i ++) {
               auto oth = cells.find(neigh_coords[i]);
               if (oth != cells.end()) {
                    HexCell* neigh = oth->second;
                    cell->neighbours[i] = neigh;
               }
     }
}
}

void HexBoard::generate_maze(pair<int, int> start_coord, double branch_prob) {
    /**
     * @todo Your code here!
     */
     map<pair<int, int>, bool> visited;
     Stack<HexCell*> stack;
     int edgePath = 0;

     this->start_coord = start_coord;
     HexCell* startCell = cells[start_coord];
     startCell->path_dist_from_start = 0;
     longest_path_dist = startCell->path_dist_from_start;

     visited[start_coord] = true;
     stack.push(startCell);

     while (!stack.isEmpty()) {
          HexCell* curr_cell = stack.peek();
          HexCell* neigh_cell = chooseNeighbour(curr_cell, visited, branch_prob);


          if (neigh_cell) {
               curr_cell->link(neigh_cell);

               visited[{neigh_cell->q, neigh_cell->r}] = true;

               neigh_cell->path_dist_from_start = curr_cell->path_dist_from_start + 1;

               if (longest_path_dist < neigh_cell->path_dist_from_start) {
                    longest_path_dist = neigh_cell->path_dist_from_start;
               }

               if (neigh_cell->is_edge() && (edgePath < neigh_cell->path_dist_from_start)) {
                    edgePath = neigh_cell->path_dist_from_start;
                    end_coord = {neigh_cell->q, neigh_cell->r};
               }

               stack.push(neigh_cell);

          } else {
               stack.pop();
          }
     }

}




void HexBoard::solve_maze() {
    /**
     * @todo Your code here!
     */


     pair<int, int> tempCoord = start_coord;
     HexCell* curr = cells[start_coord];
     HexCell* end = cells[end_coord];

     map<pair<int, int>, bool> visited;
     map<pair<int, int>, bool> secondVisited;
     

     while (!(tempCoord == end_coord)) {
          pair<int, int> noExitCoord = tempCoord;
          for (int i = 0; i < 6; i++) {

               HexCell* next = curr->links[i];
               
               if ((next != nullptr) && (visited[{next->q, next->r}] == false) && (secondVisited[{next->q, next->r}] == false)) {
                    if (next->q == end->q && next->r == end->r) {
                         solution.push_back(tempCoord);
                         tempCoord = end_coord;
                         
                         
                    }
                    
                    visited[tempCoord] = true;
                    pair<int, int> t = tempCoord;

                    tempCoord = {next->q, next->r};
                    curr = cells[{next->q, next->r}];

                    solution.push_back(t);
                    break;
               }
          }
          // if either visited or not linked, then need go back
          if (tempCoord == noExitCoord) {
               secondVisited[tempCoord] = true;
               tempCoord = solution.back();
               curr = cells[tempCoord];
               solution.pop_back();
               //break;
          }
     }
        
     
}