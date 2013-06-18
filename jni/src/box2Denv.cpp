#include "box2Denv.h"
#include "box2d.hpp"
#include "game-gl.h"
b2World* m_world;
static b2Vec2 gravity;
b2PolygonShape convertToPolygon(Charectar c){
	LOGD("Creating Shape");
	b2PolygonShape polygon;
	int i;
	int i2 = 0;
	int halfLen = c.box2DVertexLen/2;
	b2Vec2 vertices[halfLen];
	for(i=0; i < (halfLen); i++){
		float x = c.box2DVertex[i2++];
		float y = c.box2DVertex[i2++];
		LOGD("Creating Vertex %f,%f", x, y);
		vertices[i].Set(x, y);
	}
	polygon.Set(vertices, halfLen);
	return polygon;
}
int init()
{
  gravity.Set(0.0f, -10.0f);
  b2Vec2 gravity(0.0f, -10.0f);
  m_world = new b2World(gravity);
  Charectar c;
  c.box2DVertexLen = 8;
  float values[8] = {-1.0f,1.0f,1.0f,1.0f,1.0f,-1.0f,-1.0f,-1.0f};
  c.box2DVertex = &values[0];
  convertToPolygon(c);
}
