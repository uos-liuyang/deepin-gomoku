/*
   * Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
   *
   * Author:     zhengxiaokang <zhengxiaokang@uniontech.com>
   *
   * Maintainer: zhengxiaokang <zhengxiaokang@uniontech.com>
   *
   * This program is free software: you can redistribute it and/or modify
   * it under the terms of the GNU General Public License as published by
   * the Free Software Foundation, either version 3 of the License, or
   * any later version.
   *
   * This program is distributed in the hope that it will be useful,
   * but WITHOUT ANY WARRANTY; without even the implied warranty of
   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   * GNU General Public License for more details.
   *
   * You should have received a copy of the GNU General Public License
   * along with this program.  If not, see <http://www.gnu.org/licenses/>.
   */
#ifndef CHECKERBOARDSCENE_H
#define CHECKERBOARDSCENE_H

#include "chesswidget/chessitem.h"

#include <QGraphicsScene>

class checkerboardscene : public QGraphicsScene
{
    Q_OBJECT
public:
    checkerboardscene(QObject *parent = nullptr);
    ~checkerboardscene() override;

    void setchessType(int chess = 0);
    void setchessPoint(int row, int col);
    // QGraphicsScene interface
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QVector<QVector<chessitem *>> chessItemList{};
    chessitem *currentItem = nullptr;
    int chessType = 1;
    int clickPosRow = 0; //点击的行
    int clickPosCol = 0; // 点击的列
};

#endif // CHECKERBOARDSCENE_H