#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>

#include "includes/colorLinux.cpp"

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
void start(Map &map);
//----------//----------//----------//
void gameLogic(Map &map);
bool canToGrow(Map map, Point cell);
bool wantToGrow();
Point grow(Map map, Point cell);
//----------//----------//----------//

int main() {
    srand(time(0));

    Map map = createMap();
    //setColor(YELLOW);
    start(map);

    return 0;
}

//----------//----------//----------//
void printMap(Map map){
    for (int i = 0; i < map.size; ++i) {
        for (int j = 0; j < map.size; ++j) {
            switch (map.array[i][j]){
                case 1:
                    setColor(BLUE);
                    cout << "X";
                    setColor(RESET);
                    break;
                case 2:
                    setColor(RED);
                    cout << "X";
                    setColor(RESET);
                    break;
                default:
                    cout << "O";
                    break;
            }
        }
        cout<<"\n";
    }
    cout << "\n";
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
void start(Map &map){
    bool end = false;
    int i = 0;

    while(!end){
        gameLogic(map);
        system("clear");
        printMap (map);

        usleep(100000);

        i++;
        if(i == 250){
            end = true;
        }
    }
}
//----------//----------//----------//
void gameLogic(Map &map){
    Point array1[map.size*map.size];
    Point array2[map.size*map.size];
    int iter1 = 0;
    int iter2 = 0;

    Point cell;
    for (int i = 0; i < map.size; ++i) {
        for (int j = 0; j < map.size; ++j) {
            cell.x = j;
            cell.y = i;
            if (canToGrow(map, cell) && wantToGrow()) {
                if (map.array[i][j] == 1) {
                    array1[iter1] = grow(map, cell);
                    iter1++;
                } else if (map.array[i][j] == 2) {
                    array2[iter2] = grow(map, cell);
                    iter2++;
                }
            }
        }
    }
    for (int k = 0; k < iter1; ++k) {
        if (map.array[array1[k].y][array1[k].x] == 0) {
            map.array[array1[k].y][array1[k].x] = 1;
        } else map.array[array1[k].y][array1[k].x] = 0;
    }

    for (int k = 0; k < iter2; ++k) {
        if (map.array[array2[k].y][array2[k].x] == 0) {
            map.array[array2[k].y][array2[k].x] = 2;
        } else map.array[array2[k].y][array2[k].x] = 0;
    }
    //----------//
    /*cout <<"Array1: ";
    for (int k = 0; k < iter1; ++k) {
        cout << "|" << array1[k].x <<" " << array1[k].y <<"|";
    }
    cout <<"\nArray2: ";
    for (int k = 0; k < iter2; ++k) {
        cout << "|" << array2[k].x <<" " << array2[k].y <<"|";
    }
    cout << "\n";*/
    //----------//
}
bool canToGrow(Map map, Point cell){
    if((cell.y != 0) && (map.array[cell.y][cell.x] != map.array[cell.y-1][cell.x] ))
        return true;
    if((cell.y != map.size-1) && (map.array[cell.y][cell.x] != map.array[cell.y+1][cell.x] ))
        return true;
    if((cell.x != 0) && (map.array[cell.y][cell.x] != map.array[cell.y][cell.x-1] ))
        return true;
    if((cell.x != map.size-1) && (map.array[cell.y][cell.x] != map.array[cell.y][cell.x+1] ))
        return true;
    return false;
}
bool wantToGrow(){
    int a = rand()%2;
    if (a == 0)
        return false;
    return true;
}
Point grow(Map map, Point cell){
    Point cellNew;
    int random;
    int q = true;
    while(q) {
        random = rand() % 4 +1;
        switch (random){
            case 1:
                if((cell.y != 0) && (map.array[cell.y][cell.x] != map.array[cell.y-1][cell.x] )) {
                    cellNew.x = cell.x;
                    cellNew.y = cell.y - 1;
                    q = false;
                }
                break;
            case 2:
                if((cell.y != map.size-1) && (map.array[cell.y][cell.x] != map.array[cell.y+1][cell.x] )){
                    cellNew.x = cell.x;
                    cellNew.y = cell.y + 1;
                    q = false;
                }
                break;
            case 3:
                if((cell.x != 0) && (map.array[cell.y][cell.x] != map.array[cell.y][cell.x-1] )){
                    cellNew.x = cell.x - 1;
                    cellNew.y = cell.y;
                    q = false;
                }
                break;
            case 4:
                if((cell.x != map.size-1) && (map.array[cell.y][cell.x] != map.array[cell.y][cell.x+1] )){
                    cellNew.x = cell.x + 1;
                    cellNew.y = cell.y;
                    q = false;
                }
                break;
        }

    }
    return cellNew;
}
//----------//----------//----------//