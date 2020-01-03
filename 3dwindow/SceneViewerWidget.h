#pragma once

#include <QObject>
#include <QWidget>
#include <Qt3DCore>

#include "CameraController.h"

class SceneViewerWidget : public QWidget
{
  Q_OBJECT

  QWidget*            m_ViewContainer;
  Qt3DCore::QEntity*  m_RootEntity;
  CameraController*   m_CameraController;

public:
  explicit SceneViewerWidget(QWidget *parent = nullptr);
  ~SceneViewerWidget();

protected:
  void keyPressEvent(   QKeyEvent *event   ) override;
  void keyReleaseEvent( QKeyEvent *event   ) override;
  void focusOutEvent(   QFocusEvent* event ) override;
};