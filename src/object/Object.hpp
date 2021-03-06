
#pragma once
#include <string>
#include "cinder/app/AppNative.h"


class Object {
public:
  enum class State {
    Awake,
    Active,
    Dead
  };
  
  enum class Collider {
    None,
    Rect,
    Circle
  };
  
  enum class DebugModule {
    Disable,
    Enable
  };
  
  Object();
  
  void setState(const State& state);
  const State& getState() const;
  
  const bool isAwake()  const;
  const bool isActive() const;
  const bool isDead()   const;
  
  void setColliderType(const Collider& type);
  const Collider& getColliderType() const;
  
  const bool isColliderTypeNone()   const;
  const bool isColliderTypeRect()   const;
  const bool isColliderTypeCircle() const;
  
  void enableDebugModule();
  
  
  void setName(const std::string& name);
  const std::string& getName() const;
  
  const ci::Vec3f&  getPos()    const;
  const ci::Vec3f&  getSize()   const;
  const ci::Vec3f&  getRotate() const;
  const ci::ColorA& getColor()  const;
  
  virtual void setup()  = 0;
  virtual void update() = 0;
  virtual void draw()   = 0;
  virtual void onCollisionUpdate(const std::shared_ptr<Object>& compare) {};
  
protected:
  std::string mName;
  State       mState;
  Collider    mCollider;
  DebugModule mDebug;
  
  ci::Vec3f  mPos;
  ci::Vec3f  mSize;
  ci::Vec3f  mRotate;
  ci::ColorA mColor;
};