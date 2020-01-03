#pragma once

#include <Qt3DExtras\qabstractcameracontroller.h>
#include <Qt3DInput\QMouseHandler>

class CameraController : public Qt3DExtras::QAbstractCameraController
{
  Q_OBJECT

private:
  enum KeyFlags : uint_fast8_t {
    none_pressed  = 0x00,
    w_offset      = 0,
    a_offset      = 1,
    s_offset      = 2,
    d_offset      = 3,
    e_offset      = 4,
    q_offset      = 5,
    shift_offset  = 6,

    w_pressed     = 1 << w_offset,
    a_pressed     = 1 << a_offset,
    s_pressed     = 1 << s_offset,
    d_pressed     = 1 << d_offset,
    e_pressed     = 1 << e_offset,
    q_pressed     = 1 << q_offset,
    shift_pressed = 1 << shift_offset
  };

  uint_fast8_t m_keyState;
  QPoint m_mousePosition;
public:
  CameraController( QNode* node = nullptr);

  void moveCamera(const Qt3DExtras::QAbstractCameraController::InputState &state, float dt) override;
  void keyPressed( Qt::Key key);
  void keyReleased( Qt::Key key);
};