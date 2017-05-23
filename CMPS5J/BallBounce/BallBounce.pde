//----------------------------------------------------------------- 
// BallBounce
// scho29
// cmps 5J
// programming assignment 6 
//-----------------------------------------------------------------
// ball variables


float X, Y, Xspeed, Yspeed;
float r, x, y, speed;
// environment variables
float gravity, stopSpeed, dissipation;
void setup() {
  size(500, 500);
  smooth();
  ellipseMode(RADIUS);

  // initialize ball variables
  r = 50;
  X = width/2;
  Y = r;
  speed = 0;

  // initialize environment variables
  gravity = 0.6; 
  stopSpeed = 0.2;
  dissipation = .08;
}

//
void draw() {
  background(0, 255, 255);
  displayBall();
  if ( mousePressed && mouseOnBall() ) {
    holdBall();
  } else {
    moveBall();
    updateSpeed();
  }
}
void displayBall() {
  fill(255, 0, 0);
  noStroke();
  ellipse(X, Y, r, r);
}
void holdBall() {
  X = constrain(mouseX, r, width - r);
  Y = constrain(mouseY, r, height - r);
  Xspeed = mouseX-pmouseX;
  Yspeed = mouseY-pmouseY;
}
void moveBall() { 
  X += Xspeed;
  Y += Yspeed;
}

//Update Speed. It checks the boundaries of the program. Updates the speed accordingly.
void updateSpeed() {
  if ( abs(Yspeed)<stopSpeed && abs(height - Y) < r) {
    Yspeed = 0.0;
  } else {
    if ( Y >= height-r && abs(Yspeed) == Yspeed || Y <= r && abs(Yspeed) != Yspeed) {
      Yspeed *= -(1-dissipation);
    }
    if ( X >= width-r && abs(Xspeed) == Xspeed || X <= r && abs(Xspeed) != Xspeed) {
      Xspeed *= -(1-dissipation);
    }
    Yspeed += gravity;
  }
}

//mouse on ball, returns true.
boolean mouseOnBall() {
  if (dist (X, Y, constrain(mouseX, 50, width - 50), constrain(mouseY, 50, height - 50)) <= 50)
    return true;
  return false;
}

