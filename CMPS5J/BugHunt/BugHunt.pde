// BugHunt
// CMPS 5J
// pa7

int n = 20;            // number of bugs
Bug[] B = new Bug[n];  // bug array
int clickCount = 0;
int deadCount = 0;
float killRate;

void setup(){
  size(500,500);
  smooth();
  for(int i=0; i<n; i++){
    B[i] = new Bug(random(20,480),random(20,480),(int)random(1,5));
  }
}

void draw(){
  background(170);
  for(int i=0; i<n; i++){
    B[i].display();
    B[i].crawl();
  }
}

void mousePressed(){
  clickCount++;
  for(int i=0; i<n; i++){
    if( B[i].mouseOn() ){ 
      B[i].squash();
      deadCount++;
    }else if( B[i].scared() ){ 
      B[i].runAway();
    }
  }
  killRate = float(deadCount)/clickCount;
  println("kill rate = "+killRate);
}
