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

#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
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
