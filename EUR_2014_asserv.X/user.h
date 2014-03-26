/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        80000000UL
#define FCY             SYS_FREQ/2

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */


/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

#define led _LATA2

/* TODO User level functions prototypes (i.e. InitApp) go here */


void InitApp(void);         /* I/O and Peripheral Initialization */
long int limit_int(long int valeur, long int inf, long int sup);
float limit_float(float valeur, float inf, float sup);