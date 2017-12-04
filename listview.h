#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QListWidget>
#include "listitem.h"

class ListView : public QListWidget
{
    Q_OBJECT

public:
    ListView(QWidget *parent = nullptr);
    ~ListView();

    void addItems(const QStringList &list);

signals:
    void countChanged(const int &count, const QString &filePath);

private slots:
    void handleClose(QListWidgetItem *list);
};

#endif

