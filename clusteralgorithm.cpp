#include "clusteralgorithm.h"
#include <limits>
ClusterAlgorithm::ClusterAlgorithm()
{
    mClusterMaxSize = INT_MAX;
}

ClusterAlgorithm::ClusterAlgorithm(const ClusterAlgorithm &src)
{
    *this = src;
}

ClusterAlgorithm::ClusterAlgorithm(int num, const AdjacencyMatrix &am)
{
    setClusterNumber(num);
    setAdjacencyMatrix(am);
    mClusterMaxSize = INT_MAX;
}

void ClusterAlgorithm::setClusterNumber(int num)
{
    this->mClusterSet.clear();
    for(int i=0;i<num;i++){
        mClusterSet.insert(Cluster(i));
    }
}

void ClusterAlgorithm::setClusterMaxSize(int num)
{
    mClusterMaxSize = num;
}

void ClusterAlgorithm::setClusterMinSize(int num)
{
    mClusterMinSize = num;
}

void ClusterAlgorithm::setAdjacencyMatrix(const AdjacencyMatrix& am)
{
    mAdjacencyMatrix = am;
    mMaxDistance = am.maxDistance();
}

const ClusterAlgorithm &ClusterAlgorithm::operator=(const ClusterAlgorithm &src)
{
    mAdjacencyMatrix = src.mAdjacencyMatrix;
    mMaxDistance = src.mMaxDistance;
    mClusterMaxSize = src.mClusterMaxSize;
    mClusterSet = src.mClusterSet;
    return *this;
}

QSet<Cluster> ClusterAlgorithm::getOriginClusterSet() const
{
    return mClusterSet;
}

AdjacencyMatrix ClusterAlgorithm::getAdjacencyMatrix() const
{
    return mAdjacencyMatrix;
}
bool ClusterAlgorithm::existsPairClusterMinDistanceSmallerThan(const QSet<Cluster>&set,Cluster& a,Cluster&b,int threshold)
{
    if(set.size()<=1)return false;
    QList<Cluster> list = set.toList();
    for(int i=0;i<list.size();i++){
        for(int j=i+1;j<list.size();j++){
            if(list[i].minDistance(mAdjacencyMatrix,list[j])<=threshold){
                if(list[i].size()+list[j].size()>mClusterMaxSize){
                    continue;
                }
                a = list[i];
                b = list[j];
                return true;
            }
        }
    }
    return false;
}

bool ClusterAlgorithm::existsPairClusterMaxDistanceSmallerThan(const QSet<Cluster> &set, Cluster &a, Cluster &b, int threshold)
{
    if(set.size()<=1)return false;
    QList<Cluster> list = set.toList();
    for(int i=0;i<list.size();i++){
        for(int j=i+1;j<list.size();j++){
            if(list[i].maxDistance(mAdjacencyMatrix,list[j])<=threshold){
                if(list[i].size()+list[j].size()>mClusterMaxSize){
                    continue;
                }
                a = list[i];
                b = list[j];
                return true;
            }
        }
    }
    return false;
}

bool ClusterAlgorithm::existsPairClusterAvgDistanceSmallerThan(const QSet<Cluster> &set, Cluster &a, Cluster &b, int threshold)
{
    if(set.size()<=1)return false;
    QList<Cluster> list = set.toList();
    for(int i=0;i<list.size();i++){
        for(int j=i+1;j<list.size();j++){
            if(list[i].avgDistance(mAdjacencyMatrix,list[j])<=threshold){
                int clusterSize = list[i].size()+list[j].size();
                if(clusterSize>mClusterMaxSize){
                    continue;
                }
                a = list[i];
                b = list[j];
                return true;
            }
        }
    }
    return false;
}
QSet<ClusterAlgorithmOutcomeTuple> ClusterAlgorithm::singleAlgorithm()
{
    QSet<Cluster> set= mClusterSet;
    int distanceThreshold = 0;
    int clusterCount = mClusterSet.size();
    QSet<ClusterAlgorithmOutcomeTuple> ret;
    ret.insert(ClusterAlgorithmOutcomeTuple(distanceThreshold,set));
    while(clusterCount != 1 && distanceThreshold <= mMaxDistance){
        distanceThreshold ++;
        Cluster a,b;
        while(existsPairClusterMinDistanceSmallerThan(set,a,b,distanceThreshold)){
            set.remove(a);
            set.remove(b);
            set.insert(a+b);
            clusterCount = set.size();
        }
        ret.insert(ClusterAlgorithmOutcomeTuple(distanceThreshold,set));
    }
    return ret;
}

QSet<ClusterAlgorithmOutcomeTuple> ClusterAlgorithm::completerAlgorithm()
{
    QSet<Cluster> set= mClusterSet;
    int distanceThreshold = 0;
    int clusterCount = mClusterSet.size();
    QSet<ClusterAlgorithmOutcomeTuple> ret;
    ret.insert(ClusterAlgorithmOutcomeTuple(distanceThreshold,set));
    while(clusterCount != 1 && distanceThreshold <= mMaxDistance){
        distanceThreshold ++;
        Cluster a,b;
        while(existsPairClusterMaxDistanceSmallerThan(set,a,b,distanceThreshold)){
            set.remove(a);
            set.remove(b);
            set.insert(a+b);
            clusterCount = set.size();
        }
        ret.insert(ClusterAlgorithmOutcomeTuple(distanceThreshold,set));
    }
    return ret;
}

QSet<ClusterAlgorithmOutcomeTuple> ClusterAlgorithm::averageAlgorithm()
{
    QSet<Cluster> set= mClusterSet;
    int distanceThreshold = 0;
    int clusterCount = mClusterSet.size();
    QSet<ClusterAlgorithmOutcomeTuple> ret;
    ret.insert(ClusterAlgorithmOutcomeTuple(distanceThreshold,set));
    while(clusterCount != 1 && distanceThreshold <= mMaxDistance){
        distanceThreshold ++;
        Cluster a,b;
        while(existsPairClusterAvgDistanceSmallerThan(set,a,b,distanceThreshold)){
            set.remove(a);
            set.remove(b);
            set.insert(a+b);
            clusterCount = set.size();
        }
        ret.insert(ClusterAlgorithmOutcomeTuple(distanceThreshold,set));
    }
    return ret;
}
