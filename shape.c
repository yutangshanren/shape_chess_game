#include <stdio.h>
#include <stdlib.h>

#include "BaseType.h"


static ShapeDescriptor *gShapeDesc = NULL;



//   *   *
//     *
//   *   *
static SubShapeDescriptor gSubStar = 
{
    .w = 3,
    .h = 3,
    .desc = {
        0,1,0,0,
        1,1,1,0,
        0,1,0,0,
        0,0,0,0
    }
};

//   *    *
// *   *    *
static SubShapeDescriptor gSubM[4] = 
{
    {
        .w = 3,
        .h = 3,
        .desc = {
            1,0,0,0,
            1,1,0,0,
            0,1,1,0,
            0,0,0,0
        }
    },

    {
        .w = 3,
        .h = 3,
        .desc = {
            0,0,1,0,
            0,1,1,0,
            1,1,0,0,
            0,0,0,0
        }
    },

    {
        .w = 3,
        .h = 3,
        .desc = {
            1,1,0,0,
            0,1,1,0,
            0,0,1,0,
            0,0,0,0
        }
    },

    {
        .w = 3,
        .h = 3,
        .desc = {
            0,1,1,0,
            1,1,0,0,
            1,0,0,0,
            0,0,0,0
        }
    },
    
};

//  *
//  *
//  *  *  *
static SubShapeDescriptor gSubBigCorner[4] = 
{
    {
        .w = 3,
        .h = 3,
        .desc = {
            1,0,0,0,
            1,0,0,0,
            1,1,1,0,
            0,0,0,0
        }
    },

    {
        .w = 3,
        .h = 3,
        .desc = {
            0,0,1,0,
            0,0,1,0,
            1,1,1,0,
            0,0,0,0
        }
    },

    {
        .w = 3,
        .h = 3,
        .desc = {
            1,1,1,0,
            0,0,1,0,
            0,0,1,0,
            0,0,0,0
        }
    },

    {
        .w = 3,
        .h = 3,
        .desc = {
            1,1,1,0,
            1,0,0,0,
            1,0,0,0,
            0,0,0,0
        }
    },
    
};

