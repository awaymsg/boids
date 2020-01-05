#pragma once
#include <Qt3DRender>
#include <Qt3DExtras>

class Boid : public Qt3DCore::QEntity
{
  Q_OBJECT;

private:
  enum { RANDSIZE = 10, RANDMODIFIER = 5, BOUNDS = 12 };

  QVector3D m_Position;
  QVector3D m_UpVector;
  QVector3D m_DownVector;
  QVector3D m_RotationVector;
  QVector3D m_EulerAngles;
  float m_SensoryRange;

  Qt3DExtras::QConeMesh *m_BoidMesh;
  Qt3DCore::QTransform *m_BoidTransform;
  Qt3DExtras::QPhongMaterial *m_BoidMaterial;
  Qt3DCore::QEntity *m_BoidEntity;
  QColor m_BoidColor;
  QNode *parent;

public:
  Boid(QNode *parent = nullptr);
  QVector3D position() { return m_Position; };
  QVector3D forwardVector() { return m_UpVector; };
  QVector3D eulerAngles() { return m_EulerAngles; }

  void moveBoid();
  QVector3D calculateVectorFromRotation(const QVector3D &v);
  void calculateUpFromRotation();
  void checkPosition(const QVector3D &target, const QVector3D &targetAngles);

protected:
  void separation(const QVector3D &targetPos);
  void cohesion(const QVector3D &eulerAngles);
  void attraction(const QVector3D &targetPos);
};