#include <QtGui>
#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    openAction = new QAction(QIcon(":/images/file-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    //每一个Action后就写一个Connect
    saveAction = new QAction(QIcon(":/images/file-save"), tr("&Save..."), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save a new file"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);
    file->addAction(saveAction);

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);

    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);
}
/*QTextEdit类用于显示富文本文件。也就是说，它不仅仅用于显示文本，还可以显示图片、表格等等。
 * 不过，我们现在只用它显示纯文本文件。QMainWindow有一个setCentralWidget()函数，
 * 可以将一个组件作为窗口的中心组件，放在窗口中央显示区。显然，在一个文本编辑器中，
 * 文本编辑区就是这个中心组件，因此我们将QTextEdit作为这种组件。*/


MainWindow::~MainWindow()
{
}

void MainWindow::openFile()
{
    /*getOpenFileName:
     *parent：父窗口。我们前面介绍过，Qt 的标准对话框提供静态函数，用于返回一个模态对话框（在一定程度上这就是外观模式的一种体现）；
     *caption：对话框标题；
     *dir：对话框打开时的默认目录，“.” 代表程序运行目录，“/” 代表当前盘符的根目录（特指 Windows 平台；Linux 平台当然就是根目录），这个参数也可以是平台相关的，比如“C:\\”等；
     *filter：过滤器。我们使用文件对话框可以浏览很多类型的文件，但是，很多时候我们仅希望打开特定类型的文件。比如，文本编辑器希望打开文本文件，图片浏览器希望打开图片文件。过滤器就是用于过滤特定的后缀名。如果我们使用“Image Files(*.jpg *.png)”，则只能显示后缀名是 jpg 或者 png 的文件。如果需要多个过滤器，使用“;;”分割，比如“JPEG Files(*.jpg);;PNG Files(*.png)”；
     *selectedFilter：默认选择的过滤器；
     *options：对话框的一些参数设定，比如只显示文件夹等等，它的取值是enum QFileDialog::Option，每个选项可以使用 | 运算组合起来。
     *QFileDialog::getOpenFileName()返回值是选择的文件路径。我们将其赋值给 path。通过判断 path 是否为空，可以确定用户是否选择了某一文件。只有当用户选择了一个文件时，我们才执行下面的操作。在saveFile()中使用的QFileDialog::getSaveFileName()也是类似的。*/
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Read File"), tr("Cannot open file:\n%1").arg(path));
            return;
        }
        /*QTextStream::readAll()读取文件所有内容，然后将其赋值给QTextEdit显示出来。最后不要忘记关闭文件。
         * 另外，saveFile()函数也是类似的，只不过最后一步，我们使用<<重定向，将QTextEdit的内容输出到一个文件中。*/
        QTextStream in(&file);
        textEdit->setText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
    }
}

void MainWindow::saveFile()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Text Files(*.txt)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"), tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
    }
}
