/*
 * Support and FAQ: visit Atmel Support
 */

#ifndef CONF_SSD1306_H_INCLUDED
#define CONF_SSD1306_H_INCLUDED

// Interface configuration for SAM4S Xplained Pro
#define SSD1306_SPI_INTERFACE
#define SSD1306_SPI SPI

#define SSD1306_DC_PIN       UG_2832HSWEG04_DATA_CMD_GPIO
#define SSD1306_RES_PIN      UG_2832HSWEG04_RESET_GPIO
#define SSD1306_CS_PIN       UG_2832HSWEG04_SS

/* Minimum clock period is 50ns@3.3V -> max frequency is 20MHz */
#define SSD1306_CLOCK_SPEED          UG_2832HSWEG04_BAUDRATE
#define SSD1306_DISPLAY_CONTRAST_MAX 40
#define SSD1306_DISPLAY_CONTRAST_MIN 30

#endif /* CONF_SSD1306_H_INCLUDED */