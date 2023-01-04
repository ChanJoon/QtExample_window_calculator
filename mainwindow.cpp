#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setup User Interface
    ui->setupUi(this);
    setUI();

    // Initialize variables
    keyInputVal = "0";
    outputVal = "";
    calMode = false;
    isLastOp = false;
    isCalButtonClicked = false;

    // ButtonHandler
    handleNumButton();
    handleOperatorButton();
    handleMathOperatorButton();
    handleOtherButton();
    handleInitMemButton();
    handleMemoryButton();

    showResult();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setUI()
{
    // Custom UI designs
    ui->toolButton->setText(QString::fromUtf8("\u2261"));
    ui->toolButton->setStyleSheet("QToolButton{background: transparent; font-size: 25px;}\
                                  QToolButton:hover{background: none; font-size: 25px;}");

    ui->clock->setText(QString::fromUtf8("\xe2\x9f\xb2"));
    ui->clock->setStyleSheet("QToolButton{background: transparent; font-size: 25px; color: black;}\
                                  QToolButton:hover{background: none; font-size: 25px; color: black;}");

    ui->outputLabel -> setStyleSheet("color: grey");

    ui->inputLabel->setStyleSheet("background: transparent; border: 0;");

    QFont fontKeyInput = ui->inputLabel->font();
    fontKeyInput.setLetterSpacing(QFont::PercentageSpacing, 95);
    ui->inputLabel->setFont(fontKeyInput);

    ui->pushButton_root->setText(QString::fromUtf8("\u221A"));
    ui->pushButton_root->setStyleSheet("font-size: 20px");

    ui->pushButton_p->setText(QString::fromUtf8("\u002B"));
    ui->pushButton_p->setStyleSheet("font-size: 20px");

    ui->pushButton_m->setText(QString::fromUtf8("\u2212"));
    ui->pushButton_m->setStyleSheet("font-size: 20px");

    ui->pushButton_x->setText(QString::fromUtf8("\u00D7"));
    ui->pushButton_x->setStyleSheet("font-size: 20px");

    ui->pushButton_div->setText(QString::fromUtf8("\u00F7"));
    ui->pushButton_div->setStyleSheet("font-size: 20px");

    ui->pushButton_del->setText(QString::fromUtf8("\xe2\x8c\xab"));

    ui->pushButton_eq->setText(QString::fromUtf8("\u003D"));
    ui->pushButton_eq->setStyleSheet("color: white; background-color: #2C74B3; border: 0; border-radius: 5px; font-size: 20px");
}
void MainWindow::handleNumButton()
{
    connect(ui->pushButton_0, &QPushButton::clicked, this, &MainWindow::numButtonClicked);
    connect(ui->pushButton_1, &QPushButton::clicked, this, &MainWindow::numButtonClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::numButtonClicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::numButtonClicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::numButtonClicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::numButtonClicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::numButtonClicked);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::numButtonClicked);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::numButtonClicked);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::numButtonClicked);
}
void MainWindow::handleOperatorButton()
{
    connect(ui->pushButton_p, &QPushButton::clicked, this, &MainWindow::opButtonClicked);
    connect(ui->pushButton_m, &QPushButton::clicked, this, &MainWindow::opButtonClicked);
    connect(ui->pushButton_x, &QPushButton::clicked, this, &MainWindow::opButtonClicked);
    connect(ui->pushButton_div, &QPushButton::clicked, this, &MainWindow::opButtonClicked);
    connect(ui->pushButton_eq, &QPushButton::clicked, this, &MainWindow::opButtonClicked);
}
void MainWindow::handleMathOperatorButton()
{
    connect(ui->pushButton_inv, &QPushButton::clicked, this, &MainWindow::mathOpButtonClicked);
    connect(ui->pushButton_sq, &QPushButton::clicked, this, &MainWindow::mathOpButtonClicked);
    connect(ui->pushButton_root, &QPushButton::clicked, this, &MainWindow::mathOpButtonClicked);
}
void MainWindow::handleOtherButton()
{
    connect(ui->pushButton_mod, &QPushButton::clicked, this, &MainWindow::modButtonClicked);
    connect(ui->pushButton_pm, &QPushButton::clicked, this, &MainWindow::pmButtonClicked);
    connect(ui->pushButton_dot, &QPushButton::clicked, this, &MainWindow::dotButtonClicked);
    connect(ui->pushButton_del, &QPushButton::clicked, this, &MainWindow::delButtonClicked);
    connect(ui->pushButton_CE, &QPushButton::clicked, this, &MainWindow::clearEButtonClicked);
    connect(ui->pushButton_C, &QPushButton::clicked, this, &MainWindow::clearButtonClicked);
}
void MainWindow::handleInitMemButton()
{
    connect(ui->pushButton_Mp, &QPushButton::clicked, this, &MainWindow::MpButtonClicked);
    connect(ui->pushButton_Mm, &QPushButton::clicked, this, &MainWindow::MmButtonClicked);
    connect(ui->pushButton_MS, &QPushButton::clicked, this, &MainWindow::MSButtonClicked);
}
void MainWindow::handleMemoryButton()
{
    // if memory empty, deactivate MC, MR, M Buttons.
    if(!mem.isEmpty())
    {
        ui->pushButton_MC->setStyleSheet("QPushButton{background: transparent;}\
    QPushButton:hover{background: none}");
        ui->pushButton_MR->setStyleSheet("QPushButton{background: transparent;}\
    QPushButton:hover{background: none}");
        ui->pushButton_M->setStyleSheet("QPushButton{background: transparent;}\
    QPushButton:hover{background: none}");

        connect(ui->pushButton_MC, &QPushButton::clicked, this, &MainWindow::MCButtonClicked);
        connect(ui->pushButton_MR, &QPushButton::clicked, this, &MainWindow::MRButtonClicked);
        connect(ui->pushButton_M, &QPushButton::clicked, this, &MainWindow::MButtonClicked);
    }
    else
    {
        ui->pushButton_MC->setStyleSheet("QPushButton{background: transparent; color: grey;}");
        ui->pushButton_MR->setStyleSheet("QPushButton{background: transparent; color: grey;}");
        ui->pushButton_Mp->setStyleSheet("QPushButton{background: transparent;}\
    QPushButton:hover{background: none}");
        ui->pushButton_Mm->setStyleSheet("QPushButton{background: transparent;}\
    QPushButton:hover{background: none}");
        ui->pushButton_MS->setStyleSheet("QPushButton{background: transparent;}\
    QPushButton:hover{background: none}");
        ui->pushButton_M->setStyleSheet("QPushButton{background: transparent; color: grey;}");

        disconnect(ui->pushButton_MC, &QPushButton::clicked, this, &MainWindow::MCButtonClicked);
        disconnect(ui->pushButton_MR, &QPushButton::clicked, this, &MainWindow::MRButtonClicked);
        disconnect(ui->pushButton_M, &QPushButton::clicked, this, &MainWindow::MButtonClicked);
    }
}
void MainWindow::numButtonClicked()
{
    QObject* pObject = sender();
    QString num = pObject->objectName().back();

    if (num == "0" && keyInputVal == "0"); // Button0 clicked when initial state
    else{
        if (keyInputVal == "0" || isCalButtonClicked){
            // After = button clicked, if operator clicked then calculation continued. if not initialized.
            if(isCalButtonClicked)
            {
                if(outputVal.length() != 2) outputVal = ""; // Exception e.g. 3=
                isCalButtonClicked = false;
            }
            keyInputVal = num;  // If button clicked when "0" is on screen or After calculation, Button Number is not added but replaced.
        }
        else keyInputVal += num; // Normally, Button Number will be accumulated.

        if (isLastOp == true)
        {
            keyInputVal = num;
            isLastOp = false;
            calMode = true;   // numButton is clicked, when there are number and operator
        }
    }
    showResult();
}
void MainWindow::opButtonClicked()
{
    QObject* pObject = sender();
    QString opName = pObject->objectName().split("_").last();
    QString op;

    isLastOp = true;
    isCalButtonClicked = false;

    // Get operator from button name.
    if (opName == "p") op = "\u002B";
    else if (opName == "m") op = "-";
    else if (opName == "x") op = "\u00D7";
    else if (opName == "div") op = "\u00F7";
    else if (opName == "eq"){
        op = "=";
        isCalButtonClicked = true;
        isLastOp = false;
    }

    if (calMode == true){
        QString opLast;
        double a = 0;
        double b = keyInputVal.toDouble();
        double result = 0;

        if (outputVal.isEmpty()){
            // No Operator exsited before. e.g. 3=
            outputVal = keyInputVal + op;
            isLastOp = false;
            isCalButtonClicked = false;
        }
        else{
            opLast = outputVal.back();
            a = outputVal.chopped(1).toDouble();
        }

        if (b == 0 && opLast == "\u00F7"){
            qDebug() << "Division by zero";
            keyInputVal = QString("0으로 나눌 수 없습니다");

            isCalButtonClicked = false;
        }
        else{
            // Calculate
            if (opLast == "\u002B") result = a + b;
            else if (opLast == "-") result = a - b;
            else if (opLast == "\u00D7") result = a * b;
            else if (opLast == "\u00F7") result = a / b;
            else{
                // When 1/x, x^2, sqrt(x), % clikced
                // opLast is not last value of outputVal.
                QStringList outputArr;

                if (outputVal.contains("\u002B")){          // plus
                    opLast = "\u002B";
                    outputArr = outputVal.split("\u002B");
                    a = outputArr[0].toDouble();
                    result = a + keyInputVal.toDouble();
                }
                else if (outputVal.contains("-")){          // minus
                    opLast = "-";
                    outputArr = outputVal.split("-");
                    a = outputArr[0].toDouble();
                    result = a - keyInputVal.toDouble();
                }
                else if (outputVal.contains("\u00D7")){     // multiplication
                    opLast = "\u00D7";
                    outputArr = outputVal.split("\u00D7");
                    a = outputArr[0].toDouble();
                    result = a * keyInputVal.toDouble();
                }
                else if (outputVal.contains("\u00F7")){     // division
                    opLast = "\u00F7";
                    outputArr = outputVal.split("\u00F7");
                    a = outputArr[0].toDouble();
                    result = a - keyInputVal.toDouble();
                }
                else qDebug() << "[ERROR] Calculation Error";
                b = keyInputVal.toDouble();
            }
            keyInputVal = QString::number(result, 'g', 10);

            if (isCalButtonClicked){            // visualize = operator at the end of the privious result.
                outputVal = QString::number(a, 'g', 10) + opLast + QString::number(b, 'g', 10) + op;
            }
            else outputVal = keyInputVal + op;  // else operator changes.


        }
        calMode = false;
    }
    else{   // calMode = false; only number & operator e.g. 12+
        outputVal = keyInputVal + op;
    }
    showResult();
}
void MainWindow::mathOpButtonClicked()
{
    QObject* pObject = sender();
    QString opName = pObject->objectName().split("_").last();
    QString op, opLast;
    double a = keyInputVal.toDouble();

    isLastOp = true;
    if (!outputVal.isEmpty()) opLast = outputVal.back();
    else{
        // Debug
        opLast = "";
        qDebug() << "[ERROR] No operation existed. outputVal is empty";
    }

    if (opName == "inv")
    {
        op = "1/(";
        if (opLast == "=" || opLast == ")") outputVal = op + keyInputVal + ")";  // 1/(2)
        else outputVal +=  op + keyInputVal + ")";  // 1 + 1/(2)
        keyInputVal = QString::number(1 / a, 'g', 10);
    }
    else if (opName == "sq")
    {
        op = "sqr(";
        if (opLast == "=" || opLast == ")") outputVal = op + keyInputVal + ")";  // sqr(4)
        else outputVal += op + keyInputVal + ")";   // 3 + sqr(4)
        keyInputVal = QString::number(pow(a,2), 'g', 10);
    }
    else if (opName == "root")
    {
        op = "\u221A(";
        if (opLast == "=" || opLast == ")") outputVal = op + keyInputVal + ")";  // sqrt(6)
        else outputVal += op + keyInputVal + ")";   // 5 + sqrt(6)
        keyInputVal = QString::number(sqrt(a), 'g', 10);
    }
    showResult();
}
void MainWindow::dotButtonClicked()
{
    // add decimal point once
    if (!keyInputVal.contains(".")) keyInputVal += ".";
    showResult();
}
void MainWindow::delButtonClicked()
{
    keyInputVal.chop(1);
    if (keyInputVal.isEmpty() == true) keyInputVal = "0";
    showResult();
}
void MainWindow::clearEButtonClicked()
{
    keyInputVal = "0";
    showResult();
}
void MainWindow::clearButtonClicked()
{
    // reinitialize
    keyInputVal = "0";
    outputVal = "";
    isLastOp = false;
    calMode = false;
    isCalButtonClicked = false;
    showResult();
}
void MainWindow::pmButtonClicked()
{
    if (keyInputVal != "0"){
        if (keyInputVal.front() != '-') keyInputVal = "-" + keyInputVal;
        else keyInputVal = keyInputVal.right(keyInputVal.length()-1);
    }
    showResult();
}
void MainWindow::modButtonClicked()
{
    if(!outputVal.isEmpty()){
        QString op;
        if (!outputVal.isEmpty()) op = outputVal.back();
        else qDebug() << "[ERROR] No operation existed. outputVal is empty";

        if (op != "="){
            double a = outputVal.chopped(1).toDouble();
            double b = keyInputVal.toDouble();
            double result = 0;

            isLastOp = true;
            result = a * b / 100;
            keyInputVal = QString::number(result, 'g', 10);
            outputVal = QString::number(a, 'g', 10) + op + QString::number(result, 'g', 10);
        }
    }
    else{
        keyInputVal = "0";
        outputVal = "0";
    }

    showResult();
}
void MainWindow::MCButtonClicked()
{
    if(mem.isEmpty()) return;
    else mem.clear();

    if (isCalButtonClicked) outputVal = "";
    qDebug() << "[MC]" << mem;

    setUI();
    handleMemoryButton();
}
void MainWindow::MRButtonClicked()
{
    if(mem.isEmpty()) return;
    else
    {
        keyInputVal = QString::number(mem.takeLast());
        mem.append(keyInputVal.toDouble());
        qDebug() << keyInputVal;
    }

    if (isCalButtonClicked) outputVal = "";
    qDebug() << "[MR]" << mem;

    setUI();
    showResult();
}
void MainWindow::MpButtonClicked()
{
    if(mem.isEmpty()) mem.append(keyInputVal.toDouble());
    else mem.append(mem.takeLast() + keyInputVal.toDouble());

    if (isCalButtonClicked) outputVal = "";
    qDebug() << "[M+]" << mem;

    isCalButtonClicked = true;
    setUI();
    handleMemoryButton();
}
void MainWindow::MmButtonClicked()
{
    if(mem.isEmpty()) mem.append(-keyInputVal.toDouble());
    else mem.append(mem.takeLast() - keyInputVal.toDouble());

    if (isCalButtonClicked) outputVal = "";
    qDebug() << "[M-]" << mem;

    isCalButtonClicked = true;
    setUI();
    handleMemoryButton();
}
void MainWindow::MSButtonClicked()
{
    mem.append(keyInputVal.toDouble());
    if (isCalButtonClicked) outputVal = "";
    qDebug() << "[MS]" << mem;

    setUI();
    handleMemoryButton();
}
void MainWindow::MButtonClicked()
{
    setUI();
}
void MainWindow::showResult()
{
//    qDebug() << "isCalButtonClicked: " << isCalButtonClicked << "CalMode: " << calMode << "isLastOp: " << isLastOp;

    QString keyOutput;
    if(keyInputVal != "0으로 나눌 수 없습니다") keyOutput = addComma(keyInputVal); // Exception. Division by zero.
    else keyOutput = keyInputVal;

    // Dynamically resizing QLabel text.
    QFont DynamicText = font();
    float fontSize = getWidgetMaximumFontSize(ui->inputLabel, keyInputVal);
    DynamicText.setPointSizeF(fontSize);
    ui->inputLabel->setFont(DynamicText);

    ui->inputLabel->setText(keyOutput);
    ui->outputLabel->setText(outputVal);
}
char *MainWindow::commify(double val, char *buf, int round)
{
    /*****************************************************************************
     *                                commify()                                  *
     *                                                                           *
     *  Commify a number, that is add commas between every third digit ahead of  *
     *  the decimal point.  Rounds off to abs(round) digits following the        *
     *  decimal point. Stores the results into the buf[] passed to the function  *
     *  and returns a pointer to it.  Uses the standard library function fcvt()  *
     *  to do the conversion from the double val to the string of digits.        *
     *                                                                           *
     *****************************************************************************/

    static char *result;
    char *nmr;
    int  dp, sign;

    result = buf;
    if(round < 0)                        /*  Be sure round-off is positive  */
        round = -round;
    nmr = fcvt(val, round, &dp, &sign);  /*  Convert number to a string     */
    if(sign)                             /*  Prefix minus sign if negative  */
        *buf++ = '-';
    if(dp <= 0){                         /*  Check if number is less than 1 */
        if(dp < -round)                  /*  Set dp to max(dp, -round)      */
            dp = -round;
        *buf++ = '0';                    /*  Prefix with "0."               */
        *buf++ = '.';
        while(dp++)                      /*  Write zeros following decimal  */
            *buf++ = '0';                /*     point                       */
    }
    else{                                /*  Number is >= 1, commify it     */
        while(dp--){
            *buf++ = *nmr++;
            if(dp % 3 == 0)
                *buf++ = dp ? ',' : '.';
        }
    }
    strcpy(buf, nmr);                     /*  Append rest of digits         */
    return result;                        /*     following dec pt           */

}
QString MainWindow::addComma(QString s)
{
    bool isDecimal = s.contains(".", Qt::CaseInsensitive);
    QStringList keyInputArr;
    char buf[32];
    int round;

    if (isDecimal == true)
    {
        keyInputArr = s.split(".");
        round = keyInputArr[1].length() + 1;
    }
    else
    {
        round = 0;
    }
    QString keyInputVal_ = commify(s.toDouble(), buf, round);
    s = keyInputVal_.chopped(1);

    return s;
}
float MainWindow::getWidgetMaximumFontSize(QWidget *widget, QString text)
{
//    MIT License

//    Copyright (c) 2017 Jonas Dourado

//    Permission is hereby granted, free of charge, to any person obtaining a copy
//    of this software and associated documentation files (the "Software"), to deal
//    in the Software without restriction, including without limitation the rights
//    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//    copies of the Software, and to permit persons to whom the Software is
//    furnished to do so, subject to the following conditions:

//    The above copyright notice and this permission notice shall be included in all
//    copies or substantial portions of the Software.

//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//    SOFTWARE.

    QFont font = widget->font();
    const QRect widgetRect = widget->contentsRect();
    const float widgetWidth = widgetRect.width();
    const float widgetHeight = widgetRect.height();
    const float FONT_PRECISION = 0.5;

    QRectF newFontSizeRect;
    float currentSize = font.pointSizeF();

    float step = currentSize/2.0;

    /* If too small, increase step */
    if (step<=FONT_PRECISION){
        qDebug() << "step is too small";
        step = FONT_PRECISION*4.0;
    }

    float lastTestedSize = currentSize;

    float currentHeight = 0;
    float currentWidth = 0;
    if (text==""){
        return currentSize;
    }

    /* Only stop when step is small enough and new size is smaller than QWidget */
    while(step>FONT_PRECISION || (currentHeight > widgetHeight) || (currentWidth > widgetWidth)){
        /* Keep last tested value */
        lastTestedSize = currentSize;

        /* Test label with its font */
        font.setPointSizeF(currentSize);
        /* Use font metrics to test */
        QFontMetricsF fm(font);

        /* Check if widget is QLabel */
        QLabel *label = qobject_cast<QLabel*>(widget);
        if (label) {
            newFontSizeRect = fm.boundingRect(widgetRect, (label->wordWrap()?Qt::TextWordWrap:0) | label->alignment(), text);
        }
        else{
            newFontSizeRect = fm.boundingRect(widgetRect,  0, text);
        }

        currentHeight = newFontSizeRect.height();
        currentWidth = newFontSizeRect.width()+30;

        /* If new font size is too big, decrease it */
        if ((currentHeight > widgetHeight) || (currentWidth > widgetWidth)){
//            qDebug() << "--/ contentsRect()" << label->contentsRect() << "rect"<< label->rect() << " newFontSizeRect" << newFontSizeRect << "Tight" << text << currentSize;
            currentSize -=step;
            /* if step is small enough, keep it constant, so it converge to biggest font size */
            if (step>FONT_PRECISION){
                step/=2.0;
            }
            /* Do not allow negative size */
            if (currentSize<=0){
                break;
            }
        }
        /* If new font size is smaller than maximum possible size, increase it */
        else{
            //qDebug() << "++ contentsRect()" << label->contentsRect() << "rect"<< label->rect() << " newFontSizeRect" << newFontSizeRect << "Tight" << text << currentSize;
            currentSize +=step;
        }
    }
    return lastTestedSize;
}
