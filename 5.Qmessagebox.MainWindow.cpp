#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QDebug>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Main Window"));

    openAction = new QAction(QIcon(":/images/doc-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);
}

MainWindow::~MainWindow()
{
}

void MainWindow::open()
{
//    QDialog *dialog = new QDialog;
//    dialog->setAttribute(Qt::WA_DeleteOnClose);
//    dialog->setWindowTitle(tr("Hello, dialog!"));
//    dialog->show();
    QMessageBox msgBox;
    msgBox.setText(tr("The document has been modified."));
    msgBox.setInformativeText(tr("Do you want to save your changes?"));
    msgBox.setDetailedText(tr("Differences here..."));
    msgBox.setStandardButtons(QMessageBox::Save
                              | QMessageBox::Discard
                              | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Save:
        qDebug() << "Save document!";
        break;
    case QMessageBox::Discard:
        qDebug() << "Discard changes!";
        break;
    case QMessageBox::Cancel:
        qDebug() << "Close document!";
        break;
    }
}

/*
Qt 的内置对话框大致分为以下几类：
QColorDialog：选择颜色；
QFileDialog：选择文件或者目录；
QFontDialog：选择字体；
QInputDialog：允许用户输入一个值，并将其值返回；
QMessageBox：模态对话框，用于显示信息、询问问题等；
QPageSetupDialog：为打印机提供纸张相关的选项；
QPrintDialog：打印机配置；
QPrintPreviewDialog：打印预览；
QProgressDialog：显示操作过程。
这里我们简单地介绍一下标准对话框QMessageBox的使用。在前面有了关于对话框的基础之上，应该可以结合文档很轻松地学习如何使用 Qt 的标准对话框。其它种类的标准对话框，我们将在后面的章节中再一一介绍。

QMessageBox用于显示消息提示。我们一般会使用其提供的几个 static 函数：
void about(QWidget * parent, const QString & title, const QString & text)：显示关于对话框。这是一个最简单的对话框，其标题是 title，内容是 text，父窗口是 parent。对话框只有一个 OK 按钮。
void aboutQt(QWidget * parent, const QString & title = QString())：显示关于 Qt 对话框。该对话框用于显示有关 Qt 的信息。
StandardButton critical(QWidget * parent, const QString & title, const QString & text, StandardButtons buttons = Ok, StandardButton defaultButton = NoButton)：显示严重错误对话框。这个对话框将显示一个红色的错误符号。我们可以通过 buttons 参数指明其显示的按钮。默认情况下只有一个 Ok 按钮，我们可以使用StandardButtons类型指定多种按钮。
StandardButton information(QWidget * parent, const QString & title, const QString & text, StandardButtons buttons = Ok, StandardButton defaultButton = NoButton)：QMessageBox::information()函数与QMessageBox::critical()类似，不同之处在于这个对话框提供一个普通信息图标。
StandardButton question(QWidget * parent, const QString & title, const QString & text, StandardButtons buttons = StandardButtons( Yes | No ), StandardButton defaultButton = NoButton)：QMessageBox::question()函数与QMessageBox::critical()类似，不同之处在于这个对话框提供一个问号图标，并且其显示的按钮是“是”和“否”两个。
StandardButton warning(QWidget * parent, const QString & title, const QString & text, StandardButtons buttons = Ok, StandardButton defaultButton = NoButton)：QMessageBox::warning()函数与QMessageBox::critical()类似，不同之处在于这个对话框提供一个黄色叹号图标。
*/
