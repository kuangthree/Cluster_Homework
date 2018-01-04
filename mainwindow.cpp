#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mChanged = true;
    ui->setupUi(this);
    connect(ui->addButton,SIGNAL(clicked(bool)),this,SLOT(addElement()));
    connect(ui->deleteButton,SIGNAL(clicked(bool)),this,SLOT(removeElement()));
    connect(ui->avgButton,SIGNAL(clicked(bool)),this,SLOT(onPressAverageAlgorithm()));
    connect(ui->completeButton,SIGNAL(clicked(bool)),this,SLOT(onPressCompleterAlgorithm()));
    connect(ui->singleButton,SIGNAL(clicked(bool)),this,SLOT(onPressSingleAlgorithm()));
    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(displayElement(QListWidgetItem*)));
    connect(ui->vertexCountSpin,SIGNAL(valueChanged(int)),this,SLOT(onChangeVertexCount(int)));
    connect(ui->maxTaskCountSpin,SIGNAL(valueChanged(int)),this,SLOT(onMaxTaskChange()));
    onChangeVertexCount(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initAlgorithm()
{
    if(!mChanged){
        return;
    }
    mChanged = false;
    mAlgorithm = ClusterAlgorithm();
    mAlgorithm.setClusterMaxSize(ui->maxTaskCountSpin->value());
    mAlgorithm.setClusterMinSize(2);
    mAlgorithm.setClusterNumber(ui->vertexCountSpin->value());
    int maxPrice = 0;
    for(Param p:mParamList){
        if(p.price>maxPrice){
            maxPrice = p.price;
        }
    }
    AdjacencyMatrix am(ui->vertexCountSpin->value(),maxPrice+1);
    for(Param p:mParamList){
        am.put(p.source,p.destination , maxPrice+1-p.price);
    }
    mAlgorithm.setAdjacencyMatrix(am);
}

void MainWindow::refreshList()
{
    ui->listWidget->clear();
    for(int index = 0;index < mParamList.size();index++){
        QString title =QString::number(index+1)
                + QString("  ")
                + QString::number(mParamList[index].source)
                + QString("->")
                + QString::number(mParamList[index].destination)
                + QString("  ")
                + QString::number(mParamList[index].price);
        ui->listWidget->addItem(title);
    }
}

int MainWindow::priceCompute(const QSet<Cluster>& clusters)
{
    if(clusters.size()<=1){
        return 0;
    }
    if(clusters.size()==2){
        auto l = clusters.toList();
        Cluster a = l[0];
        Cluster b = l[1];
        int sum = 0;
        for(auto i:a.getElements()){
            for(auto j:b.getElements()){
                for(auto k:mParamList){
                    if(k.source == i && k.destination == j){
                        sum+=k.price;
                        continue;
                    }
                }
            }
        }
        return sum;
    }
    int sum = 0;
    auto list = clusters.toList();
    for(int i=0;i<list.size();i++){
        for(int j=i+1;j<list.size();j++){
            if(i == j)continue;
            QSet<Cluster> newCluster;
            newCluster.insert(list[i]);
            newCluster.insert(list[j]);
            sum+=priceCompute(newCluster);
        }
    }
    return sum;
}

void MainWindow::addElement()
{
    mChanged = true;
    Param p;
    p.destination = ui->destComboBox->currentText().toInt();
    p.source = ui->sourceComboBox->currentText().toInt();
    p.price = ui->priceSpinBox->value();
    if(p.destination == p.source){
        QMessageBox::information(this,"错误","源与目标结点不可以相同",QMessageBox::Yes);
        return;
    }
    int searchIndex = -1;
    for(int i=0;i<mParamList.size();++i){
        if(mParamList[i].source == p.source && mParamList[i].destination == p.destination){
            searchIndex = i;
            break;
        }
    }
    if(searchIndex>=0){
        mParamList[searchIndex].price = p.price;
    }else{
        mParamList.append(p);
    }
    refreshList();
}

void MainWindow::removeElement()
{
    mChanged = true;
    int destination = ui->destComboBox->currentText().toInt();
    int source = ui->sourceComboBox->currentText().toInt();
    int searchIndex = -1;
    for(int i=0;i<mParamList.size();i++){
        if(destination == mParamList[i].destination && source == mParamList[i].source){
            searchIndex = i;
            break;
        }
    }
    if(searchIndex>=0){
        mParamList.removeAt(searchIndex);
    }
    refreshList();
}

void MainWindow::displayElement(QListWidgetItem* item)
{
    QString str = item->text();
    QStringList list = str.split("  ");
    QString n = list[0];
    Param p = mParamList[n.toInt()-1];
    ui->destComboBox->setCurrentIndex(p.destination);
    ui->sourceComboBox->setCurrentIndex(p.source);
    ui->priceSpinBox->setValue(p.price);
}

void MainWindow::onPressSingleAlgorithm()
{
    initAlgorithm();
    ui->outComeListWidget->clear();
    auto retSet = mAlgorithm.singleAlgorithm();
    QList<ClusterAlgorithmOutcomeTuple> list = retSet.toList();
    std::sort(list.begin(),list.end(),
                [](const ClusterAlgorithmOutcomeTuple&a,
                   const ClusterAlgorithmOutcomeTuple& b){
                         return a.distanceThreshold < b.distanceThreshold;
                });
    for(auto tuple:list){
        QString str = tuple.toString()+QString(" 代价：")+QString::number(priceCompute(tuple.clusterSet));
        ui->outComeListWidget->addItem(str);
    }
}

void MainWindow::onPressCompleterAlgorithm()
{
    initAlgorithm();
    ui->outComeListWidget->clear();
    auto retSet = mAlgorithm.completerAlgorithm();
    QList<ClusterAlgorithmOutcomeTuple> list = retSet.toList();
    std::sort(list.begin(),list.end(),
                [](const ClusterAlgorithmOutcomeTuple&a,
                   const ClusterAlgorithmOutcomeTuple& b){
                         return a.distanceThreshold < b.distanceThreshold;
                });
    for(auto tuple:list){
        QString str = tuple.toString()+QString(" 代价：")+QString::number(priceCompute(tuple.clusterSet));
        ui->outComeListWidget->addItem(str);
    }
}

void MainWindow::onPressAverageAlgorithm()
{
    initAlgorithm();
    ui->outComeListWidget->clear();
    auto retSet = mAlgorithm.averageAlgorithm();
    QList<ClusterAlgorithmOutcomeTuple> list = retSet.toList();
    std::sort(list.begin(),list.end(),
                [](const ClusterAlgorithmOutcomeTuple&a,
                   const ClusterAlgorithmOutcomeTuple& b){
                         return a.distanceThreshold < b.distanceThreshold;
                });
    for(auto tuple:list){
        QString str = tuple.toString()+QString(" 代价：")+QString::number(priceCompute(tuple.clusterSet));
        ui->outComeListWidget->addItem(str);
    }
}

void MainWindow::onChangeVertexCount(int count)
{
    mChanged = true;
    ui->sourceComboBox->clear();
    ui->destComboBox->clear();
    for(int i=0;i<count;i++){
        ui->sourceComboBox->addItem(QString::number(i));
        ui->destComboBox->addItem(QString::number(i));
    }
    ui->sourceComboBox->setCurrentIndex(0);
    ui->destComboBox->setCurrentIndex(0);
}

void MainWindow::onMaxTaskChange()
{
    mChanged = true;
}
