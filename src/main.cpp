#include "main.h"
#include "downloadLatestZip.h"

// Downloads .zip file from url and saves to the dir
void updateApp(std::string url, std::string dir)
{
    try {
        downloadLatestZip(url, dir + ".zip");
    } catch(const std::exception& e) {
        std::cerr << "Error downloading update" << std::endl;
        return;
    }

    std::cout << "Extracting..." << std::endl;
    try {
        elz::extractZip(dir + ".zip", dir);
    } catch(const std::exception& e) {
        std::cerr << "Error extracting file: " << e.what() << std::endl;
        return;
    }

    std::cout << "Update complete" << std::endl;
}

// Helper to make widgets easier
void setUpWidget(QWidget *widget, QLayout *layout, float width = 150, float height = 50, int fontSize = 12, Qt::Alignment alignment = Qt::AlignCenter)
{
    // Set size
    widget->setFixedSize(QSize(width, height));

    // Align the text on labels to be centered
    if (QLabel *label = qobject_cast<QLabel*>(widget)) {
        label->setAlignment(Qt::AlignCenter);
    }

    // Font size
    QFont font = widget->font();
    font.setPointSize(fontSize);
    widget->setFont(font);

    // Add widget and set alignment
    layout->addWidget(widget);
    layout->setAlignment(widget, alignment);
}

int main(int argc, char *argv[])
{
    const std::string joatApiUrl = "https://api.github.com/repos/PopU27/Jack-of-All-Trades/contents/Builds/Windows/Latest";
    const std::string joatPath = "games/Jack-of-All-Trades";

    QApplication app(argc, argv);

    QWidget mainWindow;

    // Keeps settings from last session
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

    // Set up the stacked widget
    auto *mainLayout = new QVBoxLayout(&mainWindow);
    auto *stackedWidget = new QStackedWidget(&mainWindow);
    mainLayout->addWidget(stackedWidget);

    // --- TITLE PAGE ---
    QWidget *titlePage = new QWidget();
    QVBoxLayout *titleLayout = new QVBoxLayout(titlePage);

    QLabel *title = new QLabel("27Launcher", titlePage);
    setUpWidget(title, titleLayout, 150, 50, 20);

    QPushButton *joatButton = new QPushButton("Jack of All Trades", titlePage);
    setUpWidget(joatButton, titleLayout);

    QPushButton *quit = new QPushButton("Quit", titlePage);
    setUpWidget(quit, titleLayout);

    titleLayout->addStretch(1);

    stackedWidget->addWidget(titlePage);
    stackedWidget->setCurrentWidget(titlePage);

    QObject::connect(quit, &QPushButton::clicked, &mainWindow, &QWidget::close);

    QObject::connect(joatButton, &QPushButton::clicked, [stackedWidget]() {
        stackedWidget->setCurrentIndex(1);
    });

    // --- Jack of All Trades page ---
    QWidget *joatPage = new QWidget(stackedWidget);
    QVBoxLayout * joatLayout = new QVBoxLayout(joatPage);

    QLabel *joatTitle = new QLabel("Jack of All Trades", joatPage);
    setUpWidget(joatTitle, joatLayout, 300, 50, 20);

    QPushButton *playJoat = new QPushButton("Play", joatPage);
    setUpWidget(playJoat, joatLayout);

    QPushButton *updateJoat = new QPushButton("Update", joatPage);
    setUpWidget(updateJoat, joatLayout);

    QPushButton *backButtonJoat = new QPushButton("Home", joatPage);
    setUpWidget(backButtonJoat, joatLayout);

    joatLayout->addStretch(1);

    stackedWidget->addWidget(joatPage);

    QObject::connect(playJoat, &QPushButton::clicked, [=]() {
        updateJoat->setEnabled(false);
        playJoat->setEnabled(false);

        QThreadPool::globalInstance()->start([=]() {
            
            int result = std::system(".\\games\\Jack-of-All-Trades\\Builds\\JackOfAllTrades.exe");

            QMetaObject::invokeMethod(playJoat, [=]() {
                updateJoat->setEnabled(true);
                playJoat->setEnabled(true);
            }, Qt::QueuedConnection);
        });
    });

    QObject::connect(updateJoat, &QPushButton::clicked, [=]() {
        updateJoat->setEnabled(false);
        playJoat->setEnabled(false);

        QThreadPool::globalInstance()->start([=]() {
            updateApp(joatApiUrl, joatPath);

            QMetaObject::invokeMethod(updateJoat, [=]() {
                updateJoat->setEnabled(true);
                playJoat->setEnabled(true);
            }, Qt::QueuedConnection);
        });
    });

    QObject::connect(backButtonJoat, &QPushButton::clicked, [stackedWidget]() {
        stackedWidget->setCurrentIndex(0);
    });


    // --- Update page ---
    QWidget *updatePage = new QWidget(stackedWidget);
    QVBoxLayout * updateLayout = new QVBoxLayout(updatePage);

    mainWindow.show();

    return app.exec();
}