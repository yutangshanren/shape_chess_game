#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BaseType.h"

static int ShapeMap[SHAPE_TYPE_MAX];

/**
 * @brief Play the game for the initialize tree.
 * 
 * @return int 
 */
static int playGame(struct PlayTree *pPlayRoot)
{
    int i;
    struct PlayTree *pPrev = pPlayRoot;
    GameBoard *pFinalBoard = NULL;

    for(i=0; i<SHAPE_TYPE_MAX; i++) {
        printf(" %d%% :", (i*100)/SHAPE_TYPE_MAX);
        // shape already in tree
        if(ShapeMap[i]) { 
            printf("\n");
		    continue;
		}
        struct PlayTree *pHead = NULL;
        struct PlayTree *pTail = NULL;

        ShapeDescriptor *pDesc = getShapeDescriptor(i);
        while(pPrev) {
            int subtype;

            /**
             * Construct the current board from pPrev to root.
             */
            GameBoard *pboard = (GameBoard *) malloc(sizeof(GameBoard));
            if(pboard == NULL) {
                printf("Not enough memory when construct a board\n");
                exit(-1);
            }
            initBoard(pboard);
            constructBoardFromTreeNode(pboard, pPrev);

            for(subtype = 0; subtype < pDesc->subShapeNumber; subtype++) {
                int x,y;
                for(y=0; y<BOARD_SIZE;y++){
                    for(x=0; x<=y; x++) {
                        if(checkShapeOnBoard(pboard, pDesc->pSubArray[subtype], y, x) == 0) {
                            struct PlayTree *pNewNode = NULL;
                            pNewNode = (struct PlayTree *)malloc(sizeof(struct PlayTree));
                            if(pNewNode == NULL) {
                                printf("Not enough memory when alloc new node\n");
                                exit(-1);
                            }
                            pNewNode->parent = pPrev;
                            pNewNode->sibling = NULL;
                            pNewNode->type = i;
                            pNewNode->subtype = subtype;
                            pNewNode->xpos = x;
                            pNewNode->ypos = y;

                            if(pHead == NULL) {
                                pHead = pNewNode;
                            }
                            if(pTail != NULL) {
                                pTail->sibling = pNewNode;
                            }
                            pTail = pNewNode;
                        }
                    }
                }
            }
            if(pboard) {
                free(pboard);
            }
            pPrev = pPrev->sibling;
        }
        pPrev = pHead;
        ShapeMap[i] = 1;

        if(pHead == NULL) {
            printf("Could not find a solution 111!\n");
            exit(-1);
        }

		{

            struct PlayTree *pst = pHead;
			long long int nodeNr = 0;
			while(pst) {
			    nodeNr++;
				pst = pst->sibling;

			}
            printf("(%lld)\n",nodeNr);

		}
    }

    printf("100%%\n");

    if(pPrev == NULL) {
        printf("Could not find a solution 222!\n");
        exit(-1);
    } 

    int solution = 1;
    while(pPrev) {
        pFinalBoard = (GameBoard *) malloc(sizeof(GameBoard));
        if(pFinalBoard == NULL) {
            printf("Not enough memory when construct final board\n");
            exit(-1);
        }

        initBoard(pFinalBoard);
        constructBoardFromTreeNode(pFinalBoard, pPrev);
        printf("---------------------------------\n");
        printf("Solution:%d\n", solution);
        showBoard2(pFinalBoard);
        printf("---------------------------------\n");
        pPrev = pPrev->sibling;
        solution++;
    }

    return 0;
}

static int runATestPattern()
{
    struct PlayTree *t1 = (struct PlayTree *) malloc(sizeof(struct PlayTree));
    struct PlayTree *t2 = (struct PlayTree *) malloc(sizeof(struct PlayTree));

    t1->parent = NULL;
    t1->sibling = NULL;
    t1->type = 2;
    t1->subtype = 0;
    t1->ypos = 7;
    t1->xpos = 0;
    ShapeMap[2] = 1;

    t2->parent = t1;
    t2->sibling = NULL;
    t2->type = 1;
    t2->subtype = 0;
    t2->ypos = 7;
    t2->xpos = 2;
    ShapeMap[1] = 1;

    GameBoard *pb = (GameBoard *) malloc(sizeof(GameBoard));
    initBoard(pb);
    constructBoardFromTreeNode(pb, t2);
    printf("-------------------------\n");
    printf("      Initial Board      \n");
    printf("-------------------------\n");
    showBoard2(pb);

    playGame(t2);

	return 0;
}

