//
//  Particle.cpp
//  Bird
//
//  Created by 斉藤俊介 on 2018/05/11.
//

#include "Particle.hpp"

Particle::Particle() {
    Particle(ofVec3f(500, 500, -1000), ofColor::fromHsb(100, 255, 255));
}

Particle::~Particle() {
    cout << "Particle destructor is called" << endl;
}

Particle::Particle(ofVec3f _position, ofColor _color) {
    startPos = _position;
    for (int i = 0; i < NUM; i++) {
        verts[i] = _position;
        colors[i] = (ofFloatColor)_color;
    }
    velocity[0] = ofVec3f(5, 5, 5);
    for (int i = 1; i < NUM; i++) {
        velocity[i] = ofVec3f(ofRandom(-10, 10), ofRandom(-6, 6), ofRandom(-5, 5));
    }
}

void Particle::flow() {
    if (!check())
        update();
    draw();
}

bool Particle::check() {
    if (startPos.distance(verts[0]) >= 500)
        isThreshold = true;
    return isThreshold;
}

void Particle::setup() {
    // テクスチャを２乗モードに
    ofDisableArbTex();
    
    ofImage img;
    img.load("tex/particle.png");
    textures.push_back(img);
    
    // テクスチャを元のモードに
    ofEnableArbTex();
    
    for (int i = 0; i < NUM; i++) {
        // 法線の情報をポイントサイズとテクスチャの選択に利用
        normals[i].set(ofRandom(2, 50), (int)ofRandom(0, textures.size()));
    }
    
    vbo.setVertexData(verts, NUM, GL_DYNAMIC_DRAW);
    vbo.setColorData(colors, NUM, GL_DYNAMIC_DRAW);
    vbo.setNormalData(normals, NUM, GL_DYNAMIC_DRAW);
    
    mPointSprite.load("shaders/pointSprite.vert","shaders/pointSprite.frag");
}

void Particle::update() {
    for (int i = 0; i < NUM; i++) {
        velocity[i] *= friction;
        verts[i] += velocity[i];
    }
    vbo.updateVertexData(verts, NUM);
    vbo.updateColorData(colors, NUM);
    vbo.updateNormalData(normals, NUM);
}

void Particle::draw() {
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnableAlphaBlending();
    ofEnablePointSprites();
    
    mPointSprite.begin();
    mPointSprite.setUniformTexture("tex1", textures[0], 0);
    vbo.draw(GL_POINTS, 0, NUM);
    mPointSprite.end();
    
    ofDisablePointSprites();
}
