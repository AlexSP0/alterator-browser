#ifndef DETAILSDIALOG_H
#define DETAILSDIALOG_H

#include <QDialog>

namespace Ui
{
class DetailsDialog;
}

class DetailsDialog : public QDialog
{
    Q_OBJECT
public:
    DetailsDialog(QWidget *parent = nullptr);
    ~DetailsDialog();

    void setDetailsText(QString text);
    void clearDetailsText();

private slots:
    void on_closePushButton_clicked();

private:
    Ui::DetailsDialog *ui;

private:
    DetailsDialog(const DetailsDialog &) = delete;
    DetailsDialog(DetailsDialog &&)      = delete;
    DetailsDialog &operator=(const DetailsDialog &) = delete;
    DetailsDialog &operator=(DetailsDialog &&) = delete;
};

#endif // DETAILSDIALOG_H
