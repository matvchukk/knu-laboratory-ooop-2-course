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
