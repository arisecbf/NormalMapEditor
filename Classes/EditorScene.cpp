// (C) 2015 Turnro.com

#include "EditorScene.h"
#include "TRLocale.h"

USING_NS_CC;
bool EditorScene::init()
{
    assert(TRBaseScene::init());

    _layer = Layer::create();
    this->addChild(_layer);


    auto sp = Sprite::create("images/dungeoncraft.png");
    sp->setPosition(genPos({0.5,0.75}));
    _layer->addChild(sp);
    auto size = Director::getInstance()->getWinSize();

    _pointLayer = Layer::create();
    _pointLayer->setPosition(genPos({0.5,0.5}));
    this->addChild(_pointLayer);

    initKeyboardMouse();


    return true;
}


cocos2d::Vec2 EditorScene::help_touchPoint2editPosition(const cocos2d::Vec2& touchpoint)
{
    auto size = Director::getInstance()->getWinSize();
    return {touchpoint.x - size.width/2, touchpoint.y - size.height/2};
}

void EditorScene::initKeyboardMouse()
{
    auto _keyboardListener = EventListenerKeyboard::create();
    _keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event){
        switch (code) {
            case EventKeyboard::KeyCode::KEY_SPACE:
                break;

            case EventKeyboard::KeyCode::KEY_R:
                _ks_addPoint = true;
                break;
            case EventKeyboard::KeyCode::KEY_T:
                _ks_deletePoint = true;
                break;
            case EventKeyboard::KeyCode::KEY_F:
                _ks_addLine = true;
                break;
            case EventKeyboard::KeyCode::KEY_G:
                _ks_deleteLine = true;
                break;

            default:
                break;
        }
    };
    _keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event* event){
        switch (code) {
            case EventKeyboard::KeyCode::KEY_SPACE:
                break;

            case EventKeyboard::KeyCode::KEY_R:
                _ks_addPoint = false;
                break;
            case EventKeyboard::KeyCode::KEY_T:
                _ks_deletePoint = false;
                break;
            case EventKeyboard::KeyCode::KEY_F:
                _ks_addLine = false;
                break;
            case EventKeyboard::KeyCode::KEY_G:
                _ks_deleteLine = false;
                break;

            default:
                break;
        }
        
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);

    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = [this](Touch* touch, Event* event){
        auto pos = help_touchPoint2editPosition(touch->getLocation());
        CCLOG("click in at %f %f", pos.x, pos.y);

        if (_ks_addPoint) {
            CCLOG("add point");

        }

        return false;
    };

    listener->onTouchMoved = [this](Touch* touch, Event* event){
    };

    listener->onTouchEnded = [this](Touch* touch, Event* event){
    };

    listener->onTouchCancelled = [this](Touch* touch, Event* event){
    };

    _pointLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, _pointLayer);

}