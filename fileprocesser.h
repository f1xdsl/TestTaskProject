#ifndef FILEPROCESSER_H
#define FILEPROCESSER_H

#include <QObject>
#include <QStringList>
#include <QDir>
#include <QTimer>
#include <QByteArray>
#include <QFile>

class FileProcesser : public QObject
{
    Q_OBJECT
public:
    FileProcesser();
    FileProcesser(const QStringList& inputFiles, const QString& outputDir, const QByteArray& value,
                const bool removeFiles, const bool overwriteFiles);
    void startProcessing();


    bool deleteFiles() const;
    void setDeleteFiles(bool newDeleteFiles);
    bool exit() const;
    void setExit(bool newExit);

signals:
    errorSignal(const QString& msg);

protected:

    QStringList inputFiles() const;
    void setInputFiles(const QStringList &newInputFiles);

    QString outputDir() const;
    void setOutputDir(const QString &newOutputDir);

    QStringList fullInputFiles() const;
    void setFullInputFiles(const QStringList &newFullInputFiles);

    QByteArray value() const;
    void setValue(const QByteArray &newValue);

    bool overwriteFiles() const;
    void setOverwriteFiles(bool newOverwriteFiles);



private:
    QString generateOutputFilename(const QString& fullfname);
    void filesProcessing();
    QByteArray modifyFile(const QByteArray& inputBytes);
    QStringList getFullFileList(const QStringList& flist);

    QStringList m_fullInputFiles;
    QStringList m_inputFiles;
    QString m_outputDir;
    QByteArray m_value;
    bool m_deleteFiles;
    bool m_overwriteFiles;
    bool m_exit;


};

#endif // FILEPROCESSER_H
