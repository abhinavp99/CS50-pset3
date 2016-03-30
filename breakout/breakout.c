//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400
#define P_HEIGHT 10
#define P_WIDTH 70


// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel score = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // creates invisible rect to detect if ball has gone beyond window
    
    
    double x = drand48();
    if (x < 0.5)
    {
        x = x * 2;
    }
    else
    {
        x = x * 4;
    } 
    double y = drand48();
    if (y < 0.5)
    {
        y = y * 3;
    }
    else
    {
        y = y * 6;
    }
    double velocity_x = x;
    double velocity_y = y;
    
    
    // keep playing until game over
    
    while (lives > 0 && bricks > 0)
    {
        move(ball, velocity_x, velocity_y);
        pause(7.5);
            
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocity_x = -velocity_x;
        }
        else if (getX(ball) < 0)
        {
            velocity_x = -velocity_x;    
        }
        else if (getY(ball) <= 0 )
        {
            velocity_y = -velocity_y;
        }
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives = lives - 1;
            int velocity_x_end = velocity_x * 0;
            int velocity_y_end = velocity_y * 0;
                
            while (getY(ball) + getHeight(ball) >= getHeight(window))
            {
                move(ball, velocity_x_end, velocity_y_end);
                GEvent mouse_clicked = getNextEvent(MOUSE_EVENT);
                if (mouse_clicked != NULL)
                {
                    if (getEventType(mouse_clicked) == MOUSE_CLICKED)
                    {
                       setLocation(ball,((WIDTH/2)-(30/2)),((HEIGHT/2)+(30/2)));
                       move(ball, velocity_x, velocity_y);
                    } 
                }
            }            
        }
        GObject collide = detectCollision(window, ball);
        if(collide == paddle)
        {               
            if (velocity_y > 0)
            {
                velocity_y = -velocity_y;
            }
        }
        else if (strcmp(getType(collide),"GRect") == 0 && collide != paddle)
        {
            if (velocity_y < 0)
            {
                velocity_y = -velocity_y;
            }
            removeGWindow(window, collide);
            points = points + 1;              
            updateScoreboard(window, score, points);
        }
                        
        GEvent move_paddle = getNextEvent(MOUSE_EVENT);
        if (move_paddle != NULL)
        {
            if (getEventType(move_paddle) == MOUSE_MOVED)
            {
                double x_paddle = getX(move_paddle);
                setLocation(paddle, x_paddle - (P_WIDTH/2), 550);
            } 
        }
          
     if (points == 50)
     {
        break;
     }
     }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int b_y = 40;
    for (int i = 0; i < 5; i++)
    {
        int b_x = 2;
        for (int j = 0; j < 10; j++)
        {            
            GRect bricks = newGRect(b_x, b_y, 35, 10);
            add(window, bricks);
                       
            if (i == 0)
            {
                setFillColor(bricks, "BLUE");
            } 
            else if (i == 1)
            {
                setFillColor(bricks, "BLACK");
            } 
            else if (i == 2)
            {
                setFillColor(bricks, "RED");
            } 
            else if (i == 3)
            {
                setFillColor(bricks, "YELLOW");
            } 
            else if (i == 4)
            {
                setFillColor(bricks, "GREEN");
            }         
                       
            setFilled(bricks, true);            
             
            b_x = b_x + 40;            
            
                       
        }
        b_y = b_y + 20;
        
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(((WIDTH/2)-(30/2)),((HEIGHT/2)+(30/2)), 30, 30);
    add(window, ball);
    setFillColor(ball, "BLACK");
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(((WIDTH/2)-35), 550, P_WIDTH, P_HEIGHT);
    setColor(paddle, "BLACK");
    setFillColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel score = newGLabel("0");
    setFont(score, "SansSerif-36");
    add(window, score);
    double x_score = (getWidth(window) - getWidth(score)) / 2;
    double y_score = (getHeight(window) - getHeight(score)) / 2;
    setLocation(score, x_score, y_score);
    return score;
}


/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
