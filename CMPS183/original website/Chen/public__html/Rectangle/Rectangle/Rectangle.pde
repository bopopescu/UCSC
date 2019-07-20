int i;
int a=0;

void setup(){
  size(600, 600);
  background(226,245,120
  );
  frameRate(2);
  strokeWeight(4);
  smooth();
}

void draw(){
  if(random(0,1)<0.5){
    fill(193,245,242,189);
    stroke(25,25,25,160);
  }else{
    fill(230,30,145,188);
    stroke(165,237,187,160);
  }
  
  for (i=0;i<10;i++){
    rect(random(0,499),random(0,499),random(0,499),random(0,499));
  }
}

void mousePressed() {
    if (a>0)
    a=0;
    else
    a=255;//if press mouse, changing color
  }
