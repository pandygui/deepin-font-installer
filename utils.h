#ifndef UTILS_H
#define UTILS_H

#include <QObject>

namespace Utils
{
    QString getQssContent(const QString &filePath);
    bool fontIsExists(const QString &fontName);
    bool suffixIsFont(const QString &suffix);
    QStringList suffixList();
    QString getFontType(const QString &suffix);
    QStringList getFontName(const QString &filePath);
    void getFontInfo(const QString &filePath, QString &familyName, QString &styleName, QString &type, QString &version, QString &copyright, QString &description);
    void exec(const QString &cmd, QStringList args);
    void sudoExec(const QString &cmd, QStringList args);
}

#endif // UTILS_H
