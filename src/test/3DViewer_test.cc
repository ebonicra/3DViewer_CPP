#include <gtest/gtest.h>

#include "../model/affinis.h"
#include "../model/model.h"

#define kAcc 1e-6

TEST(ModelTest, OpenFile1) {
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/naruto.obj");
  ASSERT_TRUE(model->FileIsValid());
}

TEST(ModelTest, OpenFile2) {
    s21::Model* model = &s21::Model::getInstance();
    model->OpenFile("objfiles/test.obj");
    ASSERT_TRUE(model->FileIsValid());
    ASSERT_EQ(model->getCountOfVertexes(), 5);
    ASSERT_EQ(model->getCountOfFacets(), 4);
}

TEST(ModelTest, WrongOpenFile) {
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/pupu.obj");
  ASSERT_FALSE(model->FileIsValid());
}

TEST(ModelTest, WrongOpenFile2) {
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/wrong_test.obj");
  ASSERT_FALSE(model->FileIsValid());
}

TEST(ModelTest, WrongOpenFile3) {
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/wrong_test2.obj");
  ASSERT_FALSE(model->FileIsValid());
}

TEST(ModelTest, GetVertexes) {
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/test.obj");
  std::vector<s21::Vertex> vertexes = model->getVertexes();
  ASSERT_FALSE(vertexes.empty());
  ASSERT_EQ(vertexes.size(), 5);
  ASSERT_DOUBLE_EQ(vertexes[0].getX(), 0.0);
  ASSERT_DOUBLE_EQ(vertexes[0].getY(), 0.8);
  ASSERT_DOUBLE_EQ(vertexes[0].getZ(), 0.0);
}

TEST(ModelTest, WrongGetVertexes) {
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/pupu.obj");
  std::vector<s21::Vertex> vertexes = model->getVertexes();
  ASSERT_TRUE(vertexes.empty());
}

TEST(ModelTest, GetFacets) {
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/test.obj");
  std::vector<s21::Facet> facets = model->getFacets();
  ASSERT_FALSE(facets.empty());
  ASSERT_EQ(facets.size(), 4);
  std::vector<unsigned int> vertexIndices = facets[0].getVertexIndices();
  ASSERT_FALSE(vertexIndices.empty());
  ASSERT_EQ(vertexIndices.size(), 6);
}

TEST(ModelTest, WrongGetFacets) {
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/pupu.obj");
  std::vector<s21::Facet> facets = model->getFacets();
  ASSERT_TRUE(facets.empty());
}

TEST(AffinesTest, MoveX) {
  s21::AffinisOperation affinis(new s21::XStrategy());
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/test.obj");
  std::vector<s21::Vertex> vertexes = model->getVertexes();

  affinis.Move(vertexes, 5.0);
  ASSERT_DOUBLE_EQ(vertexes[0].getX(), 5.0);
}

TEST(AffinesTest, MoveY) {
  s21::AffinisOperation affinis(new s21::YStrategy());
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/test.obj");
  std::vector<s21::Vertex> vertexes = model->getVertexes();

  affinis.Move(vertexes, 5.0);
  ASSERT_DOUBLE_EQ(vertexes[1].getY(), 5.0);
}

TEST(AffinesTest, MoveZ) {
  s21::AffinisOperation affinis(new s21::ZStrategy());
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/test.obj");
  std::vector<s21::Vertex> vertexes = model->getVertexes();

  affinis.Move(vertexes, 5.0);
  ASSERT_DOUBLE_EQ(vertexes[4].getZ(), 5.5);
}

TEST(AffinesTest, RotateX) {
  s21::AffinisOperation affinis(new s21::XStrategy());
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/test.obj");
  std::vector<s21::Vertex> vertexes = model->getVertexes();

  affinis.Rotate(vertexes, 90.0);
  ASSERT_NEAR(vertexes[0].getX(), 0.0, kAcc);
  ASSERT_NEAR(vertexes[0].getY(), 0.0, kAcc);
  ASSERT_NEAR(vertexes[0].getZ(), -0.8, kAcc);
}

TEST(AffinesTest, RotateY) {
  s21::AffinisOperation affinis(new s21::YStrategy());
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/test.obj");
  std::vector<s21::Vertex> vertexes = model->getVertexes();

  affinis.Rotate(vertexes, 90.0);
  ASSERT_NEAR(vertexes[0].getX(), 0.0, kAcc);
  ASSERT_NEAR(vertexes[0].getY(), 0.8, kAcc);
  ASSERT_NEAR(vertexes[0].getZ(), 0.0, kAcc);
}

TEST(AffinesTest, RotateZ) {
  s21::AffinisOperation affinis(new s21::ZStrategy());
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/test.obj");
  std::vector<s21::Vertex> vertexes = model->getVertexes();

  affinis.Rotate(vertexes, 90.0);
  ASSERT_NEAR(vertexes[0].getX(), 0.8, kAcc);
  ASSERT_NEAR(vertexes[0].getY(), 0.0, kAcc);
  ASSERT_NEAR(vertexes[0].getZ(), 0.0, kAcc);
}

TEST(AffinesTest, Scaling) {
  s21::AffinisOperation affinis(new s21::ZStrategy());
  s21::Model* model = &s21::Model::getInstance();
  model->OpenFile("objfiles/test.obj");
  std::vector<s21::Vertex> vertexes = model->getVertexes();

  affinis.Scaling(vertexes, 2.0);
  ASSERT_NEAR(vertexes[0].getX(), 0.0, kAcc);
  ASSERT_NEAR(vertexes[0].getY(), 1.6, kAcc);
  ASSERT_NEAR(vertexes[0].getZ(), 0.0, kAcc);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  free(__cxxabiv1::__cxa_get_globals());
  return RUN_ALL_TESTS();
}