#ifndef LISTITEM_H
#define LISTITEM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QVBoxLayout>
#include "dimagebutton.h"

DWIDGET_USE_NAMESPACE

class ListItem : public QWidget
{
    Q_OBJECT

public:
    ListItem(QWidget *parent = nullptr);

    QListWidgetItem *getItem();
    void setFilePath(const QString &filePath);
    QString getFilePath() const;

signals:
    void closeBtnClicked(QListWidgetItem *item);

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
    QListWidgetItem *m_item;
    QHBoxLayout *m_layout;
    QVBoxLayout *m_infoLayout;
    QLabel *m_nameLabel;
    QLabel *m_styleLabel;
    QLabel *m_infoLabel;
    QLabel *m_statusLabel;
    DImageButton *m_closeBtn;
    QString m_filePath;
};

#endif // LISTITEM_H
