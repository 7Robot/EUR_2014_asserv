/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif

//include libpic
#include <stdint.h>        /* Includes uint16_t definition   */
#include <stdbool.h>       /* Includes true/false definition */
#include <timer.h>
#include <uart.h>

//include projet
#include "user.h"
#include "ax12.h"
#include "libasserv_robot.h"
#include "asserv/libasserv.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
     _TRISA2 = 0;
    /* TODO Initialize User Ports/Peripherals/Project here */
     
    // activation de la priorité des interruptions
     _NSTDIS = 0;

    OpenTimer2(T2_ON &
                T2_IDLE_CON &
                T2_GATE_OFF &
                T2_PS_1_256 &
                T2_SOURCE_INT, 1560 ); //100Hz

    //ConfigIntTimer2(T2_INT_PRIOR_4 & T2_INT_ON);

	//UART AX12
    OpenUART2(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW
            & UART_UEN_00 & UART_DIS_WAKE & UART_DIS_LOOPBACK
            & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE & UART_BRGH_SIXTEEN
            & UART_NO_PAR_8BIT & UART_1STOPBIT,
              UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO
            & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_TX_BUF_NOT_FUL & UART_INT_RX_CHAR
            & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR,
              BRGVALAX12);

    ConfigIntUART2(UART_RX_INT_PR4 & UART_RX_INT_EN
                 & UART_TX_INT_PR4 & UART_TX_INT_DIS);
				 
	_ODCB5 = 1; //OPEN DRAIN pour AX12
	
	Init_PWM();
	Init_QEI();
}

void Init_PWM(void)
{
    // P1TCON
    P1TCONbits.PTEN = 1; // enable module PWM
    P1TCONbits.PTCKPS = 0; // Clk input of the PWM module is TCY (no prescale)
    P1TCONbits.PTMOD = 0; // free-runnig mode

    /*
* la période des PWM (temps entre 2 fronts montants)
* est fixée à 1500 cycles de 40MHz
* ça donne une periode de sortie de 37.5 µs soit 26.66 kHz
* RMQ : les registres de rapport cycliques ayant une précision double
* leur valeur max sera 3000
*/
    P1TPER = 1500;

    //PWM1CON1
    PWM1CON1bits.PMOD2 = 1; // sorties indépendantes
    PWM1CON1bits.PMOD3 = 1;
    // desactivation de toutes les sorties
    // à réactiver une fois le pinout trouvé ;)

    // sorties High du pwm
    PWM1CON1bits.PEN1H = 0;
    PWM1CON1bits.PEN2H = 1;
    PWM1CON1bits.PEN3H = 1;

    // sorties Low (opposé du High, on ne l'utilise pas)
    PWM1CON1bits.PEN1L = 0;
    PWM1CON1bits.PEN2L = 0;
    PWM1CON1bits.PEN3L = 0;

    // réglage des rapports cycliques, pour l'instant on mets 0 lors de l'initialisation
    P1DC2 = 0;
    P1DC3 = 0;

    // Activation en sortie des pin de sens du PONT en H
    MOTOR_1A_TRIS = 0;
    MOTOR_1B_TRIS = 0;
    MOTOR_2A_TRIS = 0;
    MOTOR_2B_TRIS = 0;

    // pins de sens des moteurs
    MOTOR_1A_O = 0;
    MOTOR_1B_O = 0;
    MOTOR_2A_O = 0;
    MOTOR_2B_O = 0;
}

void Init_QEI(void)
{
    // module QEI1 = Moteur Droit
    QEI1CONbits.QEISIDL = 1; // module toujours actif, meme en etat de pause du pic
    QEI1CONbits.QEIM = 6; // module en mode x4 : regarde tous les fronts, reset sur index, désactivé en dessous
    QEI1CONbits.POSRES = 0; // desactive l'index => pas de reset du compteur;
    QEI1CONbits.TQCS = 0; // use PIC clock

    // configuration des pins A et B du module
    // ce sont des pins dites remapable,
    // ce qui veut dire que l'on peut choisir presque toutes les IO du PIC
    RPINR14bits.QEA1R = 25; // 25 = pin RP25
    RPINR14bits.QEB1R = 22;


    // module QEI2 identique = Moteur Gauche
    QEI2CONbits.QEISIDL = 1; // module toujours actif, meme en etat de pause du pic
    QEI2CONbits.QEIM = 6; // module en mode x4 : regarde tous les fronts, reset sur index, désactivé en dessous
    QEI2CONbits.POSRES = 0; // desactive l'index => pas de reset du compteur;
    QEI2CONbits.TQCS = 0; // use PIC clock

    // configuration des pins A et B du module
    RPINR16bits.QEA2R = 23; // 23 = pin RP23
    RPINR16bits.QEB2R = 24;
}

