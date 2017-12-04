#include <DApplication>
#include <DWidgetUtil>
#include "mainwindow.h"
#include "utils.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
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

    MainWindow w;
    w.setFixedSize(500, 400);
    w.setWindowIcon(QIcon(":/images/deepin-font-installer.svg"));
    w.show();

    Dtk::Widget::moveToCenter(&w);

    return app.exec();
}
