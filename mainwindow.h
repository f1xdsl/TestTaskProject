#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qbrowseview.h"
#include "qselectedview.h"
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QIntValidator>
#include <QRegularExpressionValidator>




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralWidget;
    QVBoxLayout *mainVLay;
    QHBoxLayout *viewHLay;
    QHBoxLayout *labelHLay;
    QHBoxLayout *comboBoxHLay;
    QHBoxLayout *destHLay;
    QHBoxLayout *timerHLay;
    QHBoxLayout *modVarHLay;
    QGridLayout *gridLay;

    QBrowseView *browseView;
    QPushButton *browseViewButton;
    QLabel *browseViewLabel;

    QSelectedView *selectedView;
    QLabel *selectedViewLabel;

    QComboBox *actionComboBox;
    QLabel *actionComboBoxLabel;

    QCheckBox *deleteBox;

    QCheckBox *useTimerBox;
    QLabel *timerLabel;
    QLineEdit *timerLineEdit;

    QPushButton *browseDestButton;
    QLineEdit *destLineEdit;
    QLabel *destLabel;

    QLineEdit *modVarLineEdit;
    QLabel *modVarLabel;

    QPushButton *processButton;

    QIntValidator *intValidator;
    QRegularExpression regex;
    QRegularExpressionValidator *hexValidator;
    QString destPath;

private slots:
    void chooseDestPath();
    void enableTimer(bool enable);
};
#endif // MAINWINDOW_H
