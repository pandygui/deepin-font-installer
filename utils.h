#ifndef UTILS_H
#define UTILS_H

#include <QObject>

namespace Utils
{
    QString getQssContent(const QString &filePath);
    QString convertUtf16ToUtf8(QByteArray content);
    bool fontIsExists(const QString &fontName);
    bool suffixIsFont(const QString &suffix);
    QString getFontType(const QString &suffix);
    QStringList getFontName(const QString &filePath);
    void getFontInfo(const QString &filePath, QString &familyName, QString &styleName, QString &type, QString &version, QString &copyright, QString &description);
}

#endif // UTILS_H
