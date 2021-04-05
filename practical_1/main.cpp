#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;



const Keyboard::Key controls[6] = {
    Keyboard::A,    // Player1 UP
    Keyboard::Z,    // Player1 Down
    Keyboard::Up,   // Player2 UP
    Keyboard::Down,  // Player2 Down
    Keyboard::P,  //play 2 Player
    Keyboard::C,  //Play Computer
};

Font font;
Text text1;
Text text2;
const Color black;
const Vector2f centerLineSize(5.f, 600.f);
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const float innerRingRadius = 100.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
Vector2f ballVelocity;
bool server = false;
bool AI = false;
int playerOneScore = 0;
int playerTwoScore = 0;
string scores[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };



CircleShape ball;
CircleShape innerRing;
RectangleShape paddles[2];
RectangleShape centerLine;

void Load() {
    // set size and origin of peddles
    for (auto& p : paddles) {
        p.setSize(paddleSize - Vector2f(3, 3));
        p.setOrigin(paddleSize / 2.f);
    }

    font.loadFromFile("res/fonts/Goldman-Regular");

    text1.setFont(font);
    text1.setCharacterSize(24);
    text1.setString(scores[playerTwoScore]);
    text1.setPosition((gameWidth * 0.5) - (13 + text1.getLocalBounds().getSize().x), 10);

    text2.setFont(font);
    text2.setCharacterSize(24);
    text2.setString(scores[playerOneScore]);
    text2.setPosition((gameWidth * 0.5) + 10, 10);


    centerLine.setSize(centerLineSize - Vector2f(3, 3));
    centerLine.setOrigin(centerLineSize / 2.f);

    // set size and origin of balls
    ball.setRadius(ballRadius);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);

    innerRing.setRadius(innerRingRadius);
    innerRing.setOrigin(innerRingRadius / 2, innerRingRadius / 2);
    innerRing.setOutlineThickness(3.f);
    innerRing.setFillColor(black);

    // reset paddle position
    paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
    paddles[1].setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);

    //reset ball position
    ball.setPosition((gameWidth / 2) - (ball.getRadius() / 2), (gameHeight / 2) - (ball.getRadius() / 2));

    centerLine.setPosition((gameWidth / 2) + 2.5,(gameHeight / 2) + 2);

    innerRing.setPosition((gameWidth / 2) - (innerRing.getRadius() / 2), (gameHeight / 2) - (innerRing.getRadius() / 2));

    //sets the ball velocity (inline if)
    ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
}

void Reset() {

    // reset paddle position
    paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
    paddles[1].setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);

    //reset ball position
    ball.setPosition((gameWidth / 2) - (ball.getRadius() / 2), (gameHeight / 2) - (ball.getRadius() / 2));

    //sets the ball velocity (inline if)
    ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

    text1.setPosition((gameWidth * 0.5) - (13 + text1.getLocalBounds().getSize().x), 0 + 10);
    text2.setPosition((gameWidth * 0.5) + 10, 0 + 10);


}

// Updates the position of the game objects for each tick
void Update(RenderWindow& window) {

    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();

    // check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

    // Toggle AI
    if (Keyboard::isKeyPressed(Keyboard::P)) {
        Reset();
        if (!AI) {
            AI = true;
        }
        else {
            AI = false;
        }

    }


    // handle paddle movement
    float paddle1Direction = 0.0f;
    float paddel2Direction = 0.0f;
    float AIpaddleDirection = 0.0f;

    //first paddle
    //move paddle up as long as top edge of paddle is not touching top boarder of game window
    if (Keyboard::isKeyPressed(controls[0]) && paddles[0].getPosition().y - (paddleSize.y * 0.5) > 0) {
        paddle1Direction--;
    }
    //move paddle down as long as bottom edge of paddle  is not touching bottom edge of game window
    if (Keyboard::isKeyPressed(controls[1]) && paddles[0].getPosition().y + (paddleSize.y * 0.5) < gameHeight) {
        paddle1Direction++;
    }

    paddles[0].move(0, paddle1Direction * paddleSpeed * dt);


    //second paddle
    if (Keyboard::isKeyPressed(controls[2]) && paddles[1].getPosition().y - (paddleSize.y * 0.5) > 0) {
        paddel2Direction--;
    }
    if (Keyboard::isKeyPressed(controls[3]) && paddles[1].getPosition().y + (paddleSize.y * 0.5) < gameHeight) {
        paddel2Direction++;
    }
    paddles[1].move(0, paddel2Direction * paddleSpeed * dt);

    //Second paddle AI
    if (AI == true && ball.getPosition().y < paddles[1].getPosition().y && paddles[1].getPosition().y - (paddleSize.y * 0.5) > 0) {
        AIpaddleDirection--;
    }
    if (AI == true && ball.getPosition().y > paddles[1].getPosition().y && paddles[1].getPosition().y + (paddleSize.y * 0.5) < gameHeight) {
        AIpaddleDirection++;
    }
    paddles[1].move(0, AIpaddleDirection * paddleSpeed * dt);


    //ball
    ball.move(ballVelocity * dt);

    //ball position
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;

    //check ball collision

    if (by + ballRadius >= gameHeight) {
        //bottom wall collision
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(0, -10);
    }
    else if (by < 0) {
        //top wall
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(0, 10);
    }
    else if (bx > gameWidth) {
        //right wall
        if (playerOneScore == 9) {
            playerOneScore = 0;
            playerTwoScore = 0;
            text1.setString(scores[playerOneScore]);
            text2.setString(scores[playerTwoScore]);

            server = false;
            Reset();
        }
        else {
            playerOneScore++;
            text1.setString(scores[playerOneScore]);
            server = false;
            Reset();
        }
    }
    else if (bx < 0) {
        //left wall
        if (playerTwoScore == 9) {
            playerTwoScore = 0;
            playerOneScore = 0;
            server = true;
            text1.setString(scores[playerOneScore]);
            text2.setString(scores[playerTwoScore]);
            Reset();
        }
        else {
            playerTwoScore++;
            text2.setString(scores[playerTwoScore]);
            server = true;
            Reset();
        }
    }
    else if (
        //ball is inline or behind paddle
        bx < paddleSize.x &&
        //AND ball is below top edge of paddle
        by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
        //AND ball is above bottom edge of paddle
        by < paddles[0].getPosition().y + (paddleSize.y * 0.5))
    {
        //bounce off left paddle
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;
        ball.move(10, 0);
    }
    else if (
        //ball is inline or behind paddle
        bx > gameWidth - paddleSize.x - 10 &&
        //AND ball is below top edge of paddle
        by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
        //AND ball is above bottom edge of paddle
        by < paddles[1].getPosition().y + (paddleSize.y * 0.5))
    {
        //bounce off right paddle
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;
        ball.move(-10, 0);
    }


}

void Render(RenderWindow& window) {
    // Draw Everything
    window.draw(innerRing);
    window.draw(centerLine);
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
    window.draw(text1);
    window.draw(text2);
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}

//int main() {
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
//    return 0;
//}