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

#include "mainwindow.h"
#include "utils.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_mainWidget(new QWidget),
      m_mainLayout(new QStackedLayout(m_mainWidget)),
      m_homePage(new HomePage),
      m_singleFilePage(new SingleFilePage),
      m_multiFilePage(new MultiFilePage)
{
    // add widget to main layout.
    m_mainLayout->addWidget(m_homePage);
    m_mainLayout->addWidget(m_singleFilePage);
    m_mainLayout->addWidget(m_multiFilePage);

    // init window flags.
    setWindowTitle(tr("Deepin Font Installer"));
    setCentralWidget(m_mainWidget);
    setAcceptDrops(true);

    // connect the signals to the slot function.
    connect(m_homePage, &HomePage::fileSelected, this, &MainWindow::onSelected);
    connect(m_multiFilePage, &MultiFilePage::countChanged, this, &MainWindow::refreshPage);
    connect(m_singleFilePage, &SingleFilePage::installBtnClicked, this, [=] { });
}

MainWindow::~MainWindow()
{
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    auto *const mime = e->mimeData();

    // not has urls.
    if (!mime->hasUrls())
        return e->ignore();

    for (const auto &item : mime->urls()) {
        const QFileInfo info = item.path();
        if (info.isDir())
            return e->accept();
        if (info.isFile() && Utils::isFontSuffix(info.suffix()))
            return e->accept();
    }

    e->ignore();
}

void MainWindow::dropEvent(QDropEvent *e)
{
    auto *const mime = e->mimeData();

    if (!mime->hasUrls())
        return e->ignore();

    e->accept();

    // find font files.
    QStringList fileList;
    for (const auto &url : mime->urls()) {
        if (!url.isLocalFile())
            continue;

        const QString localPath = url.toLocalFile();
        const QFileInfo info(localPath);

        if (info.isFile() && Utils::isFontSuffix(info.suffix())) {
            fileList << localPath;
        }
    }

    onSelected(fileList);
}

void MainWindow::refreshPage()
{
    const int count = m_multiFilePage->dataList.count();

    if (count == 0)
        return;

    if (count == 1) {
        // switch to single file page.
        m_mainLayout->setCurrentIndex(1);
        m_singleFilePage->updateInfo(m_multiFilePage->dataList.first());
    } else {
        // switch to multi file page.
        m_mainLayout->setCurrentIndex(2);
    }
}

void MainWindow::onSelected(const QStringList &files)
{
    for (const auto &file : files) {
        m_multiFilePage->addItem(file);
    }
    
    refreshPage();
}
