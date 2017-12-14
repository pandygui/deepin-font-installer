#ifndef DFONTINFO_H
#define DFONTINFO_H

#include <QObject>
#include <fontconfig/fontconfig.h>
#include <ft2build.h>
#include <glib.h>

#include FT_FREETYPE_H
#include FT_SFNT_NAMES_H
#include FT_TRUETYPE_IDS_H
#include FT_TYPE1_TABLES_H

struct FontNode {
    QString familyName;
    QString styleName;
    QString version;
    QString copyright;
    QString description;
};

class DFontInfo : public QObject
{
    Q_OBJECT

public:
    DFontInfo(QObject *parent = nullptr);
    ~DFontInfo();

    FontNode getFontInfo(const QString &filePath);
    QStringList families();
    bool isFontInstalled(const QString &familyName);

private:
    FT_Library m_ftlib;
    FT_Face m_face;
};

#endif
