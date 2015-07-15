#include <QtWidgets>
#include <QtTest/QtTest>
#include "vertex.h"
#include "face.h"
#include "objload.h"

class TestQString: public QObject
{
    Q_OBJECT
private slots:
    /* Vertex Class Tests */
    void testVertexFindNormal();
    void testVertexEquals();
    void testVertexGetters();

    /* Face Class Tests */
    void testFaceNormalFuncs();
    void testFaceEquals();

    /* Obj Load Tests */
    void testObjLoad();

    /* GUI event Tests */
    void testMouseDrag();
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
     std::vector<float> actualN = v1.findNormal(v2,v3);
     std::cout << actualN.at(0) << " " << actualN.at(1) << " " << actualN.at(2) << std::endl;
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

void TestQString::testVertexGetters()
{
    /* Initialize Vertices */
     std::string s1 = "v 0 0 0";
     std::string s2 = "v 1 1 0";
     std::string s3 = "v 1 0 0";
     Vertex v1(s1, s1[0]);
     Vertex v2(s2, s2[0]);
     Vertex v3(s3, s3[0]);
     QVERIFY(v1.getX() == 0);
     QVERIFY(v1.getY() == 0);
     QVERIFY(v1.getZ() == 0);
     QVERIFY(v2.getZ() == 0);
     QVERIFY(v2.getY() == 1);
     QVERIFY(v2.getX() == 1);
     QVERIFY(v3.getX() == 1);
     QVERIFY(v3.getY() == 0);
     QVERIFY(v3.getZ() == 0);
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
     QVERIFY(std::equal(vN.begin(), vN.begin() + 2, f.getNormal().begin()));
     QVERIFY(f.getVertex(1).equalsVertex(v1));
     QVERIFY(f.getVertex(2).equalsVertex(v2));
     QVERIFY(f.getVertex(3).equalsVertex(v3));
     QVERIFY(v1.getNormal() == vN);

}

void TestQString::testFaceEquals(){
    std::string s1 = "v 0 0 0";
    std::string s2 = "v 1 1 0";
    std::string s3 = "v 1 0 0";
    Vertex v1(s1, s1[0]);
    Vertex v2(s2, s2[0]);
    Vertex v3(s3, s3[0]);
    face f1(v1,v2,v3);
    face f2(v1,v2,v3);
    face f3(v3,v2,v1);
    QVERIFY(f1.equalsFace(f2));
    QVERIFY(!f1.equalsFace(f3));
}

void TestQString::testObjLoad(){
    /* Construct objLoad from Cube File */
    objLoad loader("/Users/Kadie/Documents/kadiesworkspace/A-STAR-IHPC-Project/projectV1/testFiles/cube.obj");
    std::vector<face> faces = loader.getFacets();
    std::vector<Vertex> vertices = loader.getVertices();
    /* Manual Vertices and Faces */
    std::vector<Vertex> manualVs;
    std::string s1 = "v 0 0 0";
    std::string s2 = "v 0 0 1";
    std::string s3 = "v 0 1 0";
    std::string s4 = "v 0 1 1";
    std::string s5 = "v 1 0 0";
    std::string s6 = "v 1 0 1";
    std::string s7 = "v 1 1 0";
    std::string s8 = "v 1 1 1";

    Vertex v1(s1, 'v');
    Vertex v2(s2, 'v');
    Vertex v3(s3, 'v');
    Vertex v4(s4, 'v');
    Vertex v5(s5, 'v');
    Vertex v6(s6, 'v');
    Vertex v7(s7, 'v');
    Vertex v8(s8, 'v');

    manualVs.push_back(v1);
    manualVs.push_back(v2);
    manualVs.push_back(v3);
    manualVs.push_back(v4);
    manualVs.push_back(v5);
    manualVs.push_back(v6);
    manualVs.push_back(v7);
    manualVs.push_back(v8);

    face f1(v1,v7,v5);
    face f2(v1,v3,v7);
    face f3(v1,v4,v3);
    face f4(v1,v2,v4);
    face f5(v3,v8,v7);
    face f6(v3,v4,v8);
    face f7(v5,v7,v8);
    face f8(v5,v8,v6);
    face f9(v1,v5,v6);
    face f10(v1,v6,v2);
    face f11(v2,v6,v8);
    face f12(v2,v8,v4);

    std::vector<face> manualFs;
    manualFs.push_back(f1);
    manualFs.push_back(f2);
    manualFs.push_back(f3);
    manualFs.push_back(f4);
    manualFs.push_back(f5);
    manualFs.push_back(f6);
    manualFs.push_back(f7);
    manualFs.push_back(f8);
    manualFs.push_back(f9);
    manualFs.push_back(f10);
    manualFs.push_back(f11);
    manualFs.push_back(f12);

   for (unsigned i = 0; i < manualFs.size(); i++){
       QVERIFY(manualFs.at(i).equalsFace(faces.at(i)));
   }

   for (unsigned i = 0; i < manualVs.size(); i++){
       QVERIFY(manualVs.at(i).equalsVertex(vertices.at(i)));
   }
}

void TestQString::testMouseDrag(){

}

//QTEST_MAIN(TestQString)
#include "testqstring.moc"

