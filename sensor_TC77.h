//////////////////////////////////////////////////////////////////////////////
//  Obtiene la temperatura a partir del sensor SPI Microchip TC77			//
//  modificada de http://www.todopic.com.ar/foros/index.php?topic=31591.0	//
//																			//
//  por Rommel Contreras:  rommeljose@gmail.com    Cumaná 23-01-2015		//
// 																			//
//  El sensor contiene un diodo interno que es monitoreado por un conversor	//
//  A/D de 13 bit's, tres registros digitales y una interfaz SPI.			//
//																			//
//  Tiene dos modos de operacion: Continuo y Shutdown.						//
//  El modo de operacion continua realiza una conversión de temperatura 	//
//  aproximadamente cada 300ms. 											//
//  El consumo de corriente del modo shutdown es menor a 1uA.				//
//																			//
//  Se debe modificar el Pin correspondiente a la señal CS  <---			//
//																			//
//  Esta librería no ha sido probada para valores de temperaturas negativa.	//
//  Los valores positivos fueron probados en la PICDEM™ Z Demonstration Kit	//
//  con el PIC 18F25k20														//
//																			//
//////////////////////////////////////////////////////////////////////////////

float Temperatura (){

	#define CS PIN_A2

	signed int16 Temp16Bits=0;
	int Templ=0;
	int Temph=0;
	float decimales=0;
	float enteros=0;
	float Temp;
        
		SETUP_SPI(SPI_MASTER|SPI_CLK_DIV_4|SPI_L_TO_H|SPI_XMIT_L_TO_H );
//		setup_spi(spi_master|spi_l_to_h| spi_ss_disabled);

		 
	/*	//configuracion del sensor en modo continuo
		output_low(CS);
		spi_read(0);				//leemos byte alto
		spi_read(0);				//leemos byte bajo
		spi_write(0x00);
		spi_write(0xFF);
		spi_read(0);				//leemos byte alto
		spi_read(0);				//leemos byte bajo
		spi_write(0x00);
		spi_write(0x00);
		output_high(CS);
	*/

			output_low(CS);
	
				Temph=spi_read(0);	// registro de temperatura alto del 
				Templ=spi_read(0);	// registro de temperatura bajo del 
	
			output_high(CS);
	
			Temp16Bits = make16(Temph,Templ);	// convertimos a un registro de 16Bits
	
			Temp16Bits = Temp16Bits >> 3;		// descartamos los 3 bits MSB
	
			decimales = (float)(Temp16Bits & 0x000F) * 0.0625; // formato a los decimales
	
			enteros = (float)(Temp16Bits >> 4); // descartando decimales para los enteros
	
			Temp= (enteros + decimales);

			return (Temp);
}

 