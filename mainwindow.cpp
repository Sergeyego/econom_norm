#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    modelEl = new ModelRo(this);
    modelWire = new ModelRo(this);

    connect(ui->radioButtonEl,SIGNAL(clicked(bool)),this,SLOT(updProd()));
    connect(ui->radioButtonWire,SIGNAL(clicked(bool)),this,SLOT(updProd()));
    updProd();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updProd()
{
    if (ui->radioButtonEl->isChecked()){
        QSqlQuery query;
        query.prepare("select distinct c.id_el, c.id_diam, NULL, e.marka || ' ф ' || d2.sdim as snam from cena c "
                     "inner join elrtr e on e.id=c.id_el "
                      "inner join diam d2 on d2.id=c.id_diam "
                      "order by snam");
        if (modelEl->execQuery(query)){
            modelEl->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("Наименование"));
        }
        ui->tableViewProd->setModel(modelEl);
    } else {
        QSqlQuery query;
        query.prepare("select distinct wc.id_provol, wc.id_diam, wc.id_pack, p.nam || ' ф' || d.sdim ||' '||wpk.short as snam "
                      "from wire_cena wc "
                      "inner join provol p on p.id=wc.id_provol "
                      "inner join diam d on d.id=wc.id_diam "
                      "inner join  wire_pack_kind wpk on wpk.id=wc.id_pack "
                      "order by snam ");
        if (modelWire->execQuery(query)){
            modelWire->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("Наименование"));
        }
        ui->tableViewProd->setModel(modelWire);
    }
    ui->tableViewProd->setColumnHidden(0,true);
    ui->tableViewProd->setColumnHidden(1,true);
    ui->tableViewProd->setColumnHidden(2,true);
    ui->tableViewProd->setColumnWidth(3,250);
}
