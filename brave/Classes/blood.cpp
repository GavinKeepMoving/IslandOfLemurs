//
//  blood.cpp
//  brave
//
//  Xiaojing Liu 10/06/2014
//
//
#include "blood.h"
#include "Progress.h"
//#include "VisibleRect.h"
blood::blood() {
    
}

blood::~blood() {
    
}

bool blood::initBloodWithPlayerType(Player::PlayerType type){
	switch(type)
	{
	case Player::PlayerType::PLAYER:
		_health = 100;
		_maxHealth = 100;
		_isCanAttack = true;

		break;
	case Player::PlayerType::ENEMY1:
		_health = 50;
		_maxHealth = 50;
		_isCanAttack = true;
	
		break;
	case Player::PlayerType::ENEMY2:
		_health = 50;
		_maxHealth = 50;
		_isCanAttack = true;
		break;
	}

	return true;
}

bool blood::isAlive(){
	return _isCanAttack;
}

bool blood::isAttack(int attack){
	
	this->_health -= attack;
	if(this->_health <= 0)
	{
		this->_health = 0;
		//the role need to be mark die
		return false;
	}
	return true;
}

void blood::reset(){ 
	//reset player's health value for next level
	int _health = 100;
	bool _isCanAttack = true;
}


