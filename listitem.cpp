#include "listitem.h"
#include "utils.h"
#include <QPainter>

ListItem::ListItem(QWidget *parent)
    : QWidget(parent)
{
    m_item = new QListWidgetItem;
    m_layout = new QHBoxLayout(this);
    m_infoLayout = new QVBoxLayout;
    m_nameLabel = new QLabel;
    m_styleLabel = new QLabel;
    m_infoLabel = new QLabel;
    m_statusLabel = new QLabel;
    m_closeBtn = new DImageButton(":/images/close_normal.svg",
                                  ":/images/close_hover.svg",
                                  ":/images/close_press.svg");

    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(m_nameLabel);
    nameLayout->addWidget(m_styleLabel);

    m_styleLabel->setStyleSheet("QLabel { color: #909090; }");

    m_closeBtn->setFixedSize(24, 24);
    m_closeBtn->setVisible(false);

    m_infoLayout->addLayout(nameLayout);
    m_infoLayout->addWidget(m_infoLabel);

    m_layout->addLayout(m_infoLayout);
    m_layout->addStretch();
    m_layout->addWidget(m_closeBtn);
    m_layout->addWidget(m_statusLabel);

    connect(m_closeBtn, &DImageButton::clicked, this, [=] {
        emit closeBtnClicked(m_item);
    });
}

QListWidgetItem *ListItem::getItem()
{
    return m_item;
}

void ListItem::setFilePath(const QString &filePath)
{
    const QStringList list = Utils::getFontName(filePath);

    m_nameLabel->setText(list.first());
    m_styleLabel->setText(list.last());

    if (Utils::isFontInstalled(list.first())) {
        m_statusLabel->setText(tr("Installed"));
    }

    m_filePath = filePath;
}

QString ListItem::getFilePath() const
{
    return m_filePath;
}

void ListItem::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#e4e4e4"));
    painter.drawRect(QRect(0, rect().height() - 1, rect().width(), 1));
}

void ListItem::enterEvent(QEvent *e)
{
    m_closeBtn->setVisible(true);
    m_statusLabel->setVisible(false);

    QWidget::enterEvent(e);
}

void ListItem::leaveEvent(QEvent *e)
{
    m_closeBtn->setVisible(false);
    m_statusLabel->setVisible(true);

    QWidget::leaveEvent(e);
}
