#include "avl_tree.h"

#include <stdio.h>
#include <iostream>

int64_t insertCount = 0;


AvlTree
MakeEmpty( AvlTree T )
{
    if( T != NULL )
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

int64_t
FindLT( ElementType X, AvlTree T )
{
    if( T == NULL )
        return -1;
    if( X < T->Element )
        return FindLT( X, T->Left );
    else
    if( X > T->Element )
        return FindLT( X, T->Right );
    else
        return T->offset;
}

int64_t
FindLTE( ElementType X, AvlTree T, ElementType limit )
{
    if(T) {
        if( X < T->Element )
            if(!T->Left) {
                return 0;
            }
            else {
                return FindLTE( X, T->Left, limit );
            }
        else
        if( X > T->Element) {
            if(!T->Right) {
                return T->offset;
            }
            else {
                return FindLTE( X, T->Right, limit );
            }
        }
        else
            return T->offset;
    }

    return limit;
}

PositionAVL
FindMin( AvlTree T )
{
    if( T == NULL )
        return NULL;
    else
    if( T->Left == NULL )
        return T;
    else
        return FindMin( T->Left );
}


/* START: fig4_36.txt */
static int64_t
Height( PositionAVL P )
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}
/* END */

static ElementType
Max( ElementType Lhs, ElementType Rhs )
{
    return Lhs > Rhs ? Lhs : Rhs;
}

/* START: fig4_39.txt */
/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */
/* Update heights, then return new root */

static PositionAVL
SingleRotateWithLeft( PositionAVL K2 )
{
    PositionAVL K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  /* New root */
}
/* END */

/* This function can be called only if K1 has a right child */
/* Perform a rotate between a node (K1) and its right child */
/* Update heights, then return new root */

static PositionAVL
SingleRotateWithRight( PositionAVL K1 )
{
    PositionAVL K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;  /* New root */
}

/* START: fig4_41.txt */
/* This function can be called only if K3 has a left */
/* child and K3's left child has a right child */
/* Do the left-right double rotation */
/* Update heights, then return new root */

static PositionAVL
DoubleRotateWithLeft( PositionAVL K3 )
{
    /* Rotate between K1 and K2 */
    K3->Left = SingleRotateWithRight( K3->Left );

    /* Rotate between K3 and K2 */
    return SingleRotateWithLeft( K3 );
}
/* END */

/* This function can be called only if K1 has a right */
/* child and K1's right child has a left child */
/* Do the right-left double rotation */
/* Update heights, then return new root */

static PositionAVL
DoubleRotateWithRight( PositionAVL K1 )
{
    /* Rotate between K3 and K2 */
    K1->Right = SingleRotateWithLeft( K1->Right );

    /* Rotate between K1 and K2 */
    return SingleRotateWithRight( K1 );
}

int64_t lookup(ElementType X, AvlTree T) {
    while (true) {
        if (X == T->Element)
            return T->offset;
        else if (X < T->Element)
            T = T->Left;
        else
            T = T->Right;

    }
}



/* START: fig4_37.txt */
AvlTree
Insert( int64_t offset, ElementType X, AvlTree T )
{
    if( T == NULL )
    {
        insertCount++;
//        std::cout << "Insert Count: " << insertCount << "s\n";
        /* Create and return a one-node tree */
        T = (AvlTree) malloc( sizeof( struct AvlNode ) );
        if( T == NULL )
            printf( "Out of space!!!" );
        else
        {
            T->Element = X; T->Height = 0;
            T->Left = T->Right = NULL;
            T->offset = offset;
        }
    }
    else
    if( X < T->Element )
    {
        T->Left = Insert( offset, X, T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 ){
            if( X < T->Left->Element )
                T = SingleRotateWithLeft( T );
            else
                T = DoubleRotateWithLeft( T );
        }
    }
    else
    if( X > T->Element )
    {
        T->Right = Insert( offset, X, T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 ){
            if( X > T->Right->Element )
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
        }
    }
    /* Else X is in the tree already; we'll do nothing */

    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;

    return T;
}


/* END */
IntPair createOffsetPair(PositionAVL first, PositionAVL second, ElementType limit){
    IntPair op = (IntPair) malloc(sizeof(struct int_pair));
    if (first && second){
        if (first->offset == 0)
            op->first = first->offset;
        else
            op->first = first->offset+1;
        op->second = second->offset;
    }
    else if (first){
        if (first->offset == 0)
            op->first = first->offset;
        else
            op->first = first->offset+1;
        op->second = limit;
    }
    else if (second){
        op->first = 0;
        op->second = second->offset;
    }
    else{
        op->first = 0;
        op->second = limit;
    }
    return op;
}

