#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clusteralgorithm.h"
#include <QListWidgetItem>
#include <QMessageBox>
/*
author Shensheng Kuang
*/
namespace Ui {
class MainWindow;
}

struct Param
{
    int source;
    int destination;
    int price;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ClusterAlgorithm mAlgorithm;
    bool mChanged;
    QList<Param> mParamList;
    void initAlgorithm();
    void refreshList();
    int priceCompute(const QSet<Cluster>& clusters);
private slots:
    void addElement();
    void removeElement();
    void displayElement(QListWidgetItem*);
    void onPressSingleAlgorithm();
    void onPressCompleterAlgorithm();
    void onPressAverageAlgorithm();
    void onChangeVertexCount(int);
    void onMaxTaskChange();
};

#endif // MAINWINDOW_H
