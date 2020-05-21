//
//  Snack.cpp
//  SnackGame
//
//  Created by Song on R 2/05/20.
//  Copyright © Reiwa 2 Sou. All rights reserved.
//

#include "Snack.hpp"

void Snack::InsertHead(vector2 pos) {
    SnackNode *newNode = new SnackNode(pos);
    newNode->next = first;
    first = newNode;
}

void Snack::DeleteLast() {
    if (first == 0) {
        return;
    }

    SnackNode *secondLast = first;
    while (secondLast->next->next != 0) {
        secondLast = secondLast->next;
    }

    delete (secondLast->next);
    secondLast->next = NULL;
}

int Snack::SearchNode(vector2 pos) {
    if (first == 0) {
        return -1;
    }

    SnackNode *current = first;
    int i = 0;
    while (current->next != 0) {
        if ((current->pos.x + POINT_WH > pos.x && pos.x > current->pos.x - POINT_WH) &&
            (current->pos.y + POINT_WH > pos.y && pos.y > current->pos.y - POINT_WH)) {
            return i;
        }
        current = current->next;
        i++;
    }

    return -1;
}
