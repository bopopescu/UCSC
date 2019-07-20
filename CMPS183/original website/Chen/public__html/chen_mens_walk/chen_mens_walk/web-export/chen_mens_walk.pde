int walk=0; //Which leg steps
int x=0;    //main body motion
int stepl=0;//left leg step
int stepr=0;//right leg step


void setup(){
  size(500,500);
  frameRate(30);
  noFill();
  strokeWeight(3);//ticker line
}

void draw(){       
  background(255);
  fill(255,0,0);  //erase previous
  ellipse(100,250,100,100);  //piece together 
  ellipse(200,250,100,100);  //a heart shape 
  triangle(53,270,248,270,150,400);//from basic shapes 
  rect(140,250,20,20);
  line(50,170,302,170);         //land left of abyss
  line(302,170,300,300);        //left side of abyss
  line(333,170,450,170);        //right side of abyss
  line(333,170,333,300);        //right of abyss
  stroke(100,10,10);              //stick man is read
  ellipse(100+x,100,20,20);     //head
  fill(193,245,195);
  rect(95+x,110,10,30);         //body
  line(95+x,125,80+x,110);      //left arm
  line(105+x,125,120+x,110);    //right arm
  ellipse(60+x,100,20,20);     //head
  fill(193,245,195);
  rect(55+x,110,10,30);         //body
  line(55+x,125,40+x,110);      //left arm
  line(65+x,125,80+x,110);    //right arm
  if(walk==0){                  //which leg is moving
    stepl=stepl+2;              //left, go faster
  }else{
    stepr=stepr+2;              //right, go faster
  }
  line(100+x,140,90+stepl,170);  //left foot
  line(100+x,140,110+stepr,170);  //right foot
  line(60+x,140,45+stepl,170);  // left foot
  line(60+x,140,65+stepr,170);  //right foot
  if(abs(stepl-stepr)>=15){
    walk=1-walk;
  }
  x=x+1;
}

