/* 
 * File:   actions_ax12.h
 * Author: zoltarius
 *
 * Created on 4 avril 2014, 18:41
 */

#ifndef ACTIONS_AX12_H
#define	ACTIONS_AX12_H


#define BOUGIE_init_arm (1<<0)
#define BOUGIE_launch_net (1<<1)
#define BOUGIE_catch_arm (1<<2)
#define BOUGIE_stock_arm (1<<3)
#define BOUGIE_pull_arm (1<<4)
#define BOUGIE_push_arm (1<<5)
#define BOUGIE_convoyer (1<<6)
#define BOUGIE_slight_convoyer (1<<7)
#define BOUGIE_poulet (1<<8)
#define BOUGIE_raise_arm (1<<9)
#define BOUGIE_salut (1<<10)









#define SD1             4
#define SD2             13
#define SD3             17

#define SG1             12
#define SG2             42
#define SG3             2

#define LAU             18
#define CONV            15


void choose_arm(int);
void init_arm(int);
void catch_arm(int);
void stock_arm(int);
void raise_arm(int);
void pull_arm(int);
void push_arm(int);
void launch_net();
void convoyer();
void slight_convoyer();
void poulet();
void  salut(int);




#endif	/* ACTIONS_AX12_H */

