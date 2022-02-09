#include <stdio.h>
#include <stdlib.h>

#include "BaseType.h"

static void showBoardColor(int type)
{
    switch(type){
        case 0:
            printf("\033[0;31m");
        break;

        case 1:
            printf("\033[0;31m");
        break;

        case 2:
            printf("\033[0;34m");
        break;

        case 3:
            printf("\033[0;35m");
        break;

        case 4:
            printf("\033[0;34m");
        break;

        case 5:
            printf("\033[0;37m");
        break;

        case 6:
            printf("\033[0;37m");
        break;

        case 7:
            printf("\033[0;32m");
        break;

        case 8:
            printf("\033[0;32m");
        break;

        case 9:
            printf("\033[0;31m");
        break;

        case 10:
            printf("\033[0;33m");
        break;

        case 11:
            printf("\033[0;32m");
        break;

        default:
            printf("\033[0;37m");
        break;
    }
}

int initBoard(GameBoard *pb)
{
    int i,j;

    if(pb == NULL) {
        return -1;
    }

    for(i = 0; i < BOARD_SIZE; i++){
        for (j = 0; j < BOARD_SIZE; j++) {
            if (j <= i) {
                pb->board[i][j] = 0;
            }
            else {
                pb->board[i][j] = -1;
            }
        }
    }
	
	return 0;
}

int showBoard(GameBoard *pb) 
{
    int i,j;

    if(pb == NULL) {
        return -1;
    }

    for(i = 0; i < BOARD_SIZE; i++){
        for (j = 0; j < BOARD_SIZE; j++) {
            if (j <= i) {
                if(pb->board[i][j] == 0 ) {
                    printf("*  ");
                }
                else {
                    if(pb->board[i][j] == -1 ) {
                        printf("x  ");
                    }
                    else {
                        showBoardColor(pb->board[i][j]-1);
                        printf("%02d ",pb->board[i][j]);
                        printf("\033[0m");
                    }
                    
                }
            }
        }
        printf("\n");
    }

    return 0;
}

int showBoard2(GameBoard *pb) 
{
    int i,j,k;

    if(pb == NULL) {
        return -1;
    }

    for(i = 0; i < BOARD_SIZE; i++){
        int start_row = BOARD_SIZE-1;
        int start_column = i;

        for (k=0;k<BOARD_SIZE-1-i;k++) {
            printf("  ");
        }

        for(j = 0; j <= i; j++) {
            if(pb->board[start_row][start_column] == 0 ) {
                printf("*   ");
            }
            else {
                if(pb->board[start_row][start_column] == -1 ) {
                    printf("x   ");
                }
                else {
                    showBoardColor(pb->board[start_row][start_column]-1);
                    printf("%02d  ",pb->board[start_row][start_column]);
                    printf("\033[0m");
                }
            }
            start_row--;
            start_column--;   
        }
        printf("\n");
    }

    return 0;
}

int checkShapeOnBoard(GameBoard *pb, SubShapeDescriptor subShape, int row, int column)
{
    int i, j;

    if(pb == NULL) {
        return -1;
    }

    if(row < 0 || row >= BOARD_SIZE || (row + subShape.h )> BOARD_SIZE ) {
        //printf("row[%d] range overflow\n",row);
        return -1;
    }

    if(column < 0 || column >= BOARD_SIZE || (column + subShape.w )> BOARD_SIZE) {
        //printf("column[%d] range overflow\n",column);
        return -1;
    }

    for(i = 0; i < subShape.h; i++ ){
        for (j=0; j< subShape.w; j++ ) {
            if (subShape.desc[i][j] != 0) {
                if(pb->board[row + i][column + j] != 0) {
                    return -1;
                }
            }
        }
    }

    return 0;
}

int addShapeOnBoard(GameBoard *pb, SubShapeDescriptor subShape, int row, int column, int shapeType)
{
    int i, j;
    int ret = -1;

    if(pb == NULL) {
        return -1;
    }
    //showSubShapeDescriptor(subShape);
    if(checkShapeOnBoard(pb, subShape, row, column) == 0) {
        for(i = 0; i < subShape.h; i++ ){
            for (j=0; j< subShape.w; j++ ) {
                if (subShape.desc[i][j] != 0) {
                    pb->board[row + i][column + j] = shapeType + 1;
                }
            }
        }

        ret = 0;
    }
    else {
        //printf("Check Board Error\n");
        ret = -1;
    }

    return ret;
}

/**
 * @brief Botom up to construct the board.
 *           O
 *           ^
 *           |
 *           O
 *          ...
 * @param pb 
 * @param pNode 
 * @return int 
 */
int constructBoardFromTreeNode(GameBoard *pb, struct PlayTree *pNode)
{
    ShapeDescriptor *pShapeDesc;
    int hasError = 0, ret = 0;

    if(pb == NULL || pNode == NULL) {
        return -1;
    }

    while(pNode) {
        pShapeDesc = getShapeDescriptor(pNode->type);
        ret = addShapeOnBoard(pb, pShapeDesc->pSubArray[pNode->subtype], pNode->ypos, pNode->xpos, pNode->type);
        if(ret != 0) {
            hasError = 1;
        }
        pNode = pNode->parent;
        //showBoard(pb);
    }

    if(hasError) {
        return -1;
    }
    else {
        return 0;
    }
}
