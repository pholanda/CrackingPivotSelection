#pragma once

#include <vector>
#include <cstdlib>
#include <iostream>

#include <iomanip>

#include <cmath>
#include <queue>
#include <climits>
#include <algorithm>

struct Column {
    std::vector<int64_t> data;
};

struct RangeQuery {
    std::vector<int64_t> leftpredicate;
    std::vector<int64_t> rightpredicate;
};
class IndexEntry {
public:


    int64_t m_key;
    int64_t m_rowId;

    IndexEntry(int64_t i)
            : m_key(i)
            , m_rowId(-1)
    {
    }

    IndexEntry()
            : m_key(-1)
            , m_rowId(-1)
    {}

    IndexEntry(int64_t key, int64_t rowId)
            : m_key(key)
            , m_rowId(rowId)
    {}
//Query comparisons
    bool operator>(int64_t& other) const { return m_key > other; }
    bool operator>=(int64_t& other) const { return m_key >= other; }
    bool operator<(int64_t& other) const { return m_key < other; }
    bool operator<=(int64_t& other) const { return m_key <= other; }
    bool operator!=(int64_t& other) const { return m_key != other; }
    bool operator==(int64_t& other) const { return m_key == other; }

    bool operator>(const IndexEntry& other) const { return m_key > other.m_key; }
    bool operator>=(const IndexEntry& other) const { return m_key >= other.m_key; }
    bool operator<(const IndexEntry& other) const { return m_key < other.m_key; }
    bool operator<=(const IndexEntry& other) const { return m_key <= other.m_key; }
    bool operator!=(const IndexEntry& other) const { return m_key != other.m_key; }

};

struct int_pair
{
    int64_t first;
    int64_t second;
};
typedef struct int_pair *IntPair;

typedef int64_t ElementType;

struct AvlNode;

typedef struct AvlNode *PositionAVL;
typedef struct AvlNode *AvlTree;

struct AvlNode
{
    ElementType Element;
    int64_t offset;

    AvlTree  Left;
    AvlTree  Right;
    int64_t      Height;
};
