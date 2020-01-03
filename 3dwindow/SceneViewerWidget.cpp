#include "SceneViewerWidget.h"

#include <Qt3DRender/qcamera.h>
#include <Qt3DRender/qcameralens.h>
#include <qlayout.h>
#include <QtGui/QScreen>

#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DExtras/Qt3DWindow.h>

#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <QDebug>

#include "Gizmos.h"
#include "BoidController.h"

SceneViewerWidget::SceneViewerWidget( QWidget* parent)
  : QWidget(parent)
{
  setFocusPolicy( Qt::StrongFocus );

  Qt3DExtras::Qt3DWindow* view = new Qt3DExtras::Qt3DWindow();
  view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x3333333)));
  m_ViewContainer = createWindowContainer(view);
  QSize screenSize = view->screen()->size();

  QHBoxLayout *hLayout = new QHBoxLayout( this);
  QVBoxLayout *vLayout = new QVBoxLayout();
  vLayout->setAlignment(Qt::AlignTop);
  hLayout->addWidget(m_ViewContainer, 1);
  hLayout->addLayout(vLayout);

  m_RootEntity = new Qt3DCore::QEntity();
  view->setRootEntity(m_RootEntity);

  Qt3DRender::QCamera* cameraEntity = view->camera();
  cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
  cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
  cameraEntity->setUpVector(QVector3D(0, 1, 0));
  cameraEntity->setViewCenter(QVector3D(0, 0, 0));

  m_CameraController = new CameraController( m_RootEntity);
  m_CameraController->setLookSpeed( 75.0);
  m_CameraController->setCamera( cameraEntity);

  //Gizmos::Axes *axes = new Gizmos::Axes( m_RootEntity );
  //Gizmos::Grid *grid = new Gizmos::Grid( m_RootEntity );
  BoidController *boidController = new BoidController( m_RootEntity );
}

SceneViewerWidget::~SceneViewerWidget()
{
  delete m_CameraController;
}

void SceneViewerWidget::keyPressEvent( QKeyEvent* event )
{
  m_CameraController->keyPressed( (Qt::Key)event->key() );
}

void SceneViewerWidget::keyReleaseEvent( QKeyEvent* event)
{
  m_CameraController->keyReleased( (Qt::Key)event->key() );
}

void SceneViewerWidget::focusOutEvent( QFocusEvent* event)
{
  setFocus();
}