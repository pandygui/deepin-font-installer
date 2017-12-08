#include "singlefilepage.h"
#include "dsvgrenderer.h"
#include "utils.h"
#include <QFileInfo>

DWIDGET_USE_NAMESPACE

SingleFilePage::SingleFilePage(QWidget *parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_iconLabel = new QLabel;
    m_nameLabel = new QLabel;
    m_styleLabel = new QLabel;
    m_typeLabel = new QLabel;
    m_versionLabel = new QLabel;
    m_copyrightLabel = new QLabel;
    m_descLabel = new QLabel;
    m_statusLabel = new QLabel;
    m_installBtn = new QPushButton(tr("Install"));
    m_uninstallBtn = new QPushButton(tr("Remove"));
    m_reinstallBtn = new QPushButton(tr("Reinstall"));

    m_nameLabel->setWordWrap(true);
    m_styleLabel->setWordWrap(true);
    m_typeLabel->setWordWrap(true);
    m_versionLabel->setWordWrap(true);
    m_copyrightLabel->setWordWrap(true);
    m_descLabel->setWordWrap(true);

    // set pixmap to icon label.
    QPixmap iconPixmap = DSvgRenderer::render(":/images/icon.svg", QSize(65, 65) * devicePixelRatioF());
    m_iconLabel->setFixedSize(65, 65);
    m_iconLabel->setPixmap(iconPixmap);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(m_installBtn);
    bottomLayout->addWidget(m_uninstallBtn);
    bottomLayout->addWidget(m_reinstallBtn);
    bottomLayout->addStretch();

    m_installBtn->setFixedSize(120, 36);
    m_installBtn->setObjectName("BlueButton");
    m_installBtn->hide();

    m_uninstallBtn->setFixedSize(120, 36);
    m_uninstallBtn->setObjectName("GrayButton");
    m_uninstallBtn->hide();

    m_reinstallBtn->setFixedSize(120, 36);
    m_reinstallBtn->setObjectName("GrayButton");
    m_reinstallBtn->hide();

    m_layout->addWidget(m_iconLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    m_layout->addWidget(m_nameLabel, 0, Qt::AlignHCenter);
    m_layout->addWidget(m_styleLabel);
    m_layout->addWidget(m_typeLabel);
    m_layout->addWidget(m_versionLabel);
    m_layout->addWidget(m_copyrightLabel);
    m_layout->addWidget(m_descLabel);
    m_layout->addStretch();
    m_layout->addLayout(bottomLayout);
    m_layout->addStretch();
}

SingleFilePage::~SingleFilePage()
{
}

void SingleFilePage::updateInfo(const QString &filePath)
{
    const QFileInfo info = filePath;
    QString name;
    QString style;
    QString type;
    QString version;
    QString copyright;
    QString description;
    Utils::getFontInfo(filePath, name, style, type, version, copyright, description);

    if (Utils::fontIsExists(name)) {
        m_installBtn->hide();
        m_uninstallBtn->show();
        m_reinstallBtn->show();
    } else {
        m_installBtn->show();
        m_uninstallBtn->hide();
        m_reinstallBtn->hide();
    }

    m_nameLabel->setText(name);
    m_styleLabel->setText("Style: " + style);
    m_typeLabel->setText("Type: " + Utils::getFontType(info.suffix()));
    m_versionLabel->setText("Version: " + version);
    m_copyrightLabel->setText("Copyright: " + m_copyrightLabel->fontMetrics().elidedText(copyright, Qt::ElideRight, this->width() * 2));
    m_descLabel->setText("Description: "+ m_descLabel->fontMetrics().elidedText(description, Qt::ElideRight, this->width() * 2));
}
