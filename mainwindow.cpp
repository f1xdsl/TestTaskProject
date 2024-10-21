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
    processButtonHLay = new QHBoxLayout(this);


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
    modVarLineEdit->setText("0");



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
    processStopButton = new QPushButton("Стоп", this);
    processStopButton->setEnabled(false);

    processButtonHLay->addWidget(processButton);
    processButtonHLay->addWidget(processStopButton);

    gridLay->addLayout(destHLay,            0,  0,  1,  2);
    gridLay->addLayout(comboBoxHLay,        1,  1);
    gridLay->addWidget(deleteBox,           2,  1,  1,  1,  Qt::AlignRight);
    gridLay->addLayout(timerHLay,           3,  1,  1,  1,  Qt::AlignRight);
    gridLay->addLayout(modVarHLay,          4,  1,  1,  1,  Qt::AlignRight);
    gridLay->addLayout(processButtonHLay,   5,  1,  1,  1,  Qt::AlignRight);

    mainVLay->addLayout(labelHLay);
    mainVLay->addLayout(viewHLay);
    mainVLay->addLayout(destHLay);
    mainVLay->addLayout(gridLay);

    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    centralWidget->setLayout(mainVLay);

    processing = false;

    m_timer = new QTimer();


    connect(browseView, &QBrowseView::selectFile,
            selectedView, &QSelectedView::selectFile);

    connect(browseDestButton, &QPushButton::clicked, this, &MainWindow::chooseDestPath);

    connect(useTimerBox, &QCheckBox::clicked, this, &MainWindow::enableTimer);

    connect(destLineEdit, &QLineEdit::textChanged, this, &MainWindow::changeDestDir);

    connect(modVarLineEdit, &QLineEdit::textChanged, this, &MainWindow::changeModValue);

    connect(processStopButton, &QPushButton::clicked, this, &MainWindow::stopTimer);
    connect(processButton, &QPushButton::clicked, this, &MainWindow::processFiles);


    connect(m_timer, &QTimer::timeout, this, &MainWindow::onTimeout);

}

MainWindow::~MainWindow() {}

void MainWindow::disableAll()
{
    browseView->setEnabled(false);
    selectedView->setEnabled(false);
    actionComboBox->setEnabled(false);
    deleteBox->setEnabled(false);
    useTimerBox->setEnabled(false);
    timerLineEdit->setEnabled(false);
    actionComboBox->setEnabled(false);
    modVarLineEdit->setEnabled(false);

}

void MainWindow::enableAll()
{
    browseView->setEnabled(true);
    selectedView->setEnabled(true);
    actionComboBox->setEnabled(true);
    deleteBox->setEnabled(true);
    useTimerBox->setEnabled(true);
    actionComboBox->setEnabled(true);
    modVarLineEdit->setEnabled(true);
    if(useTimerBox->isChecked())
        timerLineEdit->setEnabled(true);

}

void MainWindow::onTimeout()
{
    processFiles();
}

void MainWindow::stopTimer()
{

    m_timer->stop();
    processButton->setEnabled(true);
    processStopButton->setEnabled(false);
    enableAll();
}


void MainWindow::processFiles()
{
    if(useTimerBox->isChecked() && !m_timer->isActive()){
        m_timer->start(timerLineEdit->text().toInt() * 1000);
        processButton->setEnabled(false);
        processStopButton->setEnabled(true);
        disableAll();
    }
    bool overwrite = actionComboBox->currentText() == "Перезапись"? true : false;
    FileProcesser fp = FileProcesser(selectedView->getStringList(), m_destDir, m_value,
                                     deleteBox->isChecked(), overwrite);

    connect(&fp, &FileProcesser::errorSignal, this, &MainWindow::errorHandler);

    fp.startProcessing();

}

void MainWindow::chooseDestPath()
{
    m_destPath = QFileDialog::getExistingDirectory(this, "Выберите директорию назначения");

    if(!m_destPath.isEmpty()){
        destLineEdit->setText(m_destPath);
    }
}

void MainWindow::changeDestDir(const QString &newText)
{
     m_destDir = newText;
}

void MainWindow::changeModValue(const QString &newText)
{
    m_value = QByteArray::fromHex(newText.leftJustified(16, '0').toUtf8());


}

void MainWindow::enableTimer(bool enable)
{
    if(!enable){
        timerLineEdit->setText("0");
    }
    timerLineEdit->setEnabled(enable);
}

void MainWindow::errorHandler(const QString &msg)
{
    QMessageBox::warning(this, "Ошибка", msg);
}
