#include "AllSprites.h"
AllSprites::AllSprites(){

}
AllSprites::~AllSprites(){

}
int AllSprites::get_typeid(){
	return -1;
}
void AllSprites::SetAnimation(int from, int to, bool run_directon,int loop){

}
bool AllSprites::get_skill_J_ishurted(){
	return false;
}
void AllSprites::set_skill_J_ishurted(bool skill_J_ishurted){

}
bool AllSprites::get_skill_K_ishurted(){
	return false;
}
void AllSprites::set_skill_K_ishurted(bool skill_K_ishurted){

}
int AllSprites::get_life(){
	return 0;
}
void AllSprites::set_life(int delta){

}
void AllSprites::set_life_bar(int side){

}
float AllSprites::get_speed(){
	return 0.1;
}
void AllSprites::core(){

}
void AllSprites::object_select(Vector<AllSprites *> sprites){

}
bool AllSprites::get_hittest_A(){
	return false;
}
void AllSprites::set_hittest_A(bool hittest_A){

}
void AllSprites::attack_A_effect(AllSprites *enemy){

}
int AllSprites::get_attack_A_distance(){
	return 0;
}
bool AllSprites::get_hittest_J(){
	return false;
}
void AllSprites::skill_J_attack(AllSprites *enemy){

}
bool AllSprites::get_hittest_K(){
	return false;
}
void AllSprites::skill_K_attack(AllSprites *enemy){

}
bool AllSprites::get_Direction(){
	return false;
}
bool AllSprites::get_isblowup(){
	return false;
}
void AllSprites::set_isblowup(bool isblowup){
	
}
bool AllSprites::get_money_paid(){
	return true;
}
void AllSprites::set_money_paid(bool paid){

}
bool AllSprites::get_canControl(){
	return false;
}
void AllSprites::set_canControl(bool canControl){
	
}
bool AllSprites::get_isOver(){
	return false;
}
bool AllSprites::get_isdeath(){
	return false;
}
bool AllSprites::is_melee(){
	return true;
}
int AllSprites::get_fly_kind(){
	return -1;
}
bool AllSprites::is_fly_kind(){
	return false;
}
int AllSprites::earn_money(){
	return 0;
}
Vec2 AllSprites::get_object_aim_pst(){
	return Vec2(0, 0);
}
Sprite* AllSprites::get_n_Sprite(){
	return	n_Sprite;
}
void AllSprites::set_isMoving(bool isMoving){

}
bool AllSprites::get_isMoving(){
	return false;
}