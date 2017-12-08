#include <DApplication>
#include <DWidgetUtil>
#include <QCommandLineParser>
#include "mainwindow.h"
#include "utils.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    // load dtk xcb plugin.
    DApplication::loadDXcbPlugin();

    // init Dtk application's attrubites.
    DApplication app(argc, argv);
    app.setTheme("light");
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);
    app.loadTranslator();
    app.setOrganizationName("deepin");
    app.setApplicationVersion("1.0");
    app.setApplicationAcknowledgementPage("https://www.deepin.org/acknowledgments/deepin-font-installer");
    app.setProductIcon(QIcon(":/images/deepin-font-installer.svg"));
    app.setProductName(DApplication::translate("Main", "Deepin Font Installer"));
    app.setStyleSheet(Utils::getQssContent(":/qss/style.qss"));
    app.setApplicationDescription(DApplication::translate("Main", "Deepin Font Installer is used to install and uninstall font file for users with bulk install function."));

    // add command line parser to app.
    QCommandLineParser parser;
    parser.setApplicationDescription("Deepin Font Installer.");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("filename", "Font file path.", "file [file..]");
    parser.process(app);

    // init modules.
    MainWindow w;
    w.setFixedSize(520, 400);
    w.setWindowIcon(QIcon(":/images/deepin-font-installer.svg"));
    w.show();

    Dtk::Widget::moveToCenter(&w);

    // handle command line parser.
    const QStringList fileList = parser.positionalArguments();

    if (!fileList.isEmpty()) {
        QMetaObject::invokeMethod(&w, "onSelected", Qt::QueuedConnection, Q_ARG(QStringList, fileList));
    }

    return app.exec();
}
