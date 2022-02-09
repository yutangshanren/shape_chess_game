#include <stdio.h>
#include <stdlib.h>

#include "BaseType.h"


struct PlayTree * allocPlayTreeNode(int type, int subtype, int x, int y)
{
    struct PlayTree *ptr = NULL;

    ptr = (struct PlayTree *) malloc(sizeof(struct PlayTree));
    if(ptr) {
        ptr->parent = NULL;
        ptr->sibling = NULL;
        ptr->type = type;
        ptr->subtype = subtype;
        ptr->xpos = x;
        ptr->ypos = y;
    }

    return ptr;
}

int releasPlayTreeNode( struct PlayTree *pTree )
{
    if(pTree) {
        free(pTree);
    }

    return 0;
}


