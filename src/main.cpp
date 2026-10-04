#include "main.h"
#include "downloadLatestZip.h"

void updateApp(std::string url, std::string dir)
{
    downloadLatestZip(url, dir + ".zip");

    std::cout << "Extracting..." << std::endl;
    elz::extractZip(dir + ".zip", dir);
}

void setUpWidget(QWidget *widget, QLayout *layout, float width = 150, float height = 50, int fontSize = 12, Qt::Alignment alignment = Qt::AlignCenter)
{
    widget->setFixedSize(QSize(width, height));

    if (QLabel *label = qobject_cast<QLabel*>(widget)) {
        label->setAlignment(Qt::AlignCenter);
    }

    QFont font = widget->font();
    font.setPointSize(fontSize);
    widget->setFont(font);

    layout->addWidget(widget);
    layout->setAlignment(widget, alignment);
}

int main(int argc, char *argv[])
{
    const std::string JackOfAllTradesApiUrl = "https://api.github.com/repos/PopU27/Jack-of-All-Trades/contents/Builds/Windows/Latest";
    const std::string JackOfAllTradesPath = "games/Jack-of-All-Trades";

    QApplication app(argc, argv);

    QWidget mainWindow;

    QSettings settings("PopU27", "27Launcher");
    settings.beginGroup("MainWindow");
    if (settings.contains("geometry")) {
        mainWindow.restoreGeometry(settings.value("geometry").toByteArray());
    }
    settings.endGroup();

    QObject::connect(&app, &QApplication::aboutToQuit, [&mainWindow]() {
        QSettings settings("PopU27", "27Launcher");
        settings.beginGroup("MainWindow");
        settings.setValue("geometry", mainWindow.saveGeometry());
        settings.endGroup();
    });

    mainWindow.showNormal();

    auto *mainLayout = new QVBoxLayout(&mainWindow);
    auto *stackedWidget = new QStackedWidget(&mainWindow);
    mainLayout->addWidget(stackedWidget);

    QWidget *titlePage = new QWidget();
    QVBoxLayout *titleLayout = new QVBoxLayout(titlePage);

    QLabel *title = new QLabel("27Launcher", titlePage);
    setUpWidget(title, titleLayout, 150, 50, 20);

    QPushButton *jackOfAllTradesButton = new QPushButton("Jack of All Trades", titlePage);
    setUpWidget(jackOfAllTradesButton, titleLayout);

    QPushButton *quit = new QPushButton("Quit", titlePage);
    setUpWidget(quit, titleLayout);

    titleLayout->addStretch(1);

    stackedWidget->addWidget(titlePage);
    stackedWidget->setCurrentWidget(titlePage);

    QObject::connect(quit, &QPushButton::clicked, &mainWindow, &QWidget::close);

    QObject::connect(jackOfAllTradesButton, &QPushButton::clicked, [stackedWidget]() {
        stackedWidget->setCurrentIndex(1);
    });

    QWidget *joatPage = new QWidget(stackedWidget);
    QVBoxLayout * joatLayout = new QVBoxLayout(joatPage);

    QPushButton *playJoat = new QPushButton("Play", joatPage);
    setUpWidget(playJoat, joatLayout);

    QPushButton *updateJoat = new QPushButton("Update", joatPage);
    setUpWidget(updateJoat, joatLayout);

    QPushButton *backButtonJoat = new QPushButton("Home", joatPage);
    setUpWidget(backButtonJoat, joatLayout);

    joatLayout->addStretch(1);

    stackedWidget->addWidget(joatPage);

    QObject::connect(playJoat, &QPushButton::clicked, [playJoat, JackOfAllTradesApiUrl]() {
        playJoat->setEnabled(false);

        QThreadPool::globalInstance()->start([=]() {
            int result = std::system(".\\games\\Jack-of-All-Trades\\Builds\\JackOfAllTrades.exe");

            QMetaObject::invokeMethod(playJoat, [playJoat]() {
                playJoat->setEnabled(true);
            }, Qt::QueuedConnection);
        });
    });

    QObject::connect(updateJoat, &QPushButton::clicked, [=]() {
        updateJoat->setEnabled(false);

        QThreadPool::globalInstance()->start([=]() {
            updateApp(JackOfAllTradesApiUrl, JackOfAllTradesPath);

            QMetaObject::invokeMethod(updateJoat, [updateJoat]() {
                updateJoat->setEnabled(true);
                std::cout << "Update complete" << std::endl;
            }, Qt::QueuedConnection);
        });
    });

    QObject::connect(backButtonJoat, &QPushButton::clicked, [stackedWidget]() {
        stackedWidget->setCurrentIndex(0);
    });

    mainWindow.show();

    return app.exec();
}