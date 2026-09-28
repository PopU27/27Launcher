#include "main.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget mainWindow;
    mainWindow.setWindowTitle("27Launcher");
    mainWindow.resize(320, 240);

    QVBoxLayout *layout = new QVBoxLayout(&mainWindow);
    QPushButton *button = new QPushButton("Click Me", &mainWindow);
    
    layout->addWidget(button);

    QObject::connect(button, &QPushButton::clicked, &mainWindow, &QWidget::close);

    mainWindow.show();

    return app.exec();
}
