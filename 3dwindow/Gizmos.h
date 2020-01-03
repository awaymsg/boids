#pragma once

#include <qvector3d.h>
#include <Qt3DCore\qentity.h>

#include <Qt3DRender/qgeometryrenderer.h>

namespace Gizmos
{
  class Grid : public Qt3DCore::QEntity
  {
    Q_OBJECT
  private:
    static const QColor kGridColor;

    float               m_GridSize;
    unsigned            m_NumGrids;

    Qt3DRender::QGeometry* ConstructGeometry();

  public:
    Grid( QNode* parent = nullptr);

    float     gridSize    ( ) const                    { return m_GridSize; }
    unsigned  numGrids    ( ) const                    { return m_NumGrids; }

    void      setGridSize ( float value )              { m_GridSize = value; }
    void      setNumGrids ( unsigned value )           { m_NumGrids = value; }
  };




  class Axes : public Qt3DCore::QEntity
  {
    Q_OBJECT

  public:
    Axes( QNode* parent = nullptr );
  };




  class Line : public Qt3DCore::QEntity
  {
    Q_OBJECT
  public:
    Line( QVector3D start, QVector3D end, QColor color, QNode* parent = nullptr );
  };
}