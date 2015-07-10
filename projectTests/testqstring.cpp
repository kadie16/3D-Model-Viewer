#include <QString>
#include <QtTest>

class vertexTest : public QObject
{
    Q_OBJECT

public:
    vertexTest();

private Q_SLOTS:
    void testCase1();
};

vertexTest::vertexTest()
{
}

void vertexTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(vertexTest)

#include "tst_vertextest.moc"
