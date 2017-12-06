#include "homepage.h"
#include "dsvgrenderer.h"
#include <QFileDialog>

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_iconLabel = new QLabel;
    m_tipsLabel = new QLabel(tr("Drag and drop file here"));
    m_splitLine = new QLabel;
    m_chooseBtn = new DLinkButton(tr("Select File"));

    QPixmap iconPixmap = DSvgRenderer::render(":/images/icon.svg", QSize(140, 140) * devicePixelRatioF());
    m_iconLabel->setFixedSize(140, 140);
    m_iconLabel->setPixmap(iconPixmap);

    m_splitLine->setPixmap(QPixmap(":/images/split_line.svg"));

    m_layout->addStretch();
    m_layout->addWidget(m_iconLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    m_layout->addSpacing(20);
    m_layout->addWidget(m_tipsLabel, 0, Qt::AlignHCenter);
    m_layout->addSpacing(10);
    m_layout->addWidget(m_splitLine, 0, Qt::AlignHCenter);
    m_layout->addSpacing(20);
    m_layout->addWidget(m_chooseBtn, 0, Qt::AlignHCenter);
    m_layout->addStretch();

    connect(m_chooseBtn, &DLinkButton::clicked, this, &HomePage::onChooseBtnClicked);
}

HomePage::~HomePage()
{
}

void HomePage::onChooseBtnClicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter("Font Files (*.ttf *.otf)");

    if (dialog.exec() != QDialog::Accepted)
        return;

    emit fileSelected(dialog.selectedFiles());
}
