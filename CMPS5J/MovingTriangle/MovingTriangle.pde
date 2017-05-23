//cmps 5j
//scho29
//pa8

int x[];
int y[];

int speed = 3;  // speed of triangle
int state = 0;  // "state" of triangle (0, 1, 2, or 3)

void setup() {
  fill(0, 255, 0);
  size(400, 400);
  x = new int[3];
  y = new int[3];
  x[0] = 0;
  y[0] = 0;
  x[1] = 0;
  y[1] = height;
  x[2] = width;
  y[2] = height;
}

void draw() {
  background(0, 255, 0);

  // Display the triangle
  stroke(0);
  fill(255, 0, 255);
  triangle(x[0], y[0], x[1], y[1], x[2], y[2]);

  // change position, change state if necessary
  if (state == 0) {        // moving left to right
    x[0] += speed;
    if (x[0] >= width) {    // if right side hit, change state
      x[0] = width;
      state = 1;
    }
  } else if (state == 1) { // moving top to bottom
    y[1] -= speed;
    if (y[1] <= 0) {   // if bottom hit, change state
      y[1] = 0;
      state = 2;
    }
  } else if (state == 2) { // moving right to left
    x[2] -= speed;
    if (x[2] <= 0) {           // if left side hit, change state
      x[2] = 0;
      state = 3;
    }
  } else if (state == 3) { // moving bottom to top
    y[0] += speed;
    if (y[0] >= height) {           // if top hit, change state
      y[0] = height;
      state = 4;
    }
  } else if (state == 4) {
    x[1] += speed;
    if (x[1] >= width) {
      x[1] = width;
      state = 5;
    }
  } else if (state == 5) {
    y[2] -= speed;
    if (y[2] <= 0) {
      y[2] = 0;
      state = 6;
    }
  } else if (state == 6) {
    x[0] -= speed;
    if (x[0] <= 0) {
      x[0] = 0;
      state = 7;
    }
  } else if (state == 7) {
    y[1] += speed;
    if (y[1] >= height) {
      y[1] = height;
      state = 8;
    }
  } else if (state == 8) {
    x[2] += speed;
    if (x[2] >= width) {
      x[2] = width;
      state = 9;
    }
  } else if (state == 9) {
    y[0] -= speed;
    if (y[0] <= 0) {
      y[0] = 0;
      state = 10;
    }
  } else if (state == 10) {
    x[1] -= speed;
    if (x[1] <= 0) {
      x[1] = 0;
      state = 11;
    }
  } else if (state == 11) {
    y[2] += speed;
    if (y[2] >= height) {
      y[2] = height;
      state = 0;
    }
  }
}

//when mouse is pressed, the moving triangle stops moving
void mousePressed () {
  if (speed == 3) {
    speed = 0;
  } else speed = 3;
}
