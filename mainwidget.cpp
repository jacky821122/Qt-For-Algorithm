#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPainter>
#include <QFileDialog>
#include <QVector>
//#include <string>
//#include <fstream>
//#include <sstream>

//using namespace std;

int PathNum = 10, m = 100, n = 100, in_x = 0, in_y = 0, out_x, out_y, tmplength, tmpwidth, screen, pointx, pointy;
QVector<QVector<cell*> > C;
QVector<QVector<cell*> > QvPath;
//vector<vector<cell*> > c;
//vector<vector<cell*> > vPath;

MainWidget::MainWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(PathNum);
    ui->label_2->setHidden(1);
    ui->label_3->setHidden(1);
    ui->label_4->setHidden(1);
    ui->label_5->setHidden(1);
    for(int i = 0; i < m; ++i)
    {
        QVector<cell*> QColcell;
        //vector<cell*> Colcell;
        for(int j = 0; j < n; ++j)
        {
            cell* tmpc = new cell(i, j);
            //Colcell.push_back(tmpc);
            QColcell.push_back(tmpc);
        }
        //c.push_back(Colcell);
        C.push_back(QColcell);
    }
    screen = height()*0.8;
    delta = 1;
    times = 1;
    size = QSize(0,0);
    pointx = (width() - screen) / 2;
    pointy = (height() - screen) / 2;
    rect = QRect(point, size);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::paintEvent(QPaintEvent *)
{
    paint = new QPainter(this);
    paint->setBrush(QBrush(QColor(0, 147, 255), Qt::SolidPattern));
        for (int x = pointx; x < pointx+((screen%m == 0)? screen/m : screen/m+1)*m; x+=((screen%m == 0)? screen/m : screen/m+1)) {
        for (int y = pointy; y <pointy + ((screen%n == 0)? screen/n : screen/n + 1)*n; y+=(screen%n == 0)? screen/n : screen/n + 1) {

            int coorxtoX = (x - pointx)/((screen%m == 0)? screen/m : screen/m+1)+1;
            int coorytoY = n - (y - pointy)/((screen%n == 0)? screen/n : screen/n + 1);

            paint->save();
            paint->translate(x, y);

            if(C[coorxtoX - 1][coorytoY - 1]->is_tar == true)
            {
                paint->setBrush(QBrush(QColor(232, 143, 13), Qt::SolidPattern));
            }

            if(delta == 1)
            {
                QVector<QVector<cell* > > QtmpvPath = QvPath;
                //vector<vector<cell* > > tmpvPath = vPath;
                int R = 255, G = 219, B = 25;
                while(!QtmpvPath.empty())
                                {
                                    QVector<cell*> QtmpPath1 = QtmpvPath.back();
                                    //vector<cell*> tmpPath1 = tmpvPath.back(); //path
                                    for(int i = 1; i < times; ++i)
                                    {
                                        QtmpvPath.pop_back();
                                        QtmpPath1 = QtmpvPath.back();
                                    }

                                    while(!QtmpPath1.empty())
                                    {
                                        cell* tmpc = QtmpPath1.back(); //path nodes

                                        if(coorxtoX-1 == tmpc->x && coorytoY-1 == tmpc->y)
                                        {
                                            paint->setBrush(QBrush(QColor(R, G, B), Qt::SolidPattern));
                                        }


                                            if(coorxtoX-1 == tmpc->x && coorytoY-1 == tmpc->y && C[coorxtoX - 1][coorytoY - 1]->is_tar == true)
                                            {
                                                paint->setBrush(QBrush(QColor(255, 255, 255), Qt::SolidPattern));
                                            }

                                        QtmpPath1.pop_back();
                                    }
                                    QtmpvPath.pop_back();
                                    R -= 50;
                                    G -= 50;
                                    B += 50;
                                    if (R < 50 || G < 50 || B > 200)
                                    {
                                        R = 255;
                                        G = 219;
                                        B = 25;
                                    }
                                    break;
                                }
            }



            if((coorxtoX == in_x && coorytoY == in_y) || (coorxtoX == out_x && coorytoY == out_y))
            {
                paint->setBrush(QBrush(QColor(0, 255, 0), Qt::SolidPattern));
                if(coorxtoX == in_x && coorytoY == in_y)
                    paint->setBrush(QBrush(QColor(255, 0, 0), Qt::SolidPattern));
            }

            if(C[coorxtoX - 1][coorytoY - 1]->is_obs == true)
            {
                paint->setBrush(QBrush(QColor(192, 200, 232), Qt::SolidPattern));
            }

            /*if(coorxtoX == 1 && coorytoY == 1)
            {
                paint->setBrush(QBrush(QColor(0, 0, 0), Qt::SolidPattern));
            }*/

            paint->drawRect(rect);
            paint->restore();
        }
    }
}

