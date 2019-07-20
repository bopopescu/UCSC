//this is created by Seongwoo Choi and Ziping Tang. Assignment 07.  

int i;
float x;

void setup(){
  size(500,500);
  background(255,255,255);
  frameRate(6);
  fill(0);
} 
  void draw(){
  if(random(0,1)<0.5){
    fill(30,144,225);
    stroke(180,180,12,100);
  }else{
    fill(248,248,255);
    stroke(124,113,194,22);
  }
  for(i=0;i<10;i++){
    x=random(2,100);
    ellipse(random(1,500), random(1,500),x,x);
  }
}


