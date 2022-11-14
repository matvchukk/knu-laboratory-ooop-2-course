#ifndef AREA_H
#define AREA_H

#include <QWidget>

#include <QColor>
#include <QPoint>
#include <QImage>

class DrawingArea : public QWidget
{
    Q_OBJECT
public:
    DrawingArea(QWidget *parent = nullptr);
    bool openFile(const QString &file);
    bool saveFile(const QString &file, const char *fileFormat);
    void setColor(const QColor &color);
    void setWidth(int width);

    bool pictureModified() const
    {
        return modified;
    }

    QColor penColor() const
    {
        return myColor;
    }

    int penWidth() const
    {
        return myWidth;
    }

public slots:
    void print();
    void clear();

protected:
    void mousePressEvent(QMouseEvent *events) override;
    void mouseMoveEvent(QMouseEvent *events) override;
    void mouseReleaseEvent(QMouseEvent *events) override;
    void paintEvent(QPaintEvent *events) override;
    void resizeEvent(QResizeEvent *events) override;

private:
    void drawLineTo(const QPoint &end);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool isDrawing;
    int myWidth;
    QColor myColor;
    QImage image;
    QPoint lastPoint;
};

#endif // AREA_H
