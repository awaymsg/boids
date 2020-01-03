#pragma once
#include <Qt3DRender>
#include <Qt3DExtras>

class Boid : public Qt3DCore::QEntity
{
  Q_OBJECT;

private:
  QVector3D m_Position;
  QVector3D m_MovementVector;
  QVector3D m_ForwardVector;
  QVector3D m_BackwardVector;
  QVector3D m_RotationVector;
  QVector3D m_EulerAngles;

  Qt3DExtras::QConeMesh *m_BoidMesh;
  Qt3DCore::QTransform *m_BoidTransform;
  Qt3DExtras::QPhongMaterial *m_BoidMaterial;
  Qt3DCore::QEntity *m_BoidEntity;
  bool m_Near;
  QColor m_BoidColor;
  QNode *parent;

public:
  Boid(QNode *parent = nullptr);
  QVector3D position() { return m_Position; };
  QVector3D forwardVector() { return m_ForwardVector; };
  QVector3D eulerAngles() { return m_EulerAngles; }
  
  Qt3DExtras::QConeMesh *getMesh() { return m_BoidMesh; };
  Qt3DCore::QTransform *getTransform() { return m_BoidTransform; };
  Qt3DExtras::QPhongMaterial *getPhongMaterial() { return m_BoidMaterial; };
  Qt3DCore::QEntity *getEntity() { return m_BoidEntity; };

  void moveBoid();
  QVector3D calculateVectorFromRotation(QVector3D v);
  void calculateForward();
  void checkPosition(QVector3D target, QVector3D targetAngles);

protected:
  void separation(QVector3D targetPos);
  void cohesion(QVector3D eulerAngles);
  void alignment(QVector3D targetPos);
};