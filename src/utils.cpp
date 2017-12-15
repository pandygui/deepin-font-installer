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

#include "utils.h"

#include <QDebug>
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QFontInfo>
#include <QFontDatabase>

#include <fontconfig/fontconfig.h>
#include <ft2build.h>
#include <glib.h>

#include FT_FREETYPE_H
#include FT_TYPE1_TABLES_H
#include FT_SFNT_NAMES_H
#include FT_TRUETYPE_IDS_H

QString Utils::getQssContent(const QString &filePath)
{
    QFile file(filePath);
    QString qss;

    if (file.open(QIODevice::ReadOnly)) {
        qss = file.readAll();
    }

    return qss;
}

bool Utils::isFontInstalled(const QString &fontName)
{
    const QStringList families = getAllFontName();

    for (const QString &name : families) {
        if (name == fontName) {
            return true;
        }
    }

    return false;
}

bool Utils::isFontSuffix(const QString &suffix)
{
    if (suffix == "ttf" || suffix == "ttc" || suffix == "otf") {
        return true;
    } else {
        return false;
    }
}

QString Utils::suffixList()
{
    return QString("Font Files (*.ttf *.ttc *.otf)");
}

QString Utils::getFontType(const QString &suffix)
{
    if (suffix == "ttf" || suffix == "ttc") {
        return "TrueType";
    } else if (suffix == "otf") {
        return "OpenType";
    } else {
        return "Unknow";
    }
}

void Utils::getFontInfo(FontData *data)
{
    FT_Library library = 0;
    FT_Face face = 0;

    // init freetype and face.
    FT_Init_FreeType(&library);
    FT_New_Face(library, data->filePath.toLatin1().data(), 0, &face);

    // get the basic data.
    data->familyName = QString::fromLatin1(face->family_name);
    data->styleName = QString::fromLatin1(face->style_name);

    // get font type.
    const QFileInfo fileInfo(data->filePath);
    data->type = getFontType(fileInfo.suffix());

    const int count = FT_Get_Sfnt_Name_Count(face);
    for (int i = 0; i < count; ++i) {
        FT_SfntName sname;

        if (FT_Get_Sfnt_Name(face, i, &sname) != 0)
            continue;

        // only handle the unicode names for US langid.
        if (!(sname.platform_id == TT_PLATFORM_MICROSOFT &&
              sname.encoding_id == TT_MS_ID_UNICODE_CS &&
              sname.language_id == TT_MS_LANGID_ENGLISH_UNITED_STATES))
            continue;

        switch (sname.name_id) {
        case TT_NAME_ID_COPYRIGHT:
            data->copyright = g_convert((char *)sname.string,
                                        sname.string_len,
                                        "UTF-8", "UTF-16BE", NULL, NULL, NULL);
            break;
        case TT_NAME_ID_VERSION_STRING:
            data->version = g_convert((char *)sname.string,
                                      sname.string_len,
                                      "UTF-8", "UTF-16BE", NULL, NULL, NULL);
            break;
        case TT_NAME_ID_DESCRIPTION:
            data->description = g_convert((char *)sname.string,
                                          sname.string_len,
                                          "UTF-8", "UTF-16BE", NULL, NULL, NULL);
            break;
        }
    }

    // destroy object.
    if (face) {
        FT_Done_Face(face);
    }
    if (library) {
        FT_Done_FreeType(library);
    }
}

void Utils::fontInstall(const QStringList &files)
{
    QProcess *process = new QProcess;
    QString cmd = "pkexec cp -r ";

    for (auto const file : files) {
        cmd.append(file + " ");
    }

    cmd.append("/usr/share/fonts/");

    process->start(cmd);
    process->waitForFinished();
    process->kill();
    process->close();
}

QStringList Utils::getAllFontName()
{
    QStringList families;
    FcPattern *pattern = FcNameParse((FcChar8 *) ":");
    FcObjectSet *objectset = FcObjectSetBuild(FC_FILE, NULL);
    FcFontSet *fontset = FcFontList(NULL, pattern, objectset);
    FcInit();

    FT_Library library = 0;
    FT_Face face = 0;
    FT_Init_FreeType(&library);

    for (int i = 0; i < fontset->nfont; ++i) {
        FcChar8 *family;
        if (FcPatternGetString(fontset->fonts[i], FC_FILE, 0, &family) == FcResultMatch) {
            FT_New_Face(library, (char *)family, 0, &face);
            families << face->family_name;
        }
    }

    // destroy object.
    if (face)
        FT_Done_Face(face);
    if (library)
        FT_Done_FreeType(library);
    if (objectset)
        FcObjectSetDestroy(objectset);
    if (pattern)
        FcPatternDestroy(pattern);
    if (fontset)
        FcFontSetDestroy(fontset);

    return families;
}
