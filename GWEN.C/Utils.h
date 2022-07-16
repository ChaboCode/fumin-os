#pragma once

typedef struct lklistnode LkListNode;
typedef struct lnklistnode LexList;

struct lnklistnode {
        int data;
        LkListNode *next;
};
