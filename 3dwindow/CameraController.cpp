#include "CameraController.h"

#include <QApplication>
#include <QCursor>
#include <QKeyboardDevice>
#include <Qt3DRender/QCamera>
#include "Foundation/Util.h"

CameraController::CameraController( QNode* parent)
  : QAbstractCameraController( parent ),
    m_keyState( none_pressed)
{
}

void CameraController::moveCamera( const Qt3DExtras::QAbstractCameraController::InputState &state, float dt)
{
  UNREFERENCED_PARAMETER( state )

  auto cam = camera( );
  if ( cam == nullptr ) {
    return;
  }

  if (m_keyState & shift_pressed)
  {
    QVector3D movement_vector = {
      (float)( ( ( m_keyState & d_pressed ) >> d_offset ) - ( ( m_keyState & a_pressed ) >> a_offset ) ),
      (float)( ( ( m_keyState & e_pressed ) >> e_offset ) - ( ( m_keyState & q_pressed ) >> q_offset ) ),
      (float)( ( ( m_keyState & w_pressed ) >> w_offset ) - ( ( m_keyState & s_pressed ) >> s_offset ) )
    };

    movement_vector.normalize( );
    movement_vector *= linearSpeed( ) * dt;
    
    cam->translate( movement_vector );

    QPoint pos = QCursor::pos( );

    QPoint mouse_diff = pos - m_mousePosition;

    float theLookSpeed = lookSpeed( );
    const QVector3D upVector( 0.0f, 1.0f, 0.0f );
    cam->pan ( ( (float)mouse_diff.x() / 10.0f ) * theLookSpeed * dt, upVector );
    cam->tilt( ( (float)mouse_diff.y() / 10.0f ) * theLookSpeed * dt );

    QCursor::setPos( m_mousePosition );
  }
}

void CameraController::keyPressed( Qt::Key key )
{
  switch( key )
  {
  case Qt::Key_W:
    m_keyState |= w_pressed;
    break;
  case Qt::Key_A:
    m_keyState |= a_pressed;
    break;
  case Qt::Key_S:
    m_keyState |= s_pressed;
    break;
  case Qt::Key_D:
    m_keyState |= d_pressed;
    break;
  case Qt::Key_E:
    m_keyState |= e_pressed;
    break;
  case Qt::Key_Q:
    m_keyState |= q_pressed;
    break;
  case Qt::Key_Shift:

    m_keyState |= shift_pressed;
    m_mousePosition = QCursor::pos( );
    QApplication::setOverrideCursor( Qt::BlankCursor );

    break;
  }
}

void CameraController::keyReleased( Qt::Key key )
{
  switch (key)
  {
  case Qt::Key_W:
    m_keyState &= ~w_pressed;
    break;
  case Qt::Key_A:
    m_keyState &= ~a_pressed;
    break;
  case Qt::Key_S:
    m_keyState &= ~s_pressed;
    break;
  case Qt::Key_D:
    m_keyState &= ~d_pressed;
    break;
  case Qt::Key_E:
    m_keyState &= ~e_pressed;
    break;
  case Qt::Key_Q:
    m_keyState &= ~q_pressed;
    break;
  case Qt::Key_Shift:

    m_keyState &= ~shift_pressed;
    QApplication::restoreOverrideCursor();

    break;
  }
}