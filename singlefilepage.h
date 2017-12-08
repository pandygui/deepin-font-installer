#ifndef SINGLEFILEPAGE_H
#define SINGLEFILEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class SingleFilePage : public QWidget
{
    Q_OBJECT

public:
    SingleFilePage(QWidget *parent = nullptr);
    ~SingleFilePage();

    void updateInfo(const QString &filePath);

private:
    QVBoxLayout *m_layout;
    QLabel *m_nameLabel;
    QLabel *m_iconLabel;
    QLabel *m_styleLabel;
    QLabel *m_typeLabel;
    QLabel *m_versionLabel;
    QLabel *m_copyrightLabel;
    QLabel *m_descLabel;
    QLabel *m_statusLabel;
    QPushButton *m_installBtn;
    QPushButton *m_uninstallBtn;
    QPushButton *m_reinstallBtn;
};

#endif
