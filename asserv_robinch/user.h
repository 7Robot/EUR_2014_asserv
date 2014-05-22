/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        80000000UL
#define FCY             SYS_FREQ/2

#define BAUDRATEAX12 57600
#define BRGVALAX12 ((FCY / BAUDRATEAX12 / 16) - 1)

#define BRGVAL ((FCY / BAUDRATE / 16) - 1)

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */


/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

#define led _LATA2

extern int odoBroadcast;
extern unsigned long int odoBroadcastDelay;


void InitApp(void);         /* I/O and Peripheral Initialization */
void Init_PWM(void);
void Init_QEI(void);
int motor_corrector(int order);
void Set_Vitesse_MoteurD(int consigne, int inverse);
void Set_Vitesse_MoteurG(int consigne, int inverse);

extern void InterruptAX(void);
