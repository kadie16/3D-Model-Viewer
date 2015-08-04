#include <QtWidgets>
#include <QtTest/QtTest>
#include "objload.h"

class TestQString: public QObject
{
    Q_OBJECT
private slots:
    /* GUI event Tests */
    void testMouseDrag();
};


void TestQString::testMouseDrag(){

}

//QTEST_MAIN(TestQString)
#include "testqstring.moc"

