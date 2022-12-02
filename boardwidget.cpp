#include "boardwidget.h"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include<QDebug>
#include<QPushButton>
#include<QMessageBox>
BoardWidget::BoardWidget(QWidget *parent,timer *timewidget)
    : QWidget(parent)
{
    setAcceptDrops(true);
    setMinimumSize(800, 800);
    setMaximumSize(800, 800);
    setBoard();
    Parent = parent;
    this->timewidget=timewidget;
}

void BoardWidget::clear()
{
    pieces.clear();
    highlightedRect = QRect();
    inPlace = 0;
    update();
}

void BoardWidget::dragEnterEvent(QDragEnterEvent *event)
{

    if (event->mimeData()->hasFormat(BoardWidget::puzzleMimeType()))
        event->accept();
    else
        event->ignore();
}

void BoardWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);
    event->accept();
}

void BoardWidget::dragMoveEvent(QDragMoveEvent *event)
{
    QRect updateRect = highlightedRect.united(targetSquare(event->position().toPoint()));
     if (event->mimeData()->hasFormat(BoardWidget::puzzleMimeType())
        && (findPiece(targetSquare(event->position().toPoint())) == -1||(findPiece(targetSquare(event->position().toPoint())) != -1
         /*&& pieces.at(findPiece(targetSquare(event->position().toPoint()))).id_color!=move*/))) {

        highlightedRect = targetSquare(event->position().toPoint());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        highlightedRect = QRect();
        event->ignore();
    }

    update(updateRect);
}