void Set_Vitesse_MoteurD(float consigne)
{
	if (consigne < 0.0)
	{
		consigne = -consigne;
		MOTOR_1A_O = 0;
		MOTOR_1B_O = 1;
	}
	else
	{
		MOTOR_1A_O = 1;
		MOTOR_1B_O = 0;		
	}
	if (consigne < CONSIGNE_NULLE) consigne = 0;
	else if (consigne > CONSIGNE_MAX) consigne = CONSIGNE_MAX;
	P1DC2 = (int)(consigne);
}

void Set_Vitesse_MoteurG(float consigne)
{
	if (consigne < 0.0)
	{
		consigne = -consigne;
		MOTOR_2A_O = 0;
		MOTOR_2B_O = 1;
	}
	else
	{
		MOTOR_2A_O = 1;
		MOTOR_2B_O = 0;		
	}
	if (consigne < CONSIGNE_NULLE) consigne = 0;
	else if (consigne > CONSIGNE_MAX) consigne = CONSIGNE_MAX;
	P1DC3 = (int)(consigne);
}

/******************************************************************************/
/* Interrupt Vector Options                                                   */
/******************************************************************************/
/*                                                                            */
/* Refer to the C30 (MPLAB C Compiler for PIC24F MCUs and dsPIC33F DSCs) User */
/* Guide for an up to date list of the available interrupt options.           */
/* Alternately these names can be pulled from the device linker scripts.      */
/*                                                                            */
/* dsPIC33F Primary Interrupt Vector Names:                                   */
/*                                                                            */
/* _INT0Interrupt      _C1Interrupt                                           */
/* _IC1Interrupt       _DMA3Interrupt                                         */
/* _OC1Interrupt       _IC3Interrupt                                          */
/* _T1Interrupt        _IC4Interrupt                                          */
/* _DMA0Interrupt      _IC5Interrupt                                          */
/* _IC2Interrupt       _IC6Interrupt                                          */
/* _OC2Interrupt       _OC5Interrupt                                          */
/* _T2Interrupt        _OC6Interrupt                                          */
/* _T3Interrupt        _OC7Interrupt                                          */
/* _SPI1ErrInterrupt   _OC8Interrupt                                          */
/* _SPI1Interrupt      _DMA4Interrupt                                         */
/* _U1RXInterrupt      _T6Interrupt                                           */
/* _U1TXInterrupt      _T7Interrupt                                           */
/* _ADC1Interrupt      _SI2C2Interrupt                                        */
/* _DMA1Interrupt      _MI2C2Interrupt                                        */
/* _SI2C1Interrupt     _T8Interrupt                                           */
/* _MI2C1Interrupt     _T9Interrupt                                           */
/* _CNInterrupt        _INT3Interrupt                                         */
/* _INT1Interrupt      _INT4Interrupt                                         */
/* _ADC2Interrupt      _C2RxRdyInterrupt                                      */
/* _DMA2Interrupt      _C2Interrupt                                           */
/* _OC3Interrupt       _DCIErrInterrupt                                       */
/* _OC4Interrupt       _DCIInterrupt                                          */
/* _T4Interrupt        _DMA5Interrupt                                         */
/* _T5Interrupt        _U1ErrInterrupt                                        */
/* _INT2Interrupt      _U2ErrInterrupt                                        */
/* _U2RXInterrupt      _DMA6Interrupt                                         */
/* _U2TXInterrupt      _DMA7Interrupt                                         */
/* _SPI2ErrInterrupt   _C1TxReqInterrupt                                      */
/* _SPI2Interrupt      _C2TxReqInterrupt                                      */
/* _C1RxRdyInterrupt                                                          */
/*                                                                            */
/* dsPIC33E Primary Interrupt Vector Names:                                   */
/*                                                                            */
/* _INT0Interrupt     _IC4Interrupt      _U4TXInterrupt                       */
/* _IC1Interrupt      _IC5Interrupt      _SPI3ErrInterrupt                    */
/* _OC1Interrupt      _IC6Interrupt      _SPI3Interrupt                       */
/* _T1Interrupt       _OC5Interrupt      _OC9Interrupt                        */
/* _DMA0Interrupt     _OC6Interrupt      _IC9Interrupt                        */
/* _IC2Interrupt      _OC7Interrupt      _PWM1Interrupt                       */
/* _OC2Interrupt      _OC8Interrupt      _PWM2Interrupt                       */
/* _T2Interrupt       _PMPInterrupt      _PWM3Interrupt                       */
/* _T3Interrupt       _DMA4Interrupt     _PWM4Interrupt                       */
/* _SPI1ErrInterrupt  _T6Interrupt       _PWM5Interrupt                       */
/* _SPI1Interrupt     _T7Interrupt       _PWM6Interrupt                       */
/* _U1RXInterrupt     _SI2C2Interrupt    _PWM7Interrupt                       */
/* _U1TXInterrupt     _MI2C2Interrupt    _DMA8Interrupt                       */
/* _AD1Interrupt      _T8Interrupt       _DMA9Interrupt                       */
/* _DMA1Interrupt     _T9Interrupt       _DMA10Interrupt                      */
/* _NVMInterrupt      _INT3Interrupt     _DMA11Interrupt                      */
/* _SI2C1Interrupt    _INT4Interrupt     _SPI4ErrInterrupt                    */
/* _MI2C1Interrupt    _C2RxRdyInterrupt  _SPI4Interrupt                       */
/* _CM1Interrupt      _C2Interrupt       _OC10Interrupt                       */
/* _CNInterrupt       _QEI1Interrupt     _IC10Interrupt                       */
/* _INT1Interrupt     _DCIEInterrupt     _OC11Interrupt                       */
/* _AD2Interrupt      _DCIInterrupt      _IC11Interrupt                       */
/* _IC7Interrupt      _DMA5Interrupt     _OC12Interrupt                       */
/* _IC8Interrupt      _RTCCInterrupt     _IC12Interrupt                       */
/* _DMA2Interrupt     _U1ErrInterrupt    _DMA12Interrupt                      */
/* _OC3Interrupt      _U2ErrInterrupt    _DMA13Interrupt                      */
/* _OC4Interrupt      _CRCInterrupt      _DMA14Interrupt                      */
/* _T4Interrupt       _DMA6Interrupt     _OC13Interrupt                       */
/* _T5Interrupt       _DMA7Interrupt     _IC13Interrupt                       */
/* _INT2Interrupt     _C1TxReqInterrupt  _OC14Interrupt                       */
/* _U2RXInterrupt     _C2TxReqInterrupt  _IC14Interrupt                       */
/* _U2TXInterrupt     _QEI2Interrupt     _OC15Interrupt                       */
/* _SPI2ErrInterrupt  _U3ErrInterrupt    _IC15Interrupt                       */
/* _SPI2Interrupt     _U3RXInterrupt     _OC16Interrupt                       */
/* _C1RxRdyInterrupt  _U3TXInterrupt     _IC16Interrupt                       */
/* _C1Interrupt       _USB1Interrupt     _ICDInterrupt                        */
/* _DMA3Interrupt     _U4ErrInterrupt    _PWMSpEventMatchInterrupt            */
/* _IC3Interrupt      _U4RXInterrupt     _PWMSecSpEventMatchInterrupt         */
/*                                                                            */
/* For alternate interrupt vector naming, simply add 'Alt' between the prim.  */
/* interrupt vector name '_' and the first character of the primary interrupt */
/* vector name.  There is no Alternate Vector or 'AIVT' for the 33E family.   */
/*                                                                            */
/* For example, the vector name _ADC2Interrupt becomes _AltADC2Interrupt in   */
/* the alternate vector table.                                                */
/*                                                                            */
/* Example Syntax:                                                            */
/*                                                                            */
/* void __attribute__((interrupt,auto_psv)) <Vector Name>(void)               */
/* {                                                                          */
/*     <Clear Interrupt Flag>                                                 */
/* }                                                                          */
/*                                                                            */
/* For more comprehensive interrupt examples refer to the C30 (MPLAB C        */
/* Compiler for PIC24 MCUs and dsPIC DSCs) User Guide in the                  */
/* <C30 compiler instal directory>/doc directory for the latest compiler      */
/* release.  For XC16, refer to the MPLAB XC16 C Compiler User's Guide in the */
/* <XC16 compiler instal directory>/doc folder.                               */
/*                                                                            */
/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* TODO Add interrupt routine code here. */
static int ticd;
static int diffd;
static int old_ticd;
static int compteur_ticd;
static int ticg;
static int diffg;
static int old_ticg;
static int compteur_ticg;


