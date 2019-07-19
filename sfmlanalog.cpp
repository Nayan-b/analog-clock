#include <SFML/Graphics.hpp>
#include<math.h>
#include<iostream>
#include <sstream>
#include<string>
using namespace sf;
using namespace std;
class Number{
private:
    float x_p,y_p,xy_a,pi=3.1415926/180;
public:
     void setangle(int &a){
       xy_a=pi*(a);
       a+=30;    }
    void setpos(int xpp, int ypp, int radius){
        x_p=xpp-1+radius*cos(xy_a);
        y_p=ypp-5+radius*sin(xy_a);}
    void display(char number[][15], RenderWindow &window, int i,Font font)
    {   Text text(number[i],font,30);
        text.setPosition(x_p,y_p);
        text.setColor(Color::Red);
        window.draw(text);}
};
    void fontdisplay(int x,int y,RenderWindow &window,Font fontx)
    {
        Text mytext(":",fontx,50);
        mytext.setPosition(x,y);
       mytext.setColor(Color::White);
       window.draw(mytext);
    }

void clockfun(int a,int x, int y,int r,char number[][15],RenderWindow &window,Font font)
{
    for (int i=0;i<12;i++){
            Number num;
            num.setangle(a);
            num.setpos(x,y,r+5);
              num.display(number,window,i,font);
            }
}
void returnline(int x, int y,int r,int linesizex,float linesizey,RectangleShape &line)
    {
    line.setSize(Vector2f(linesizex,linesizey*r));
    line.setPosition(x+6,y+11);
  }
void displaytime(int arr,int pos,Font fontt,RenderWindow &window)
{
    ostringstream stringtime;
    stringtime <<arr;
    Text textime(stringtime.str(),fontt,50);
    Text timet(stringtime.str(),fontt,50);
    textime.setPosition(pos,400);
    window.draw(textime);
}
 int main(void)
{
    int r=200,x=500,y=300,a=0,count1=0,cc=0,arrayint[20],hr_t=0,min_t=0,sec_t=0,counting=0,aaa=0,xx=0,num=0,timet;
    char arrayy[20][25];
    RenderWindow window(sf::VideoMode(1100, 720), "SFML works!");
    Time t2;

    CircleShape shape(r+3);
    shape.setPosition(x-r+3,y-r+13);
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineThickness(20);

    sf::CircleShape shape1(4);
    shape1.setPosition(x+2,y+5);
    shape1.setFillColor(sf::Color::White);

        RectangleShape linehour,lineminute,linesecond;
        returnline(x,y,r,4,0.4,linehour);
        returnline(x,y,r,3,0.6,lineminute);
        returnline(x,y,r,2,0.8,linesecond);
        linehour.setFillColor(Color::Blue);
        lineminute.setFillColor(Color::Red);
        linesecond.setFillColor(Color::Yellow);
        Font font1;
        font1.loadFromFile("fonts/BELL.ttf");
        Text mytext;
                Text text1(" PRESS  S  TO START",font1,80);
                Text text2("WELCOME TO MY ANALOG CLOCK WINDOW",font1,50);
                Text text3("ENTER HOUR, MINUTE AND SECOND",font1,30);
                Text texthms(" h h : m m : s s",font1,40);
                text1.setPosition(80,500);
                text1.setColor(Color::Red);
                text2.setPosition(10,100);
                text2.setColor(Color::Red);
                text3.setPosition(40,300);
                text3.setColor(Color::Red);
                texthms.setPosition(70,350);

    char number[13][15]={"3","4","5","6","7","8","9","10","11","12","1","2"};
    Clock clock;

    while (window.isOpen())
    {   window.clear();
        if(count1==0){
                fontdisplay(140,400,window,font1);
                fontdisplay(240,400,window,font1);
                window.draw(text3);
                window.draw(text2);
                window.draw(texthms);
                t2=clock.restart();
                if(counting==1){window.draw(text1);}
                }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
         { count1=1; xx=2000;}

        sf::Event event;
        while (window.pollEvent(event))
        {
        if (event.type == sf::Event::TextEntered)
          {    if (event.text.unicode >= 48 && event.text.unicode <= 57){
                arrayy[cc][50]=static_cast<char>(event.text.unicode);
                arrayint[cc]=static_cast<int>(event.text.unicode)-48;
                 cc+=1;}}
           else if (event.type == sf::Event::Closed)
                window.close();
        }
        if(cc>0&&cc<7){
            if(cc>0){displaytime(arrayint[0],60+xx,font1,window);}
            if(cc>1){displaytime(arrayint[1],100+xx,font1,window);}
            if(cc>2){displaytime(arrayint[2],160+xx,font1,window);}
            if(cc>3){displaytime(arrayint[3],200+xx,font1,window);}
            if(cc>4){displaytime(arrayint[4],260+xx,font1,window);}
            if(cc>5){displaytime(arrayint[5],300+xx,font1,window);}
            }
        hr_t=arrayint[0]*10+arrayint[1];
        min_t=arrayint[2]*10+arrayint[3];
        sec_t=arrayint[4]*10+arrayint[5];
        if(sec_t>=0 && sec_t<=60)
            {counting=1;}
        if (counting == 1 && aaa == 0){linesecond.rotate(180+sec_t*6);
                                lineminute.rotate(180+sec_t*0.1+min_t*6);
                                linehour.rotate(180+min_t*0.5+hr_t*30); aaa=1;}
         if(count1==1){
              window.draw(shape);
              window.draw(shape1);
              t2=clock.getElapsedTime();
              timet=t2.asSeconds();
             if(timet==num){
               {linesecond.rotate(6);
                lineminute.rotate(0.1);
                linehour.rotate(0.008333);
                num++;   } }
            else { window.draw(linehour);
                       window.draw(lineminute);
                       window.draw(linesecond); }
            clockfun(a,x,y,r+6,number,window,font1);
         }
        window.display();
    }
return 0;
}
