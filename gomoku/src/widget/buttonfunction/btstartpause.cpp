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
#include "btstartpause.h"

BTStartPause::BTStartPause(QGraphicsItem *parent)
    : ButtonItem(parent)
    , beginPixmap(DHiDPIHelper::loadNxPixmap(":/resources/icon/begin.svg"))
    , stopPixmap(DHiDPIHelper::loadNxPixmap(":/resources/icon/stop.svg"))
{
}

BTStartPause::~BTStartPause()
{
}

/**
 * @brief BTStartPause::setStopStatus 设置游戏暂停状态
 */
void BTStartPause::setStopStatus()
{
    //修改按钮图片
    mouseReleased = true;
    //更新功能
    buttonFunction();
    update();
}

/**
 * @brief BTStartPause::setFirstGameStatus 设置是否第一次开始游戏
 */
void BTStartPause::setNotFirstGame()
{
    firstStartGame = false;
    mouseReleased = false;
    update();
}

QRectF BTStartPause::boundingRect() const
{
    return ButtonItem::boundingRect();
}

void BTStartPause::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal rectWidth = this->boundingRect().width();
    qreal rectHeight = this->boundingRect().height();

    painter->setRenderHint(QPainter::Antialiasing);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->drawPixmap(QPointF(boundingRect().x(), boundingRect().y()), backgrounePix);
    painter->restore();

    painter->save();
    painter->setPen(Qt::NoPen);
    if (firstStartGame) {
        painter->drawPixmap(QPointF(rectWidth * pixmapPosWidth, rectHeight * pixmapPosHeight),
                            beginPixmap);
    } else {
        if (mouseReleased) {
            painter->drawPixmap(QPointF(rectWidth * pixmapPosWidth, rectHeight * pixmapPosHeight),
                                beginPixmap);
        } else {
            painter->drawPixmap(QPointF(rectWidth * pixmapPosWidth, rectHeight * pixmapPosHeight),
                                stopPixmap);
        }
    }
    painter->restore();

    painter->save();
    QFont font;
    font.setFamily("Yuanti SC");
    font.setPointSize(16);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(QColor("#024526"));
    if (firstStartGame) {
        painter->drawText(QPointF(rectWidth * textPosWidth, rectHeight * textPosHeight),
                          tr("Start"));
    } else {
        if (mouseReleased) {
            painter->drawText(QPointF(rectWidth * textPosWidth, rectHeight * textPosHeight),
                              tr("Continue"));
        } else {
            painter->drawText(QPointF(rectWidth * textPosWidth, rectHeight * textPosHeight),
                              tr("Stop"));
        }
    }
    painter->restore();
}

//按钮功能
void BTStartPause::buttonFunction()
{
    if (!firstStartGame) {
        //开始暂停功能
        if (mouseReleased) {
            //暂停游戏
            emit signalGameStop();
        } else {
            //继续游戏
            emit signalGameContinue();
        }
    } else {
        //开始游戏
        emit signalGameStart();
    }
}