void MainWidget::parsing(QString Filename)
{
    for(int i = 0; i < m; ++i)
    {
        //c[i].clear();
        C[i].clear();
    }
    //c.clear();
    C.clear();
    QFile Qfin(Filename);

    //string file = Filename.toStdString();

    //string line;
    //stringstream ss;
    int lineCount = 1, lineCellNum;
        //fstream fin(file.c_str());
        if(Qfin.open(QIODevice::ReadOnly))
        {
            while(!Qfin.atEnd())
                {
                QString Qline = Qfin.readLine();
                QStringList tokens = Qline.split(" ");
                    //istringstream token(line);
                    if (lineCount == 1) // Deal With M. N. Cin.x Cout.y
                    {
                        //token >> m;
                        //token >> n;
                        m = tokens.at(0).toInt();
                        n = tokens.at(1).toInt();
                        for(int i = 0; i < m; ++i)
                        {
                            QVector<cell*> QColcell;
                            //vector<cell*> Colcell;
                            for(int j = 0; j < n; ++j)
                            {
                                cell* tmpc = new cell(i, j);
                                //Colcell.push_back(tmpc);
                                QColcell.push_back(tmpc);
                            }
                            //c.push_back(Colcell);
                            C.push_back(QColcell);
                        }

                        /*----------Cinput-----------*/
                        //token >> in_x;
                        //token >> in_y;
                        in_x = tokens.at(2).toInt();
                        in_y = tokens.at(3).toInt();
                        //c[in_x - 1][in_y - 1]->is_in = true;
                        C[in_x - 1][in_y - 1]->is_in = true;
                        /*----------Coutput-----------*/
                        //token >> out_x;
                        //token >> out_y;
                        out_x = tokens.at(4).toInt();
                        out_y = tokens.at(5).toInt();
                        //c[out_x - 1][out_y - 1]->is_out = true;
                        C[out_x - 1][out_y - 1]->is_out = true;
                    }
                    else // Deal With Targets and Obstacles
                    {
                        //token >> lineCellNum;
                        lineCellNum = tokens.at(0).toInt();

                        for (int i = 1; i <= lineCellNum*2; i+=2)
                        {
                            int tmpx, tmpy;
                            //token >> tmpx;
                            //token >> tmpy;
                            tmpx = tokens.at(i).toInt();
                            tmpy = tokens.at(i+1).toInt();

                            if(lineCount == 2)
                            {
                                //c[tmpx - 1][tmpy - 1]->is_tar = true;
                                C[tmpx - 1][tmpy - 1]->is_tar = true;
                            }
                            else
                            {
                                C[tmpx - 1][tmpy - 1]->is_obs = true;
                                //c[tmpx - 1][tmpy - 1]->is_obs = true;
                            }
                        }
                    }
                    lineCount++;
                }
        }


        tmplength = screen/m;
        tmpwidth = screen/n;
        size = QSize(tmplength, tmpwidth);
        rect = QRect(point, size);
        delta = 0;

        QString cinx, ciny, coutx, couty, label2text, label3text;
        cinx.setNum(in_x);
        ciny.setNum(in_y);
        coutx.setNum(out_x);
        couty.setNum(out_y);
        label2text = QString("Cin : (");
        label2text.append(cinx);
        label2text.append(",");
        label2text.append(ciny);
        label2text.append(") (Red)");
        ui->label_2->setText(label2text);
        ui->label_2->setHidden(false);
        label3text = QString("Cout : (");
        label3text.append(coutx);
        label3text.append(",");
        label3text.append(couty);
        label3text.append(") (Green)");
        ui->label_3->setText(label3text);
        ui->label_3->setHidden(false);

        ui->label_4->setHidden(1);
        ui->label_5->setHidden(1);
        update();
}

