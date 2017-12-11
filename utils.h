/*
 * Copyright (C) 2011 ~ 2017 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 * Maintainer: rekols <rekols@foxmail.com>
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

#ifndef UTILS_H
#define UTILS_H

#include <QObject>

namespace Utils
{
    QString getQssContent(const QString &filePath);
    bool isFontInstalled(const QString &fontName);
    bool isFontSuffix(const QString &suffix);
    QString suffixList();
    QString getFontType(const QString &suffix);
    QStringList getFontName(const QString &filePath);
    void getFontInfo(const QString &filePath, QString &familyName, QString &styleName, QString &type, QString &version, QString &copyright, QString &description);
    void fontInstall(const QStringList &files);
    QStringList getAllFontName();
}

#endif // UTILS_H
