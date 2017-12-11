#ifndef UTILS_H
#define UTILS_H

#include <QObject>

namespace Utils
{
    QString getQssContent(const QString &filePath);
    bool fontIsExists(const QString &fontName);
    bool suffixIsFont(const QString &suffix);
    QString suffixList();
    QString getFontType(const QString &suffix);
    QStringList getFontName(const QString &filePath);
    QString getSfntName(const QString &filePath);
    void getFontInfo(const QString &filePath, QString &familyName, QString &styleName, QString &type, QString &version, QString &copyright, QString &description);
    void fontInstall(const QStringList &files);
    QStringList getAllFontName();
}

#endif // UTILS_H