void MainWidget::parsing_output(QString Filename)
{
        delta = 1;
        //string file = Filename.toStdString();
        //fstream fin(file.c_str());
        QFile Qfin(Filename);
        //if(!fin.is_open()) {}
        //string line;
        //stringstream ss;
        int lineCount = 1, lineCellNum;
        int totalPathLength = 0;
        Qfin.open(QIODevice::ReadOnly);
    //getline(fin, line);

        while(!Qfin.atEnd())
            {
                QString Qline = Qfin.readLine();
                QStringList tokens = Qline.split(" ");
                //istringstream token(line);
                if (lineCount == 1)
                {

                    //token >> PathNum;
                    PathNum = tokens.at(0).toInt();
                }
                else
                {
                    //token >> lineCellNum;
                    lineCellNum = tokens.at(0).toInt();
                    QVector<cell*> QtmpPath;
                    //vector<cell*> tmpPath;
                    for (int i = 1; i <= lineCellNum*2; i+=2)
                    {
                        int tmpx, tmpy;
                        //token >> tmpx;
                        //token >> tmpy;
                        tmpx = tokens.at(i).toInt();
                        tmpy = tokens.at(i+1).toInt();
                        QtmpPath.push_back(C[tmpx - 1][tmpy - 1]);
                        ++totalPathLength;
                    }
                    QvPath.push_back(QtmpPath);
                }
                lineCount++;
            }

        ui->spinBox->setMaximum(PathNum);
        QString label4("Totol Length : "), label5("Number of Paths : "), numofpath, pathlength;
        numofpath.setNum(PathNum);
        label5.append(numofpath);
        ui->label_5->setText(label5);
        ui->label_5->show();
        pathlength.setNum(totalPathLength);
        label4.append(pathlength);
        ui->label_4->setText(label4);
        ui->label_4->show();
        update();
}

void MainWidget::on_action_Imput_FIle_triggered()
{
    QString FileName;
        QFileDialog dialog(this, tr("Open Files"), tr("../algorithm_qt"));
        QPoint pos = dialog.pos();
        QPoint pos1 = this -> pos();
        if (pos.x() != pos1.x()) pos.setX(pos1.x());
        if (pos.y() != pos1.y()) pos.setY(pos1.y());
        dialog.move(pos);
        FileName = dialog.getOpenFileName();
        if (!FileName.isEmpty())
        {
            this->parsing(FileName);
        }
}

void MainWidget::on_action_Outputfile_triggered()
{
    QString FileName;
        QFileDialog dialog(this, tr("Open Files"), tr("../algorithm_qt"));
        QPoint pos = dialog.pos();
        QPoint pos1 = this -> pos();
        if (pos.x() != pos1.x()) pos.setX(pos1.x());
        if (pos.y() != pos1.y()) pos.setY(pos1.y());
        dialog.move(pos);
        FileName = dialog.getOpenFileName();
        if (!FileName.isEmpty())
        {
            this->parsing_output(FileName);
        }
}

void MainWidget::on_pushButton_clicked()
{
    delta = 0;
    update();
}

void MainWidget::on_spinBox_valueChanged(int arg1)
{
    times = arg1;
    delta = 1;
    if(times < 1) times = 1;
    if(times > PathNum) times = PathNum;
    update();
}
