#include <QApplication>//引入的是QApplication以及QLabel这两个类。
#include <QLabel>
/*main()函数一般以创建 application 对象
 * （GUI 程序是QApplication，非 GUI 程序是QCoreApplication。
 * QApplication实际上是QCoreApplication的子类。）
 * 开始，后面才是实际业务的代码。这个对象用于管理 Qt 程序的生命周期，
 * 开启事件循环，这一切都是必不可少的。*/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QLabel label("Hello, world!");
    label.show();

    return app.exec();//调用app.exec()，开启事件循环。可以简单地将事件循环理解成一段无限循环。正因为如此，我们在栈上构建了QLabel对象，却能够一直显示在那里
}
