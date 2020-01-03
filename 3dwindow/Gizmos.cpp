#include "Gizmos.h"

#include <Qt3DRender>
#include <Qt3DExtras>

const QColor Gizmos::Grid::kGridColor = QColor( 128, 128, 128);

Gizmos::Grid::Grid( QNode* parent )
  : QEntity( parent)
  , m_GridSize( 1.0f )
  , m_NumGrids( 10 )
{ 
  auto* geometry = ConstructGeometry();

  auto* mesh = new Qt3DRender::QGeometryRenderer( parent );
  mesh->setGeometry( geometry );
  mesh->setPrimitiveType( Qt3DRender::QGeometryRenderer::Lines );

  auto* material = new Qt3DExtras::QPhongMaterial( parent );
  material->setAmbient( kGridColor );

  addComponent( mesh );
  addComponent( material );
}

Qt3DRender::QGeometry* Gizmos::Grid::ConstructGeometry()
{
  auto* geometry = new Qt3DRender::QGeometry(this);

  QByteArray geometryBuffer;
  static constexpr unsigned pts_per_line = 2;
  static constexpr unsigned num_axes = 2;

  unsigned num_pts_total = (m_NumGrids + 1) * pts_per_line * num_axes;

  geometryBuffer.resize(num_pts_total * 3 * sizeof(float));
  float *positions = reinterpret_cast<float*>(geometryBuffer.data());

  float half_size = (float)m_NumGrids * m_GridSize / 2.0f;
  for (unsigned xline = 0; xline < m_NumGrids + 1; ++xline)
  {
    // start
    *positions++ = -half_size;
    *positions++ = 0.0f;
    *positions++ = -half_size + (xline * m_GridSize);

    // end
    *positions++ = half_size;
    *positions++ = 0.0f;
    *positions++ = -half_size + (xline * m_GridSize);
  }

  for (unsigned zline = 0; zline < m_NumGrids + 1; ++zline)
  {
    // start
    *positions++ = -half_size + (zline * m_GridSize);
    *positions++ = 0.0f;
    *positions++ = -half_size;

    // end
    *positions++ = -half_size + (zline * m_GridSize);
    *positions++ = 0.0f;
    *positions++ = half_size;
  }

  auto *buf = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, geometry);
  buf->setData(geometryBuffer);

  auto *positionAttribute = new Qt3DRender::QAttribute(geometry);
  positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
  positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
  positionAttribute->setVertexSize(3);
  positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
  positionAttribute->setBuffer(buf);
  positionAttribute->setByteStride(3 * sizeof(float));
  positionAttribute->setCount(num_pts_total);
  geometry->addAttribute(positionAttribute); // We add the vertices in the geometry

  // connectivity between vertices
  QByteArray indexBytes;
  indexBytes.resize(num_pts_total * sizeof(unsigned int)); // start to end
  unsigned int *indices = reinterpret_cast<unsigned int*>(indexBytes.data());
  for (unsigned iindex = 0; iindex < num_pts_total; ++iindex)
  {
    *indices++ = iindex;
  }

  auto *indexBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, geometry);
  indexBuffer->setData(indexBytes);

  auto *indexAttribute = new Qt3DRender::QAttribute(geometry);
  indexAttribute->setVertexBaseType(Qt3DRender::QAttribute::UnsignedInt);
  indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
  indexAttribute->setBuffer(indexBuffer);
  indexAttribute->setCount(num_pts_total);
  geometry->addAttribute(indexAttribute); // We add the indices linking the points in the geometry

  return geometry;
}

Gizmos::Axes::Axes( QNode* parent )
  : QEntity( parent )
{
  Line* x = new Line({ 0, 0, 0 }, { 1, 0, 0 }, { 255, 0, 0 }, this);
  Line* y = new Line({ 0, 0, 0 }, { 0, 1, 0 }, { 0, 255, 0 }, this);
  Line* z = new Line({ 0, 0, 0 }, { 0, 0, 1 }, { 0, 0, 255 }, this);
}

Gizmos::Line::Line( QVector3D start, QVector3D end, QColor color, QNode* parent)
  : QEntity( parent )
{
  auto* geometry = new Qt3DRender::QGeometry();

  QByteArray geometryBuffer;
  geometryBuffer.resize( 3 * 2 * sizeof( float ) );

  float *positions = reinterpret_cast<float*>(geometryBuffer.data());
  *positions++ = start.x();
  *positions++ = start.y();
  *positions++ = start.z();

  *positions++ = end.x();
  *positions++ = end.y();
  *positions++ = end.z();

  auto *buf = new Qt3DRender::QBuffer( Qt3DRender::QBuffer::VertexBuffer, geometry );
  buf->setData(geometryBuffer);

  auto *positionAttribute = new Qt3DRender::QAttribute( geometry );
  positionAttribute->setName( Qt3DRender::QAttribute::defaultPositionAttributeName( ) );
  positionAttribute->setVertexBaseType( Qt3DRender::QAttribute::Float );
  positionAttribute->setVertexSize( 3 );
  positionAttribute->setAttributeType( Qt3DRender::QAttribute::VertexAttribute );
  positionAttribute->setBuffer( buf );
  positionAttribute->setByteStride( 3 * sizeof( float ) );
  positionAttribute->setCount( 2 );
  geometry->addAttribute( positionAttribute ); // We add the vertices in the geometry

  // connectivity between vertices
  QByteArray indexBytes;
  indexBytes.resize( 2 * sizeof( unsigned int ) ); // start to end
  unsigned int *indices = reinterpret_cast<unsigned int*>( indexBytes.data() );
  *indices++ = 1;
  *indices++ = 2;

  auto *indexBuffer = new Qt3DRender::QBuffer( Qt3DRender::QBuffer::IndexBuffer, geometry );
  indexBuffer->setData( indexBytes );

  auto *indexAttribute = new Qt3DRender::QAttribute( geometry );
  indexAttribute->setVertexBaseType ( Qt3DRender::QAttribute::UnsignedInt );
  indexAttribute->setAttributeType  ( Qt3DRender::QAttribute::IndexAttribute );
  indexAttribute->setBuffer         ( indexBuffer );
  indexAttribute->setCount          ( 2 );
  geometry->addAttribute            ( indexAttribute );

  auto* mesh = new Qt3DRender::QGeometryRenderer( parent );
  mesh->setGeometry( geometry );
  mesh->setPrimitiveType( Qt3DRender::QGeometryRenderer::Lines );

  auto* material = new Qt3DExtras::QPhongMaterial( parent );
  material->setAmbient( color );

  addComponent( mesh );
  addComponent( material );
}