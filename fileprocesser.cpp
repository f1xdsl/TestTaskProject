#include "fileprocesser.h"

FileProcesser::FileProcesser() {}

FileProcesser::FileProcesser(const QStringList &inputFiles, const QString &outputDir, const QByteArray &value, const bool removeFiles = false, const bool overwriteFiles = true)
                      : m_inputFiles(inputFiles), m_outputDir(outputDir), m_value(value),
                        m_deleteFiles(removeFiles), m_overwriteFiles(overwriteFiles)
{

}

void FileProcesser::startProcessing(){
   filesProcessing();
}


void FileProcesser::filesProcessing(){

    if(inputFiles().isEmpty()){
        emit errorSignal("Список файлов пуст");
        return;
    }
    if(!QDir(outputDir()).exists()){
        emit errorSignal("Некорректный выходной путь");
        return;
    }

    setFullInputFiles(getFullFileList(inputFiles()));

    foreach (QString filename, fullInputFiles()) {
        QFile inputFile(filename);
        if(!inputFile.open(QIODevice::ReadOnly)){
            emit errorSignal("Не удалось открыть файл " + filename);
            return;
        }

        QByteArray fileData = inputFile.readAll();
        QByteArray outputData = modifyFile(fileData);
        QString outputFilename = generateOutputFilename(filename);
        QFile outputFile(outputFilename);

        if(!outputFile.open(QIODevice::WriteOnly)){
            emit errorSignal("Не удалось создать файл " + outputFilename);
        }
        outputFile.write(outputData);
        outputFile.close();

        if(deleteFiles()){
            inputFile.remove();
        }
        else{
            inputFile.close();
        }
    }



}

QByteArray FileProcesser::modifyFile(const QByteArray& inputBytes)
{
    QByteArray outputBytes = inputBytes;
    for(int i = 0; i < inputBytes.length(); i++){
        outputBytes[i] ^= value()[i%8];
    }
    return outputBytes;
}

QStringList FileProcesser::getFullFileList(const QStringList &flist)
{
    QStringList fullFList;

    foreach (const QString filename, flist) {
        QDir dir(filename.first(filename.lastIndexOf("/")+1));
        QStringList dirFiles = dir.entryList((QStringList)filename.mid(filename.lastIndexOf("/")+1));
        QString dirPath = dir.absolutePath() + "/";
        foreach (const QString file, dirFiles) {
            fullFList += dirPath + file;
        }
    }

    return fullFList;
}


QString FileProcesser::generateOutputFilename(const QString &fullfname)
{
    QString fname = fullfname.mid(fullfname.lastIndexOf("/")+1);
    QString ext = fname.mid(fname.lastIndexOf("."));
    QString name = fname.first(fname.lastIndexOf("."));
    QString outputFileName = outputDir() + "/" + "modified_" + fname;
    if(!overwriteFiles() && QFile::exists(outputFileName)){
        int counter = 1;
        while(QFile::exists(outputDir() + "/modified_" + name + " (" + QString::number(counter) + ")" + ext)){
            counter++;
        }
        outputFileName = outputDir() + "/modified_" + name + " (" + QString::number(counter) + ")" + ext;
    }

    return outputFileName;
}

bool FileProcesser::deleteFiles() const
{
    return m_deleteFiles;
}

void FileProcesser::setDeleteFiles(bool newDeleteFiles)
{
    m_deleteFiles = newDeleteFiles;
}


QString FileProcesser::outputDir() const
{
    return m_outputDir;
}

void FileProcesser::setOutputDir(const QString &newOutputDir)
{
    m_outputDir = newOutputDir;
}

QStringList FileProcesser::inputFiles() const
{
    return m_inputFiles;
}

void FileProcesser::setInputFiles(const QStringList &newInputFiles)
{
    m_inputFiles = newInputFiles;
}


bool FileProcesser::overwriteFiles() const
{
    return m_overwriteFiles;
}

void FileProcesser::setOverwriteFiles(bool newOverwriteFiles)
{
    m_overwriteFiles = newOverwriteFiles;
}

QByteArray FileProcesser::value() const
{
    return m_value;
}

void FileProcesser::setValue(const QByteArray &newValue)
{
    m_value = newValue;
}

QStringList FileProcesser::fullInputFiles() const
{
    return m_fullInputFiles;
}

void FileProcesser::setFullInputFiles(const QStringList &newFullInputFiles)
{
    m_fullInputFiles = newFullInputFiles;
}