void BoardWidget::dropEvent(QDropEvent *event)
{

    if(event->mimeData()->hasFormat(BoardWidget::puzzleMimeType())
            &&findPiece(targetSquare(event->position().toPoint())) != -1
            &&pieces.at(findPiece(targetSquare(event->position().toPoint()))).id_color==move
            ){
        QByteArray pieceData = event->mimeData()->data(BoardWidget::puzzleMimeType());
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        Piece piece;
        piece.rect = targetSquare(event->position().toPoint());
        qDebug()<<piece.rect;
        dataStream >> piece.pixmap >> piece.location>>piece.id_piece>>piece.id_color>>piece.vrgn;
        if(piece.id_piece==6
                           &&piece.vrgn==0
                           &&pieces.at(findPiece(targetSquare(event->position().toPoint()))).id_piece==4
                             &&pieces.at(findPiece(targetSquare(event->position().toPoint()))).vrgn==0
                           &&inbetweenpiecefinder(from_square,targetSquare(event->position().toPoint()))
                        &&findPiece(targetSquare(event->position().toPoint())) != -1){

                   // qDebug()<<"yo line samma pugya cha";
                    qDebug()<<left;
                    if(left==1){
                     //   qDebug()<<"yo line samma pugya cha";

                        QRect king(200,700,100,100);
                        QRect rook(300,700,100,100);
                        Piece dummy;
                        piece.rect=king;
                        dummy=pieces.takeAt(findPiece(targetSquare(event->position().toPoint())));
                        dummy.rect=rook;
                        ++piece.vrgn;
                        pieces.append(piece);
                        pieces.append(dummy);
                        update(dummy.rect);
                        update(piece.rect);
                                for (int i=0;i<5;++i){
                                update(QRect(i*100,700,100,100));
                                }
                    }
                    else{
                        QRect king(600,700,100,100);
                        QRect rook(500,700,100,100);
                        Piece dummy;
                        piece.rect=king;
                        dummy=pieces.takeAt(findPiece(targetSquare(event->position().toPoint())));
                        dummy.rect=rook;
                        ++piece.vrgn;
                        pieces.append(piece);
                        pieces.append(dummy);
                        update(dummy.rect);
                        update(piece.rect);
                                for (int i=4;i<8;++i){
                                update(QRect(i*100,700,100,100));
                                }

                    }
                    if (piece.id_color==move&&move==13)
                        move++;
                    if(piece.id_color==move&&move==14)
                        --move;
                    update(piece.rect);
                }
        else if(piece.id_piece==12
                        &&piece.vrgn==0
                        &&pieces.at(findPiece(targetSquare(event->position().toPoint()))).id_piece==10
                          &&pieces.at(findPiece(targetSquare(event->position().toPoint()))).vrgn==0
                        &&inbetweenpiecefinder(from_square,targetSquare(event->position().toPoint()))
                     &&findPiece(targetSquare(event->position().toPoint())) != -1){

                // qDebug()<<"yo line samma pugya cha";
                 qDebug()<<left;
                 if(left==1){
                 //    qDebug()<<"yo line samma pugya cha";

                     QRect king(200,0,100,100);
                     QRect rook(300,0,100,100);
                     Piece dummy;
                     piece.rect=king;
                     dummy=pieces.takeAt(findPiece(targetSquare(event->position().toPoint())));
                     dummy.rect=rook;
                     ++piece.vrgn;
                     pieces.append(piece);
                     pieces.append(dummy);
                     update(dummy.rect);
                     update(piece.rect);
                             for (int i=0;i<5;++i){
                             update(QRect(i*100,0,100,100));
                             }
                 }
                 else{
                     QRect king(600,0,100,100);
                     QRect rook(500,0,100,100);
                     Piece dummy;
                     piece.rect=king;
                     dummy=pieces.takeAt(findPiece(targetSquare(event->position().toPoint())));
                     dummy.rect=rook;
                     ++piece.vrgn;
                     pieces.append(piece);
                     pieces.append(dummy);
                     update(dummy.rect);
                     update(piece.rect);
                             for (int i=4;i<8;++i){
                             update(QRect(i*100,0,100,100));
                             }



                 }
                 if (piece.id_color==move&&move==13)
                     move++;
                 if(piece.id_color==move&&move==14)
                     --move;
                 update(piece.rect);
             }


        else
          return;


      highlightedRect = QRect();
      update(piece.rect);

      event->setDropAction(Qt::MoveAction);
     event->accept();

     int countkings=0;
     int win=0;
     for (int i = 0, size = pieces.size(); i < size; ++i) {
         if (pieces.at(i).id_piece == 6||pieces.at(i).id_piece == 12)
             countkings++;
         if(pieces.at(i).id_piece == 6)
             win+=13;
         if(pieces.at(i).id_piece == 12)
            win+=14;
     }
     if(countkings!=2){

         QMessageBox box;
         box.setStyleSheet("QLabel{background-color:#444444 ;min-width:200 px; font-size: 13px;color:white;} "
                           "QPushButton { background-color: #999999;"
                           "color: #ffffff;"
                           "font-family:  Helvetica, Arial, sans-serif;"
                           "font-size: 13px;"
                           "margin: 0;"
                           "padding: 10px 12px;"
                           "text-align: center;"
                           "vertical-align: baseline;"
                           "white-space: nowrap;}"
                           " QMessageBox{ "
                           "left: 0;"
                           "top: 0;"
                           "width: 100%; /* Full width */"
                           "height: 100%; /* Full height */"
                           "background-color: #444444; /* Fallback color */"
                           "}");
         if(win==13)
         box.setText("GAME OVER!WHITE WINS.");
         else
         box.setText("GAME OVER!BLACK WINS.");
    box.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
         box.setInformativeText("Play Another One");
         box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
         box.setDefaultButton(QMessageBox::Cancel);
         int ret=box.exec();
         if( ret==QMessageBox::Ok  ){
              setBoard();

         }
         if( ret==QMessageBox::Cancel  ){


         }
         //   QMessageBox::information(this,"Game over","GO BACK TO HOME MENU",QMessageBox::Ok);

      }



      if (piece.location == piece.rect.topLeft() / pieceSize()) {
          inPlace++;
          if (inPlace == 32)
              emit puzzleCompleted();
      }

    }


  else  if (event->mimeData()->hasFormat(BoardWidget::puzzleMimeType())
            && (findPiece(targetSquare(event->position().toPoint())) == -1||(findPiece(targetSquare(event->position().toPoint())) != -1
             && pieces.at(findPiece(targetSquare(event->position().toPoint()))).id_color!=move))) {

        QByteArray pieceData = event->mimeData()->data(BoardWidget::puzzleMimeType());
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        Piece piece;

        piece.rect = targetSquare(event->position().toPoint());

        qDebug()<<piece.rect;
        dataStream >> piece.pixmap >> piece.location>>piece.id_piece>>piece.id_color>>piece.vrgn;
        qDebug()<<"piece="<<piece.id_piece<<"  "<<piece.id_color;
        if(piece.id_piece!=1&&piece.id_piece!=7
                &&rule_movement(from_square,targetSquare(event->position().toPoint()),piece.id_piece,piece.id_color)
                &&findPiece(targetSquare(event->position().toPoint())) == -1){
            qDebug()<<from_square;

                ++piece.vrgn;
                pieces.append(piece);
                if (piece.id_color==move&&move==13)
                    move++;
                if(piece.id_color==move&&move==14)
                    --move;
                update(piece.rect);



        }


        else if(piece.id_piece!=1&&piece.id_piece!=7
                &&rule_movement(from_square,targetSquare(event->position().toPoint()),piece.id_piece,piece.id_color)
                &&findPiece(targetSquare(event->position().toPoint())) != -1){
            qDebug()<<from_square;
                pieces.removeAt(findPiece(targetSquare(event->position().toPoint())));
                pieces.squeeze();
                ++piece.vrgn;
                pieces.append(piece);
                if (piece.id_color==move&&move==13)
                    move++;
                if(piece.id_color==move&&move==14)
                    --move;
                update(piece.rect);



        }
        else if(findPiece(targetSquare(event->position().toPoint())) == -1
                &&(piece.id_piece==1||piece.id_piece==7)
                &&rule_movement(from_square,targetSquare(event->position().toPoint()),piece.id_piece,piece.id_color)
                    ){
            if((piece.id_piece==1&&targetSquare(event->position().toPoint()).y()==0)
                    ||(piece.id_piece==7&&targetSquare(event->position().toPoint()).y()==700)){
                QMessageBox box;
                box.setStyleSheet("QLabel{background-color:#444444 ;min-width:200 px; font-size: 13px;color:white;} "
                                  "QPushButton { background-color: #999999;"
                                  "color: #ffffff;"
                                  "font-family:  Helvetica, Arial, sans-serif;"
                                  "font-size: 13px;"
                                  "margin: 0;"
                                  "padding: 10px 12px;"
                                  "text-align: center;"
                                  "vertical-align: baseline;"
                                  "white-space: nowrap;}"
                                  " QMessageBox{ "
                                  "left: 0;"
                                  "top: 0;"
                                  "width: 100%; /* Full width */"
                                  "height: 100%; /* Full height */"
                                  "background-color: #444444; /* Fallback color */"
                                  "}");
                box.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
                box.setText("PROMOTION!!!");
                QPushButton *queenButton=box.addButton("",QMessageBox::ActionRole);
                queenButton->setIcon(QIcon(":/images/king.png"));
                queenButton->setIconSize(QSize(100,100));
                QPushButton *rookButton=box.addButton("",QMessageBox::ActionRole);
                rookButton->setIcon(QIcon(":/images/rook.png"));
                rookButton->setIconSize(QSize(100,100));
                QPushButton *bishopButton=box.addButton("",QMessageBox::ActionRole);
                bishopButton->setIcon(QIcon(":/images/bishop.png"));
                bishopButton->setIconSize(QSize(100,100));
                QPushButton *knightButton=box.addButton("",QMessageBox::ActionRole);
                knightButton->setIcon(QIcon(":/images/knight.png"));
                knightButton->setIconSize(QSize(100,100));
                box.setInformativeText("Please chose the piece you want to promote to:");

                box.exec();
                if( box.clickedButton() == queenButton  &&piece.id_piece==1){
                    QPixmap dummy;
                    dummy.load(":/images/king.png");
                    piece.pixmap=dummy;
                    piece.id_piece=5;
                    update(piece.rect);
                }
                else if( box.clickedButton() == queenButton  &&piece.id_piece==7){
                    QPixmap dummy;
                    dummy.load(":/images/bking.png");
                    piece.pixmap=dummy;
                    piece.id_piece=11;
                    update(piece.rect);
                }


               else if( box.clickedButton() == rookButton  &&piece.id_piece==1){
                    QPixmap dummy;
                    dummy.load(":/images/rook.png");
                    piece.pixmap=dummy;
                    piece.id_piece=4;
                    update(piece.rect);

                }
                else if( box.clickedButton() == rookButton  &&piece.id_piece==7){
                    QPixmap dummy;
                    dummy.load(":/images/brook.png");
                    piece.pixmap=dummy;
                    piece.id_piece=10;
                    update(piece.rect);
                }
               else if( box.clickedButton() == bishopButton &&piece.id_piece==1 ){
                    QPixmap dummy;
                    dummy.load(":/images/bishop.png");
                    piece.pixmap=dummy;
                    piece.id_piece=2;
                    update(piece.rect);

                }
                else if( box.clickedButton() == bishopButton &&piece.id_piece==7 ){
                     QPixmap dummy;
                     dummy.load(":/images/bbishop.png");
                     piece.pixmap=dummy;
                     piece.id_piece=8;
                     update(piece.rect);

                 }
                else if( box.clickedButton() == knightButton  &&piece.id_piece==1){
                    QPixmap dummy;
                    dummy.load(":/images/knight.png");
                    piece.pixmap=dummy;
                    piece.id_piece=3;
                    update(piece.rect);

                }
                else if( box.clickedButton() == knightButton  &&piece.id_piece==7){
                    QPixmap dummy;
                    dummy.load(":/images/bknight.png");
                    piece.pixmap=dummy;
                    piece.id_piece=9;
                    update(piece.rect);

                }
                else
                {}

            }
            ++piece.vrgn;
            qDebug()<<"here";
            pieces.append(piece);
            if (piece.id_color==move&&move==13)
                move++;
            if(piece.id_color==move&&move==14)
                --move;
            update(piece.rect);

        }
        else if(findPiece(targetSquare(event->position().toPoint())) != -1
                &&(piece.id_piece==1||piece.id_piece==7)){
            if(piece.id_piece==1){
                if(rule_movement(from_square,targetSquare(event->position().toPoint()),15,piece.id_color)){
                    pieces.removeAt(findPiece(targetSquare(event->position().toPoint())));
                    pieces.squeeze();
                    if((piece.id_piece==1&&targetSquare(event->position().toPoint()).y()==0)
                            ||(piece.id_piece==7&&targetSquare(event->position().toPoint()).y()==700)){
                        QMessageBox box;
                        box.setStyleSheet("QLabel{background-color:#444444 ;min-width:200 px; font-size: 13px;color:white;} "
                                          "QPushButton { background-color: #999999;"
                                          "color: #ffffff;"
                                          "font-family:  Helvetica, Arial, sans-serif;"
                                          "font-size: 13px;"
                                          "margin: 0;"
                                          "padding: 10px 12px;"
                                          "text-align: center;"
                                          "vertical-align: baseline;"
                                          "white-space: nowrap;}"
                                          " QMessageBox{ "
                                          "left: 0;"
                                          "top: 0;"
                                          "width: 100%; /* Full width */"
                                          "height: 100%; /* Full height */"
                                          "background-color: #444444; /* Fallback color */"
                                          "}");
                        box.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
                        box.setText("PROMOTION!!!");
                        QPushButton *queenButton=box.addButton("",QMessageBox::ActionRole);
                        queenButton->setIcon(QIcon(":/images/king.png"));
                        queenButton->setIconSize(QSize(100,100));
                        QPushButton *rookButton=box.addButton("",QMessageBox::ActionRole);
                        rookButton->setIcon(QIcon(":/images/rook.png"));
                        rookButton->setIconSize(QSize(100,100));
                        QPushButton *bishopButton=box.addButton("",QMessageBox::ActionRole);
                        bishopButton->setIcon(QIcon(":/images/bishop.png"));
                        bishopButton->setIconSize(QSize(100,100));
                        QPushButton *knightButton=box.addButton("",QMessageBox::ActionRole);
                        knightButton->setIcon(QIcon(":/images/knight.png"));
                        knightButton->setIconSize(QSize(100,100));
                        box.setInformativeText("Please chose the piece you want to promote to:");

                        box.exec();
                        if( box.clickedButton() == queenButton  &&piece.id_piece==1){
                            QPixmap dummy;
                            dummy.load(":/images/king.png");
                            piece.pixmap=dummy;
                            piece.id_piece=5;
                            update(piece.rect);
                        }
                        else if( box.clickedButton() == queenButton  &&piece.id_piece==7){
                            QPixmap dummy;
                            dummy.load(":/images/bking.png");
                            piece.pixmap=dummy;
                            piece.id_piece=11;
                            update(piece.rect);
                        }


                       else if( box.clickedButton() == rookButton  &&piece.id_piece==1){
                            QPixmap dummy;
                            dummy.load(":/images/rook.png");
                            piece.pixmap=dummy;
                            piece.id_piece=4;
                            update(piece.rect);

                        }
                        else if( box.clickedButton() == rookButton  &&piece.id_piece==7){
                            QPixmap dummy;
                            dummy.load(":/images/brook.png");
                            piece.pixmap=dummy;
                            piece.id_piece=10;
                            update(piece.rect);
                        }
                       else if( box.clickedButton() == bishopButton &&piece.id_piece==1 ){
                            QPixmap dummy;
                            dummy.load(":/images/bishop.png");
                            piece.pixmap=dummy;
                            piece.id_piece=2;
                            update(piece.rect);

                        }
                        else if( box.clickedButton() == bishopButton &&piece.id_piece==7 ){
                             QPixmap dummy;
                             dummy.load(":/images/bbishop.png");
                             piece.pixmap=dummy;
                             piece.id_piece=8;
                             update(piece.rect);

                         }
                        else if( box.clickedButton() == knightButton  &&piece.id_piece==1){
                            QPixmap dummy;
                            dummy.load(":/images/knight.png");
                            piece.pixmap=dummy;
                            piece.id_piece=3;
                            update(piece.rect);

                        }
                        else if( box.clickedButton() == knightButton  &&piece.id_piece==7){
                            QPixmap dummy;
                            dummy.load(":/images/bknight.png");
                            piece.pixmap=dummy;
                            piece.id_piece=9;
                            update(piece.rect);

                        }
                        else
                        {}
}
                    ++piece.vrgn;

                    pieces.append(piece);
                    if (piece.id_color==move&&move==13)
                        move++;
                    if(piece.id_color==move&&move==14)
                        --move;
                    update(piece.rect);
                }
                else return;

            }
            if(piece.id_piece==7) {
                if(rule_movement(from_square,targetSquare(event->position().toPoint()),16,piece.id_color)){
                    pieces.removeAt(findPiece(targetSquare(event->position().toPoint())));
                    pieces.squeeze();
                    ++piece.vrgn;
                    pieces.append(piece);
                    if (piece.id_color==move&&move==13)
                        move++;
                    if(piece.id_color==move&&move==14)
                        --move;
                    update(piece.rect);
                }
                else return;

            }

        }


          else
            return;


        highlightedRect = QRect();
        update(piece.rect);

        event->setDropAction(Qt::MoveAction);
       event->accept();
       ++piece.vrgn;
       int countkings=0;
       int win=0;
       for (int i = 0, size = pieces.size(); i < size; ++i) {
           if (pieces.at(i).id_piece == 6||pieces.at(i).id_piece == 12)
               countkings++;
           if(pieces.at(i).id_piece == 6)
               win+=13;
           if(pieces.at(i).id_piece == 12)
              win+=14;
       }
       if(countkings!=2){

           QMessageBox box;box.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
           if(win==13)
           box.setText("GAME OVER!WHITE WINS.");
           else
           box.setText("GAME OVER!BLACK WINS.");
           box.setStyleSheet("QLabel{background-color:#444444 ;min-width:200 px; font-size: 13px;color:white;} "
                             "QPushButton { background-color: #999999;"
                             "color: #ffffff;"
                             "font-family:  Helvetica, Arial, sans-serif;"
                             "font-size: 13px;"
                             "margin: 0;"
                             "padding: 10px 12px;"
                             "text-align: center;"
                             "vertical-align: baseline;"
                             "white-space: nowrap;}"
                             " QMessageBox{ "
                             "left: 0;"
                             "top: 0;"
                             "width: 100%; /* Full width */"
                             "height: 100%; /* Full height */"
                             "background-color: #444444; /* Fallback color */"
                             "}");
           box.setInformativeText("Play Another One");
           box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
           box.setDefaultButton(QMessageBox::Cancel);
           int ret=box.exec();
           if( ret==QMessageBox::Ok  ){
                setBoard();

           }
           if( ret==QMessageBox::Cancel  ){


           }
           //   QMessageBox::information(this,"Game over","GO BACK TO HOME MENU",QMessageBox::Ok);

        }



        if (piece.location == piece.rect.topLeft() / pieceSize()) {
            inPlace++;
            if (inPlace == 32)
                emit puzzleCompleted();
        }
    }

            else {
        highlightedRect = QRect();
        event->ignore();
    }

}

