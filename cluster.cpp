#include "cluster.h"
#include <cfloat>
uint qHash(const Cluster &a)
{
    return qHash(a.mElements);
}

Cluster::Cluster(int e)
{
    mElements.insert(e);
}

Cluster::Cluster()
{

}

Cluster::Cluster(const Cluster &src)
{
    this->mElements = src.mElements;
}

Cluster::~Cluster()
{

}

void Cluster::put(int e)
{
    mElements.insert(e);
}

bool Cluster::contains(int e) const
{
    return mElements.contains(e);
}

bool Cluster::isSingle() const
{
    return mElements.size()==1;
}

bool Cluster::isEmpty() const
{
    return mElements.isEmpty();
}

int Cluster::size() const
{
    return mElements.size();
}

const Cluster Cluster::operator+(const Cluster &added) const
{
    Cluster out;
    out.mElements = this->mElements + added.mElements;
    return out;
}

const Cluster Cluster::operator-(const Cluster &subed) const
{
    Cluster out;
    out.mElements = this->mElements - subed.mElements;
    return out;
}

Cluster& Cluster::operator+=(const Cluster &added)
{
    *this = *this + added;
    return *this;
}

Cluster& Cluster::operator-=(const Cluster &subed)
{
    *this = *this - subed;
    return *this;
}

QSet<int> Cluster::getElements()
{
    return mElements;
}

bool Cluster::operator==(const Cluster &e) const
{
    return e.mElements == this->mElements;
}

double Cluster::maxDistance(const AdjacencyMatrix &adjacencyMatrix, const Cluster &m) const
{
    if(this->isEmpty() || m.isEmpty()){
        throw "The cluster is empty!";
    }
    double max = 0.0;
    for(int a:m.mElements){
        for(int b:this->mElements){
            int distance = adjacencyMatrix.get(a,b);
            if(distance > max){
                max = distance;
            }
        }
    }
    return max;
}

double Cluster::minDistance(const AdjacencyMatrix &adjacencyMatrix, const Cluster &m) const
{
    if(this->isEmpty() || m.isEmpty()){
        throw "The cluster is empty!";
    }
    double min = DBL_MAX;
    for(int a:m.mElements){
        for(int b:this->mElements){
            int distance = adjacencyMatrix.get(a,b);
            if(distance < min){
                min = distance;
            }
        }
    }
    return min;
}

double Cluster::avgDistance(const AdjacencyMatrix &adjacencyMatrix, const Cluster &m) const
{
    if(this->isEmpty() || m.isEmpty()){
        throw "The cluster is empty!";
    }
    double sum = 0.0;
    int count = 0;
    for(int a:m.mElements){
        for(int b:this->mElements){
            int distance = adjacencyMatrix.get(a,b);
            sum+=distance;
            count++;
        }
    }
    return sum/count;
}
