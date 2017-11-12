#ifndef CLUSTERALGORITHMOUTCOMETUPLE_H
#define CLUSTERALGORITHMOUTCOMETUPLE_H
#include<QSet>
#include "cluster.h"

class ClusterAlgorithmOutcomeTuple
{
    friend uint qHash(const ClusterAlgorithmOutcomeTuple& a);
public:
    ClusterAlgorithmOutcomeTuple(int d,const QSet<Cluster>& k);
    int distanceThreshold;
    QSet<Cluster> clusterSet;
    bool operator == (const ClusterAlgorithmOutcomeTuple&)const;
    QString toString();
};

#endif // CLUSTERALGORITHMOUTCOMETUPLE_H
