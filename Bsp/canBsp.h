#ifndef __CAN_BSP_H__
#define __CAN_BSP_H__

#define CAN_CONFIG_ENABLE 0

#define CAN1_RX0_INT_ENABLE	1		//0,不使能;1,使能.								    
										 							 				    
void CAN_Config (void);//CAN初始化
 
u8 CAN1_Send_Msg(u8* msg,u8 len);						//发送数据

u8 CAN1_Receive_Msg(u8 *buf);							//接收数据

#endif