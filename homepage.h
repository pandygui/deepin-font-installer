#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "dlinkbutton.h"

DWIDGET_USE_NAMESPACE

class HomePage : public QWidget
{
    Q_OBJECT

public:
    HomePage(QWidget *parent = nullptr);
    ~HomePage();

signals:
    void fileSelected(const QStringList files) const;

private:
    void onChooseBtnClicked();

private:
    QVBoxLayout *m_layout;
    QLabel *m_iconLabel;
    QLabel *m_tipsLabel;
    QLabel *m_splitLine;
    DLinkButton *m_chooseBtn;
};

#endif
