#include "listview.h"
#include <QListWidgetItem>

ListView::ListView(QWidget *parent)
    : QListWidget(parent)
{
    setSelectionMode(QAbstractItemView::NoSelection);
    setStyleSheet("QListWidget { border: 1px solid #F4F4F4; border-radius: 8px; }");
}

ListView::~ListView()
{
}

void ListView::addItems(const QStringList &list)
{
    for (const auto &path : list) {
        ListItem *fileItem = new ListItem;
        fileItem->setFilePath(path);
        addItem(fileItem->getItem());
        fileItem->getItem()->setSizeHint(QSize(100, 60));
        setItemWidget(fileItem->getItem(), fileItem);
        connect(fileItem, &ListItem::closeBtnClicked, this, &ListView::handleClose);
    }
}

void ListView::handleClose(QListWidgetItem *item)
{
    ListItem *fileItem = static_cast<ListItem *>(itemWidget(item));
    delete takeItem(row(fileItem->getItem()));

    emit countChanged(count(), fileItem->getFilePath());
}
