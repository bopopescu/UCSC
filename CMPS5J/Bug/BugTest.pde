// BugTest
// Tester for Bug class
// tests Bug methods: display(), mouseOn(), and scared()
// scho29

Bug B;  // just one Bug object
String s1 = "please don't squash me!";
String s2 = "I'm scared!";
String s3 = "I'm a bug";

void setup(){
  size(500,500);
  smooth();
  B = new Bug(width/2,height/2,3);
}

void draw(){
  background(170);
  
  // draw bug
  B.display();
  
  // draw concentric circles around bug
  noFill();
  ellipse(width/2,height/2,30,30);
  ellipse(width/2,height/2,60,60);
  
  // print bug talk
  textAlign(CENTER);
  fill(255,0,0);
  if( B.mouseOn() ){
    textSize(40);
    text(s1,15,100,475,100);
    println(s1);
  }else if( B.scared() ){
    textSize(35);
    text(s2,15,100,475,100);
    println(s2);
  }else{
    textSize(30);
    text(s3,15,100,475,100);
    println(s3);
  }
}

