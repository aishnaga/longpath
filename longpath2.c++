#include <iostream>
#include <vector>

using namespace std;

const uint64_t mod = 1000000007ULL;

int main() {
    uint64_t num_rooms;
    cin >> num_rooms;

    // create the maze 
    vector<uint64_t> maze;
    maze.push_back(0);

    uint64_t portal;
    cin >> portal;
    maze.push_back(2);     

    uint64_t moves = 2;
    // populate the maze characteristics  
    for (uint64_t i = 2; i <= num_rooms; ++i) {
        uint64_t portal;
        cin >> portal;
        uint64_t cell = 2;
        for (uint64_t j = portal; j < i; ++j) {
            cell += maze[j];
        }
        cell %= mod;
        maze.push_back(cell);     
        moves += cell;
        moves %= mod;
        //cout << i << " " << moves << endl;
    }

    if (moves < mod) {
        cout << moves << endl;
    }
    else {
        cout << moves % mod << endl; 
    }

    return 0;
}

