#include "graphics.h"
#include "vector3.h"
#include <utility>

// We are using freeglut as our OpenGL Utility Toolkit: http://freeglut.sourceforge.net/
#include "freeglut.h"


// TODO: These are default window size constants, but we should have it configurable
const int Graphics::s_window_width  = 1024;
const int Graphics::s_window_height = 768;


Color::Color()
   : m_red(0.0f),
     m_green(0.0f),
     m_blue(0.0f)
{
}

Color::Color(float red, float green, float blue)
   : m_red(red),
     m_green(green),
     m_blue(blue)
{
}

Color::Color(const Color& color)
{
   *this = color;
}

Color& Color::operator = (const Color& color)
{
   m_red   = color.m_red;
   m_green = color.m_green;
   m_blue = color.m_blue;

   return *this;
}

Color::Color(Color&& color)
{
   *this = std::move(color);
}

Color& Color::operator = (Color&& color)
{
   m_red   = color.m_red;
   m_green = color.m_green;
   m_blue = color.m_blue;

   return *this;
}

Color::~Color()
{
}

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

Graphics& Graphics::GetInstance()
{
   static Graphics s_instance;
   return s_instance;
}

void Graphics::drawVector3(const Vector3& start, const Vector3& end, const Color& color)
{
   glBegin(GL_LINES);

   glColor3f(color.m_red, color.m_green, color.m_blue);
   glVertex3f(start.m_x, start.m_y, start.m_z);
   glVertex3f(end.m_x, end.m_y, end.m_z);
   
   glEnd();
}

void Graphics::drawAxis(float length, const Color& color)
{
   Vector3 origin(0.0f, 0.0f, 0.0f);
   drawVector3(origin, Vector3(length, 0.0f, 0.0f), color);
   drawVector3(origin, Vector3(0.0f, length, 0.0f), color);
   drawVector3(origin, Vector3(0.0f, 0.0f, length), color);
}

void Graphics::renderScene()
{
   glClear(GL_COLOR_BUFFER_BIT);

   // Camera setup
   // TODO: The following parameters should be configurable
   glLoadIdentity();
   gluPerspective(1.0f, 1.0f, 1.0f, 10000.0f);
   gluLookAt(-3000.0f, -3000.0f, -3000.0f, 0, 0, 0, 0.0f, 1.0f, 0.0f);

   drawAxis(50.0f, Color(0.0f, 1.0f, 0.0f));

   glFlush();
}

void Graphics::init(int argc, char* argv[], const char* name)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
   glutInitWindowSize(s_window_width, s_window_height);
   glutCreateWindow(name);
   glutDisplayFunc(renderScene);
   glutMainLoop();
}