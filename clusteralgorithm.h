#ifndef CLUSTERALGORITHM_H
#define CLUSTERALGORITHM_H
#include "adjacencymatrix.h"
#include "cluster.h"
#include "clusteralgorithmoutcometuple.h"
#include <QSet>
class ClusterAlgorithm
{
public:
    ClusterAlgorithm();
    ClusterAlgorithm(const ClusterAlgorithm& src);
    ClusterAlgorithm(int num,const AdjacencyMatrix& am);
    void setClusterNumber(int num);
    void setClusterMaxSize(int num);
    void setAdjacencyMatrix(const AdjacencyMatrix& am);
    const ClusterAlgorithm& operator=(const ClusterAlgorithm& src);
    QSet<Cluster> getOriginClusterSet()const;
    AdjacencyMatrix getAdjacencyMatrix()const;
    QSet<ClusterAlgorithmOutcomeTuple> singleAlgorithm();
    QSet<ClusterAlgorithmOutcomeTuple> completerAlgorithm();
    QSet<ClusterAlgorithmOutcomeTuple> averageAlgorithm();
private:
    QSet<Cluster> mClusterSet;
    int mClusterMaxSize;
    int mMaxDistance;
    AdjacencyMatrix mAdjacencyMatrix;
    bool existsPairClusterMinDistanceSmallerThan(const QSet<Cluster>&set,Cluster& a,Cluster&b,int threshold);
    bool existsPairClusterMaxDistanceSmallerThan(const QSet<Cluster>&set,Cluster& a,Cluster&b,int threshold);
    bool existsPairClusterAvgDistanceSmallerThan(const QSet<Cluster>&set,Cluster& a,Cluster&b,int threshold);
};

#endif // CLUSTERALGORITHM_H
