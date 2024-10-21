#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qbrowseview.h"
#include "qselectedview.h"
#include "fileprocesser.h"
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
#include <QByteArray>
#include <QMessageBox>
#include <QTimer>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    stopProc();

private:
    QWidget *centralWidget;
    QVBoxLayout *mainVLay;
    QHBoxLayout *viewHLay;
    QHBoxLayout *labelHLay;
    QHBoxLayout *comboBoxHLay;
    QHBoxLayout *destHLay;
    QHBoxLayout *timerHLay;
    QHBoxLayout *modVarHLay;
    QHBoxLayout *processButtonHLay;
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
    QPushButton *processStopButton;

    QIntValidator *intValidator;
    QRegularExpression regex;
    QRegularExpressionValidator *hexValidator;
    QString m_destPath;
    QString m_destDir;
    QByteArray m_value;
    QTimer *m_timer;
    bool processing;

    void disableAll();
    void enableAll();

private slots:
    void onTimeout();
    void stopTimer();
    void processFiles();
    void chooseDestPath();
    void changeDestDir(const QString& newText);
    void changeModValue(const QString& newText);
    void enableTimer(bool enable);
    void errorHandler(const QString& error);
};
#endif // MAINWINDOW_H
