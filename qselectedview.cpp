#include "qselectedview.h"

QSelectedView::QSelectedView(QWidget* parent) :
    QListView(parent)
{
    smodel = new QStringListModel(this);
    this->setModel(smodel);
}

QSelectedView::~QSelectedView() {}

QStringList QSelectedView::getStringList()
{
    return smodel->stringList();
}

void QSelectedView::selectFile(const QString fname, const QString fpath){
    QStringList slist = smodel->stringList();

    QString name = fname;
    int ind = name.lastIndexOf(".");
    name = "*" + name.mid(ind);

    if (name == fname){
        QString fileExt = name.mid(ind);
        QRegularExpression regex(fpath + ".*" + fileExt);
        for(QString& s: slist){
            if(regex.match(s).hasMatch()){
                slist.removeOne(s);
            }
        }
    }

    if(!slist.contains(fpath+name) && !slist.contains(fpath+fname)){
        slist.append(fpath+fname);
        smodel->setStringList(slist);
    }

    smodel->setStringList(slist);

}

void QSelectedView::mousePressEvent(QMouseEvent *event){
    QModelIndex index = this->indexAt(event->pos());
    if(event->button() == Qt::RightButton){
        smodel->removeRows(index.row(),1);
    }
}

