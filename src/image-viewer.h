#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QFrame>
#include <QGraphicsPixmapItem>
#include "image-viewer-global.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

namespace pal {

class PixmapItem;
class GraphicsView;

/**
 * @brief ImageViewer displays images and allows basic interaction with it
 */
class IMAGE_VIEWER_PUBLIC ImageViewer : public QFrame {
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = nullptr);

    /// Text displayed on the left side of the toolbar
    QString text() const;

    /// The currently displayed image
    const QImage& image() const;

public slots:
    void setText(const QString &txt);
    void setImage(const QImage &);

    void zoomFit();
    void zoomOriginal();
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);
    void mouseAt(int x, int y);

signals:
    void imageChanged();

private:
    void setMatrix();
    void makeTools();
    QLayout * makeToolbar();

private:
    int m_zoom_level;
    QLabel *m_text_label;
    QLabel *m_pixel_value;
    GraphicsView *m_view;
    PixmapItem *m_pixmap;
};


class IMAGE_VIEWER_PUBLIC PixmapItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    PixmapItem(QGraphicsItem *parent = nullptr);
    const QImage & image() const { return m_image; }

public slots:
    void setImage(QImage im);

signals:
    void imageChanged(const QImage &);
    void sizeChanged(int w, int h);
    void mouseMoved(int x, int y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *) override;

private:
    QImage m_image;
};

} // namespace pal

#endif // IMAGEVIEWER_H
