#include "displaywidget.h"

#include <QHeaderView>
#include <QPainter>
#include <QPen>
#include <qmath.h>

DisplayWidget::DisplayWidget(QWidget *parent) :
    QTableView(parent)
{
    //this->setGridStyle(Qt::DotLine);
    this->setShowGrid(false);
    this->currentTool = t_box;

    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

void DisplayWidget::toolChanged()
{
    QAction* toolAction = (QAction*)sender();
    currentTool = toolAction->data().value<DrawTool>();
}

void DisplayWidget::tileChanged(WorldTile newTile)
{
    this->selectedTile = newTile;
}

void DisplayWidget::mousePressEvent(QMouseEvent *event)
{

    switch(currentTool)
    {
    case t_pen:
        break;
    case t_box:
    case t_hollow_box:
    case t_circle:
    case t_hollow_circle:
    {
        rubberBandOrigin = event->pos();
        if(!rubberBand)
        {
            rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        }

        QRect geometry = QRect(rubberBandOrigin, QSize());
        int headerHeight = this->horizontalHeader()->height();
        int headerWidth = this->verticalHeader()->width();
        rubberBand->setGeometry(geometry.adjusted(headerWidth, headerHeight, headerWidth, headerWidth));
        rubberBand->show();
        break;
    }
    default:
        break;
    }
}

void DisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(this->rect().contains(event->pos()))
    {
        switch(currentTool)
        {
        case t_pen:
        {
            QVariant v;
            v.setValue(selectedTile);
            model()->setData(this->indexAt(event->pos()), v);
            break;
        }
        case t_box:
        case t_hollow_box:
        case t_circle:
        case t_hollow_circle:
        {
            QRect geometry = QRect(rubberBandOrigin, event->pos()).normalized();
            int headerHeight = this->horizontalHeader()->height();
            int headerWidth = this->verticalHeader()->width();
            rubberBand->setGeometry(geometry.adjusted(headerWidth, headerHeight, headerWidth, headerHeight));

            if(currentTool == t_circle || currentTool == t_hollow_circle)
            {
            }

            break;
        }
        default:
            break;
        }
    }
}

void DisplayWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QVariant v;
    v.setValue(selectedTile);

    switch(currentTool)
    {
    case t_pen:
    {
        model()->setData(this->indexAt(event->pos()), v);
        break;
    }
    case t_box:
    case t_hollow_box:
    case t_circle:
    case t_hollow_circle:
    {
        rubberBand->hide();

        int headerHeight = this->horizontalHeader()->height();
        int headerWidth = this->verticalHeader()->width();

        // rubber band draws based on the displays 0,0 as origin
        // indexes use inside corner of the headers as 0,0
        //
        // v-- this is 0,0 for rubber band
        // []=================
        // ||+<-- this is 0,0 for table fields
        // ||
        QRect selection = rubberBand->geometry().adjusted(-headerWidth, -headerHeight, -headerWidth, -headerHeight);
        QModelIndex center = this->indexAt(selection.center());
        QModelIndex topLeft = this->indexAt(selection.topLeft());
        QModelIndex bottomRight = this->indexAt(selection.bottomRight());

        // determine selections
        if(currentTool == t_box)
        {
            for(int i = topLeft.column(); i <= bottomRight.column(); i++)
            {
                for(int j = topLeft.row(); j <= bottomRight.row(); j++)
                {
                    model()->setData(model()->index(j, i), v);
                }
            }
        }
        else if(currentTool == t_hollow_box)
        {
            for(int i = topLeft.column(); i <= bottomRight.column(); i++)
            {
                model()->setData(model()->index(topLeft.row(), i), v);
                model()->setData(model()->index(bottomRight.row(), i), v);
            }
            for(int i = topLeft.row(); i <= bottomRight.row(); i++)
            {
                model()->setData(model()->index(i, topLeft.column()), v);
                model()->setData(model()->index(i, bottomRight.column()), v);
            }
        }
        // currently suffer w/even diameters, index at center does not necessarily correlate to
        // center of the actual circle.  adjust to use diameter / 2 for calculations.
        else if(currentTool == t_circle)
        {
            // x-radius
            double a = bottomRight.column() - center.column();
            // y-radius
            double b = topLeft.row() - center.row();

            // (x-h)^2/a^2 + (y-k)^2/b^2 <= 1
            for(int i = topLeft.column(); i <= bottomRight.column(); i++)
            {
                for(int j = topLeft.row(); j <= bottomRight.row(); j++)
                {
                    double topx = i - center.column();
                    double topy = j - center.row();
                    if(
                      (((topx * topx) / (a * a)) + ((topy * topy) / (b * b))) <= 1.0
                      )
                    {
                        model()->setData(model()->index(j, i), v);
                    }
                }
            }

        }
        else if(currentTool == t_hollow_circle)
        {
            // x(t) = (right - center) * cos(t) = a * cos(t)
            // y(t) = (top - center) * sin(t) = b * sin(t)
            int a = bottomRight.column() - center.column();
            int b = topLeft.row() - center.row();

            for(double d = 0.0; d <= 2 * M_PI; d+=(M_PI / 100))
            {
                int x = center.column() + qRound(a * cos(d));
                int y = center.row() + qRound(b * sin(d));
                model()->setData(model()->index(y, x), v);
            }
        }
        break;
    }
    default:
        break;
    }
}

