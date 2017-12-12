#include "multifilepage.h"
#include <QDebug>

MultiFilePage::MultiFilePage(QWidget *parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_listView = new ListView;
    m_installBtn = new QPushButton(tr("Install"));

    m_installBtn->setObjectName("BlueButton");

    m_layout->addWidget(m_listView);
    m_layout->addWidget(m_installBtn, 0, Qt::AlignHCenter);

    connect(m_listView, &ListView::countChanged, this, &MultiFilePage::countChanged);
}

MultiFilePage::~MultiFilePage()
{
}

void MultiFilePage::loadItems(const QStringList &list)
{
    m_listView->clear();
    m_listView->addItems(list);
}
