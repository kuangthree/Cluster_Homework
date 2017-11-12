#ifndef CLUSTER_H
#define CLUSTER_H
#include "adjacencymatrix.h"
#include <QSet>
/*
author: Shensheng Kuang
*/
class Cluster
{
    friend uint qHash(const Cluster&);
public:
    Cluster(int e);
    Cluster();
    Cluster(const Cluster& src);
    virtual ~Cluster();
    void put(int e);
    bool contains(int e) const;
    bool isSingle() const;
    bool isEmpty() const;
    int size() const;
    const Cluster operator+(const Cluster& added) const;
    const Cluster operator-(const Cluster& subed) const;
    Cluster& operator+=(const Cluster& added);
    Cluster& operator-=(const Cluster& subed);
    QSet<int> getElements();
    bool operator==(const Cluster& e)const;
    double maxDistance(const AdjacencyMatrix& adjacencyMatrix,const Cluster& m) const;
    double minDistance(const AdjacencyMatrix& adjacencyMatrix,const Cluster& m)const;
    double avgDistance(const AdjacencyMatrix& adjacencyMatrix,const Cluster& m)const;
private:
    QSet<int> mElements;
};

#endif // CLUSTER_H
