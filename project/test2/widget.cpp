#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene;
    mytrain = new train(0);
    bar[0] = new lightbars(0);
    bar[1] = new lightbars(200);
    bar[2] = new lightbars(400);
    bar[3] = new lightbars(600);
    bar[4] = new lightbars(800);
    bar[5] = new lightbars(1000);
    bar[6] = new lightbars(1200);
    bar[7] = new lightbars(1400);

    light[0] = new lights(0);
    light[1] = new lights(200);
    light[2] = new lights(400);
    light[3] = new lights(600);
    light[4] = new lights(800);
    light[5] = new lights(1000);
    light[6] = new lights(1200);
    light[7] = new lights(1400);

    scene->setSceneRect(-300, -300, 1600, 800); //meaning?
//    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->addItem(mytrain);
    scene->addItem(bar[0]);
    scene->addItem(bar[1]);
    scene->addItem(bar[2]);
    scene->addItem(bar[3]);
    scene->addItem(bar[4]);
    scene->addItem(bar[5]);
    scene->addItem(bar[6]);
    scene->addItem(bar[7]);

    scene->addItem(light[0]);
    scene->addItem(light[1]);
    scene->addItem(light[2]);
    scene->addItem(light[3]);
    scene->addItem(light[4]);
    scene->addItem(light[5]);
    scene->addItem(light[6]);
    scene->addItem(light[7]);


    QObject::connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setBackgroundBrush(Qt::cyan);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
//    ui->graphicsView->resize(800, 600);
    ui->graphicsView->show();

    //todo: connect--> lb has car-->emit signal, left lb send signal, right lb recive signal and turn into orange
    //connect(bar[0],SIGNAL(lightbars::lbChange(int)),bar[1],SLOT(lightbars::lbSet(int)));
//    QObject::connect(bar[0],lightbars::lbChange(int),bar[1],lightbars::lbSet(1));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{

}

void Widget::on_start_btn_clicked()
{

    //todo use btn to control
    timer.start(1000/33);
}

void Widget::on_stop_btn_clicked()
{
    timer.stop();
}
