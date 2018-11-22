#include <cstdlib>
#include <vector>
#include "../structs.h"

AvlTree MakeEmpty( AvlTree T );

int64_t FindLT( ElementType X, AvlTree T );
int64_t FindLTE( ElementType X, AvlTree T, ElementType limit );
PositionAVL FindMin( AvlTree T );
AvlTree Insert( int64_t offset, ElementType X, AvlTree T );
IntPair FindNeighborsLT( ElementType X, AvlTree T, ElementType limit );
IntPair FindNeighborsGTE( ElementType X, AvlTree T, ElementType limit );
int64_t lookup(ElementType X, AvlTree T);
AvlTree FindNeighborsLT( ElementType X, AvlTree T);
AvlTree FindNeighborsGTFinal( ElementType X, AvlTree T);

std::vector<AvlTree> GetNodesInOrder(AvlTree T);
AvlTree FindFirstPiece( AvlTree T );
AvlTree FindLastPiece( AvlTree T );
AvlTree FindNeighborsLTFinal( ElementType X, AvlTree T);
AvlTree FindNodeLTE( ElementType X, AvlTree T);
IntPair FindBiggestPiece(int64_t low_key,int64_t high_key, AvlTree T, int64_t limit,IndexEntry*& c);
void FindTwoBiggestPieces(int64_t low_key,int64_t high_key, AvlTree T, int64_t limit,IndexEntry*& c, IntPair &biggest_piece, IntPair &second_biggest);
// AvlTree FindNodeLTE( ElementType X, AvlTree T, ElementType limit );

void Print( AvlTree T );
