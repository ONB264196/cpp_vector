#define _VECTOR_CHASE
#include "libOne.h"

#ifdef _VECTOR_ADD
void gmain() {
    window(1000, 1000);
    while (notQuit) {
        clear(224, 225, 204);
        mathAxis(3.1f);

        VECTOR2 a(-1, 1);
        VECTOR2 b(mathMouseX, mathMouseY);
        VECTOR2 c = a + b;

        strokeWeight(3);
        //vec:a
        stroke(255, 0, 0);
        mathArrow(0, 0, a.x, a.y);
        //vec:b
        stroke(0, 0, 255);
        mathArrow(0, 0, b.x, b.y);
        stroke(0, 0, 255, 63);
        mathArrow(0 + a.x, 0 + a.y, b.x + a.x, b.y + a.y);
        //vec:c
        stroke(255, 0, 255);
        mathArrow(0, 0, c.x, c.y);
    }
}
#endif


#ifdef _VECTOR_SUB
void gmain() {
    window(1000, 1000);
    while (notQuit) {
        clear(224, 225, 204);
        mathAxis(3.1f);

        VECTOR2 a(-1, 1);
        VECTOR2 b(mathMouseX, mathMouseY);
        VECTOR2 c = a - b;

        strokeWeight(3);
        //vec:a
        stroke(255, 0, 0);
        mathArrow(0, 0, a.x, a.y);
        //vec:b
        stroke(0, 0, 255);
        mathArrow(0, 0, b.x, b.y);
        stroke(0, 0, 255, 63);
        mathArrow(0 + a.x, 0 + a.y, -b.x + a.x, -b.y + a.y);
        //vec:c
        stroke(255, 0, 255);
        mathArrow(0, 0, c.x, c.y);
    }
}
#endif


#ifdef _VECTOR_REFRECT
class SEGMENT {
    VECTOR2 Sp, Ep;  //壁の始点・終点  
    VECTOR2 N;  //垂直ベクトル
public:
    SEGMENT(float spx, float spy, float epx, float epy) {
        Sp.x = spx; Sp.y = spy; Ep.x = epx; Ep.y = epy;
        VECTOR2 v = Ep - Sp;
        N.x = -v.y;
        N.y = v.x;
        N.normalize();
    }
    void draw() {
        strokeWeight(1.5f);
        stroke(0);
        //壁
        mathLine(Sp.x, Sp.y, Ep.x, Ep.y);
        //垂直ベクトル
        stroke(31, 30, 51);
        mathArrow(0, 0, N.x, N.y);
    }
    const VECTOR2& n() { return N; }
    const VECTOR2& sp() { return Sp; }
};
class BALL {
    VECTOR2 Pos, Vel;
    float Speed = 0.02f;
    float Radius = 0.08f;
public:
    void setPos(const VECTOR2 pos) { Pos = pos; }
    void setVel(const VECTOR2 vel) {
        Vel = vel;
        Vel.setMag(Speed);
    }
    void collision(const VECTOR2& pos, const VECTOR2& n) {
        VECTOR2 v = Pos - pos;
        float dist = n.dot(v);
        if (absolute(dist) < Radius) {
            Vel = n.dot(-Vel) * 2 * n + Vel;

        }
    }
    void move() {
        Pos += Vel;
    }
    void draw() {
        fill(0, 127, 0);
        mathCircle(Pos.x, Pos.y, Radius * 2);
    }
};

void gmain() {
    window(1000, 1000);

    SEGMENT segment(-2, 5, 2, -5);
    VECTOR2 n = segment.n();
    BALL ball;

    while (notQuit) {
        clear(224, 225, 204);
        mathAxis(5);
        
        VECTOR2 mouse(mathMouseX, mathMouseY);
        VECTOR2 vel = -mouse;
        VECTOR2 ref = n.dot(-vel) * 2 * n + vel;

        strokeWeight(3);
        //マウスから原点へのベクトル
        stroke(255, 0, 0);
        mathArrow(mouse.x, mouse.y, 0, 0);
        //速度ベクトル
        stroke(127);
        mathArrow(0, 0, vel.x, vel.y);
        //反射ベクトル
        stroke(0, 0, 255);
        mathArrow(0, 0, ref.x, ref.y);

        /*
        //VECTOR2 ref = n.dot(-vel) * 2 * n + velの分解
        //垂線ベクトル・速度逆ベクトルの内積 * 垂線ベクトル
        stroke(200, 200, 0, 63);
        VECTOR2 dn = n.dot(-vel) * n;
        mathArrow(0, 0, dn.x, dn.y);
        mathLine(-vel.x, -vel.y, dn.x, dn.y);
        //2倍する
        VECTOR2 dn2 = dn * 2;
        mathArrow(0, 0, dn2.x, dn2.y);
        //速度ベクトルを加算
        mathArrow(0 + dn2.x, 0 + dn2.y, vel.x + dn2.x, vel.y + dn2.y);
        */

        segment.draw();

        if (isTrigger(MOUSE_LBUTTON)) {
            ball.setPos(mouse);
            ball.setVel(vel);
        }
        ball.move();
        ball.collision(segment.sp(), segment.n());
        ball.draw();
    }
}
#endif


