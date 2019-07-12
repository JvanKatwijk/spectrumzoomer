/********************************************************************************
** Form generated from reading UI file 'hackrf-widget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HACKRF_2D_WIDGET_H
#define UI_HACKRF_2D_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hackrfWidget
{
public:
    QFrame *frame;
    QLabel *statusLabel;
    QSlider *lnagainSlider;
    QLCDNumber *lnagainDisplay;
    QLabel *serialNumber;
    QSlider *vgagainSlider;
    QLCDNumber *vgagainDisplay;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *serial_number_display;
    QLabel *usb_board_id_display;
    QCheckBox *AntEnableButton;
    QCheckBox *AmpEnableButton;
    QSpinBox *ppm_correction;
    QLabel *label;
    QLabel *label_4;

    void setupUi(QWidget *hackrfWidget)
    {
        if (hackrfWidget->objectName().isEmpty())
            hackrfWidget->setObjectName(QStringLiteral("hackrfWidget"));
        hackrfWidget->resize(256, 300);
        frame = new QFrame(hackrfWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 10, 251, 291));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        statusLabel = new QLabel(frame);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setGeometry(QRect(16, 180, 121, 21));
        lnagainSlider = new QSlider(frame);
        lnagainSlider->setObjectName(QStringLiteral("lnagainSlider"));
        lnagainSlider->setGeometry(QRect(210, 40, 20, 161));
        lnagainSlider->setMaximum(39);
        lnagainSlider->setOrientation(Qt::Vertical);
        lnagainDisplay = new QLCDNumber(frame);
        lnagainDisplay->setObjectName(QStringLiteral("lnagainDisplay"));
        lnagainDisplay->setGeometry(QRect(200, 10, 41, 23));
        lnagainDisplay->setDigitCount(3);
        lnagainDisplay->setSegmentStyle(QLCDNumber::Flat);
        serialNumber = new QLabel(frame);
        serialNumber->setObjectName(QStringLiteral("serialNumber"));
        serialNumber->setGeometry(QRect(10, 210, 141, 20));
        vgagainSlider = new QSlider(frame);
        vgagainSlider->setObjectName(QStringLiteral("vgagainSlider"));
        vgagainSlider->setGeometry(QRect(150, 40, 24, 161));
        vgagainSlider->setMaximum(62);
        vgagainSlider->setOrientation(Qt::Vertical);
        vgagainDisplay = new QLCDNumber(frame);
        vgagainDisplay->setObjectName(QStringLiteral("vgagainDisplay"));
        vgagainDisplay->setGeometry(QRect(133, 10, 61, 23));
        vgagainDisplay->setSegmentStyle(QLCDNumber::Flat);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(150, 210, 31, 16));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(210, 210, 31, 20));
        serial_number_display = new QLabel(frame);
        serial_number_display->setObjectName(QStringLiteral("serial_number_display"));
        serial_number_display->setGeometry(QRect(10, 250, 231, 16));
        QFont font;
        font.setPointSize(11);
        serial_number_display->setFont(font);
        usb_board_id_display = new QLabel(frame);
        usb_board_id_display->setObjectName(QStringLiteral("usb_board_id_display"));
        usb_board_id_display->setGeometry(QRect(10, 180, 111, 16));
        AntEnableButton = new QCheckBox(frame);
        AntEnableButton->setObjectName(QStringLiteral("AntEnableButton"));
        AntEnableButton->setGeometry(QRect(10, 30, 91, 20));
        AntEnableButton->setChecked(false);
        AmpEnableButton = new QCheckBox(frame);
        AmpEnableButton->setObjectName(QStringLiteral("AmpEnableButton"));
        AmpEnableButton->setGeometry(QRect(10, 60, 101, 20));
        ppm_correction = new QSpinBox(frame);
        ppm_correction->setObjectName(QStringLiteral("ppm_correction"));
        ppm_correction->setGeometry(QRect(10, 120, 91, 22));
        ppm_correction->setMinimum(-100);
        ppm_correction->setMaximum(100);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 100, 111, 16));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 230, 91, 16));

        retranslateUi(hackrfWidget);

        QMetaObject::connectSlotsByName(hackrfWidget);
    } // setupUi

    void retranslateUi(QWidget *hackrfWidget)
    {
        hackrfWidget->setWindowTitle(QApplication::translate("hackrfWidget", "HACKRF control", nullptr));
        statusLabel->setText(QString());
        serialNumber->setText(QString());
        label_2->setText(QApplication::translate("hackrfWidget", "vga", nullptr));
        label_3->setText(QApplication::translate("hackrfWidget", "lna", nullptr));
        serial_number_display->setText(QString());
        usb_board_id_display->setText(QString());
        AntEnableButton->setText(QApplication::translate("hackrfWidget", "Ant Enable", nullptr));
        AmpEnableButton->setText(QApplication::translate("hackrfWidget", "Amp Enable", nullptr));
        label->setText(QApplication::translate("hackrfWidget", "ppm Correction", nullptr));
        label_4->setText(QApplication::translate("hackrfWidget", "Serial Number", nullptr));
    } // retranslateUi

};

namespace Ui {
    class hackrfWidget: public Ui_hackrfWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HACKRF_2D_WIDGET_H
