#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QLine>
#include <QVector>
#include <QPoint>
#include <QRect>
#include <QTimer>
#include "snake.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    bool eventFilter(QObject *object, QEvent *event);
    ~Widget();
    void paintEvent(QPaintEvent *);
public slots:
    void timeout();
private:
    Ui::Widget *ui;
    QLabel * showKey = nullptr;
    Snake snake;
    QTimer overTimer;
    QPoint getOrigin(void);
    double getScal(int pix);
    QLine getLine(int x1,int y1,int x2,int y2);

};
#endif // WIDGET_H
