
#include <QtTest/QtTest>
#include "vertex.h"
#include "face.h"
class TestQString: public QObject
{
    Q_OBJECT
private slots:
    void testVertexFindNormal();
    void testVertexEquals();

    void testFaceNormalFuncs();

    void testObjLoadParseFace();
};

void TestQString::testVertexFindNormal()
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

void TestQString::testVertexEquals()
{
    std::string s1 = "v 0 0 0";
    std::string s2 = "v 1 1 0";
    Vertex v1(s1, s1[0]);
    Vertex v2(s1, s1[0]);
    Vertex v3(s2, s2[0]);
    Vertex v4(s2, s2[0]);
    QVERIFY(v1.equalsVertex(v2));
    QVERIFY(v2.equalsVertex(v1));
    QVERIFY(v3.equalsVertex(v4));
    QVERIFY(v4.equalsVertex(v3));
}

void TestQString::testFaceNormalFuncs()
{
    /* Initialize Vertices */
     std::string s1 = "v 0 0 0";
     std::string s2 = "v 1 1 0";
     std::string s3 = "v 1 0 0";
     Vertex v1(s1, s1[0]);
     Vertex v2(s2, s2[0]);
     Vertex v3(s3, s3[0]);
     /* Give Vertices Normals */
     v1.findNormal(v2,v3);
     v2.inheritNormal(v1);
     v3.inheritNormal(v1);
     /* Make Sure Everything has same Normal */
     std::vector<float> vN;
     face f(v1,v2,v3);
     vN.push_back(0);
     vN.push_back(0);
     vN.push_back(-1);
     QVERIFY(f.getVertex(1).equalsVertex(v1));
     QVERIFY(f.getVertex(2).equalsVertex(v2));
     QVERIFY(f.getVertex(3).equalsVertex(v3));
     QVERIFY(v1.getNormal() == vN);

}

QTEST_MAIN(TestQString)
#include "testqstring.moc"

