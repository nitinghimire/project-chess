

//#include "puzzlewidget.h"
//#include "pieceslist.h"

//#include <QDrag>
//#include <QDragEnterEvent>
//#include <QMimeData>
//#include <QPainter>
//BoardWidget::BoardWidget( QWidget *parent)
//    : QWidget(parent)
//{
//    setAcceptDrops(true);
//    setMinimumSize(800, 800);
//    setMaximumSize(800, 800);
//}

//void BoardWidget::clear()
//{
//    pieces.clear();
//    highlightedRect = QRect();
//    inPlace = 0;
//    update();
//}

//void BoardWidget::dragEnterEvent(QDragEnterEvent *event)
//{
//    if (event->mimeData()->hasFormat(PiecesList::puzzleMimeType()))
//        event->accept();
//    else
//        event->ignore();
//}

//void BoardWidget::dragLeaveEvent(QDragLeaveEvent *event)
//{
//    QRect updateRect = highlightedRect;
//    highlightedRect = QRect();
//    update(updateRect);
//    event->accept();
//}

//void BoardWidget::dragMoveEvent(QDragMoveEvent *event)
//{
//    QRect updateRect = highlightedRect.united(targetSquare(event->position().toPoint()));

//    if (event->mimeData()->hasFormat(PiecesList::puzzleMimeType())
//        && findPiece(targetSquare(event->position().toPoint())) == -1) {

//        highlightedRect = targetSquare(event->position().toPoint());
//        event->setDropAction(Qt::MoveAction);
//        event->accept();
//    } else {
//        highlightedRect = QRect();
//        event->ignore();
//    }

//    update(updateRect);
//}

//void BoardWidget::dropEvent(QDropEvent *event)
//{
//    if (event->mimeData()->hasFormat(PiecesList::puzzleMimeType())
//        && findPiece(targetSquare(event->position().toPoint())) == -1) {

//        QByteArray pieceData = event->mimeData()->data(PiecesList::puzzleMimeType());
//        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
//        Piece piece;
//        piece.rect = targetSquare(event->position().toPoint());
//        dataStream >> piece.pixmap >> piece.location;

//        pieces.append(piece);

//        highlightedRect = QRect();
//        update(piece.rect);

//        event->setDropAction(Qt::MoveAction);
//        event->accept();

//        if (piece.location == piece.rect.topLeft() / pieceSize()) {
//            inPlace++;
//            if (inPlace == 25)
//                emit puzzleCompleted();
//        }
//    } else {
//        highlightedRect = QRect();
//        event->ignore();
//    }
//}

//int BoardWidget::findPiece(const QRect &pieceRect) const
//{
//    for (int i = 0, size = pieces.size(); i < size; ++i) {
//        if (pieces.at(i).rect == pieceRect)
//            return i;
//    }
//    return -1;
//}

//void BoardWidget::mousePressEvent(QMouseEvent *event)
//{
//    QRect square = targetSquare(event->position().toPoint());
//    const int found = findPiece(square);

//    if (found == -1)
//        return;

//    Piece piece = pieces.takeAt(found);

//    if (piece.location == square.topLeft() / pieceSize())
//        inPlace--;

//    update(square);

//    QByteArray itemData;
//    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

//    dataStream << piece.pixmap << piece.location;

//    QMimeData *mimeData = new QMimeData;
//    mimeData->setData(PiecesList::puzzleMimeType(), itemData);

//    QDrag *drag = new QDrag(this);
//    drag->setMimeData(mimeData);
//   // drag->setHotSpot(event->position().toPoint() - square.topLeft());
//  //  drag->setPixmap(piece.pixmap);

//    if (drag->exec(Qt::MoveAction) != Qt::MoveAction) {
//        pieces.insert(found, piece);
//        update(targetSquare(event->position().toPoint()));

//        if (piece.location == square.topLeft() / pieceSize())
//            inPlace++;
//    }
//}

//void BoardWidget::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);

//   for(int i=0;i<8;++i){
//           for(int j=0;j<8;++j){


//               if((i+j) %2 != 0){
//                  painter.fillRect(i*100,j*100,100,100,Qt::black);
//              }
//              else
//              {
//                  painter.fillRect(i*100,j*100,100,100,Qt::white);
//              }
//           }
//   }


//    if (highlightedRect.isValid()) {
//        painter.setBrush(QColor("#ffcccc"));
//        painter.setPen(Qt::NoPen);
//        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
//    }

//    for (const Piece &piece : pieces)

//        painter.drawPixmap(piece.rect, piece.pixmap);
//}

//const QRect BoardWidget::targetSquare(const QPoint &position) const
//{
//    QPoint topLeft = QPoint(position.x() / pieceSize(), position.y() / pieceSize()) * pieceSize();
//    return QRect(topLeft, QSize(pieceSize(), pieceSize()));
//}

//int BoardWidget::pieceSize() const
//{
//    return 800 / 8;

//}

//int BoardWidget::imageSize() const
//{

//    return 800;

//}
