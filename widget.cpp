#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    showKey = new QLabel(this);
    resize(500, 400);
    showKey->setGeometry(20, 20, 60, 20);
    showKey->setText("init");
    installEventFilter(this);
    connect(&overTimer,SIGNAL(timeout()),this,SLOT(timeout()));
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *object, QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *key = static_cast<QKeyEvent *>(e);
        switch (key->key())
        {
        case Qt::Key_W:
            showKey->setText("press W");
            snake.whenUpPress();
            break;
        case Qt::Key_A:
            showKey->setText("press A");
            snake.whenLeftPress();
            break;
        case Qt::Key_S:
            showKey->setText("press S");
            snake.whenDownPress();
            break;
        case Qt::Key_D:
            showKey->setText("press D");
            snake.whenRightPress();
            break;
        case Qt::Key_Up:
            showKey->setText("press ↑");
            snake.whenUpPress();

            break;
        case Qt::Key_Down:
            showKey->setText("press ↓");
            snake.whenDownPress();

            break;
        case Qt::Key_Left:
            showKey->setText("press ←");
            snake.whenLeftPress();
            break;
        case Qt::Key_Right:
            showKey->setText("press →");
            snake.whenRightPress();
            break;
        default:
            showKey->setText("error key");
            snake.whenTimeOut();
            break;
        }
        overTimer.start(350);
        update();
    }
    return QWidget::eventFilter(object, e);
}

void Widget::paintEvent(QPaintEvent *)
{
    static int qq = 0;
    qDebug()<<"paintEvent"<<qq++;
    QPainter painter(this);
    painter.setPen(Qt::black);
    QVector<QLine> lines;
    QVector<QRect> rects;
    for (int i = 0; i <= 16; i++)
    {
        // x
        lines.append(getLine(0, i, 16, i));

        // y
        lines.append(getLine(i, 0, i, 16));
    }
    double w = getScal(16);
    double h = w;
    unsigned char ww = 0;
    unsigned char hh = 0;
    char *mp = snake.getMap(&ww, &hh);
    QPoint ori = getOrigin();
    for (int i = 0; i < hh; i++)
    {
        for (int j = 0; j < ww; j++)
        {
            if (mp[i*BitGame::poix+j] != 0)
                rects.append(QRect(QPoint(ori.x() + 1 + static_cast<int>(j * w), ori.y() + 1 + static_cast<int>(i * h)),
                                   QPoint(ori.x() - 2 + static_cast<int>((j + 1) * w), ori.y() - 2 + static_cast<int>((i + 1) * h))));
        }
    }
    painter.drawLines(lines);
    QBrush b(QColor("blue"));
    painter.setBrush(b);
    painter.drawRects(rects);
}

QPoint Widget::getOrigin(void)
{
    int min = (width() < height()) ? (width()) : (height());
    QPoint ret(0, 0);
    ret.rx() = (width() - min) / 2;
    ret.ry() = (height() - min) / 2;
    return ret;
}
double Widget::getScal(int pix)
{
    double min = (width() < height()) ? (width()) : (height());
    return min / pix;
}
QLine Widget::getLine(int x1, int y1, int x2, int y2)
{
    QPoint origin = getOrigin();
    double scal = getScal(16);
    return QLine(static_cast<int>(x1 * scal + origin.x()),
                 static_cast<int>(y1 * scal + origin.y()),
                 static_cast<int>(x2 * scal + origin.x()),
                 static_cast<int>(y2 * scal + origin.y()));
}
void Widget::timeout()
{
    snake.whenTimeOut();
    update();
}
