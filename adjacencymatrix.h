#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

#include<QVector>
/*
author: Shensheng Kuang
*/
class AdjacencyMatrix
{
public:
    AdjacencyMatrix();
    AdjacencyMatrix(int size,int defaultValue);
    explicit AdjacencyMatrix(int size);
    AdjacencyMatrix(const AdjacencyMatrix& src);
    AdjacencyMatrix& operator=(const AdjacencyMatrix& src);
    virtual ~AdjacencyMatrix();
    int get(int x,int y)const;
    int put(int x,int y,int value);
    int maxDistance()const;
    int size()const;
private:
    QVector<QVector<int>> mMatrix;
    void init(int size,int defaultValue);
};

#endif // ADJACENCYMATRIX_H
