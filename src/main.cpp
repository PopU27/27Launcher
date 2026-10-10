#include "main.h"
#include "downloadLatestZip.h"
#include "getAppDataPath.h"

using namespace std;
using namespace elz;
using namespace filesystem;
using namespace Qt;

const string appDataPath = getAppDataPath() + "\\PopU27\\27Launcher\\";

// Downloads .zip file from url and saves to the dir
void updateApp(string url, string name)
{
    string fullPath = appDataPath + "games\\" + name;

    try {
        downloadLatestZip(url, fullPath + ".zip");
    } catch(const exception& e) {
        cerr << "Error downloading update" << endl;
        return;
    }

    cout << "Extracting..." << endl;
    try {
        extractZip(fullPath + ".zip", fullPath + name);
    } catch(const exception& e) {
        cerr << "Error extracting file: " << e.what() << endl;
        return;
    }

    cout << "Update complete" << endl;
}

// Helper to make widgets easier
void setUpWidget(QWidget *widget, QLayout *layout, float width = 150, float height = 50, int fontSize = 12, Alignment alignment = AlignCenter)
{
    // Set size
    widget->setFixedSize(QSize(width, height));

    // Align the text on labels to be centered
    if (QLabel *label = qobject_cast<QLabel*>(widget)) {
        label->setAlignment(AlignCenter);
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
    const string joatApiUrl = "https://api.github.com/repos/PopU27/Jack-of-All-Trades/contents/Builds/Windows/Latest";

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
        path targetPath = "";

        if (exists(targetPath)) {
            
        } else {
            
        }
        updateJoat->setEnabled(false);
        playJoat->setEnabled(false);

        QThreadPool::globalInstance()->start([=]() {
            
            int result = system(".\\games\\Jack-of-All-Trades\\Builds\\JackOfAllTrades.exe");

            QMetaObject::invokeMethod(playJoat, [=]() {
                updateJoat->setEnabled(true);
                playJoat->setEnabled(true);
            }, QueuedConnection);
        });
    });

    QObject::connect(updateJoat, &QPushButton::clicked, [=]() {
        updateJoat->setEnabled(false);
        playJoat->setEnabled(false);

        QThreadPool::globalInstance()->start([=]() {
            updateApp(joatApiUrl, "Jack-of-All-Trades");

            QMetaObject::invokeMethod(updateJoat, [=]() {
                updateJoat->setEnabled(true);
                playJoat->setEnabled(true);
            }, QueuedConnection);
        });

        stackedWidget->setCurrentIndex(2);
    });

    QObject::connect(backButtonJoat, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentIndex(0);
    });


    // --- Update page ---
    QWidget *updatePage = new QWidget(stackedWidget);
    QVBoxLayout * updateLayout = new QVBoxLayout(updatePage);

    QProgressBar *updateProgressBar = new QProgressBar(updatePage);
    updateProgressBar->setRange(0, 100);
    updateProgressBar->setValue(45);
    setUpWidget(updateProgressBar, updateLayout, 500);

    stackedWidget->addWidget(updatePage);

    mainWindow.show();

    return app.exec();
}