#ifdef _VECTOR_COLLISION
class SEGMENT {
    VECTOR2 Sp, Ep;  //壁の始点・終点  
    VECTOR2 N;  //垂直ベクトル
public:
    SEGMENT(float spx, float spy, float epx, float epy) {
        Sp.x = spx; Sp.y = spy; Ep.x = epx; Ep.y = epy;
        VECTOR2 v = Ep - Sp;
        N.x = -v.y;
        N.y = v.x;
        N.normalize();
    }
    void draw() {
        strokeWeight(1.5f);
        stroke(0);
        //壁
        mathLine(Sp.x, Sp.y, Ep.x, Ep.y);
        //垂直ベクトル
        //stroke(31, 30, 51);
        //mathArrow(0, 0, N.x, N.y);
    }
    const VECTOR2& n() { return N; }
    const VECTOR2& sp() { return Sp; }
    const VECTOR2& ep() { return Ep; }
};
class BALL {
    VECTOR2 Pos, Vel;
    float Speed = 0.02f;
    float Radius = 0.08f;
    float Hue = 0;
public:
    BALL(float px, float py, float vx, float vy, float sp, float r, float hue) {
        Pos.x = px; Pos.y = py; Vel.x = vx; Vel.y = vy;
        Speed = sp;
        Radius = r;
        Hue = hue;
    }
    void setPos(const VECTOR2 pos) { Pos = pos; }
    void setVel(const VECTOR2 vel) {
        Vel = vel;
        Vel.setMag(Speed);
    }
    void manual() {
        Vel.x = Vel.y = 0;
        if (isPress(KEY_D))Vel.x = 1;
        if (isPress(KEY_A))Vel.x = -1;
        if (isPress(KEY_W))Vel.y = 1;
        if (isPress(KEY_S))Vel.y = -1;
        Vel.setMag(Speed);
    }
    void collision(SEGMENT& seg) {
        const VECTOR2& n = seg.n();
        VECTOR2 v1 = Pos - seg.sp();
        float dist = n.dot(v1);
        if (absolute(dist) < Radius) {
            VECTOR2 v2 = Pos - seg.ep();
            if (n.cross(v1) < 0) {
                if (n.cross(v1) < 0 && n.cross(v2) > 0) {
                    float excess = Radius - absolute(dist);
                    if (dist > 0)Pos += n * excess;
                    else Pos += -n * excess;

                    calcRefrectVel(n);
                }
                else if (v1.sqMag() < Radius * Radius) {
                    Pos = seg.sp() + v1.normalize() * Radius;
                    calcRefrectVel(v1);
                }
                else if (v2.sqMag() < Radius * Radius) {
                    Pos = seg.ep() + v2.normalize() * Radius;
                    calcRefrectVel(v2);
                }
            }
        }
    }
    void calcRefrectVel(const VECTOR2& n) {
        Vel = n.dot(-Vel) * 2 * n + Vel;
    }
    void move() {
        Pos += Vel;
    }
    void draw() {
        noStroke();
        colorMode(HSV);
        fill(Hue, 128, 255, 220);
        mathCircle(Pos.x, Pos.y, Radius * 2);
    }
};

#include<vector>
void gmain() {
    window(1000, 1000);

    float p[]{
        -1.8f, -0.2f,
         1.0f, -1.5f,
         2.0f,  1.0f,
        -4.0f,  2.0f,
        -1.0f, -4.0f,
         3.0f, -1.0f,
    };
    std::vector<SEGMENT> segments;
    int numLine = sizeof(p) / 8 - 1;
    for (int i = 0; i < numLine; i++) {
        segments.emplace_back(
            p[i * 2 + 0],
            p[i * 2 + 1],
            p[i * 2 + 2],
            p[i * 2 + 3]);
    }

    std::vector<BALL> balls;
    for (int i = 0; i < 1000; i++) {
        balls.emplace_back(
            random(-1, 1),
            random(-1, 1),
            random(-0.04f, 0.04f),
            random(-0.04f, 0.04f),
            0,
            random(0.1f, 0.3f),
            random(6.28f)
        );
    }

    while (notQuit) {
        clear(63);
        mathAxis(5, 63);


        for (BALL& ball : balls) {
            ball.move();
            for (SEGMENT& segment : segments) {
                ball.collision(segment);
            }
            ball.draw();
        }
        for (SEGMENT& segment : segments) {
            segment.draw();
        }
    }
}
#endif