PositionAVL
FindMax( AvlTree T )
{
    if( T != NULL )
        while( T->Right != NULL )
            T = T->Right;

    return T;
}

IntPair
FindNeighborsLT( ElementType X, AvlTree T, ElementType limit )
{
    PositionAVL first = 0, second = 0;
    //if( T == NULL )
    //	return NULL;

    while (T != NULL) {
        if( X < T->Element ){
            second = T;
            T = T->Left;
        }
        else if( X > T->Element ){
            first = T;
            T = T->Right;
        }
        else {
            second = T;
            if(T->Left != NULL) {
                first = FindMax(T->Left);
            }
            break;
        }
    }

    return createOffsetPair(first, second, limit);
}



IntPair
FindNeighborsGTE( ElementType X, AvlTree T, ElementType limit )
{
    PositionAVL first = 0, second = 0;
    //if( T == NULL )
    //	return NULL;

    while (T != NULL) {
        if( X < T->Element ){
            second = T;
            T = T->Left;
        }
        else if( X > T->Element ){
            first = T;
            T = T->Right;
        }
        else {
            first = T;		// this is the only difference from FindNeighborsLT !
            break;
        }
    }

    return createOffsetPair(first, second, limit);
}



void _GetNodesInOrder(AvlTree T, std::vector<AvlTree>& vector) {
    if (T->Left) {
        _GetNodesInOrder(T->Left, vector);
    }
    vector.push_back(T);
    if (T->Right) {
        _GetNodesInOrder(T->Right, vector);
    }
}

IntPair FindBiggestPiece(int64_t low_key,int64_t high_key, AvlTree T, int64_t limit,IndexEntry*& c){
    IntPair p,p_2,last_piece;
    int64_t offset_size = 0;
    p = FindNeighborsLT(low_key, T, limit);
    last_piece = FindNeighborsLT(high_key, T, limit);
    if (p->second == limit)
        return p;
    offset_size = p->second - p->first;
    p_2 = FindNeighborsLT(c[p->second+1].m_key, T, limit);
    if(p_2->second == limit)
        if (p_2->second - p_2->first > offset_size)
            return p_2;
        else
            return p;
    while (p_2->first != p->first && p_2->second != p->second ){
       if (p_2->second - p_2->first > offset_size)
           p = p_2;
       if(p_2->first == last_piece->first && p_2->second == last_piece->second)
           return p;
        p_2 = FindNeighborsLT(c[p_2->second+1].m_key, T, limit);
        if (p_2->second - p_2->first > offset_size)
            return p_2;
        else
            return p;
    }
}

void FindTwoBiggestPieces(int64_t low_key,int64_t high_key, AvlTree T, int64_t limit,IndexEntry*& c, IntPair &biggest_piece, IntPair &second_biggest){
    IntPair last_piece, aux,aux_2;
    int64_t offset_size = 0;
    biggest_piece = FindNeighborsLT(low_key, T, limit);
    last_piece = FindNeighborsLT(high_key, T, limit);
    second_biggest = biggest_piece;
    if (biggest_piece->second == limit ||biggest_piece->second == last_piece->second){
        return;
    }
    offset_size = biggest_piece->second - biggest_piece->first;
    aux = FindNeighborsLT(c[biggest_piece->second+1].m_key, T, limit);
    size_t counter =1;
    while (aux->first != biggest_piece->first && aux->second != biggest_piece->second && aux->second != limit){
        if (aux->second - aux->first > offset_size){
            counter =1;
            second_biggest = biggest_piece;
            biggest_piece = aux;
        }
        if(aux->first == last_piece->first && aux->second == last_piece->second)
            return ;
        aux_2 = FindNeighborsLT(c[aux->second+counter].m_key, T, limit);
        if (aux->first == aux_2->first && aux->second == aux_2->second)
            counter++;
        else aux = aux_2;
    }
}



void Print( AvlTree T ){

    if(T==NULL)
        return;

    printf("(%lld,%lld) ",(long long int) T->Element, (long long int) T->offset);
    Print(T->Right);
    Print(T->Left);
    printf("\n");
}
