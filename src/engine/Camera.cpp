#include "Camera.h"
#include "Globals.h"
#include "Input.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#include <algorithm>

using namespace std;
using namespace glm;

Camera::Camera() : Actor(nullptr) {
    lookPoint = Actor::create(nullptr);
    leftTop = Actor::create(nullptr);
    leftBottom = Actor::create(nullptr);
    rightTop = Actor::create(nullptr);
    rightBottom = Actor::create(nullptr);
}

CameraPtr Camera::create(DiamondSquareTerrain& terrain) {
    static const vec3 INIT_DIR = vec3(0, 0, 1);

    CameraPtr camera = CameraPtr(new Camera());
    camera->addChilds({camera->lookPoint, camera->leftTop, camera->leftBottom,
                       camera->rightTop, camera->rightBottom});

    float yView = 1;
    float xView = Window::getRatio() * yView;
    camera->lookPoint->setPosition(INIT_DIR);
    vec3 lookDir = INIT_DIR;
    camera->allignToVector(INIT_DIR, lookDir);
    camera->up = Utils::VY;
    camera->setCornerPoints(xView, yView,
                            camera->lookPoint->getLocalPosition(), camera->up);
    
    float height = 1.5f;
    vec3 pos = terrain.calcLowestPoint();
    pos.y += height;
    camera->setPosition(pos);
    camera->velocity = 10;
    return camera;
}

void Camera::onUpdate() {
    float stepVal = velocity * Globals::deltaTime;
    vec3 step = vec3(0);
    vec3 front = normalize(lookPoint->getLocalPosition());
    vec3 right = cross(front, up);
    if (Input::isPressed(GLFW_KEY_W) || Input::isPressed(GLFW_KEY_UP)) {
        step = front * stepVal;
    }
    if (Input::isPressed(GLFW_KEY_S) || Input::isPressed(GLFW_KEY_DOWN)) {
        step = front * (-stepVal);
    }
    if (Input::isPressed(GLFW_KEY_A) || Input::isPressed(GLFW_KEY_LEFT)) {
        step = right * (-stepVal);
    }
    if (Input::isPressed(GLFW_KEY_D) || Input::isPressed(GLFW_KEY_RIGHT)) {
        step = right * stepVal;
    }

    auto newRot = getRotation() +
                  vec3(-Input::getMouseOffset().y * Globals::deltaTime,
                            -Input::getMouseOffset().x * Globals::deltaTime, 0);
    static const float MAX_X_DEG = 66;
    newRot.x = glm::min(newRot.x, MAX_X_DEG);
    newRot.x = glm::max(newRot.x, -MAX_X_DEG);
    setRotation(newRot);

    step = static_cast<vec3>(getRotationMat() * vec4(step, 0));
    move(step);
}

mat4 Camera::getViewMat() {
    return lookAt(
        getWorldPosition(), // the position of your camera, in world space
        lookPoint
            ->getWorldPosition(), // where you want to look at, in world space
        up // probably vec3(0,1,0), but (0,-1,0) would make you looking
           // upside-down, which can be great too
    );
}

mat4 Camera::getProjectionMat() {
    float fov = 45;
    return perspective(
        radians(fov), // The vertical Field of View, in radians: the amount
                           // of "zoom". Think "camera lens". Usually between
                           // 90° (extra wide) and 30° (quite zoomed in)
        Window::getRatio(), // Aspect Ratio. Depends on the size of your window.
                            // Notice that 4/3 == 800/600 == 1280/960, sounds
                            // familiar ?
        0.1f,  // Near clipping plane. Keep as big as possible, or you'll get
               // precision issues.
        2000.0f // Far clipping plane. Keep as little as possible.
    );
}

void Camera::setCornerPoints(float xView, float yView, vec3 lookDir,
                             vec3 up) {
    static const float DEPTH = 2;
    vec3 front = normalize(lookDir);
    vec3 right = normalize(cross(front, up));
    vec3 top = normalize(cross(right, front));

    front *= DEPTH;
    right *= xView;
    top *= yView;

    leftTop->setPosition(front - right + top);
    leftBottom->setPosition(front - right - top);
    rightTop->setPosition(front + right + top);
    rightBottom->setPosition(front - right - top);
}

vec3 Camera::getLeftTop() const { return leftTop->getWorldPosition(); }

vec3 Camera::getLeftBottom() const {
    return leftBottom->getWorldPosition();
}

vec3 Camera::getRightTop() const { return rightTop->getWorldPosition(); }

vec3 Camera::getRightBottom() const {
    return rightBottom->getWorldPosition();
}

void Camera::allignToVector(vec3 initDir, vec3 allignDir){
    initDir = normalize(initDir);
    allignDir = normalize(allignDir);

    vec2 initDir2d = normalize(Utils::toVec2(initDir, Utils::Axis::Y));
    vec2 allignDir2d = normalize(Utils::toVec2(allignDir, Utils::Axis::Y));
    float yRot = -degrees(orientedAngle(initDir2d, allignDir2d)); 
    float xRot = -degrees(asin(allignDir.y));
    
    vec3 rotation = vec3(xRot, yRot, 0);
    setRotation(rotation);
}