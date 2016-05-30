#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>

#include "includes/colorLinux.cpp"

using namespace std;

//----------//----------//----------//
struct Map{
    int size;
    int **array;
};
struct Point{
    int x;
    int y;
};

//----------//----------//----------//
Map createMap(int size);
void printMap(Map map);
//----------//----------//----------//
void start(Map &map, int turns);
//----------//----------//----------//
void gameLogic(Map &map);
bool canToGrow(Map map, Point cell);
bool wantToGrow();
Point grow(Map map, Point cell);
//----------//----------//----------//
void deleteMap(Map &map);
//----------//-Technical functions-//----------//
unsigned int calcVirusesCount(Map &map, int virusNumber);
//----------//----------//----------//

int main() {
    srand(time(0));

    //----------//
    int mapSize = 20;
    int turns = 2000;
    //----------//

    Map map = createMap(mapSize);
    start(map, turns);

    deleteMap(map);
    return 0;
}

//----------//----------//----------//
Map createMap(int size){
    Map map;

    map.size = size;
    map.array = new int*[map.size];
    for (int i = 0; i < map.size; ++i) {
        map.array[i] = new int[map.size];
        for (int j = 0; j < map.size; ++j) {
            map.array[i][j] = 0;
        }
    }

    map.array[0][map.size-1]=1;
    map.array[map.size-1][0]=2;
    map.array[0][0]=3;
    map.array[map.size-1][map.size-1]=4;

    return map;
}
void printMap(Map map){
    for (int i = 0; i < map.size; ++i) {
        for (int j = 0; j < map.size; ++j) {
            switch (map.array[i][j]){
                case 1:
                    setColor(RED);
                    cout << "X ";
                    setColor(RESET);
                    break;
                case 2:
                    setColor(BLUE);
                    cout << "X ";
                    setColor(RESET);
                    break;
                case 3:
                    setColor(YELLOW);
                    cout << "X ";
                    setColor(RESET);
                    break;
                case 4:
                    setColor(GREEN);
                    cout << "X ";
                    setColor(RESET);
                    break;
                default:
                    cout << "O ";
                    break;
            }
        }
        cout<<"\n";
    }
    cout << "\n";


    int countVirus[4];
    int percents = (map.size * map.size) / 100;
    for(int i = 0; i < 4; i++){
        countVirus[i] = calcVirusesCount(map, i + 1);
    }
    setColor(RED);
    cout << countVirus[0] << "(" << countVirus[0] / percents << "%)" << " ";
    setColor(BLUE);
    cout << countVirus[1] << "(" << countVirus[1] / percents << "%)" << " ";
    setColor(YELLOW);
    cout << countVirus[2] << "(" << countVirus[2] / percents << "%)" << " ";
    setColor(GREEN);
    cout << countVirus[3] << "(" << countVirus[3] / percents << "%)" << "\n";
    setColor(RESET);
}
//----------//----------//----------//
void start(Map &map, int turns){
    bool end = false;
    int i = 0;

    while(!end){
        gameLogic(map);
        system("clear");
        printMap (map);

        usleep(50000);

        i++;
        if((i == turns) || (calcVirusesCount(map, 1) == map.size * map.size)
           || (calcVirusesCount(map, 2) == map.size * map.size)
           || (calcVirusesCount(map, 3) == map.size * map.size)
           || (calcVirusesCount(map, 4) == map.size * map.size)){
            end = true;
        }
    }

    cout << "Tunrs: " << i << "\n";
}
//----------//----------//----------//
void gameLogic(Map &map){
    Point array[4][map.size*map.size];
    int iter[4];
    for (int l = 0; l < 4; ++l) {
        iter[l] = 0;
    }

    Point cell;
    for (int i = 0; i < map.size; ++i) {
        for (int j = 0; j < map.size; ++j) {
            cell.x = j;
            cell.y = i;
            if (canToGrow(map, cell) && wantToGrow() && map.array[i][j]!=0) {
                array[map.array[i][j] - 1][iter[map.array[i][j] - 1]] = grow(map, cell);
                iter[map.array[i][j]-1]++;
            }
        }
    }
    for (int i = 3; i >= 0; --i) {
        for (int k = 0; k < iter[i]; ++k) {
            if (map.array[array[i][k].y][array[i][k].x] == 0) {
                map.array[array[i][k].y][array[i][k].x] = i + 1;
            } else map.array[array[i][k].y][array[i][k].x] = 0;
        }
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
void deleteMap(Map &map){
    for (int i = 0; i < map.size; ++i) {
        delete[] map.array[i];
    }
    delete[] map.array;
}
//----------//-Technical functions-//----------//
unsigned int calcVirusesCount(Map &map, int virusNumber){
    unsigned int count = 0;
    for(int i = 0; i < map.size; i++){
        for (int j = 0; j < map.size; ++j) {
            if(map.array[i][j] == virusNumber){
                count++;
            }
        }
    }
    return count;
}
//----------//----------//----------//
