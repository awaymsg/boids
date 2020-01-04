#include "Boid.h"
#include <qdebug.h>

Boid::Boid(QNode *parent)
  : QEntity(parent),
  m_Position(rand() % 10 - 5, rand() % 10 - 5, rand() % 10 - 5),
  m_BoidColor(255, 255, 0)
{
  m_MovementVector = QVector3D(0, 0.01f, 0);
  m_RotationVector = QVector3D(rand() - 1, rand() - 1, rand() - 1);

  m_BoidMesh = new Qt3DExtras::QConeMesh();
  m_BoidMesh->setBottomRadius(0.05f);
  m_BoidMesh->setTopRadius(0);
  m_BoidMesh->setHasTopEndcap(true);
  m_BoidMesh->setHasBottomEndcap(true);
  m_BoidMesh->setSlices(100);
  m_BoidMesh->setLength(.2f);
  m_BoidMesh->setRings(100);

  m_BoidTransform = new Qt3DCore::QTransform();
  m_BoidTransform->setScale(1);
  m_BoidTransform->setTranslation(m_Position);
  m_BoidTransform->setRotation(QQuaternion::fromAxisAndAngle(m_RotationVector, 90));

  m_BoidMaterial = new Qt3DExtras::QPhongMaterial();
  m_BoidMaterial->setDiffuse(m_BoidColor);
  m_BoidMaterial->setAmbient(m_BoidColor);

  m_BoidEntity = new Qt3DCore::QEntity(parent);
  m_BoidEntity->addComponent(m_BoidMesh);
  m_BoidEntity->addComponent(m_BoidTransform);
  m_BoidEntity->addComponent(m_BoidMaterial);
}

//the boid moves by calculating its up vector from its rotation and using the up vector to determine velocity
void Boid::moveBoid() {
  m_EulerAngles = m_BoidTransform->rotation().toEulerAngles();
  calculateUpFromRotation();
  m_DownVector = m_UpVector * -1.0f;
  m_Position += m_UpVector * 0.1f;
  
  if (m_Position.x() > 12.0f) m_Position.setX(-12.0f);
  if (m_Position.x() < -12.0f) m_Position.setX(12.0f);
  if (m_Position.y() > 12.0f) m_Position.setY(-12.0f);
  if (m_Position.y() < -12.0f) m_Position.setY(12.0f);
  if (m_Position.z() > 12.0f) m_Position.setZ(-12.0f);
  if (m_Position.z() < -12.0f) m_Position.setZ(12.0f);

  m_BoidTransform->setTranslation(m_Position);
}

//this function is extra, was for cacluting any vector based on rotation
QVector3D Boid::calculateVectorFromRotation(QVector3D v) {
  QVector4D quaternion = m_BoidTransform->rotation().toVector4D();

  float num1 = quaternion.x() * 2.0f;
  float num2 = quaternion.y() * 2.0f;
  float num3 = quaternion.z() * 2.0f;
  float num4 = quaternion.x() * num1;
  float num5 = quaternion.y() * num2;
  float num6 = quaternion.z() * num3;
  float num7 = quaternion.x() * num2;
  float num8 = quaternion.x() * num3;
  float num9 = quaternion.y() * num3;
  float num10 = quaternion.w() * num1;
  float num11 = quaternion.w() * num2;
  float num12 = quaternion.w() * num3;

  QVector3D vector;

  vector.setX((float)((1.0 - ((double)num5 + (double)num6)) * (double)v.x() + ((double)num7 - (double)num12) * (double)v.y() + ((double)num8 + (double)num11) * (double)v.z()));
  vector.setY((float)(((double)num7 + (double)num12) * (double)v.x() + (1.0 - ((double)num4 + (double)num6)) * (double)v.y() + ((double)num9 - (double)num10) * (double)v.z()));
  vector.setZ((float)(((double)num8 - (double)num11) * (double)v.x() + ((double)num9 + (double)num10) * (double)v.y() + (1.0 - ((double)num4 + (double)num5)) * (double)v.z()));

  return vector;
}

