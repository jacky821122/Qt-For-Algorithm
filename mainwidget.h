#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>

namespace Ui {
class MainWidget;
}

class cell
{
public:
    cell(int a, int b){x = a; y = b; is_in = 0; is_out = 0; is_tar = 0; is_obs = 0;}
    ~cell();
    int x, y;
    bool is_in, is_out, is_tar, is_obs;
};

class MainWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void paintEvent(QPaintEvent *);
        QPainter *paint;
        QPoint point;
            QRect rect;
            QSize size;
            void parsing(QString);
                void parsing_output(QString);
                int delta,times;

private slots:
    void on_action_Imput_FIle_triggered();

    void on_action_Outputfile_triggered();

    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
