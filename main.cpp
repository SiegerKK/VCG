#include <iostream>
#include <stdlib.h>

using namespace std;

//----------//----------//----------//
struct Map{
    int size;
    int array[10][10];
};
struct Point{
    int x;
    int y;
};

//----------//----------//----------//
Map createMap();
void printMap(Map map);
//----------//----------//----------//
void start(Map map);
//----------//----------//----------//

int main() {
    srand(time(0));

    Map map = createMap();
    printMap(map);

    return 0;
}

//----------//----------//----------//
void printMap(Map map){
    for (int i = 0; i < map.size; ++i) {
        for (int j = 0; j < map.size; ++j) {
            cout << map.array[i][j] << " ";
        }
        cout<<"\n";
    }
}
Map createMap(){
    Map map;
    map.size = 10;
    for (int i = 0; i < map.size; ++i) {
        for (int j = 0; j < map.size; ++j) {
            map.array[i][j] = 0;
        }
    }
    map.array[0][map.size-1]=1;
    map.array[map.size-1][0]=2;

    return map;
}
//----------//----------//----------//
void start(Map map){
    bool end = false;

    while(!end){
        //gameLogic(map);
        printMap (map);
    }
}
//----------//----------//----------//

void gameLogic(Map map){
    Point array1[map.size*map.size];
    Point array2[map.size*map.size];

}
//----------//----------//----------//