// *  *
//    *  *  *
static SubShapeDescriptor gSubZigzag[8] = 
{
    {
        .w = 4,
        .h = 2,
        .desc = {
            1,1,0,0,
            0,1,1,1,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 4,
        .h = 2,
        .desc = {
            0,0,1,1,
            1,1,1,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 4,
        .h = 2,
        .desc = {
            0,1,1,1,
            1,1,0,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 4,
        .h = 2,
        .desc = {
            1,1,1,0,
            0,0,1,1,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 4,
        .desc = {
            1,0,0,0,
            1,1,0,0,
            0,1,0,0,
            0,1,0,0
        }
    },

    {
        .w = 2,
        .h = 4,
        .desc = {
            0,1,0,0,
            1,1,0,0,
            1,0,0,0,
            1,0,0,0
        }
    },

    {
        .w = 2,
        .h = 4,
        .desc = {
            0,1,0,0,
            0,1,0,0,
            1,1,0,0,
            1,0,0,0
        }
    },

    {
        .w = 2,
        .h = 4,
        .desc = {
            1,0,0,0,
            1,0,0,0,
            1,1,0,0,
            0,1,0,0
        }
    },
    
};

//  *  *
//  *  *  *
static SubShapeDescriptor gSubSquareHorn[8] = 
{
    {
        .w = 3,
        .h = 2,
        .desc = {
            1,1,0,0,
            1,1,1,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 3,
        .h = 2,
        .desc = {
            0,1,1,0,
            1,1,1,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 3,
        .h = 2,
        .desc = {
            1,1,1,0,
            1,1,0,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 3,
        .h = 2,
        .desc = {
            1,1,1,0,
            0,1,1,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 3,
        .desc = {
            1,1,0,0,
            1,1,0,0,
            0,1,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 3,
        .desc = {
            1,1,0,0,
            1,1,0,0,
            1,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 3,
        .desc = {
            0,1,0,0,
            1,1,0,0,
            1,1,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 3,
        .desc = {
            1,0,0,0,
            1,1,0,0,
            1,1,0,0,
            0,0,0,0
        }
    },
    
};


// *  *  *
// *     * 
static SubShapeDescriptor gSubOpenMouth[4] = 
{
    {
        .w = 3,
        .h = 2,
        .desc = {
            1,1,1,0,
            1,0,1,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 3,
        .h = 2,
        .desc = {
            1,0,1,0,
            1,1,1,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 3,
        .desc = {
            1,1,0,0,
            1,0,0,0,
            1,1,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 3,
        .desc = {
            1,1,0,0,
            0,1,0,0,
            1,1,0,0,
            0,0,0,0
        }
    },
    
};


// *  *  *  *
// *
static SubShapeDescriptor gSubBigL[8] = 
{
    {
        .w = 4,
        .h = 2,
        .desc = {
            1,1,1,1,
            1,0,0,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 4,
        .h = 2,
        .desc = {
            1,1,1,1,
            0,0,0,1,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 4,
        .h = 2,
        .desc = {
            1,0,0,0,
            1,1,1,1,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 4,
        .h = 2,
        .desc = {
            0,0,0,1,
            1,1,1,1,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 4,
        .desc = {
            1,1,0,0,
            1,0,0,0,
            1,0,0,0,
            1,0,0,0
        }
    },

    {
        .w = 2,
        .h = 4,
        .desc = {
            1,1,0,0,
            0,1,0,0,
            0,1,0,0,
            0,1,0,0
        }
    },

    {
        .w = 2,
        .h = 4,
        .desc = {
            1,0,0,0,
            1,0,0,0,
            1,0,0,0,
            1,1,0,0
        }
    },

    {
        .w = 2,
        .h = 4,
        .desc = {
            0,1,0,0,
            0,1,0,0,
            0,1,0,0,
            1,1,0,0
        }
    },
    
};

// *  *  *  *
//    *
static SubShapeDescriptor gSubLineHorn[8] = 
{
    {
        .w = 4,
        .h = 2,
        .desc = {
            1,1,1,1,
            0,1,0,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 4,
        .h = 2,
        .desc = {
            1,1,1,1,
            0,0,1,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 4,
        .h = 2,
        .desc = {
            0,1,0,0,
            1,1,1,1,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 4,
        .h = 2,
        .desc = {
            0,0,1,0,
            1,1,1,1,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 4,
        .desc = {
            1,0,0,0,
            1,1,0,0,
            1,0,0,0,
            1,0,0,0
        }
    },

    {
        .w = 2,
        .h = 4,
        .desc = {
            0,1,0,0,
            1,1,0,0,
            0,1,0,0,
            0,1,0,0
        }
    },

    {
        .w = 2,
        .h = 4,
        .desc = {
            1,0,0,0,
            1,0,0,0,
            1,1,0,0,
            1,0,0,0
        }
    },

    {
        .w = 2,
        .h = 4,
        .desc = {
            0,1,0,0,
            0,1,0,0,
            1,1,0,0,
            0,1,0,0
        }
    },
    
};

// *  *  *
// *
static SubShapeDescriptor gSubSmallL[8] = 
{
    {
        .w = 3,
        .h = 2,
        .desc = {
            1,1,1,0,
            1,0,0,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 3,
        .h = 2,
        .desc = {
            1,1,1,0,
            0,0,1,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 3,
        .h = 2,
        .desc = {
            1,0,0,0,
            1,1,1,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 3,
        .h = 2,
        .desc = {
            0,0,1,0,
            1,1,1,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 3,
        .desc = {
            1,1,0,0,
            1,0,0,0,
            1,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 3,
        .desc = {
            1,1,0,0,
            0,1,0,0,
            0,1,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 3,
        .desc = {
            1,0,0,0,
            1,0,0,0,
            1,1,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 3,
        .desc = {
            0,1,0,0,
            0,1,0,0,
            1,1,0,0,
            0,0,0,0
        }
    },
    
};


// *
// *  *
static SubShapeDescriptor gSubSmallCorner[4] = 
{
    {
        .w = 2,
        .h = 2,
        .desc = {
            1,0,0,0,
            1,1,0,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 2,
        .desc = {
            0,1,0,0,
            1,1,0,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 2,
        .desc = {
            1,1,0,0,
            1,0,1,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 2,
        .h = 2,
        .desc = {
            1,1,0,0,
            0,1,0,0,
            0,0,0,0,
            0,0,0,0
        }
    },
    
};

// *  *
// *  *
static SubShapeDescriptor gSubSquare[1] = 
{
    {
        .w = 2,
        .h = 2,
        .desc = {
            1,1,0,0,
            1,1,0,0,
            0,0,0,0,
            0,0,0,0
        }
    },
};

// *  *  *  *
static SubShapeDescriptor gSubLine[2] = 
{
    {
        .w = 4,
        .h = 1,
        .desc = {
            1,1,1,1,
            0,0,0,0,
            0,0,0,0,
            0,0,0,0
        }
    },

    {
        .w = 1,
        .h = 4,
        .desc = {
            1,0,0,0,
            1,0,0,0,
            1,0,0,0,
            1,0,0,0
        }
    },
};

int initShapeDescriptor()
{

    if ( gShapeDesc != NULL ) {
        printf("ShapeDescriptor already inited!\n");
        return -1;
    }

    gShapeDesc = (ShapeDescriptor *) malloc(sizeof(ShapeDescriptor) * SHAPE_TYPE_MAX);
    if (gShapeDesc == NULL ) {
        printf("Not enough memory for ShapeDescriptor\n");
        return -1;
    }

    //   *   *
    //     *
    //   *   *
    gShapeDesc[SHAPE_TYPE_STAR].type = SHAPE_TYPE_STAR;
    gShapeDesc[SHAPE_TYPE_STAR].subShapeNumber = 1;
    gShapeDesc[SHAPE_TYPE_STAR].pSubArray = &gSubStar;


    //   *    *
    // *   *    *
    gShapeDesc[SHAPE_TYPE_M].type = SHAPE_TYPE_M;
    gShapeDesc[SHAPE_TYPE_M].subShapeNumber = 4;
    gShapeDesc[SHAPE_TYPE_M].pSubArray = gSubM;

    //  *
    //  *
    //  *  *  *    
    gShapeDesc[SHAPE_TYPE_BIG_CORNER].type = SHAPE_TYPE_BIG_CORNER;
    gShapeDesc[SHAPE_TYPE_BIG_CORNER].subShapeNumber = 4;
    gShapeDesc[SHAPE_TYPE_BIG_CORNER].pSubArray = gSubBigCorner;

    // *  *
    //    *  *  *
    gShapeDesc[SHAPE_TYPE_ZIGZAG].type = SHAPE_TYPE_ZIGZAG;
    gShapeDesc[SHAPE_TYPE_ZIGZAG].subShapeNumber = 8;
    gShapeDesc[SHAPE_TYPE_ZIGZAG].pSubArray = gSubZigzag;

    //  *  *
    //  *  *  *
    gShapeDesc[SHAPE_TYPE_SQUARE_HORN].type = SHAPE_TYPE_SQUARE_HORN;
    gShapeDesc[SHAPE_TYPE_SQUARE_HORN].subShapeNumber = 8;
    gShapeDesc[SHAPE_TYPE_SQUARE_HORN].pSubArray = gSubSquareHorn;

    // *  *  *
    // *     *
    gShapeDesc[SHAPE_TYPE_OPEN_MOUTH].type = SHAPE_TYPE_OPEN_MOUTH;
    gShapeDesc[SHAPE_TYPE_OPEN_MOUTH].subShapeNumber = 4;
    gShapeDesc[SHAPE_TYPE_OPEN_MOUTH].pSubArray = gSubOpenMouth;

    // *  *  *  *
    // *
    gShapeDesc[SHAPE_TYPE_BIG_L].type = SHAPE_TYPE_BIG_L;
    gShapeDesc[SHAPE_TYPE_BIG_L].subShapeNumber = 8;
    gShapeDesc[SHAPE_TYPE_BIG_L].pSubArray = gSubBigL;

    // *  *  *  *
    //    *
    gShapeDesc[SHAPE_TYPE_LINE_HORN].type = SHAPE_TYPE_LINE_HORN;
    gShapeDesc[SHAPE_TYPE_LINE_HORN].subShapeNumber = 8;
    gShapeDesc[SHAPE_TYPE_LINE_HORN].pSubArray = gSubLineHorn;


    // *  *  *
    // *
    gShapeDesc[SHAPE_TYPE_SMALL_L].type = SHAPE_TYPE_SMALL_L;
    gShapeDesc[SHAPE_TYPE_SMALL_L].subShapeNumber = 8;
    gShapeDesc[SHAPE_TYPE_SMALL_L].pSubArray = gSubSmallL;

    // *
    // *  *
    gShapeDesc[SHAPE_TYPE_SMALL_CORNER].type = SHAPE_TYPE_SMALL_CORNER;
    gShapeDesc[SHAPE_TYPE_SMALL_CORNER].subShapeNumber = 4;
    gShapeDesc[SHAPE_TYPE_SMALL_CORNER].pSubArray = gSubSmallCorner;


    // *  *
    // *  *
    gShapeDesc[SHAPE_TYPE_SQUARE].type = SHAPE_TYPE_SQUARE;
    gShapeDesc[SHAPE_TYPE_SQUARE].subShapeNumber = 1;
    gShapeDesc[SHAPE_TYPE_SQUARE].pSubArray = gSubSquare;

    // *  *  *  *
    gShapeDesc[SHAPE_TYPE_LINE].type = SHAPE_TYPE_LINE;
    gShapeDesc[SHAPE_TYPE_LINE].subShapeNumber = 2;
    gShapeDesc[SHAPE_TYPE_LINE].pSubArray = gSubLine;

    return 0;
}

int showShapeDescriptor(int type)
{
    int i,k,j;
    printf("Descriptor: %d\n",type);
    printf("SubShape Number: %d\n", gShapeDesc[type].subShapeNumber);

    if(gShapeDesc[type].subShapeNumber > 0) {
        for(i = 0; i< gShapeDesc[type].subShapeNumber; i++) {
            printf("    SubShape[%d], w:%d, h:%d\n",i,gShapeDesc[type].pSubArray[i].w, gShapeDesc[type].pSubArray[i].h);
            printf("    Array:\n");
            for(j=0; j<gShapeDesc[type].pSubArray[i].h; j++) {
                printf("        ");
                for (k = 0; k < gShapeDesc[type].pSubArray[i].w; k++) {
                    if(gShapeDesc[type].pSubArray[i].desc[j][k]) {
                        //printf("%d ", gShapeDesc[type].pSubArray[i].desc[j][k]);
                        printf("O ");
                    }
                    else {
                        if(j==0 && k==0) {
                            printf("* ");
                        }
                        else {
                            printf("  ");
                        }
                    }
                }
                printf("\n");
            }
        }
    }

    return 0;
}

int showSubShapeDescriptor(SubShapeDescriptor subShape)
{
    int i,k,j;
    
    for(i = 0; i< subShape.h; i++){
        for(j = 0; j< subShape.w; j++) {
            if(subShape.desc[i][j]) {
                //printf("%d ", gShapeDesc[type].pSubArray[i].desc[j][k]);
                 printf("O ");
            }
            else {
                if(j==0 && i==0) {
                     printf("* ");
                }
                else {
                    printf("  ");
                }
            }
        }
        printf("\n");
    }

    return 0;
}

int showAllShapeDescriptor()
{
    int i;

    for(i=0; i<SHAPE_TYPE_MAX; i++) {
        showShapeDescriptor(i);
        printf("----------------------------------\n");
    }

    return 0;
}


int showShapeIndex() 
{
    printf("\n%d:\n",SHAPE_TYPE_STAR);
    printf("O   O\n");
    printf("  O  \n");
    printf("O   O\n");

    printf("\n%d:\n",SHAPE_TYPE_M);
    printf("  O   O  \n");
    printf("O   O   O\n");

    printf("\n%d:\n",SHAPE_TYPE_BIG_CORNER);
    printf("O    \n");
    printf("O    \n");
    printf("O O O\n");

    printf("\n%d:\n",SHAPE_TYPE_ZIGZAG);
    printf("O O    \n");
    printf("  O O O\n");

    printf("\n%d:\n",SHAPE_TYPE_SQUARE_HORN);
    printf("O O    \n");
    printf("O O O  \n");

    printf("\n%d:\n",SHAPE_TYPE_OPEN_MOUTH);
    printf("O O O\n");
    printf("O   O\n");

    printf("\n%d:\n",SHAPE_TYPE_BIG_L);
    printf("O O O O\n");
    printf("O      \n");

    printf("\n%d:\n",SHAPE_TYPE_LINE_HORN);
    printf("O O O O\n");
    printf("  O    \n");

    printf("\n%d:\n",SHAPE_TYPE_SMALL_L);
    printf("O O O\n");
    printf("O    \n");

    printf("\n%d:\n",SHAPE_TYPE_SMALL_CORNER);
    printf("O   \n");
    printf("O O \n");

    printf("\n%d:\n",SHAPE_TYPE_SQUARE);
    printf("O O\n");
    printf("O O\n");

    printf("\n%d:\n",SHAPE_TYPE_LINE);
    printf("O O O O\n");

    return 0;
}

ShapeDescriptor *getShapeDescriptor(int type)
{
    if(type < 0 || type >= SHAPE_TYPE_MAX || gShapeDesc == NULL) {
        return NULL;
    }

    return (ShapeDescriptor *)&gShapeDesc[type];
}
