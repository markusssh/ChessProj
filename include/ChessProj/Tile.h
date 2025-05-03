//
// Created by markusssh on 03.05.2025.
//

#ifndef TILE_H
#define TILE_H



class Tile {
public:
    Tile(int row, int col);

    ~Tile();
    int getRow();
    int getColNum();
    int getColChar();
private:
    int row;
    int col;
};



#endif //TILE_H
