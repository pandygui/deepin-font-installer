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

private slots:
    void refreshPage();
    void onSelected(const QStringList &);

private:
    QWidget *m_mainWidget;
    QStackedLayout *m_mainLayout;
    HomePage *m_homePage;
    SingleFilePage *m_singleFilePage;
    MultiFilePage *m_multiFilePage;
};

#endif
