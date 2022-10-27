#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QVector2D>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem* ball;
    QGraphicsEllipseItem *wheel1, *wheel2;
    QGraphicsPixmapItem *car;
    QGraphicsPixmapItem *man;
    //int dx,dy;
    QPointF *ballVelocity;
    qreal scale;

private slots:
    void BallGo();
};

#endif // MAINWINDOW_H
