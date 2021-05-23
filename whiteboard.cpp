#include "whiteboard.h"
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QRect>
#include <QColor>
#include <QSize>

Whiteboard::Whiteboard(QWidget *parent)
    : QWidget(parent) {
    setAttribute(Qt::WA_StaticContents);
}

void Whiteboard::setPenColor(const QColor &newColor) {
    curPenColor = newColor;
}

void Whiteboard::setPenWidth(int newWidth) {
    curPenWidth = newWidth;
}

void Whiteboard::clearImage() {
    image.fill(qRgb(255, 255, 255));
    update();
}

void Whiteboard::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        penDown = true;
    }
}

void Whiteboard::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && penDown)
        drawLineTo(event->pos());
}

void Whiteboard::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && penDown) {
        drawLineTo(event->pos());
        penDown = false;
    }
}

void Whiteboard::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void Whiteboard::resizeEvent(QResizeEvent *event) {
    if(width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void Whiteboard::drawLineTo(const QPoint &endPoint) {
    QPainter painter(&image);
    painter.setPen(QPen(curPenColor, curPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);

    int rad = (curPenWidth/2) + 2;
    update(QRect(lastPoint, endPoint)
           .normalized()
           .adjusted(-rad, -rad, +rad, +rad));

    lastPoint = endPoint;
}

void Whiteboard::resizeImage(QImage *image, const QSize &newSize) {
    if (image->size() == newSize)
        return;
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255,255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void Whiteboard::print() {
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
#endif // QT_CONFIG(printdialog)
}