int BoardWidget::findPiece(const QRect &pieceRect) const
{
    for (int i = 0, size = pieces.size(); i < size; ++i) {
        if (pieces.at(i).rect == pieceRect)
            return i;
    }
    return -1;
}

void BoardWidget::mousePressEvent(QMouseEvent *event)
{
    QRect square = targetSquare(event->position().toPoint());
    from_square = square;
    qDebug()<< from_square;
    const int found = findPiece(square);
    if (found == -1)
        return;

    Piece piece = pieces.takeAt(found);
    if(piece.id_color != move){
        pieces.insert(found,piece);
         update(square);
        return;
    }

    if (piece.location == square.topLeft() / pieceSize())
        inPlace--;

    update(square);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    dataStream << piece.pixmap << piece.location<<piece.id_piece<<piece.id_color<<piece.vrgn;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(BoardWidget::puzzleMimeType(), itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->position().toPoint() - square.topLeft());
    drag->setPixmap(piece.pixmap);

    if (drag->exec(Qt::MoveAction) != Qt::MoveAction) {
        pieces.insert(found, piece);
        update(targetSquare(event->position().toPoint()));

        if (piece.location == square.topLeft() / pieceSize())
            inPlace++;
    }
}

void BoardWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

   for(int i=0;i<8;++i){
           for(int j=0;j<8;++j){


               if((i+j) %2 != 0){
                   painter.drawRect(i*100,j*100,100,100);
                  painter.fillRect(i*100,j*100,100,100,Qt::black);
              }
              else
              {
                   painter.drawRect(i*100,j*100,100,100);
                  painter.fillRect(i*100,j*100,100,100,Qt::white);
              }

           }
   }


    if (highlightedRect.isValid()) {
        painter.setBrush(QColor("#ccccff"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }

    for (const Piece &piece : pieces)

        painter.drawPixmap(piece.rect, piece.pixmap);

}

bool BoardWidget::rule_movement(QRect from_square, QRect to_square, int idp,int idc)
{
   int x1 =from_square.x()/100; int y1 = from_square.y()/100;
    int x2=to_square.x()/100; int y2= to_square.y()/100;

        switch(idp){
        case 1:{

                if((y2==(y1-1))&&x1==x2)
                    return true;
                else
                if((y1==6 && y2==(y1-2))&&x1==x2
                        &&inbetweenpiecefinder(x1,x2,y1,y2))
                    return true;

            else return false;
        }
        case 2:{
            if((abs(x1-x2)==abs(y1-y2))
                    &&inbetweenpiecefinder(x1,x2,y1,y2))
            return true;
            else return false;


        }
        case 3:{
            if(( (x2==(x1+2)) || (x2==(x1-2)) )
               &&((y2==(y1+1))||(y2==(y1-1))))
                return true;
            else if(((y2==(y1+2))||(y2==(y1-2)))
                    &&((x2==(x1+1))||(x2==(x1-1)))     )
                return true;
            else return false;
        }
        case 4:{
            if(((x1==x2)||(y1==y2))
                    &&inbetweenpiecefinder(x1,x2,y1,y2))
            return true;
            else return false;


        }
        case 5:{
            if(((x1==x2)||(y1==y2)||(abs(x1-x2)==abs(y1-y2)))
                    &&inbetweenpiecefinder(x1,x2,y1,y2))
            return true;
            else return false;


        }
        case 6:{
            if(abs(x1-x2)<=1&&abs(y1-y2)<=1&&((x1-x2)!=0||(y1-y2)!=0))
                return true;
            else return false;
        }

            case 7:{

                            if((y1==(y2-1))&&x2==x1)
                                return true;
                           else if((y1==1 && y1==(y2-2))&&x1==x2
                                   &&inbetweenpiecefinder(x1,x2,y1,y2))
                                return true;

            else return false;

       }
        case 8:{
            if(abs(x1-x2)==abs(y1-y2)
                  &&inbetweenpiecefinder(x1,x2,y1,y2))
            return true;
            else return false;


        }
        case 9:{
            if(( (x2==(x1+2)) || (x2==(x1-2)) )
               &&((y2==(y1+1))||(y2==(y1-1))))
                return true;
            else if(((y2==(y1+2))||(y2==(y1-2)))
                    &&((x2==(x1+1))||(x2==(x1-1)))     )
                return true;
            else return false;
        }
        case 10:{
            if(((x1==x2)||(y1==y2))
                    &&inbetweenpiecefinder(x1,x2,y1,y2))
            return true;
            else return false;


        }
        case 11:{
            if(((x1==x2)||(y1==y2)||(abs(x1-x2)==abs(y1-y2)))
                    &&inbetweenpiecefinder(x1,x2,y1,y2))
            return true;
            else return false;


        }
        case 12:{
            if(abs(x1-x2)<=1&&abs(y1-y2)<=1&&((x1-x2)!=0||(y1-y2)!=0))
                return true;
            else return false;
        }

        case 15:{
            if(idc==13){
                if((y2==(y1-1))&&((x2==x1+1)||(x2==x1-1)))
                    return true;

            }
            else return false;
        }



            case 16:{
            if(idc==14){
                if((y2==(y1+1))&&((x2==x1+1)||(x2==x1-1)))
                    return true;

            }
            else return false;
       }

    return false;




}
        return false;
}



bool BoardWidget::inbetweenpiecefinder(int ax1, int ax2, int ay1, int ay2)
{
 if(ax1==ax2&&(ay1-ay2)>0){
     for(int i=0;i<(ay1-ay2);++i){
         QRect rect(100*ax1,100*(ay1-i),100,100);
         if(findPiece(rect)!=-1)
             return false;
     }
     return true;

 }
  if(ax1==ax2&&(ay2-ay1)>0){
     for(int i=0;i<(ay2-ay1);++i){
         QRect rect(100*ax1,100*(ay1+i),100,100);
         if(findPiece(rect)!=-1)
             return false;
     }
     return true;
 }
  if(ay1==ay2&&(ax1-ax2)>0){
     for(int i=0;i<(ax1-ax2);++i){
         QRect rect(100*(ax1-i),100*ay1,100,100);
         if(findPiece(rect)!=-1)
             return false;
     }
     return true;

 }
  if(ay1==ay2&&(ax2-ax1)>0){
     for(int i=0;i<(ax2-ax1);++i){
         QRect rect(100*(ax1+i),100*ay1,100,100);
         if(findPiece(rect)!=-1)
             return false;
     }
     return true;
 }
 if((ax1-ax2)>0&&(ax1-ax2)==(ay1-ay2)){
     for(int i=0;i<(ax1-ax2);++i){
         QRect rect(100*(ax1-i),100*(ay1-i),100,100);
         if(findPiece(rect)!=-1)
             return false;
     }
     return true;
 }
 if((ax1-ax2)>0&&(ax1-ax2)==(ay2-ay1)){
      for(int i=0;i<(ax1-ax2);++i){
          QRect rect(100*(ax1-i),100*(ay1+i),100,100);
          if(findPiece(rect)!=-1)
              return false;
      }
      return true;
  }
 if((ax2-ax1)>0&&(ax2-ax1)==(ay1-ay2)){
      for(int i=0;i<(ax2-ax1);++i){
          QRect rect(100*(ax1+i),100*(ay1-i),100,100);
          if(findPiece(rect)!=-1)
              return false;
      }
      return true;
  }
 if((ax2-ax1)>0&&(ax2-ax1)==(ay2-ay1)){
      for(int i=0;i<(ax2-ax1);++i){
          QRect rect(100*(ax1+i),100*(ay1+i),100,100);
          if(findPiece(rect)!=-1)
              return false;
      }
      return true;
  }
  return false;

}

bool BoardWidget::inbetweenpiecefinder(QRect from_square, QRect to_square)
{
    int x1 =from_square.x()/100; int y1 = from_square.y()/100;
     int x2=to_square.x()/100; int y2= to_square.y()/100;
     if((x1-x2)>0)
         left=1;
     else
         left=0;
     if (inbetweenpiecefinder(x1,x2,y1,y2))
         return true;
     else return false;

}



const QRect BoardWidget::targetSquare(const QPoint &position) const
{
    QPoint topLeft = QPoint(position.x() / pieceSize(), position.y() / pieceSize()) * pieceSize();
    return QRect(topLeft, QSize(pieceSize(), pieceSize()));
}

int BoardWidget::pieceSize() const
{
    return 800 / 8;

}

int BoardWidget::imageSize() const
{

    return 800;

}

void BoardWidget::setBoard()
{
    clear();
    move=13;
    for(int i=0;i<8;++i){
            for(int j=0;j<8;++j){
             if(j==0||j==1||j==6||j==7)   {
    Piece piece;
    QPixmap pixmap;
    if((i==0 || i==7) && (j==0||j==1)){
     pixmap.load(":/images/brook.png");
     piece.id_piece = 10;
     piece.id_color = 14;
     }

    if((i==1 || i==6) && (j==0||j==1)){
    pixmap.load(":/images/bknight.png");
    piece.id_piece = 9;
    piece.id_color = 14;
    }

    if((i==2 || i==5)&& (j==0||j==1)){
    pixmap.load(":/images/bbishop.png");
    piece.id_piece = 8;
    piece.id_color = 14;
    }

    if((i==3 )&& (j==0)){
    pixmap.load(":/images/bking.png");
    piece.id_piece = 11;
    piece.id_color = 14;
    }

    if((i==4)&& (j==0)){
    pixmap.load(":/images/bqueen.png");
    piece.id_piece = 12;
    piece.id_color = 14;
    }

    if(j==1){
    pixmap.load(":/images/bpawn.png");
    piece.id_piece = 7;
    piece.id_color = 14;
    }

    if((i==0 || i==7) && (j==6||j==7)){
     pixmap.load(":/images/rook.png");
     piece.id_piece = 4;
     piece.id_color = 13;
     }

    if((i==1 || i==6) && (j==6||j==7)){
    pixmap.load(":/images/knight.png");
    piece.id_piece = 3;
    piece.id_color = 13;
    }

    if((i==2 || i==5)&& (j==6||j==7)){
    pixmap.load(":/images/bishop.png");
    piece.id_piece = 2;
    piece.id_color = 13;
    }

    if((i==3)&& (j==7)){
    pixmap.load(":/images/king.png");
    piece.id_piece = 5;
    piece.id_color = 13;
    }

    if((i==4)&& (j==7)){
    pixmap.load(":/images/queen.png");
    piece.id_piece = 6;
    piece.id_color = 13;
    }

    if(j==6){
    pixmap.load(":/images/pawn.png");
    piece.id_piece = 1;
    piece.id_color = 13;
    }
    QRect dummy(i*100,j*100,100,100);
    piece.rect = dummy;
    piece.pixmap=pixmap;


    pieces.append(piece);

    highlightedRect = QRect();
    update(piece.rect);
            }
    }
    }
}

void BoardWidget::gameover()
{
    qDebug()<<"gameover ma pugyo";
    if((timewidget->timeformatblack.minutes==0
        &&timewidget->timeformatblack.seconds==0)
            ||(timewidget->timeformatwhite.minutes==0
               &&timewidget->timeformatwhite.seconds==0)){
    QMessageBox box;
    if(timewidget->timeformatblack.minutes==0&&timewidget->timeformatblack.seconds==0)
    box.setText("GAME OVER!WHITE WINS.");
    else if(timewidget->timeformatwhite.minutes==0&&timewidget->timeformatwhite.seconds==0)
    box.setText("GAME OVER!BLACK WINS.");
    else
        qDebug()<<"gomeover pugyo nothing happened";
    box.setInformativeText("Play Another One");
    box.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Cancel);
    box.setStyleSheet("QLabel{background-color:#444444 ;min-width:200 px; font-size: 13px;color:white;} "
                      "QPushButton { background-color: #999999;"
                      "color: #ffffff;"
                      "font-family:  Helvetica, Arial, sans-serif;"
                      "font-size: 13px;"
                      "margin: 0;"
                      "padding: 10px 12px;"
                      "text-align: center;"
                      "vertical-align: baseline;"
                      "white-space: nowrap;}"
                      " QMessageBox{ "
                      "left: 0;"
                      "top: 0;"
                      "width: 100%; /* Full width */"
                      "height: 100%; /* Full height */"
                      "background-color: #444444; /* Fallback color */"
                      "}");
    box.show();
    int ret=box.exec();
    if( ret==QMessageBox::Ok  ){
         setBoard();

}
    else if( ret==QMessageBox::Cancel  ){

    }

    }
}
