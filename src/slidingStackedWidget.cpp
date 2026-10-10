#include "SlidingStackedWidget.h"

SlidingStackedWidget::SlidingStackedWidget(QWidget *parent)
    : QStackedWidget(parent), mSpeed(300), mEasing(QEasingCurve::OutQuad), mActive(false), mNextIndex(-1) {}

void SlidingStackedWidget::setSpeed(int speedMs) { mSpeed = speedMs; }
void SlidingStackedWidget::setEasingCurve(QEasingCurve::Type type) { mEasing = type; }

void SlidingStackedWidget::slideToWidget(int index, Direction direction) {
    if (mActive || index == currentIndex() || index < 0 || index >= count()) return;

    mActive = true;
    mNextIndex = index;

    int width = this->width();
    int height = this->height();

    QWidget *currentW = widget(currentIndex());
    QWidget *nextW = widget(index);

    QPoint offsetCurrent, offsetNext;
    switch (direction) {
        case LeftToRight: offsetCurrent = QPoint(-width, 0);  offsetNext = QPoint(width, 0);   break;
        case RightToLeft: offsetCurrent = QPoint(width, 0);   offsetNext = QPoint(-width, 0);  break;
        case TopToBottom: offsetCurrent = QPoint(0, -height); offsetNext = QPoint(0, height);  break;
        case BottomToTop: offsetCurrent = QPoint(0, height);  offsetNext = QPoint(0, -height); break;
    }

    nextW->setGeometry(offsetNext.x(), offsetNext.y(), width, height);
    nextW->show();
    nextW->raise();

    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);

    QPropertyAnimation *animCurrent = new QPropertyAnimation(currentW, "pos");
    animCurrent->setDuration(mSpeed);
    animCurrent->setEasingCurve(mEasing);
    animCurrent->setStartValue(QPoint(0, 0));
    animCurrent->setEndValue(offsetCurrent);

    QPropertyAnimation *animNext = new QPropertyAnimation(nextW, "pos");
    animNext->setDuration(mSpeed);
    animNext->setEasingCurve(mEasing);
    animNext->setStartValue(offsetNext);
    animNext->setEndValue(QPoint(0, 0));

    group->addAnimation(animCurrent);
    group->addAnimation(animNext);

    connect(group, &QParallelAnimationGroup::finished, this, &SlidingStackedWidget::animationDone);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void SlidingStackedWidget::animationDone() {
    setCurrentIndex(mNextIndex);
    mActive = false;
}
