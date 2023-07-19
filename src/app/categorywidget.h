#ifndef CATEGORYWIDGET_H
#define CATEGORYWIDGET_H

#include <QStandardItemModel>
#include <QWidget>

#include "model/acobjectitem.h"

namespace Ui {
    class CategoryWidget;
}


class CategoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CategoryWidget(ACObjectItem *item,
                            QWidget *parent = nullptr);
    ~CategoryWidget();

    void setGeometry(const QRect &rect);
    void paintEvent(QPaintEvent *event);

private:
    Ui::CategoryWidget *ui;

    CategoryWidget(const CategoryWidget &) = delete;
    CategoryWidget(CategoryWidget &&) = delete;
    CategoryWidget &operator=(const CategoryWidget &) = delete;
    CategoryWidget &operator=(CategoryWidget &&) = delete;
};

#endif // CATEGORYWIDGET_H
