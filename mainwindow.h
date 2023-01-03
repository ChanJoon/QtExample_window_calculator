#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setUI();
    void handleNumButton();
    void handleOperatorButton();
    void handleMathOperatorButton();
    void handleOtherButton();
    void handleInitMemButton();
    void handleMemoryButton();
    void showResult();
    char *commify(double val, char *buf, int round);
    QString addComma(QString s);
    float getWidgetMaximumFontSize(QWidget *widget, QString text);
    ~MainWindow();
public slots:
    void numButtonClicked();
    void opButtonClicked();
    void mathOpButtonClicked();
    void dotButtonClicked();
    void clearEButtonClicked();
    void clearButtonClicked();
    void delButtonClicked();
    void modButtonClicked();
    void pmButtonClicked();
    void MCButtonClicked();
    void MRButtonClicked();
    void MpButtonClicked();
    void MmButtonClicked();
    void MSButtonClicked();
    void MButtonClicked();
private:
    Ui::MainWindow *ui;
    QString keyInputVal;
    QString outputVal;
    bool calMode;
    bool isLastOp;
    bool isCalButtonClicked;
    QVector<double> mem;
};
#endif // MAINWINDOW_H
