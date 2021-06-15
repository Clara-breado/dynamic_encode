#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    getStaticData();

    scene = new QGraphicsScene;
    mytrain = new train(140,600);

    //test case
//    lightbars* test = new lightbars(3300,780,400,1);
//    scene->addItem(test);

    //

    scene->setSceneRect(-20, 0, 5000, 800);
    train_1 = new logic_train(nullptr,0,550);

    scene->addItem(train_1->view_train);

    for(int i=0;i<34;i++){
        scene->addItem(lb[i]->view_lb);
    }
    for(int i=0;i<38;i++){
        //scene->addItem(light[i]);
        scene->addItem(lt[i]->view_lt);
    }

    //scene->addItem(lt[0]->view_lt);

    QObject::connect(&train_1->mytimer, SIGNAL(timeout()), scene, SLOT(advance()));

    //logic run
    for(int i = 0;i<19;i++){
        QObject::connect(&timer, SIGNAL(timeout()), lb[i], SLOT(timerTest()));
        QObject::connect(train_1,SIGNAL(sendPos(int,int)),lb[i],SLOT(changeState(int,int)));

    }
    //进站咽喉
//    QObject::connect(&timer, SIGNAL(timeout()),lb[0],SLOT(JzState()));
//    QObject::connect(&timer, SIGNAL(timeout()),lb[14],SLOT(JzState()));

    //区间光带
    for(int i = 13;i>5;i--){
        QObject::connect(lb[i],SIGNAL(stateChanged(int)),lb[i-1],SLOT(toChangestate(int)));
    }
    QObject::connect(&timer,SIGNAL(timeout()),train_1,SLOT(timerStart()));

    //区间信号机，接受下一区段码字
    for(int i = 6;i<15;i++){
        QObject::connect(lb[i],SIGNAL(stateChanged(int)),lt[i],SLOT(JM(int)));
    }
    QObject::connect(lb[0],SIGNAL(sendJzState(int)),lt[0],SLOT(JzJM(int)));
    QObject::connect(lb[14],SIGNAL(sendJzState(int)),lt[14],SLOT(JzJM(int)));


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

    int line_dt[5];
    for(int i=2; i<row_count; ++i)
    {
        for(int j=2; j<=6; ++j)
        {
            QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", i, j);
            //QVariant cell_value = cell->property("Value");  //获取单元格内容
            QString cell_value = cell->property("Value2").toString();  //获取单元格内容
            line_dt[j-2] = cell_value.toInt();
        }
        int lb_x = int(line_dt[0]-0.5*line_dt[2]);
        int lb_y = line_dt[1]-5;
        lb[i-2] = new logic_lb(nullptr,lb_x,lb_y,line_dt[2],line_dt[3],line_dt[4]);
    }

    //初始化信号机
    int line_dt_2[4];
    work_sheet = work_book->querySubObject("Sheets(int)", 2);
    used_range = work_sheet->querySubObject("UsedRange");
    rows = used_range->querySubObject("Rows");
    columns = used_range->querySubObject("Columns");
    row_count = rows->property("Count").toInt();  //获取行数
    column_count = columns->property("Count").toInt();  //获取列数
    qDebug()<<row_count<<endl;
    for(int i=2; i<row_count; ++i)
    {
        for(int j=2; j<=5; ++j)
        {
            QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", i, j);
            //QVariant cell_value = cell->property("Value");  //获取单元格内容
            QString cell_value = cell->property("Value2").toString();  //获取单元格内容
            line_dt_2[j-2] = cell_value.toInt();
        }
        light[i-2] = new lights(line_dt_2[0],line_dt_2[1],line_dt_2[2],line_dt_2[3]);
        lt[i-2] = new logic_light(nullptr,line_dt_2[0],line_dt_2[1],line_dt_2[2],line_dt_2[3]);

    }


    work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
    excel.dynamicCall("Quit(void)");  //退出
}

void Widget::on_zx_recieve_clicked()
{
    lb[0]->jl_type = 0;
    lb[0]->JZ_FLAG = true;

    lb[14]->jl_type = 0;
    lb[14]->JZ_FLAG = true;
}
