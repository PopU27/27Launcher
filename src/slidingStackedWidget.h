#pragma once

#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QParallelAnimationGroup>

class SlidingStackedWidget : public QStackedWidget {
    Q_OBJECT

public:
    enum Direction { LeftToRight, RightToLeft, TopToBottom, BottomToTop };

    explicit SlidingStackedWidget(QWidget *parent = nullptr);
    
    void setSpeed(int speedMs);
    void setEasingCurve(QEasingCurve::Type type);
    void slideToWidget(int index, Direction direction = LeftToRight);

private slots:
    void animationDone();

private:
    int mSpeed;
    QEasingCurve::Type mEasing;
    bool mActive;
    int mNextIndex;
};
