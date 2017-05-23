//Bug
//cmps5J
//scho29
//pa7


class Bug {
  // fields
  float xpos;
  float ypos;
  float speed;
  int s;
  //float squash;
  color bugColor;
  // constructor
  Bug(float x, float y, int s) {
    this.xpos = x;
    this.ypos = y;
    this.s = s;
    speed = random(1, 1.5);
    bugColor = color(random(0, 255), random(0, 255), random(0, 255));
  }
  // methods
  void crawl() {
    if (s == 1) {
      xpos = xpos + speed;
      if(xpos > width + 15)
      xpos = -15;
    }
    if (s == 2) {
      xpos = xpos - speed;
      if(xpos < -15)
      xpos = width + 15;
    }
    if (s == 3) {
      ypos = ypos + speed;
      if(ypos > height + 15)
      ypos = -15;
    }
    if (s == 4) {
      ypos = ypos - speed;
      if(ypos < -15)
      ypos = height +15;
    }
  }
  
  //draw a bug
  void display() {
    fill(bugColor);
    if (s == 1 || s == 2) {
      line(xpos-10, ypos-15, xpos-10, ypos+15);
      line(xpos, ypos-15, xpos,ypos+15);
      line(xpos+10, ypos -15, xpos +10, ypos +15);
      ellipse(xpos, ypos, 30, 20);
    
    }
    if (s == 3 || s == 4) {
      line(xpos-15, ypos-10, xpos+15, ypos-10);
      line(xpos -15, ypos, xpos+15,ypos);
      line(xpos -15, ypos +10, xpos +15, ypos +10);
      ellipse(xpos, ypos, 20, 30);

    }
  }
// state to zero
  void squash() {
    s = 0;
  }

  void runAway() {
    speed*=1.5;
  }
  
  //kill the bug
  boolean mouseOn() {
    if (dist(xpos, ypos, mouseX, mouseY)<15) {
      return true;
    } else
      return false;
  }
  
  //scaring the bug when missed
  boolean scared() {
    if (dist(xpos, ypos, mouseX, mouseY)<30 && dist(xpos, ypos, mouseX, mouseY)>15) {
      return true;
    } else 
      return false;
  }
}

