import turtle
import time
import random

# 28/12/23

delay = 0.1
points = 0
record = 0

s = turtle.Screen()
s.setup(800,800)
s.title('Snake Game')
s.bgcolor('black')

snake = turtle.Turtle()
snake.speed(1)
snake.shape('square')
snake.penup()
snake.goto(0,0)
snake.direction = 'stop'
snake.color('green')

#food
food = turtle.Turtle()
food.shape('circle')
food.color('red')
food.penup()
food.goto(0,100)
food.speed(0)
           
body = []

text = turtle.Turtle()
text.speed(0)
text.color('white')
text.penup()
text.hideturtle()
text.goto(0,300)
text.write('Scoreboard:0\tRecord:0', align='center', font=('verdana', 24, 'normal'))

def up():
    snake.direction = 'up'
    
def down():
    snake.direction = 'down'
    
def right():
    snake.direction = 'right'
    
def left():
    snake.direction = 'left'

def movement():
    if snake.direction == 'up':
        y = snake.ycor()
        snake.sety(y + 20)
    if snake.direction == 'down':
        y = snake.ycor()
        snake.sety(y - 20)
    if snake.direction == 'right':
        x = snake.xcor()
        snake.setx(x + 20)
    if snake.direction == 'left':
        x = snake.xcor()
        snake.setx(x - 20)

s.listen()
s.onkey(up, 'w')
s.onkey(down, 's')
s.onkey(right, 'd')
s.onkey(left, 'a')

while True:
    s.update()
    
    #when snakes eats, food moves randomly
    if snake.distance(food) < 20:
        x = random.randint(-300, 300)
        y = random.randint(-300, 300)
        food.goto(x, y)
        #snake grows when eating points
        new_body = turtle.Turtle()
        new_body.shape('square')
        new_body.color('green')
        new_body.penup()
        new_body.goto(0,0)
        new_body.speed(0)
        body.append(new_body)
        
        points += 10
        
        if points > record:
            record = points
            text.clear()
            text.write('Scoreboard:{}\tRecord:{}'.format(points, record), align='center', font=('verdana', 24, 'normal'))
        else:
            text.clear()
            text.write('Scoreboard:{}\tRecord:{}'.format(points, record), align='center', font=('verdana', 24, 'normal'))
    
    # the new body follows the head of the snake
    total = len(body)
    for i in range(total -1, 0, -1):
        y = body[i-1].ycor()
        x = body[i-1].xcor()
        body[i].goto(x, y)
    if total > 0:
        x = snake.xcor()
        y = snake.ycor()
        body[0].goto(x, y)
            
    movement()
    
    #dying for hitting itself
    for i in body:
        if i.distance(snake) < 20:
            for i in body:
                i.clear()
                i.hideturtle()
            snake.home()
            snake.direction = 'stop'
            body.clear()
            
            points = 0
            text.clear()
            text.write('Scoreboard:{}\tRecord:{}'.format(points, record), align='center', font=('verdana', 24, 'normal'))
            
    #dying for hitting the limit of map
    if snake.xcor() > 350 or snake.xcor() < -350 or snake.ycor() > 350 or snake.ycor() < -350:
        time.sleep(2)
        for i in body:
            i.clear()
            i.hideturtle()
        snake.home()
        snake.direction = 'stop'
        body.clear()
        points = 0
        text.clear()
        text.write('Scoreboard:{}\tRecord:{}'.format(points, record), align='center', font=('verdana', 24, 'normal'))
        
    time.sleep(delay)
    
turtle.done()
