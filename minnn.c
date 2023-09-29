/**
  3D rendering engine written in Turtle
*/

#include "simplecpp"
#include <math.h>
#include <stdio.h>

using namespace std;

#define WIDTH 300
#define HEIGHT 300
#define F 0.1

typedef struct Triangle Triangle;
struct Triangle {
  int v1[3];
  int v2[3];
  int v3[3];
};

void backward(int n) {
	left(180);
	forward(n);
	left(180);
}

void fbpool(int n) {
	forward(n); backward(n);
}

//Calculates heading wrt 0
double get_heading(int p1, int p2, int x1, int x2) {
  double d1 = x1 - p1;
  double d2 = x2 - p2;

  double head = 90 -atan2(d1, d2)*180/PI;
  return head;
}

//Calculate distance between two points
double get_mag(int p1, int p2, int x1, int x2) {
  double d1 = p1 - x1;
  double d2 = p2 - x2;

  return sqrt(d1*d1 + d2*d2);
}

// Leaves the turtle pointing right
void gopix(int x, int y) {
  resetTurtle();
  penUp();
  if(x < 0) backward(x*-1);
  else forward(x);
  left(90);

  if(y < 0) backward(y*-1);
  else forward(y);
  right(90);
}

void make_2d(Triangle* t) {
  for(int i=0; i< 2; i++) {
    t->v1[i] = t->v1[i] / (pow(t->v1[2], F)+0.000001);
    t->v2[i] = t->v2[i] / (pow(t->v2[2], F)+0.000001);
    t->v3[i] = t->v3[i] / (pow(t->v3[2], F)+0.000001);
  };
}

void draw_triangle(Triangle t) {

  make_2d(&t);

  gopix(t.v1[0], t.v1[1]);
  penDown();
  double heading = get_heading(t.v1[0], t.v1[1], t.v2[0],t.v2[1]);

  left(heading);
  forward(get_mag(t.v1[0], t.v1[1], t.v2[0],t.v2[1]));
  right(heading);


  heading = get_heading(t.v2[0], t.v2[1], t.v3[0],t.v3[1]);
  left(heading);
  forward(get_mag(t.v2[0], t.v2[1], t.v3[0],t.v3[1]));
  right(heading);


  heading = get_heading(t.v3[0], t.v3[1], t.v1[0],t.v1[1]);
  left(heading);
  forward(get_mag(t.v3[0], t.v3[1], t.v1[0],t.v1[1]));
  right(heading);

}

void rotate(int* a, int angle_deg) {
    double angle_rad = angle_deg * PI / 180.0;
    int ref[] = {0, 0, (50 - 10) / 2 + 10};

    double s = sin(angle_rad);
    double c = cos(angle_rad);

    int x = a[0];
    int y = a[1];
    int z = a[2];

    z -= 100;
    a[0] = x * c - z * s;
    a[1] = y - 150;
    a[2] = x * s + z * c;
    a[2] += 100;
}
void rotate(float* a, float angle_deg) {
    double angle_rad = angle_deg * PI / 180.0;
    int ref[] = {0, 0, (50 - 10) / 2 + 10};

    double s = sin(angle_rad);
    double c = cos(angle_rad);

    int x = a[0];
    int y = a[1];
    int z = a[2];

    z -= 100;
    a[0] = x * c - z * s;
    a[1] = y - 150;
    a[2] = x * s + z * c;
    a[2] += 100;
}


int main(int argc, char* argv[]) {
	turtleSim();

  Triangle t0[] = {
   Triangle { .v1 = {-50, -50, 50}, .v2 = {-50, 50, 50}, .v3 = {50, 50, 50} }, //Front face
   Triangle { .v1 = {-50, -50, 50}, .v2 = {50, -50, 50}, .v3 = {50, 50, 50} },

   Triangle { .v1 = {-50, -50, 150}, .v2 = {-50, 50, 150}, .v3 = {50, 50, 150} }, //Back face
   Triangle { .v1 = {-50, -50, 150}, .v2 = {50, -50, 150}, .v3 = {50, 50, 150} },

   Triangle { .v1 = {-50, 50, 50}, .v2 = {50, 50, 150}, .v3 = {-50, 50, 150} },  // Top Face
   Triangle { .v1 = {-50, 50, 50}, .v2 = {50, 50, 150}, .v3 = {50, 50, 50} },

   Triangle { .v1 = {-50, -50, 50}, .v2 = {50, -50, 150}, .v3 = {-50, -50, 150} }, // Bottom Face
   Triangle { .v1 = {-50, -50, 50}, .v2 = {50, -50, 150}, .v3 = {50, -50, 50} },

   Triangle { .v1 = {-50, -50, 50}, .v2 = {-50, -50, 150}, .v3 = {-50, 50, 50} }, // right Face
   Triangle { .v1 = {-50, 50, 50}, .v2 = {-50, -50, 150}, .v3 = {-50, 50, 150} },

  };

  int verts=sizeof(t0)/sizeof(t0[0]);
  for(int i =0; i< verts; i++) {
    int angle = atoi(argv[1]);
    rotate(t0[i].v1, angle);
    rotate(t0[i].v2, angle);
    rotate(t0[i].v3, angle);
    draw_triangle(t0[i]);
  }
  wait(atoi(argv[1]));
}