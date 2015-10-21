/*
 * gprs_transfer_packages.h
 *
 * Created: 2015-10-19 14:51:14
 *  Author: jiut0001
 */ 


#ifndef GPRS_TRANSFER_PACKAGES_H_
#define GPRS_TRANSFER_PACKAGES_H_

#define	HTTP_PACKAGE_STRING_LENGTH		3000 //Rymmer 40 paket
#define HTTP_PACKAGE_MAX_LOG_ENTRIES	40

#include "globals.h"
#include "sim808_uart.h"
#include "response_actions.h"

//Tempor�rt flyttat till globals.h d� kompilatorn j**las...
/*
typedef struct {
	uint32_t time;
	float lat;
	float lng;
	float speed;
	uint8_t inclination;
	float g_force;
} log_entry;

typedef struct {
	char date_time[12];		//Anv�nds ej
	uint32_t device;
	log_entry entries[255];
} data_log;
*/

typedef struct {
	data_log data;
	uint16_t len;
	uint16_t head;
	uint16_t tail;
} gprs_send_buffer;

volatile gprs_send_buffer gprs_log_buf;

void gprs_send_buf_init(gprs_send_buffer*);
void gprs_buf_push(log_entry, gprs_send_buffer*);
log_entry gprs_buf_pull(gprs_send_buffer*);
void gprs_send_data_log(void);

void json_add_variable(char[], uint16_t*, const char*, char*, uint8_t);



#endif /* GPRS_TRANSFER_PACKAGES_H_ */