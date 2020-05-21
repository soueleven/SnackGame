//
//  Snack.hpp
//  SnackGame
//
//  Created by Song on R 2/05/20.
//  Copyright © Reiwa 2 Sou. All rights reserved.
//

#ifndef Snack_hpp
#define Snack_hpp

#include <stdio.h>

const int POINT_WH = 10;

struct vector2 {
    float x;
    float y;
};

class Snack;

class SnackNode {
private:
    vector2 pos;
    SnackNode *next;
public:
    SnackNode(vector2 p): pos(p), next(0){};

    vector2 GetPos() {return pos;};
    SnackNode* GetNext() {return next;};

    friend class Snack;
};

class Snack {
private:
    SnackNode *first;
public:
    Snack(): first(0){};
    void InsertHead(vector2 pos);
    void DeleteLast();
    int SearchNode(vector2 pos);

    SnackNode* GetFirst() {return first;};
};

#endif /* Snack_hpp */
