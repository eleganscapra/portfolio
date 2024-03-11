import turtle
import random

# Date: 28/12/23

s = turtle.Screen()
s.title('Turtle race')

#turtle1

T1 = turtle.Turtle()
T2 = turtle.Turtle()

T1.shape('turtle')
T1.hideturtle()
T1.color('green', 'green')
T1.shapesize(2,2,2)
T1.pensize(2)
T1.penup()
T1.goto(300,100)
T1.pendown()
T1.circle(50)
T1.penup()
T1.goto(-300,150)
T1.pendown()
T1.showturtle()

#turtle2

T2.shape('turtle')
T2.hideturtle()
T2.color('blue', 'blue')
T2.shapesize(2,2,2)
T2.pensize(2)
T2.penup()
T2.goto(300,-100)
T2.pendown()
T2.circle(50)
T2.penup()
T2.goto(-300,-50)
T2.pendown()
T2.showturtle()

dice = [1,2,3,4,5,6]

for i in range(20):
    if T1.pos() >= (250,150):
        print('Green turtle has won')
        break
    elif T2.pos() >= (250,-150):
        print('Blue turtle has won')
        break
    else:
        first_turn = input('Press enter to start your turn. ')
        first_turn = random.choice(dice)
        print('Your move: ', first_turn,'steps')
        T1.pendown()
        T1.forward(20*first_turn)
    
        sec_turn = input('Press enter to start your turn. ')
        sec_turn = random.choice(dice)
        print('Your number is: ', sec_turn,'steps')
        T2.pendown()
        T2.forward(20*sec_turn)
    
turtle.done()
