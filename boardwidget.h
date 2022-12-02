#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H
#include <QPoint>
#include <QPixmap>
#include <QList>
#include <QWidget>
#include"timer.h"
QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
QT_END_NAMESPACE

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWidget( QWidget *parent = nullptr, timer *timewidget=0);
    void clear();

    int pieceSize() const;
    int imageSize() const;
    void setBoard();
  static QString puzzleMimeType() { return QStringLiteral("image/x-puzzle-piece"); }
   struct Piece {
      QPixmap pixmap;
      QRect rect;
      QPoint location;
      int id_piece;
      int id_color;
      int vrgn=0;
  };
   int move=13;

signals:
    void puzzleCompleted();
public slots:
    void gameover();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    bool rule_movement(QRect from_square,QRect to_square,int idp,int idc);

private:

    bool inbetweenpiecefinder(int ax1,int ax2,int ay1, int ay2);
    bool inbetweenpiecefinder(QRect from_square,QRect to_square);
    int findPiece(const QRect &pieceRect) const;
    const QRect targetSquare(const QPoint &position) const;

    QList<Piece> pieces;
    QRect highlightedRect;
    int inPlace;
    QRect from_square;
    QRect to_square;
    QWidget* Parent;
    int left=0;
    timer *timewidget;

};

#endif // BOARDWIDGET_H