#ifdef _VECTOR_FORCE
class CIRCLE {
    COLOR Color;
    float Radius; 
    VECTOR2 Pos, Vel, Acc;
    float Restitution;
public:
    CIRCLE(COLOR color, float radius, float px, float py, float restitution) {
        Color = color; 
        Radius = radius; 
        Pos.x = px; Pos.y = py;
        Restitution = restitution;
    }
    void applyForce(const VECTOR2& force) {
        Acc += force;
    }
    void move() {
        Vel += Acc;
        Pos += Vel;
        Acc *= 0;
    }
    void edge() {
#define _ref
#ifdef _res
        
        if (Pos.x > width + Radius || Pos.x < -Radius * 2) {
            Pos.x = random(Radius, width - Radius);
            Pos.y = -random(50, 100);
            Vel *=  0;
        }
#endif
#ifdef _ref
        if (Pos.x > width - Radius || Pos.x < Radius) Vel.x *= -1;
        if (isTrigger(KEY_SPACE)) Pos.y = -random(50, 100);
#endif


        if (Pos.y > height - Radius) {
            Pos.y = height - Radius;
            Vel.y *= -Restitution;
        }
    }
    void collision(CIRCLE& other) {
        if (this != &other) {
            VECTOR2 v = Pos - other.Pos;
            float dist = (Radius + other.Radius);
                if (v.sqMag() < dist * dist) {
                Pos = other.Pos + v.normalize() * dist;
                Vel = v.dot(-Vel) * 2 * v + Vel;
            }
        }
    }
    void draw() {
        noStroke();
        fill(Color);
        circle(Pos.x, Pos.y, Radius * 2);
    }
};
#include<vector>
void gmain() {
    window(1100, 1080, 1);
    hideCursor();
    colorMode(HSV);
    std::vector<CIRCLE> balls;
    for (int i = 0; i < 30; i++) {    //球の個数
        COLOR color(random() % 7, 128, 255, 191);
        float radius = 20;
        float px = random(radius, width - radius);
        float py = -random(50, 100);
        float restitution = 0.9;
        balls.emplace_back(color, radius, px, py, restitution);
    }
    std::vector<CIRCLE> nails;
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 10; i++) {
            COLOR color(2, 128, 180);
            float radius = 5;
            float px = 100 * i + 100;
            float py = 100 * j + 300;
            float restitution = 0;
            nails.emplace_back(color, radius, px, py, restitution);
        }
    }
    while (notQuit) {
        clear();
        fill(80);
        rect(0, 0, width, height);

        VECTOR2 gravity(0, 0.980665);
        VECTOR2 wind;
        if (isTrigger(KEY_D) || isTrigger(KEY_RIGHT)) wind.x = (rand() % 50 + 5) * 0.1;
        if (isTrigger(KEY_A) || isTrigger(KEY_LEFT)) wind.x = (-rand() % 50 + 5) * 0.1;
        for (CIRCLE& ball : balls) {
            ball.applyForce(gravity);
            ball.applyForce(wind);
            ball.move();
            for (CIRCLE& other : balls) {
                ball.collision(other);
            }
            for (CIRCLE& nail : nails) {
                ball.collision(nail);
            }
            ball.edge();
            ball.draw();
        }
        for (CIRCLE& nail : nails) {
            nail.draw();
        }
    }
}
#endif


#ifdef _VECTOR_CHASE
class CIRCLE {
    COLOR Color;
    float Radius;
    VECTOR2 Pos, Vel, Acc;
    float Restitution;
    float MaxSpeed;
    float MaxForce;
    float NearDistance;
public:
    CIRCLE(COLOR color, float radius, float px, float py, float restitution = 1) {
        Color = color;
        Radius = radius;
        Pos.x = px; Pos.y = py;
        Restitution = restitution;
    }
    void setMaxSpeed(float maxSpeed) {
        MaxSpeed = maxSpeed;
    }
    void setMaxForce(float maxForce) {
        MaxForce = maxForce;
    }
    void setNearDistance(float nearDistance) {
        NearDistance = nearDistance;
    }
    void chase(const VECTOR2& target) {
        VECTOR2 acc = target - Pos;
        float distance = acc.mag();
        float speed = MaxSpeed;
        if (distance < NearDistance) {
            speed = map(distance, 0, NearDistance, 0, MaxSpeed);
        }
        acc.setMag(speed);
        acc -= Vel;
        acc.limmit(MaxForce);
        applyForce(acc);
    }
    void applyForce(const VECTOR2& force) {
        Acc += force;
    }
    void move() {
        Vel += Acc;
        Pos += Vel;
        Acc *= 0;
    }
    void draw() {
        noStroke();
        fill(Color);
        circle(Pos.x, Pos.y, Radius * 2);
    }
    const VECTOR2& pos() { return Pos; }
};


#include<vector>
void gmain() {
    window(1920, 1080, 1);
    //hideCursor();
    colorMode(HSV);

    std::vector<CIRCLE> balls;
    float px = width / 2;
    float py = height / 2;
    int num = 20;
    float radius = 100;
    for (int i = 0; i < num; i++) {    //球の個数
        COLOR color(6.28f / num * i, 128, 255, 191);
        float r = radius - radius / num * i;
        balls.emplace_back(color, r, px, py);
    }

    while (notQuit) {
        fill(0, 0, 0, 15);
        rect(0, 0, width, height);

        VECTOR2 target = VECTOR2(mouseX, mouseY);
        for (CIRCLE& ball : balls) {
            ball.setMaxSpeed(4);
            ball.setMaxForce(0.25f);
            ball.setNearDistance(100);
            ball.chase(target);
            ball.move();
            ball.draw();
            target = ball.pos();
        }
    }
}
#endif