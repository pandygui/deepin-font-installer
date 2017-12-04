#ifndef MULTIFILEPAGE_H
#define MULTIFILEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "listview.h"

class MultiFilePage : public QWidget
{
    Q_OBJECT

public:
    MultiFilePage(QWidget *parent = 0);
    ~MultiFilePage();

    void loadItems(const QStringList &list);

signals:
    void countChanged(const int &count, const QString &filePath);

private:
    QVBoxLayout *m_layout;
    ListView *m_listView;
    QPushButton *m_installBtn;
};

#endif