static struct PlayTree * parseConfig()
{
    struct PlayTree *pRoot=NULL, *pNewNode = NULL, *pTmp = NULL;
    FILE *fp = NULL;
    int type, subtype, row, column, ret;

    fp = fopen("config.ini","r");
    if(fp == NULL) {
        return NULL;
    }

    while(!feof(fp)){
        ret = fscanf(fp,"%d %d %d %d\n",&type, &subtype, &row, &column);
        if(ret == 4) {
            //printf("%d,%d,%d,%d\n",type, subtype, row, column);
            if(type < 0 || type >= SHAPE_TYPE_MAX) {
                printf("Config file error, type=%d\n",type);
                exit(-1);
            }

            if(row < 0 || row >= BOARD_SIZE) {
                printf("Config file error, row=%d\n",row);
                exit(-1);
            }

            if(column < 0 || column >= BOARD_SIZE) {
                printf("Config file error, column=%d\n",column);
                exit(-1);
            }

            pNewNode = (struct PlayTree *)malloc(sizeof(struct PlayTree));
            if(pNewNode == NULL) {
                printf("Not enough memory for parseConfig");
                exit(-1);
            }
            pNewNode->parent = pRoot;
            pNewNode->sibling = NULL;
            pNewNode->type = type;
            pNewNode->subtype = subtype;
            pNewNode->ypos = row;
            pNewNode->xpos = column;
            pRoot = pNewNode;
            ShapeMap[type] = 1;
        }
        else{
            printf("Config file error, ret=%d\n",ret);
            while(pRoot) {
                pTmp = pRoot;
                pRoot = pRoot->parent;
                free(pTmp);
            }
            return NULL;
        }
    }

/**
    if(pRoot) {
        pTmp = pRoot;
        while(pTmp) {
            printf("%d,%d,%d,%d,%p\n",pTmp->type, pTmp->subtype, pTmp->ypos, pTmp->xpos, pTmp->parent);
            pTmp = pTmp->parent;   
        }
    }
*/
    return pRoot;
}

int main(int argc, char *argv[])
{
    int i;
    ShapeDescriptor *ptr = NULL;
    
    initShapeDescriptor();
    for(i =0; i<SHAPE_TYPE_MAX; i++) {
        ShapeMap[i] = 0;
    }
    
    argc--;
    i = 1;
    while(argc > 0) {
        if( !strcmp("-sr", argv[i])) {
            showShapeIndex();
            exit(0);
        } 
        else if (!strcmp("-st", argv[i])) {
            int type = atoi(argv[i+1]);
            if(type >= 0 && type < SHAPE_TYPE_MAX) {
                showShapeDescriptor(type);
            }
            else {
                printf(" -st type error, range [0-%d]\n",SHAPE_TYPE_MAX-1);
            }
            exit(0);
        }

        argc--;
    }

    /**
     * Read config file
     */
    struct PlayTree *pConfigRoot = NULL;
    pConfigRoot = parseConfig();
    if(pConfigRoot) {
        GameBoard *pb = (GameBoard *) malloc(sizeof(GameBoard));
        initBoard(pb);
        if(constructBoardFromTreeNode(pb, pConfigRoot) != 0) {
            printf("Could not construct the initial board, check the parameters!\n");
            struct PlayTree *ptr = NULL;
            while(pConfigRoot) {
                ptr = pConfigRoot;
                pConfigRoot = pConfigRoot->parent;
                printf("[%d,%d,%d,%d]\n", ptr->type, ptr->subtype, ptr->ypos, ptr->xpos);
                free(ptr);
            }
            free(pb);
            exit(-1);
        }
        printf("-------------------------\n");
        printf("      Initial Board      \n");
        printf("-------------------------\n");
        showBoard2(pb);
        
        /**
         * Play the game.
         */
        playGame(pConfigRoot);
    }
    else {
        printf("Read config file error\n");
    }

    //runATestPattern();

    return 0;
}

