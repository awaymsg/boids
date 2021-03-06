#include "BoidController.h"

BoidController::BoidController(QNode *parent)
{
  for (int i = 0; i < BOIDARRSIZE; i++) {
    m_BoidArr[i] = new Boid(parent);
  }

  m_timer = new QTimer(this);
  connect(m_timer, &QTimer::timeout, this, &BoidController::moveBoids);

  m_timer->start(15);
}

void BoidController::moveBoids() {
  for (int i = 0; i < BOIDARRSIZE; i++) {
    for (int j = 0; j < BOIDARRSIZE; j++) {
      if (j == i) continue;
      m_BoidArr[i]->checkPosition(m_BoidArr[j]->position(), m_BoidArr[j]->eulerAngles());
    }
  
    m_BoidArr[i]->moveBoid();
  }
}