#include "utils.h"
#include <iconv.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_TYPE1_TABLES_H
#include FT_SFNT_NAMES_H
#include FT_TRUETYPE_IDS_H

#include <QDebug>
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

QString Utils::convertUtf16ToUtf8(QByteArray content)
{
    QString convertedStr = nullptr;

    std::size_t inputBufSize { content.size() };
    std::size_t outputBufSize {inputBufSize * 4};
    char *inputBuff { content.data() };
    char *outputBuff { new char[outputBufSize] };
    char *backupPtr { outputBuff };

    iconv_t code { iconv_open("UTF-8", "UTF16BE") }; // UTF16BE to UTF8.
    std::size_t retVal { iconv(code, &inputBuff, &inputBufSize, &outputBuff, &outputBufSize) };
    std::size_t actuallyUsed { outputBuff - backupPtr };

    convertedStr = QString::fromUtf8(QByteArray(backupPtr, actuallyUsed));
    iconv_close(code);

    delete []backupPtr;
    return convertedStr;
}

bool Utils::fontIsExists(const QString &fontName)
{
    QFontDatabase dataBase;
    for (const auto &name : dataBase.families()) {
        if (name == fontName)
            return true;
    }

    return false;
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
            char c{ static_cast<char>(sname.string[i]) };
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
