#include "utils.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_TYPE1_TABLES_H
#include FT_SFNT_NAMES_H
#include FT_TRUETYPE_IDS_H

#include <QDebug>
#include <QProcess>
#include <QFile>
#include <QFontDatabase>
#include <glib.h>

QString Utils::getQssContent(const QString &filePath)
{
    QFile file { filePath };
    QString qss;

    if (file.open(QIODevice::ReadOnly)) {
        qss = file.readAll();
    }

    return qss;
}

bool Utils::fontIsExists(const QString &fontName)
{
    const QFontDatabase dataBase;
    for (const QString &name : dataBase.families()) {
        if (name == fontName)
            return true;
    }

    return false;
}

bool Utils::suffixIsFont(const QString &suffix)
{
    if (suffix == "ttf" || suffix == "ttc" || suffix == "otf") {
        return true;
    } else {
        return false;
    }
}

QStringList Utils::suffixList()
{
    QStringList list;
    list << "*.ttf" << "*.ttc" << "*.otf";

    return list;
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

QStringList Utils::getFontName(const QString &filePath)
{
    QStringList data;
    FT_Library library { 0 };
    FT_Face face { 0 };
    FT_Error error { FT_Err_Ok };
    error = FT_Init_FreeType(&library);

    if (!error) {
        FT_New_Face(library, filePath.toLatin1().data(), 0, &face);
    }

    data << QString::fromLatin1(face->family_name);
    data << QString::fromLatin1(face->style_name);

    return data;
}

void Utils::getFontInfo(const QString &filePath, QString &familyName, QString &styleName, QString &type, QString &version, QString &copyright, QString &description)
{
    FT_Library m_library { 0 };
    FT_Face face { 0 };
    FT_Error error { FT_Err_Ok };
    error = FT_Init_FreeType(&m_library);

    if (!error) {
        error = FT_New_Face(m_library, filePath.toLatin1().data(), 0, &face);
    }

    familyName = QString::fromLatin1(face->family_name);
    styleName = QString::fromLatin1(face->style_name);

    const int length { FT_Get_Sfnt_Name_Count(face) };
    for (int i = 0; i < length; ++i) {
        FT_SfntName sname;
        if (FT_Get_Sfnt_Name(face, i, &sname) != 0)
            continue;

        // only handle the unicode names for US langid.
        if (!(sname.platform_id == TT_PLATFORM_MICROSOFT &&
              sname.encoding_id == TT_MS_ID_UNICODE_CS &&
              sname.language_id == TT_MS_LANGID_ENGLISH_UNITED_STATES))
            continue;

        QString str;
        for(int i  = 0; i != sname.string_len; ++i){
            char c { static_cast<char>(sname.string[i]) };
            str.push_back(c);
        }

        switch (sname.name_id) {
        case TT_NAME_ID_COPYRIGHT:
            copyright = g_convert((char *)sname.string, sname.string_len, "UTF-8", "UTF-16BE", NULL, NULL, NULL);
            break;
        case TT_NAME_ID_VERSION_STRING:
            version = g_convert((char *)sname.string, sname.string_len, "UTF-8", "UTF-16BE", NULL, NULL, NULL);
            break;
        case TT_NAME_ID_DESCRIPTION:
            description = g_convert((char *)sname.string, sname.string_len, "UTF-8", "UTF-16BE", NULL, NULL, NULL);
            break;
        }
    }

    free(m_library);
    free(face);
}

void Utils::exec(const QString &cmd, QStringList args)
{
     QProcess *process = new QProcess;

     if (args.isEmpty()) {
         process->start(cmd);
     } else {
         process->start(cmd, args);
     }

     process->waitForFinished();
     process->kill();
     process->close();
 }

void Utils::sudoExec(const QString &cmd, QStringList args)
{
    args.push_front(cmd);
    exec("pkexec", args);
}
