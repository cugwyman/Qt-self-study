//Q_OBJECT�����̳���QObject�ࡣֻ�м̳���QObject����࣬�ž����źŲ۵����������ԣ�Ϊ��ʹ���źŲۣ�����̳�QObject������QObject�ࣨ������ֱ�����໹�Ǽ�����ࣩ����Ӧ���ڵ�һ�д���д��Q_OBJECT�������ǲ���ʹ���źŲۣ���Ӧ���������ꡣ
#include <QObject>

////////// newspaper.h
class Newspaper : public QObject
{
    Q_OBJECT
public:
    Newspaper(const QString & name) :
        m_name(name)
    {
    }

    void send()
    {
        emit newPaper(m_name);
    }

signals:
    void newPaper(const QString &name);

private:
    QString m_name;
};

////////// reader.h
#include <QObject>
#include <QDebug>

class Reader : public QObject
{
    Q_OBJECT
public:
    Reader() {}

    void receiveNewspaper(const QString & name)
    {
        qDebug() << "Receives Newspaper: " << name;
    }
};

////////// main.cpp
#include <QCoreApplication>

#include "newspaper.h"
#include "reader.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Newspaper newspaper("Newspaper A");
    Reader reader;
    QObject::connect(&newspaper, &Newspaper::newPaper,
                     &reader,    &Reader::receiveNewspaper);
    newspaper.send();

    return app.exec();
}

/*�����ܽ�һ���Զ����źŲ���Ҫע������
�����ߺͽ����߶���Ҫ��QObject�����ࣨ��Ȼ���ۺ�����ȫ�ֺ�����Lambda ���ʽ����������ߵ�ʱ����⣩��
ʹ�� signals ����źź������ź���һ���������������� void������Ҫʵ�ֺ������룻
�ۺ�������ͨ�ĳ�Ա��������Ϊ��Ա���������ܵ� public��private��protected ��Ӱ�죻
ʹ�� emit ��ǡ����λ�÷����źţ�
ʹ��QObject::connect()���������źźͲۡ�*/
