#include "adjacencymatrix.h"

AdjacencyMatrix::AdjacencyMatrix()
{

}

AdjacencyMatrix::AdjacencyMatrix(int size,int defaultValue)
{
    init(size,defaultValue);
}

AdjacencyMatrix::AdjacencyMatrix(int size)
{
    init(size,0);
}

AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix &src)
{
    *this = src;
}

AdjacencyMatrix &AdjacencyMatrix::operator=(const AdjacencyMatrix &src)
{
    this->mMatrix = src.mMatrix;
    return *this;
}

AdjacencyMatrix::~AdjacencyMatrix()
{

}

int AdjacencyMatrix::get(int x, int y)const
{
    return mMatrix[x][y];
}

int AdjacencyMatrix::put(int x, int y, int value)
{
    mMatrix[x][y]=value;
    mMatrix[y][x]=value;
    return value;
}

int AdjacencyMatrix::maxDistance()const
{
    int max = 0;
    int size = mMatrix.size();
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(i!=j && mMatrix[i][j]>max){
                max = mMatrix[i][j];
            }
        }
    }
    return max;
}

int AdjacencyMatrix::size() const
{
    return mMatrix.size();
}

void AdjacencyMatrix::init(int size,int defaultValue)
{
    mMatrix = QVector<QVector<int>>(size);
    for(int i = 0;i<size;++i){
        mMatrix[i] = QVector<int>(size);
        for(int j = 0;j<size;++j){
            mMatrix[i][j]=defaultValue;
        }
    }
}
