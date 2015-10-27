#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>
#include <bitset>
#include <iomanip>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Room struct includes 
// 1)   Whether the number of crosses in this room are even or odd.
//      By default we start out at 0, so it's even. 
// 2)   An uint64_t int representing the random portal it is connected to. 
// We don't need to include the number of the next room, it is always current room number +1.
struct room {
    bool even_crosses = true; // true if # of crosses even, false if # of crosses is odd
    uint64_t portal; // the number of the portal 
};

// Map that is indexed by room # and returns the room's characteristics as defined by the struct room
typedef vector<room> Maze;  

// For debug
void printMaze(Maze& m) {
    for (uint64_t i = 1; i <= m.size() ; ++i) {
        cout << "Room Number " << i << endl;
        cout << "Next room " << i+1 << endl;
        cout << "Portal " << m[i].portal << endl;
        cout << "Even number of crosses? " << boolalpha << m[i].even_crosses << endl;
    }
}

// Return number of moves needed
void solveMaze(Maze& m) {
    int moves = 0; 
    uint64_t next_room_key = 1; 
    uint64_t end_room_key = m.size();
    uint64_t curr_room_key = 2;
    /* 
     * === pseudo code === 
     * begin at the first room
     * toggle the # of crosses
     * check if the # of crosses is even or odd
     * make next move, update move count
     * stop when we are at room number == last room +1  
     */
    while (next_room_key != end_room_key) {
        /*cout << "In room " << next_room_key << endl;*/
        /*cout << "Moves =  " << moves << endl;*/
        m[next_room_key].even_crosses = !m[next_room_key].even_crosses;
        // even - go to +1 room
        if (m[next_room_key].even_crosses) {
            next_room_key += 1;
            if (next_room_key == curr_room_key) {
                cout << next_room_key << " " << moves+1 << endl;
                ++ curr_room_key;
            }
        }
        // odd - go to portal
        else {
            next_room_key = m[next_room_key].portal;
        }
        /*cout << "Next room " << next_room_key << endl;*/
        assert(next_room_key > 0);
        ++moves;
    }
    
    /* 
     * Also need to format the answer modulo 10^9 
     */
    if (moves < 1000000007) {
        cout << moves << endl;
    }
    else {
        cout << moves % 1000000007 << endl; 
    }
}

int main() {
    // accept inputs 
    uint64_t num_rooms;
    cin >> num_rooms;

    // create the maze 
    Maze maze; 
    //maze.resize(num_rooms+1);
    room temp;
    temp.portal = 0;
    maze.push_back(temp);

    // populate the maze characteristics  
    for (uint64_t i = 1; i <= num_rooms; ++i) {
        room temp2;
        cin >> temp2.portal;
        maze.push_back(temp2);     
    }
    // debug 
    /*printMaze(maze);*/
    
    // find answer
    solveMaze(maze); 

    return 0;
}

