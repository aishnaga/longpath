#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <map>
#include <bitset>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

// Room struct includes 
// 1)   Whether the number of crosses in this room are even or odd.
//      By default we start out at 0, so it's even. 
// 2)   An unsigned int representing the random portal it is connected to. 
// We don't need to include the number of the next room, it is always current room number +1.
struct room {
    bool even_crosses = true; // true if # of crosses even, false if # of crosses is odd
    unsigned portal; // the number of the portal 
};

// Map that is indexed by room # and returns the room's characteristics as defined by the struct room
typedef map <unsigned, room> Maze;  

// For debug
void printMaze(Maze& m) {
    for (unsigned i = 1; i <= m.size() ; ++i) {
        cout << "Room Number " << i << endl;
        cout << "Next room " << i+1 << endl;
        cout << "Portal " << m[i].portal << endl;
        cout << "Even number of crosses? " << boolalpha << m[i].even_crosses << endl;
    }
}

// If input # of crosses is even, make it odd and vice-versa
void toggleCrosses(bool& crosses) {
    if (crosses) {
        crosses = false;
    }
    else {
        crosses = true;
    }
}

// Format the answer modulo 10^9
string formatAnswer(int& x) {
    stringstream ss;
    string output;

    if (x < 1000000000) {
        ss << x;
    }
    else {
        int remainder = x % 1000000000; 
        ss << "10\u00b9 + " << remainder ; 
    }
        
    output = ss.str();
    return output;
}

// Return number of moves needed
string solveMaze(Maze& m) {
    int moves = 0; 
    unsigned next_room_key = 1; 
    unsigned end_room_key = m.size() + 1;
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
        toggleCrosses(m[next_room_key].even_crosses);
        // even - go to +1 room
        if (m[next_room_key].even_crosses) {
            next_room_key += 1; 
        }
        // odd - go to portal
        else {
            next_room_key = m[next_room_key].portal;
        }
        /*cout << "Next room " << next_room_key << endl;*/
        ++moves;
    }
    
    /* 
     * Also need to format the answer modulo 10^9 
     */
    string answer = formatAnswer(moves);
    return answer; 
}

int main() {
    // create the maze 
    Maze maze; 
    // accept inputs 
    unsigned num_rooms;
    cin >> num_rooms;
    // populate the maze characteristics  
    for (unsigned i = 1; i <= num_rooms; ++i) {
        room temp;
        cin >> temp.portal;
        maze[i] = temp;     
    }
    // debug 
    /*printMaze(maze);*/
    
    // find answer
    cout << solveMaze(maze) << endl; 

    return 0;
}

