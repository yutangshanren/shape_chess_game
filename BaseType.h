#ifndef BASE_TYPE_H
#define BASE_TYPE_H

#ifdef __cplusplus
extern "C"{
#endif

typedef enum {
    //   *   *
    //     *
    //   *   *
    SHAPE_TYPE_STAR = 0,

    //   *    *
    // *   *    *
    SHAPE_TYPE_M,

    //  *
    //  *
    //  *  *  *
    SHAPE_TYPE_BIG_CORNER,

    // *  *
    //    *  *  *
    SHAPE_TYPE_ZIGZAG,

    //  *  *
    //  *  *  *
    SHAPE_TYPE_SQUARE_HORN,

    // *  *  *
    // *     * 
    SHAPE_TYPE_OPEN_MOUTH,

    // *  *  *  *
    // *
    SHAPE_TYPE_BIG_L,

    // *  *  *  *
    //    *
    SHAPE_TYPE_LINE_HORN,

    // *  *  *
    // *
    SHAPE_TYPE_SMALL_L,

    // *
    // *  *
    SHAPE_TYPE_SMALL_CORNER,

    // *  *
    // *  *
    SHAPE_TYPE_SQUARE,

    // *  *  *  *
    SHAPE_TYPE_LINE,

    SHAPE_TYPE_MAX
}ShapeType_E;

typedef struct {
    int w;
    int h;
    int desc[4][4];
} SubShapeDescriptor;

typedef struct{
    int type;
    int subShapeNumber;
    SubShapeDescriptor *pSubArray;
} ShapeDescriptor;

#define BOARD_SIZE 10
typedef struct {
    int board[BOARD_SIZE][BOARD_SIZE];
}GameBoard;


struct PlayTree{
    struct PlayTree *parent;
    struct PlayTree *sibling;
    int type;
    int subtype;
    int xpos;
    int ypos;
};


/**
 * Shape related.
 * 
 */
extern int initShapeDescriptor();
extern int showShapeDescriptor(int type);
extern int showAllShapeDescriptor();
extern int showShapeIndex();
extern ShapeDescriptor *getShapeDescriptor(int type);
extern int showSubShapeDescriptor(SubShapeDescriptor subShape);
extern int showBoard2(GameBoard *pb);

/**
 * @brief init board.
 * 
 * @param pb 
 * @return int 
 */
extern int initBoard(GameBoard *pb);

/**
 * @brief show board.
 * 
 * @param pb 
 * @return int 
 */
extern int showBoard(GameBoard *pb);

/**
 * @brief addShapeOnBoard
 * 
 * @param pb 
 * @param desc 
 * @param row 
 * @param colum 
 * @return int 
 */
extern int addShapeOnBoard(GameBoard *pb, SubShapeDescriptor subShape, int row, int column, int shapeType);

/**
 * @brief checkShapeOnBoard
 * 
 * @param pb 
 * @param desc 
 * @param row 
 * @param colum 
 * @return int 
 */
extern int checkShapeOnBoard(GameBoard *pb, SubShapeDescriptor subShape, int row, int column);

extern int constructBoardFromTreeNode(GameBoard *pb, struct PlayTree *pNode);


#ifdef __cplusplus
}
#endif

#endif

