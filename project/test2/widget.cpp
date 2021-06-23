#include "widget.h"
#include "ui_widget.h"
#include <QFileInfo>
#include <QDir>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_menu = new QMenu(this);
    r_menu = new QMenu(this);
    m_yd = new QAction(this);
    r_yd = new QAction(this);
    m_yd->setText("引导发车");
    r_yd->setText("引导接车");
    m_menu->addAction(m_yd);
    r_menu->addAction(r_yd);
    connect(m_yd,SIGNAL(triggered()),this,SLOT(testMenu()));
    connect(r_yd,SIGNAL(triggered()),this,SLOT(r_YD()));


    setContextMenuPolicy(Qt::ActionsContextMenu);
    m_menu->show();

    getStaticData();

    //scene = new QGraphicsScene;
    scene = new myscene;

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

    QObject::connect(&train_1->mytimer, SIGNAL(timeout()), scene, SLOT(advance()));

    //logic run
    for(int i = 0;i<19;i++){
        QObject::connect(&timer, SIGNAL(timeout()), lb[i], SLOT(timerTest()));
        QObject::connect(train_1,SIGNAL(sendPos(int,int)),lb[i],SLOT(changeState(int,int)));

    }

    //区间光带
    for(int i = 14;i>4;i--){
        QObject::connect(lb[i],SIGNAL(stateChanged(int)),lb[i-1],SLOT(toChangestate(int)));
    }

    QObject::connect(&timer,SIGNAL(timeout()),train_1,SLOT(timerStart()));

    //区间信号机，接受下一区段码字
    for(int i = 6;i<15;i++){
        QObject::connect(lb[i],SIGNAL(stateChanged(int)),lt[i],SLOT(JM(int)));
    }
    QObject::connect(lb[0],SIGNAL(sendJzState(int)),lt[0],SLOT(JzJM(int)));
    QObject::connect(lb[14],SIGNAL(sendJzState(int)),lt[14],SLOT(JzJM(int)));
    QObject::connect(lb[4],SIGNAL(sendCzState(int,int)),lt[4],SLOT(CzJM(int,int)));
    QObject::connect(lb[4],SIGNAL(sendCzState(int,int)),lt[34],SLOT(CzJM(int,int)));
    QObject::connect(lb[4],SIGNAL(sendCzState(int,int)),lt[35],SLOT(CzJM(int,int)));


    for(int i=1;i<4;i++){
        QObject::connect(lb[4],SIGNAL(closeGUDAO()),lb[i],SLOT(toCloseGUDAO()));
    }

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setBackgroundBrush(Qt::black);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    ui->graphicsView->show();

    timer.start(1000/33);
}

Widget::~Widget()
{
    delete ui;
    timer.stop();
}


void Widget::on_start_btn_clicked()
{

    //todo use btn to control
   train_1->mytimer.start(1000/33);
    //timer.start(1000/33);
}

void Widget::on_stop_btn_clicked()
{
    train_1->mytimer.stop();
    //timer.stop();
}

void Widget::getStaticData(){
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible", false);
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    work_books->dynamicCall("Open (const QString&)", filePath);

    QAxObject *work_books2 = excel.querySubObject("WorkBooks");
    QAxObject *work_book2 = excel.querySubObject("ActiveWorkBook");
//    work_books2->dynamicCall("Open (const QString&)", filePath2);

    QString fileName = "../static_db_1.xlsx";
    QFileInfo info(fileName);
    if (!info.exists())
        return;
    work_book2 = work_books2->querySubObject("Open(const QString &)", info.absoluteFilePath());

    qDebug()<<info.absoluteFilePath()<<endl;
    QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
    QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets

    //初始化光带
    QAxObject *work_sheet = work_book2->querySubObject("Sheets(int)", 1);
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
    work_sheet = work_book2->querySubObject("Sheets(int)", 2);
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

    train_1->view_train->move_type = 1;

    //update view
    lb[14]->timerTest();
    ui->graphicsView->viewport()->update();
}

void Widget::on_cx_recieve_clicked()
{
    lb[0]->jl_type = 1;
    lb[0]->JZ_FLAG = true;

    lb[14]->jl_type = 1;
    lb[14]->JZ_FLAG = true;

    train_1->view_train->move_type = 2;

    //update view
    lb[14]->timerTest();
    ui->graphicsView->viewport()->update();
}

void Widget::on_lg_recieve_clicked()
{
    lb[0]->jl_type = 2;
    lb[0]->JZ_FLAG = true;

    lb[14]->jl_type = 2;
    lb[14]->JZ_FLAG = true;

    train_1->view_train->move_type = 3;

    //update view
    lb[14]->timerTest();
    ui->graphicsView->viewport()->update();

}

void Widget::on_zx_send_clicked()
{
    lb[4]->CZ_FLAG = true;
    lb[4]->jl_type = 1;

    lb[1]->view_lb->state = 8;

    train_1->view_train->move_type = 4;

    //update view
    lb[4]->timerTest();
    ui->graphicsView->viewport()->update();
}

void Widget::on_cx_send_clicked()
{
    lb[4]->CZ_FLAG = true;
    lb[4]->jl_type = 2;

    lb[2]->view_lb->state = 31;

    train_1->view_train->move_type = 5;

    //update view
    lb[4]->timerTest();
    ui->graphicsView->viewport()->update();
}

void Widget::on_lg_send_clicked()
{
    lb[4]->CZ_FLAG = true;
    lb[4]->jl_type = 3;

    lb[3]->view_lb->state = 41;


    train_1->view_train->move_type = 6;

    //update view
    lb[4]->timerTest();
    ui->graphicsView->viewport()->update();

}



void Widget::on_zx_send_customContextMenuRequested(const QPoint &pos)
{
    showMenu(pos);
}

void Widget::showMenu(const QPoint &pos){
    //qDebug()<<"cliked!"<<endl;
    int wid = ui->zx_send->width();
    int x = ui->zx_send->pos().x();
    int p_x = x+wid;
    int p_y = ui->zx_send->pos().y();
    QPoint tmp(p_x,p_y);

    m_menu->exec(mapToGlobal(tmp));
}

void Widget::showJCMenu(const QPoint &pos){
    int wid = ui->zx_recieve->width();
    int x = ui->zx_recieve->pos().x();
    int p_x = x+wid;
    int p_y = ui->zx_recieve->pos().y();
    QPoint tmp(p_x,p_y);

    r_menu->exec(mapToGlobal(tmp));
}

void Widget::testMenu(){
    //股道HB，咽喉B
    lb[4]->jl_type = 1;
    lb[4]->YD_FLAG = true;
    lb[1]->view_lb->state = 51;
    lb[4]->view_lb->state = 20;
}

void Widget::r_YD(){
    //咽喉：B    一接近：HB
    qDebug()<<"cliked!"<<endl;
    lb[14]->YD_FLAG = true;
    lb[14]->JZ_FLAG = true;
    lb[14]->jl_type = 3;
    lb[14]->getState();
    //lb[13]->view_lb->state = 50;
//    lb[10]->gz_flag = true;
//    lb[11]->getState();
}
void Widget::on_zx_recieve_customContextMenuRequested(const QPoint &pos)
{
    showJCMenu(pos);
}