void __attribute__((interrupt, auto_psv)) _T2Interrupt(void)
{
    _T2IF = 0; // On baisse le FLAG
	
    static int count = 0;
    count++;
    ticd = (int) POS1CNT;// ReadQEI2();
    diffd = ticd-old_ticd;
    old_ticd = ticd;
    compteur_ticd += diffd;
	  
    // On lit l'encodeur gauche (qui est en fait le droit)
    ticg = (int) POS2CNT; // ReadQEI1();
    diffg = ticg-old_ticg;
    old_ticg = ticg;
    compteur_ticg += diffg;
	
    int consigneG, consigneD;
	  
    motion_step(0.01, diffg, diffd, &consigneG, &consigneD);
	
    Set_Vitesse_MoteurD((float)consigneD);
    Set_Vitesse_MoteurG((float)consigneG);
	
    led = !led;    // On bascule l'état de la LED
}

/*************************************************
 *          RX Interrupt
 *
 *************************************************/


void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{
	_U2RXIF = 0;      // On baisse le FLAG
    InterruptAX();
}

/*************************************************
 *          TX Interrupt
 *
 *************************************************/


void __attribute__((__interrupt__, no_auto_psv)) _U2TXInterrupt(void)
{
   _U2TXIF = 0; // clear TX interrupt flag
}
