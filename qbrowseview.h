#ifndef QBROWSEVIEW_H
#define QBROWSEVIEW_H

#include <QListView>
#include <QObject>
#include <QWidget>
#include <QFileSystemModel>
#include <QDir>
#include <QMouseEvent>
#include <QString>
class QBrowseView : public QListView
{
    Q_OBJECT
public:
    QBrowseView(QWidget* parent = nullptr);
    ~QBrowseView();

signals:
    selectFile(const QString fname, const QString fpath);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QString sourcePath;
    QFileSystemModel* fsmodel;


};

#endif // QBROWSEVIEW_H
