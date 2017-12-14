#include "dfontinfo.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFontInfo>

DFontInfo::DFontInfo(QObject *parent) : QObject(parent)
{
    m_ftlib = 0;
    m_face = 0;

    FT_Init_FreeType(&m_ftlib);
}

DFontInfo::~DFontInfo()
{
    FT_Done_Face(m_face);
    FT_Done_FreeType(m_ftlib);
}

FontNode DFontInfo::getFontInfo(const QString &filePath)
{
    FontNode node;
    FT_New_Face(m_ftlib, filePath.toLatin1().data(), 0, &m_face);

    node.familyName = QString::fromLatin1(m_face->family_name);
    node.styleName = QString::fromLatin1(m_face->style_name);

    for (int i = 0; i < FT_Get_Sfnt_Name_Count(m_face); ++i) {
        FT_SfntName sname;

        if (FT_Get_Sfnt_Name(m_face, i, &sname) != 0)
            continue;

        // only handle the unicode names for US langid.
        if (!(sname.platform_id == TT_PLATFORM_MICROSOFT &&
              sname.encoding_id == TT_MS_ID_UNICODE_CS &&
              sname.language_id == TT_MS_LANGID_ENGLISH_UNITED_STATES))
            continue;

        switch (sname.name_id) {
        case TT_NAME_ID_COPYRIGHT:
            node.copyright = g_convert((char *)sname.string, sname.string_len, "UTF-8", "UTF-16BE", NULL, NULL, NULL);
            break;
        case TT_NAME_ID_VERSION_STRING:
            node.version = g_convert((char *)sname.string, sname.string_len, "UTF-8", "UTF-16BE", NULL, NULL, NULL);
            break;
        case TT_NAME_ID_DESCRIPTION:
            node.description = g_convert((char *)sname.string, sname.string_len, "UTF-8", "UTF-16BE", NULL, NULL, NULL);
            break;
        }
    }

    return node;
}

QStringList DFontInfo::families()
{
    QStringList list;

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
            list << face->family_name;
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

    return list;
}

bool DFontInfo::isFontInstalled(const QString &familyName)
{
    const QStringList list = families();

    for (const QString &name : list) {
        if (name == familyName) {
            return true;
        }
    }

    return false;
}
