#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QWidget>

class Whiteboard : public QWidget {
    Q_OBJECT
  public:
    Whiteboard(QWidget *parent = nullptr);
    void setPenColor(const QColor  &newColor);
    void setPenWidth(int newWidth);
    QColor penColor() const {
        return curPenColor;
    }
    int penWidth() const {
        return curPenWidth;
    }

  public slots:
    void clearImage();
    void print();

  protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

  private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    bool penDown = false;
    int curPenWidth = 1;
    QColor curPenColor = Qt::blue;
    QImage image;
    QPoint lastPoint;
};

#endif // WHITEBOARD_H
