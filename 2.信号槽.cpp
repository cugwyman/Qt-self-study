#include <QApplication>
#include <QPushButton>//按钮在 Qt 中被称为QPushButton。
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton button("Quit");
    QObject::connect(&button, &QPushButton::clicked, [](bool) {
        qDebug() << "You clicked me!";
    });
    button.show();

    return app.exec();
}

/*connect()一般会使用前面四个参数，第一个是发出信号的对象，第二个是发送对象发出的信号，第三个是接收信号的对象，第四个是接收对象在接收到信号之后所需要调用的函数。也就是说，当 sender 发出了 signal 信号之后，会自动调用 receiver 的 slot 函数。
这是最常用的形式，我们可以套用这个形式去分析上面给出的五个重载。第一个，sender 类型是const QObject *，signal 的类型是const char *，receiver 类型是const QObject *，slot 类型是const char *。这个函数将 signal 和 slot 作为字符串处理。第二个，sender 和 receiver 同样是const QObject *，但是 signal 和 slot 都是const QMetaMethod &。我们可以将每个函数看做是QMetaMethod的子类。因此，这种写法可以使用QMetaMethod进行类型比对。第三个，sender 同样是const QObject *，signal 和 slot 同样是const char *，但是却缺少了 receiver。这个函数其实是将 this 指针作为 receiver。第四个，sender 和 receiver 也都存在，都是const QObject *，但是 signal 和 slot 类型则是PointerToMemberFunction。看这个名字就应该知道，这是指向成员函数的指针。第五个，前面两个参数没有什么不同，最后一个参数是Functor类型。这个类型可以接受 static 函数、全局函数以及 Lambda 表达式。
由此我们可以看出，connect()函数，sender 和 receiver 没有什么区别，都是QObject指针；主要是 signal 和 slot 形式的区别。具体到我们的示例，我们的connect()函数显然是使用的第五个重载，最后一个参数是QApplication的 static 函数quit()。也就是说，当我们的 button 发出了clicked()信号时，会调用QApplication的quit()函数，使程序退出。
信号槽要求信号和槽的参数一致，所谓一致，是参数类型一致。如果不一致，允许的情况是，槽函数的参数可以比信号的少，即便如此，槽函数存在的那些参数的顺序也必须和信号的前面几个一致起来。这是因为，你可以在槽函数中选择忽略信号传来的数据（也就是槽函数的参数比信号的少），但是不能说信号根本没有这个数据，你就要在槽函数中使用（就是槽函数的参数比信号的多，这是不允许的）。*/
