#include "qbrowseview.h"

QBrowseView::QBrowseView(QWidget* parent) : QListView(parent)
{
    fsmodel = new QFileSystemModel(this);
    fsmodel->setFilter(QDir::AllEntries);
    fsmodel->setRootPath("C:/Qt");
    this->setModel(fsmodel);
}

QBrowseView::~QBrowseView() {}

void QBrowseView::mouseDoubleClickEvent(QMouseEvent *event){
    QModelIndex index = this->indexAt(event->pos());
    QFileInfo fileInfo = fsmodel->fileInfo(index);
    if(fsmodel->fileInfo(index).fileName() == ".."){
        QDir currDir = fileInfo.dir();
        currDir.cdUp();
        this->setRootIndex(fsmodel->index(currDir.absolutePath()));
    }
    else if(fsmodel->fileInfo(index).fileName() == "."){
        this->setRootIndex(fsmodel->index(""));
    }
    else if(fileInfo.isDir()){
        this->setRootIndex(index);
    }
}


void QBrowseView::mousePressEvent(QMouseEvent *event){
    QModelIndex index = this->indexAt(event->pos());
    QFileInfo fileInfo = fsmodel->fileInfo(index);
    if(event->button() == Qt::RightButton){
        if(fileInfo.isFile()){
            QString path = fileInfo.dir().absolutePath() + "/";
            QString fname = fileInfo.fileName();
            if(event->modifiers() & Qt::ControlModifier){
                int dotInd = fname.lastIndexOf(".");
                fname = "*"+fname.mid(dotInd);
            }
            emit selectFile(fname, path);
        }
    }
}


