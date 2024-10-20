#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainVLay     = new QVBoxLayout(this);
    labelHLay    = new QHBoxLayout(this);
    viewHLay     = new QHBoxLayout(this);
    gridLay      = new QGridLayout(this);
    destHLay     = new QHBoxLayout(this);
    comboBoxHLay = new QHBoxLayout(this);
    timerHLay    = new QHBoxLayout(this);
    modVarHLay   = new QHBoxLayout(this);


    browseView          = new QBrowseView(this);
    browseViewLabel     = new QLabel("Выбор файлов",this);

    selectedView        = new QSelectedView(this);
    selectedViewLabel   = new QLabel("Выбранные файлы",this);

    deleteBox    = new QCheckBox("Удалять исходные файлы", this);

    browseDestButton    = new QPushButton("Выбор конечной директории", this);
    destLineEdit        = new QLineEdit(this);
    destLabel           = new QLabel("Путь для сохранения:", this);
    destLineEdit->setReadOnly(true);

    useTimerBox     = new QCheckBox("Использовать таймер", this);
    timerLineEdit   = new QLineEdit(this);
    timerLabel      = new QLabel("Период таймера (сек)", this);
    intValidator    = new QIntValidator(1,9999, this);


    actionComboBox      = new QComboBox(this);
    actionComboBoxLabel = new QLabel("Действие при повторении:", this);

    modVarLabel     = new QLabel("Значение переменной для модификации (16сс)", this);
    modVarLineEdit  = new QLineEdit(this);
    regex.setPattern("^[0-9A-Fa-f]{1,16}$");
    hexValidator    = new QRegularExpressionValidator(regex,this);
    modVarLineEdit->setValidator(hexValidator);



    actionComboBox->addItem("Перезапись");
    actionComboBox->addItem("Добавление счётчика");
    actionComboBox->setMaximumSize(300,50);

    labelHLay->addWidget(browseViewLabel);
    labelHLay->addWidget(selectedViewLabel);

    viewHLay->addWidget(browseView);
    viewHLay->addWidget(selectedView);

    destHLay->addWidget(browseDestButton);
    destHLay->addWidget(destLabel);
    destHLay->addWidget(destLineEdit);

    comboBoxHLay->addWidget(actionComboBoxLabel);
    comboBoxHLay->addWidget(actionComboBox);

    comboBoxHLay->setAlignment(actionComboBoxLabel, Qt::AlignRight);

    timerHLay->addWidget(useTimerBox);
    timerHLay->addWidget(timerLabel);
    timerHLay->addWidget(timerLineEdit);

    timerLineEdit->setEnabled(false);
    timerLineEdit->setValidator(intValidator);

    modVarHLay->addWidget(modVarLabel);
    modVarHLay->addWidget(modVarLineEdit);

    processButton = new QPushButton("Запуск", this);

    gridLay->addLayout(destHLay,        0,  0,  1,  2);
    gridLay->addLayout(comboBoxHLay,    1,  1);
    gridLay->addWidget(deleteBox,       2,  1,  1,  1,  Qt::AlignRight);
    gridLay->addLayout(timerHLay,       3,  1,  1,  1,  Qt::AlignRight);
    gridLay->addLayout(modVarHLay,      4,  1,  1,  1,  Qt::AlignRight);
    gridLay->addWidget(processButton,   5,  1,  1,  1,  Qt::AlignRight);

    mainVLay->addLayout(labelHLay);
    mainVLay->addLayout(viewHLay);
    mainVLay->addLayout(destHLay);
    mainVLay->addLayout(gridLay);

    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    centralWidget->setLayout(mainVLay);


    connect(browseView, &QBrowseView::selectFile,
            selectedView, &QSelectedView::selectFile);

    connect(browseDestButton, &QPushButton::clicked, this, &MainWindow::chooseDestPath);

    connect(useTimerBox, &QCheckBox::clicked, this, &MainWindow::enableTimer);
}

MainWindow::~MainWindow() {}

void MainWindow::chooseDestPath()
{
    destPath = QFileDialog::getExistingDirectory(this, "Выберите директорию назначения");

    if(!destPath.isEmpty()){
        destLineEdit->setText(destPath + "/");
    }
}

void MainWindow::enableTimer(bool enable)
{
    if(!enable){
        timerLineEdit->clear();
    }
    timerLineEdit->setEnabled(enable);
}