void Boid::calculateUpFromRotation() {
  QVector4D quaternion = m_BoidTransform->rotation().toVector4D();
  
  float num1 = quaternion.x() * 2.0f;
  float num2 = quaternion.y() * 2.0f;
  float num3 = quaternion.z() * 2.0f;
  float num4 = quaternion.x() * num1;
  float num5 = quaternion.y() * num2;
  float num6 = quaternion.z() * num3;
  float num7 = quaternion.x() * num2;
  float num8 = quaternion.x() * num3;
  float num9 = quaternion.y() * num3;
  float num10 = quaternion.w() * num1;
  float num11 = quaternion.w() * num2;
  float num12 = quaternion.w() * num3;

  m_UpVector.setX((float)(num7 - num12));
  m_UpVector.setY((float)(1.0 - (num4 + num6)));
  m_UpVector.setZ((float)(num9 + num10));
}

void Boid::checkPosition(QVector3D target, QVector3D targetAngles) {
  //avoid distance formula if target is too far away to matter
  if (abs(target.x() - m_Position.x() > 1.5f) || abs(target.y() - m_Position.y() > 1.5f) || abs(target.z() - m_Position.z() > 1.5f)) return;
  if (m_DownVector.distanceToPoint(target) < 1.5f) return;

  if (m_Position.distanceToPoint(target) < 1.5f) {
    separation(target);
    cohesion(targetAngles);
    alignment(target);
  }
}

//steer boids away from other boids
void Boid::separation(QVector3D targetPos) {
  if (m_Position.x() < targetPos.x())
    m_BoidTransform->setRotationZ(m_BoidTransform->rotationZ() + 1);
  else
    m_BoidTransform->setRotationZ(m_BoidTransform->rotationZ() - 1);
  if (m_Position.y() < targetPos.y())
    m_BoidTransform->setRotationX(m_BoidTransform->rotationX() + 1);
  else
    m_BoidTransform->setRotationX(m_BoidTransform->rotationX() - 1);
  if (m_Position.z() < targetPos.z())
    m_BoidTransform->setRotationY(m_BoidTransform->rotationY() + 1);
  else
    m_BoidTransform->setRotationY(m_BoidTransform->rotationY() - 1);
}

//make boid try to align forward direction with nearby boids
void Boid::cohesion(QVector3D targetAngles) {
  if (m_BoidTransform->rotationX() < targetAngles.x())
    m_BoidTransform->setRotationX(m_BoidTransform->rotationX() + 1);
  else
    m_BoidTransform->setRotationX(m_BoidTransform->rotationX() - 1);
  
  if (m_BoidTransform->rotationY() < targetAngles.y())
    m_BoidTransform->setRotationY(m_BoidTransform->rotationY() + 1);
  else
    m_BoidTransform->setRotationY(m_BoidTransform->rotationY() - 1);

  if (m_BoidTransform->rotationZ() < targetAngles.z())
    m_BoidTransform->setRotationZ(m_BoidTransform->rotationZ() + 1);
  else
    m_BoidTransform->setRotationZ(m_BoidTransform->rotationZ() - 1);
}

//steer boid toward nearby boid
void Boid::alignment(QVector3D targetPos) {
  if (m_Position.x() < targetPos.x())
    m_BoidTransform->setRotationZ(m_BoidTransform->rotationZ() - 1);
  else
    m_BoidTransform->setRotationZ(m_BoidTransform->rotationZ() + 1);
  if (m_Position.y() < targetPos.y())
    m_BoidTransform->setRotationX(m_BoidTransform->rotationX() - 1);
  else
    m_BoidTransform->setRotationX(m_BoidTransform->rotationX() + 1);
  if (m_Position.z() < targetPos.z())
    m_BoidTransform->setRotationY(m_BoidTransform->rotationY() - 1);
  else
    m_BoidTransform->setRotationY(m_BoidTransform->rotationY() + 1);
}