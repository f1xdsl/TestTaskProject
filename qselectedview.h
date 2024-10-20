#ifndef QSELECTEDVIEW_H
#define QSELECTEDVIEW_H

#include <QListView>
#include <QObject>
#include <QWidget>
#include <QStringListModel>
#include <QMouseEvent>
#include <QRegularExpression>

class QSelectedView : public QListView
{
    Q_OBJECT
public:
    QSelectedView(QWidget* parent = nullptr);
    ~QSelectedView();

public slots:
    void selectFile(const QString fname, const QString fpath);

protected:
    void mousePressEvent(QMouseEvent *event) override;
private:
    QStringListModel* smodel;
};

#endif // QSELECTEDVIEW_H
