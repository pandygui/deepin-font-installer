#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QStackedLayout>
#include "homepage.h"
#include "singlefilepage.h"
#include "multifilepage.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);

private:
    void refreshPage();
    void onSelected(const QStringList &);
    void handleDelete(const int &, const QString &);

private:
    QWidget *m_mainWidget;
    QStackedLayout *m_mainLayout;
    HomePage *m_homePage;
    SingleFilePage *m_singleFilePage;
    MultiFilePage *m_multiFilePage;
    QStringList listItems;
};

#endif
