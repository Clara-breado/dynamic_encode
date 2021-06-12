#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    getStaticData();

    scene = new QGraphicsScene;
    mytrain = new train(0,100);
    train_1 = new logic_train(nullptr,0,60);
//    bar[0] = new lightbars(0);
//    bar[1] = new lightbars(200);
//    bar[2] = new lightbars(400);
//    bar[3] = new lightbars(600);
//    bar[4] = new lightbars(800);
//    bar[5] = new lightbars(1000);
//    bar[6] = new lightbars(1200);
//    bar[7] = new lightbars(1400);

//    lb[0] = new logic_lb(nullptr,0,0,200,45);
//    lb[1] = new logic_lb(nullptr,200);
//    lb[2] = new logic_lb(nullptr,400);
//    lb[3] = new logic_lb(nullptr,600);
//    lb[4] = new logic_lb(nullptr,800);
//    lb[5] = new logic_lb(nullptr,1000);
//    lb[6] = new logic_lb(nullptr,1200);
//    lb[7] = new logic_lb(nullptr,1400);

    light[0] = new lights(0);
    light[1] = new lights(200);
    light[2] = new lights(400);
    light[3] = new lights(600);
    light[4] = new lights(800);
    light[5] = new lights(1000);
    light[6] = new lights(1200);
    light[7] = new lights(1400);
    light[8] = new lights(0,160);

    scene->setSceneRect(-20, 0, 5000, 800); //meaning?
    //scene->addItem(mytrain);
    scene->addItem(train_1->view_train);
//    scene->addItem(bar[0]);
//    scene->addItem(bar[1]);
//    scene->addItem(bar[2]);
//    scene->addItem(bar[3]);
//    scene->addItem(bar[4]);
//    scene->addItem(bar[5]);
//    scene->addItem(bar[6]);
//    scene->addItem(bar[7]);
    for(int i=0;i<50;i++){
        scene->addItem(lb[i]->view_lb);
    }



    scene->addItem(light[0]);
    scene->addItem(light[1]);
    scene->addItem(light[2]);
    scene->addItem(light[3]);
    scene->addItem(light[4]);
    scene->addItem(light[5]);
    scene->addItem(light[6]);
    scene->addItem(light[7]);
    scene->addItem(light[8]);


    QObject::connect(&train_1->mytimer, SIGNAL(timeout()), scene, SLOT(advance()));

    //logic run
    for(int i = 0;i<8;i++){
        QObject::connect(&timer, SIGNAL(timeout()), lb[i], SLOT(timerTest()));
        QObject::connect(train_1,SIGNAL(sendPos(int,int)),lb[i],SLOT(changeState(int,int)));
    }
    for(int i = 7;i>0;i--){
        QObject::connect(lb[i],SIGNAL(stateChanged(int)),lb[i-1],SLOT(toChangestate(int)));
    }
    QObject::connect(&timer,SIGNAL(timeout()),train_1,SLOT(timerStart()));



    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setBackgroundBrush(Qt::cyan);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
//    ui->graphicsView->resize(800, 600);
    ui->graphicsView->show();

    //timer.start(1000/33);

    //todo :pre light --> nxt lightbar && light --> train(through lightbar? redlight send signal to train)

    //connect(bar[0],SIGNAL(lightbars::lbChange(int)),bar[1],SLOT(lightbars::lbSet(int)));
//    QObject::connect(bar[0],lightbars::lbChange(int),bar[1],lightbars::lbSet(1));

}

Widget::~Widget()
{
    delete ui;
    //timer.stop();
}

void Widget::on_pushButton_clicked()
{

}

void Widget::on_start_btn_clicked()
{

    //todo use btn to control
   train_1->mytimer.start(1000/33);
    timer.start(1000/33);
}

void Widget::on_stop_btn_clicked()
{
    train_1->mytimer.stop();
    timer.stop();
}

void Widget::on_zx_send_clicked()
{

}

void Widget::getStaticData(){
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible", false);
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    work_books->dynamicCall("Open (const QString&)", filePath);
    QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
    QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets

    //初始化光带
    QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);
    QAxObject *used_range = work_sheet->querySubObject("UsedRange");
    QAxObject *rows = used_range->querySubObject("Rows");
    QAxObject *columns = used_range->querySubObject("Columns");
    int row_start = used_range->property("Row").toInt();  //获取起始行
    int column_start = used_range->property("Column").toInt();  //获取起始列
    int row_count = rows->property("Count").toInt();  //获取行数
    int column_count = columns->property("Count").toInt();  //获取列数

    QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", 3, 2);
    QString cell_value = cell->property("Value2").toString();  //获取单元格内容
    int a  = cell_value.toInt();
    qDebug()<<a<<endl;

    int line_dt[4];
    for(int i=2; i<row_count; ++i)
    {
        for(int j=2; j<=5; ++j)
        {
            QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", i, j);
            //QVariant cell_value = cell->property("Value");  //获取单元格内容
            QString cell_value = cell->property("Value2").toString();  //获取单元格内容
            line_dt[j-2] = cell_value.toInt();
        }
        int lb_x = int(line_dt[0]-0.5*line_dt[2]);
        int lb_y = line_dt[1]-5;
        lb[i-2] = new logic_lb(nullptr,lb_x,lb_y,line_dt[2],line_dt[3]);
    }




    work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
    excel.dynamicCall("Quit(void)");  //退出
}
