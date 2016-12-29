#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);//C++提供了关键字explicit，可以阻止不应该允许的经过转换构造函数进行的隐式转换的发生。
    ~MainWindow();
/*以下是学习时忽略了的h文件改动*/
private slots:
    void openFile();
    void saveFile();
    
private:
    QAction *openAction;
    QAction *saveAction;

    QTextEdit *textEdit;
};

#endif // MAINWINDOW_H
