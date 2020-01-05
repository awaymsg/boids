#pragma once
#include <QtCore>
#include <QTimer>
#include "Boid.h"

class BoidController : public Qt3DCore::QEntity
{
  Q_OBJECT;

private:
  enum { BOIDARRSIZE = 150 };
  Boid *m_BoidArr[BOIDARRSIZE];
  QTimer *m_timer;

public:
  BoidController(QNode *parent);
  ~BoidController() { delete m_timer; };
  void moveBoids();
};