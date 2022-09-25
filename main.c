#include "stm32f0xx.h"
#include "lcd.h"
#include "midi.h"
#include "midiplay.h"
#include <stdint.h>

void init_lcd_spi(void)
{
    //enable the RCC clock to GPIOB
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    //set PB8, PB11, PB14 to be outputs (01)
    GPIOB->MODER |= 0x10410000;
    GPIOB->MODER &= ~(0x20820000);

    //Set the ODR values for PB8, PB11, PB14 to be high
    GPIOB->ODR |= 0x4900;

    //Configure PB3 and PB5 to be alternate function 0 (10)
    GPIOB->MODER |= 0x00000880;
    GPIOB->MODER &= ~(0x00000440);

    //Set their ODR values low?
    GPIOB->ODR &= ~(0x0028);

    //Set up the SPI peripheral
    //enable the RCC clock to SPI1
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    //Turn off the SPI1 peripheral (clear the SPE bit)
    SPI1->CR1 &= ~(SPI_CR1_SPE);

    //Set the baud rate to be as high as possible
    SPI1->CR1 &= ~(0x38);

    //Configure the SPI1 peripheral for "master mode"
    SPI1->CR1 |= SPI_CR1_MSTR;

    //Set the word size to be 8-bit (0111)
    SPI1->CR2 = SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;

    //Set the SSM and SSI bits
    SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;

    //Enable the SPI1 peripheral (set the SPE bit)
    SPI1->CR1 |= (SPI_CR1_SPE);
}

void setup_buttons(void)
{
    // enable GPIOB and GPIOC
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    //configure PC4-PC7 to be outputs
    GPIOC->MODER &= ~(0x0000aa00);
    GPIOC->MODER |= 0x00005500;

    GPIOC->MODER &=~0xffff0000;
    GPIOC->MODER |= 0x55000000;
    GPIOC->OTYPER |=0xf000;
    GPIOC->PUPDR |=0x550000;
    //configure PC4-PC7 to have output type open-drain
    GPIOC->OTYPER |= 0x000000f0;

    //configure PC0-PC3 to be inputs
    GPIOC->MODER &= ~0x000000ff;

    //configure PC0-PC3 to be pulled high
    GPIOC->PUPDR &= ~0xaa;
    GPIOC->PUPDR |= 0x55;
}

void setup_buttons2(void)
{
    // enable and GPIOC
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    //configure PC12-PC15 to be outputs
    GPIOC->MODER &= ~(0x0000aa0000);
    GPIOC->MODER |= 0x0000550000;

    //configure PC12-PC15 to have output type open-drain
    GPIOC->OTYPER |= 0x00000f000;

    //configure PC8-PC11 to be inputs
    GPIOC->MODER &= ~0x000000ff00;

    //configure PC8-PC11 to be pulled high
    GPIOC->PUPDR &= ~0xaa00;
    GPIOC->PUPDR |= 0x5500;
}

void basic_drawing(void);
void move_ball(void);

int main(void)
{

    /*init_wavetable_hybrid2();
    init_dac();
    init_tim6();
    //init_dma();
    MIDI_Player *mp = midi_init(midifile);
    // The default rate for a MIDI file is 2 beats per second
    // with 48 ticks per beat.  That's 500000/48 microseconds.
    init_tim2(10417);
    for(;;) {
        //asm("wfi");
        // If we hit the end of the MIDI file, start over.
        if (mp->nexttick == MAXTICKS)
            mp = midi_init(midifile);
    }*/
    setup_buttons();
   // setup_buttons2();
    LCD_Setup(); // this will call init_lcd_spi()
    basic_drawing();
    move_ball();



}
