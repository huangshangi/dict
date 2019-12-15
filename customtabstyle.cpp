#ifndef CUSTOMTABSTYLE_H
#define CUSTOMTABSTYLE_H
#include <QPainter>
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QRect>
#include <QSize>
#define ITEM_WIDTH 150
#define ITEM_HEIGHT 50
class CustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
        const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
            s.rwidth() = ITEM_WIDTH; // 设置每个tabBar中item的大小
            s.rheight() = ITEM_HEIGHT;
        }
        return s;
    }
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel) {

            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
                QRect allRect = tab->rect;
                allRect.setWidth(allRect.width());
                allRect.setHeight(allRect.height());
                //选中状态
                if (tab->state & QStyle::State_Selected) {
                    //save用以保护坐标，restore用来退出状态
                    painter->save();
                    painter->setBrush(QBrush(0xf1e7e6));
                    //矩形
                    //painter->drawRect(allRect.adjusted(0, 0, 0, 0));
                    //带有弧线矩形
                   // painter->drawRoundedRect(tab->rect, 8, 8);
                    painter->drawRect(tab->rect);
                    painter->drawImage(20,(ITEM_HEIGHT-tab->iconSize.height())/2,tab->icon.pixmap(tab->iconSize).toImage());

                    painter->restore();
                }
                //hover状态
                else if(tab->state & QStyle::State_MouseOver){
                    painter->save();
                    painter->setBrush(QBrush(0xf2f2f1));
                    painter->drawRect(tab->rect);
                  //  painter->drawRoundedRect(allRect, 8, 8);
                    painter->restore();
                }
                else{
                    painter->save();
                    painter->setBrush(QBrush(0xf2f2f1));
                    painter->drawRect(tab->rect);
                 //   painter->drawRoundedRect(allRect, 8, 8);
                    painter->restore();
                }


                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                painter->setFont(QFont("楷体", 12));
                painter->setPen(0x826682);
                painter->drawText(allRect, tab->text, option);

                return;
            }
        }
        if (element == CE_TabBarTab) {

            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
};
#endif
