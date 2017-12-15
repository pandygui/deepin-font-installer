/*
 * Copyright (C) 2017 ~ 2017 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "multifilepage.h"
#include "utils.h"
#include <QDebug>

MultiFilePage::MultiFilePage(QWidget *parent)
    : QWidget(parent),
      m_layout(new QVBoxLayout(this)),
      m_listView(new ListView),
      m_installBtn(new QPushButton(tr("Install")))
{
    m_installBtn->setObjectName("BlueButton");

    m_layout->addWidget(m_listView);
    m_layout->addWidget(m_installBtn, 0, Qt::AlignHCenter);

    connect(m_listView, &ListView::deleteItem, this, &MultiFilePage::handleDelete);
}

MultiFilePage::~MultiFilePage()
{
}

void MultiFilePage::addItem(const QString &path)
{
    // whether the same path.
    bool isExist = false;
    for (const auto *d : dataList) {
        if (d->filePath == path) {
            isExist = true;
        }
    }

    // add to dataList and listView if it does not exist.
    if (!isExist) {
        FontData *data = new FontData;

        data->filePath = path;
        Utils::getFontInfo(data);
        dataList << data;

        m_listView->addListItem(data);
    }
}

void MultiFilePage::handleDelete(FontData *p)
{
    dataList.removeAt(dataList.indexOf(p));

    if (p) {
        delete p;
    }

    emit countChanged();
}
