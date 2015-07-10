#include <QString>
#include <QtTest>

class TestVertex : public QObject
{
    Q_OBJECT

public:
    TestVertex();

private Q_SLOTS:
    void testFindNormal();
};

TestVertex::TestVertex()
{
}

void TestVertex::testFindNormal()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestVertex)

#include "tst_testvertex.moc"
