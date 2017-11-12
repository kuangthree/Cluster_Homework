#include "clusteralgorithmoutcometuple.h"

ClusterAlgorithmOutcomeTuple::ClusterAlgorithmOutcomeTuple(int d, const QSet<Cluster> &k)
{
    clusterSet = k;
    distanceThreshold = d;
}

bool ClusterAlgorithmOutcomeTuple::operator ==(const ClusterAlgorithmOutcomeTuple &a) const
{
    return distanceThreshold == a.distanceThreshold && clusterSet == a.clusterSet;
}

QString ClusterAlgorithmOutcomeTuple::toString()
{
    QString ret;
    ret.append("<");
    ret.append(QString::number(distanceThreshold));
    ret.append(",");
    ret.append(QString::number(clusterSet.size()));
    ret.append(",");
    ret.append("{");
    bool first = true;
    for(auto r:clusterSet){
        if(!first){
            ret.append(",");
        }else{
            first = false;
        }
        ret.append("{");
        bool innerFirst = true;
        for(int t : r.getElements()){
            if(!innerFirst){
                ret.append(",");
            }else{
                innerFirst = false;
            }
            ret.append(QString::number(t));
        }
        ret.append("}");
    }
    ret.append("}>");
    return ret;
}

uint qHash(const ClusterAlgorithmOutcomeTuple& a){
    return qHash(a.clusterSet) ^ qHash(a.distanceThreshold);
}
