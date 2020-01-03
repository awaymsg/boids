#include "BoidController.h"
#include <QDebug>

BoidController::BoidController(QNode *parent)
{
  for (int i = 0; i < 150; i++) {
    m_BoidArr[i] = new Boid(parent);
  }

  m_timer = new QTimer(this);
  connect(m_timer, &QTimer::timeout, this, &BoidController::moveBoids);

  m_timer->start(15);
}

void BoidController::moveBoids() {
  //qDebug() << "Running";
  for (int i = 0; i < 150; i++) {
    //qDebug() << i;
    for (int j = 0; j < 150; j++) {
      if (j == i) continue;
      m_BoidArr[i]->checkPosition(m_BoidArr[j]->position(), m_BoidArr[j]->eulerAngles());
    }
  
    m_BoidArr[i]->moveBoid();
  }
  //qDebug() << "Moved";
}