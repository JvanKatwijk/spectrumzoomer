/********************************************************************************
** Form generated from reading UI file 'soundcard-widget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOUNDCARD_2D_WIDGET_H
#define UI_SOUNDCARD_2D_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_soundcardWidget
{
public:
    QFrame *frame;
    QLCDNumber *showGain;
    QComboBox *cardSelector;
    QLabel *statusLabel;
    QComboBox *rateSelector;
    QSlider *gainSlider;
    QLabel *label;
    QLabel *status;

    void setupUi(QWidget *soundcardWidget)
    {
        if (soundcardWidget->objectName().isEmpty())
            soundcardWidget->setObjectName(QStringLiteral("soundcardWidget"));
        soundcardWidget->resize(241, 265);
        frame = new QFrame(soundcardWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 0, 231, 251));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        showGain = new QLCDNumber(frame);
        showGain->setObjectName(QStringLiteral("showGain"));
        showGain->setGeometry(QRect(170, 10, 51, 21));
        showGain->setSegmentStyle(QLCDNumber::Flat);
        cardSelector = new QComboBox(frame);
        cardSelector->setObjectName(QStringLiteral("cardSelector"));
        cardSelector->setGeometry(QRect(0, 110, 141, 21));
        statusLabel = new QLabel(frame);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setGeometry(QRect(10, 200, 121, 21));
        rateSelector = new QComboBox(frame);
        rateSelector->addItem(QString());
        rateSelector->addItem(QString());
        rateSelector->addItem(QString());
        rateSelector->addItem(QString());
        rateSelector->addItem(QString());
        rateSelector->setObjectName(QStringLiteral("rateSelector"));
        rateSelector->setGeometry(QRect(0, 70, 141, 21));
        gainSlider = new QSlider(frame);
        gainSlider->setObjectName(QStringLiteral("gainSlider"));
        gainSlider->setGeometry(QRect(190, 40, 18, 160));
        gainSlider->setMinimum(10);
        gainSlider->setMaximum(200);
        gainSlider->setOrientation(Qt::Vertical);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 180, 151, 21));
        status = new QLabel(frame);
        status->setObjectName(QStringLiteral("status"));
        status->setGeometry(QRect(10, 220, 181, 21));

        retranslateUi(soundcardWidget);

        QMetaObject::connectSlotsByName(soundcardWidget);
    } // setupUi

    void retranslateUi(QWidget *soundcardWidget)
    {
        soundcardWidget->setWindowTitle(QApplication::translate("soundcardWidget", "Form", nullptr));
        statusLabel->setText(QString());
        rateSelector->setItemText(0, QApplication::translate("soundcardWidget", "48000", nullptr));
        rateSelector->setItemText(1, QApplication::translate("soundcardWidget", "96000", nullptr));
        rateSelector->setItemText(2, QApplication::translate("soundcardWidget", "192000", nullptr));
        rateSelector->setItemText(3, QApplication::translate("soundcardWidget", "24000", nullptr));
        rateSelector->setItemText(4, QApplication::translate("soundcardWidget", "8000", nullptr));

        label->setText(QApplication::translate("soundcardWidget", "soundcard", nullptr));
        status->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class soundcardWidget: public Ui_soundcardWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOUNDCARD_2D_WIDGET_H
