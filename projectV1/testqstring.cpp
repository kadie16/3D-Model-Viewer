
#include <QtTest/QtTest>
#include "vertex.h"
class TestQString: public QObject
{
    Q_OBJECT
private slots:
    void testFindNormal();
};

void TestQString::testFindNormal()
{
    std::string s1 = "v 0 0 0";
     std::string s2 = "v 1 1 0";
     std::string s3 = "v 1 0 0";
     Vertex v1(s1, s1[0]);
     Vertex v2(s2, s2[0]);
     Vertex v3(s3, s3[0]);
     std::vector<float> vN;
     vN.push_back(0);
     vN.push_back(0);
     vN.push_back(-1);
     QVERIFY(v1.findNormal(v2, v3) == vN);
}

QTEST_MAIN(TestQString)
#include "testqstring.moc"
