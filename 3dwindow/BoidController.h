#pragma once
#include <QtCore>
#include <QTimer>
#include "Boid.h"

class BoidController : public Qt3DCore::QEntity
{
  Q_OBJECT;

private:
  Boid *m_BoidArr[150];
  QTimer *m_timer;

public:
  BoidController(QNode *parent);
  ~BoidController() { delete m_timer; };
  void moveBoids();
};