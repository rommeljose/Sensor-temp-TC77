
#include <18F25k20.h>
#fuses HS,NOPROTECT,NOLVP,NOWDT
#use delay(clock=4000000)

#include <flex_lcd.c>
#include <sensor_TC77.h>

// Con estas directivas las funciones "input" y "output_bit" no reprograman
// el pin de la puerta cada vez que son utilizadas. Si no se indica el
// modo fast_io se asume por defecto standard_io el cual reprograma el pin
// siempre antes de ser utilizadas estas funciones.

#use fast_io (C)

//Habilita las funciones RS232, velocidad a 9600 baudios

#use rs232(baud=9600, parity=N, xmit=PIN_C6, rcv=PIN_C7, stream=out)

int ANO;

void main() {

    lcd_init();
    output_low(PIN_A0);
    output_high(PIN_A1);
    
    printf(lcd_putc, " Listo Okk ... ");
    delay_ms(500);

    while (1) {

        lcd_gotoxy(1, 1);
        printf(lcd_putc, "\fTemp2 = %2.2g\337C", Temperatura()); // Caracter octal
        fprintf(out, "PICDEM Temp2 = %3.2f oC\n", Temperatura()); // Caracter octal        

        lcd_gotoxy(1, 2);
        printf(lcd_putc, "   LABORATORIO"); // Caracter octal
        
        delay_ms(500);
        output_toggle(PIN_A0);
        delay_ms(500);
        output_toggle(PIN_A1);
    }
}