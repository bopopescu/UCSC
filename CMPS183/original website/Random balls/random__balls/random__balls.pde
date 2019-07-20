//This is created by Seongwoo Choi and Ziping Tang. Assignment 07

int i = 0;

void setup()
  {
  size (500,500);
  smooth();
  ellipseMode(CENTER);
  }

void draw()
  {
  fill(2,0,1,10);
  rect(0,0,width,height);
  fill(random(0,255), random(0,255), random(0,255));
  ellipse(random(0,width), random(0,height), 10, 10);
  }
  
  void mousePressed() {
  if (mousePressed) {
    background(random(255),random(255),random(255));
  } 
  else {
  fill(2,0,1,10);
  rect(0,0,width,height);
  fill(random(0,255), random(0,255), random(0,255));
  ellipse(random(0,width), random(0,height), 10, 10);
  }
  }
  

