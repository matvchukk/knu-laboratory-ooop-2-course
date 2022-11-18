#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif
#include "area.h"

DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    isDrawing = false;
    modified = false;
    myColor = Qt::red;
    myWidth = 2;
}

void DrawingArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing = true;
        lastPoint = event->pos();
    }
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && isDrawing)
        drawLineTo(event->pos());
}

void DrawingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDrawing)
    {
        isDrawing = false;
        drawLineTo(event->pos());
    }
}

void DrawingArea::paintEvent(QPaintEvent *event)
{
    QPainter craft(this);
    QRect updated = event->rect();
    craft.drawImage(updated, image, updated);
}

void DrawingArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height())
    {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void DrawingArea::drawLineTo(const QPoint &endPoint)
{
    QPainter craft(&image);
    craft.setPen(QPen(myColor, myWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    craft.drawLine(lastPoint, endPoint);
    int newSize= (myWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-newSize, -newSize, +newSize, +newSize));
    lastPoint = endPoint;

    modified = true;
}

void DrawingArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)   return;

    QImage picture(newSize, QImage::Format_RGB32);
    picture.fill(qRgb(255, 255, 255));
    QPainter craft(&picture);
    craft.drawImage(QPoint(0, 0), *image);
    *image = picture;
}

void DrawingArea::print()
{
    #if QT_CONFIG(printdialog)

    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted)
    {
        QPainter painter(&printer);
        QSize size = image.size();
        QRect pos = painter.viewport();

        size.scale(pos.size(), Qt::KeepAspectRatio);
        painter.setViewport(pos.x(), pos.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
    #endif
}

void DrawingArea::setColor(const QColor &newColor)
{
    myColor = newColor;
}

void DrawingArea::setWidth(int newWidth)
{
    myWidth = newWidth;
}

void DrawingArea::clear()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

bool DrawingArea::openFile(const QString &file)
{
    QImage newPicture;
    if (!newPicture.load(file)) return false;
    QSize newSize = newPicture.size().expandedTo(size());
    resizeImage(&newPicture, newSize);
    image = newPicture;
    modified = false;
    update();
    return true;
}

bool DrawingArea::saveFile(const QString &file, const char *format)
{
    QImage newPicture = image;
    resizeImage(&newPicture, size());

    if (!newPicture.save(file, format))
    {
        return false;
    }
    else
    {
        modified = false;
        return true;
    }
}
